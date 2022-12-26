#ifndef B0988BAA_981F_4A9D_834D_83E81B0A29A7
#define B0988BAA_981F_4A9D_834D_83E81B0A29A7

#include <math.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "FuzzyCondition.hpp"
#include "FuzzyIO.hpp"

class FuzzyComparation : public FuzzyCondition {
public:
  /** FuzzyComparation constructor */
  FuzzyComparation(std::pair<std::string, std::string> comparation) 
    : __comparation(comparation) {};
  /** FuzzyComparation destructor */
  ~FuzzyComparation();
  /**
   * @brief Evaluate and condition
   * 
   * @param system_io 
   * @return float 
   */
  virtual float evaluate(std::vector<FuzzyInput> &system_input) const override {
    bool input_found = false;
    for (auto &input : system_input) {
      if(input.getName() == __comparation.first) {
        input_found = true;
        for (auto &membership : input.getMemberships()) {
          if(membership->getName() == __comparation.second)
            return membership->getValue();
        }
      }
    }
    if(input_found == false) {
      throw std::runtime_error("Input not found in fuzzy system.");
    }
  }
  /**
   * @brief Update system outputs with value
   * 
   * @param value 
   */
  virtual void update(float value, std::vector<FuzzyOutput> &system_output) override {
    for (auto &output : system_output) {
      if(output.getName() == __comparation.first) {
        for (auto &membership : output.getMemberships()) {
          if(membership->getName() == __comparation.second) 
            membership->setValue(fmax(value, membership->getValue()));
        }
      }
    }
  } 
  /**
   * @brief Try to parse comparation
   * 
   * @param comparation_json 
   * @return FuzzyConditionPtr 
   */
  static FuzzyConditionPtr parse(nlohmann::json comparation_json) {
    std::ostringstream err;
    std::pair<std::string, std::string> comparation;

    if(!comparation_json.contains(__IO_KEY)) {
      err << "Comparation condition not contain io object: " << comparation_json.dump();
      throw std::runtime_error(err.str());
    }
    if(!comparation_json.contains(__FUZZY_VALUE_KEY)) {
      err << "Comparation condition not contain fuzzy value object: " << comparation_json.dump();
      throw std::runtime_error(err.str());
    }
    if(!comparation_json.at(__IO_KEY).is_string()) {
      err << "Comparation: " << __IO_KEY << " not contain an string object: " << comparation_json.dump();
      throw std::runtime_error(err.str());
    }
    if(!comparation_json.at(__FUZZY_VALUE_KEY).is_string()) {
      err << "Comparation: " << __FUZZY_VALUE_KEY << " not contain an string object: " << comparation_json.dump();
      throw std::runtime_error(err.str());
    }
    comparation.first = comparation_json.at(__IO_KEY);
    comparation.second = comparation_json.at(__FUZZY_VALUE_KEY);
    return (FuzzyConditionPtr(std::make_shared<FuzzyComparation>(comparation)));
  }

private:
  /** IO key */
  static constexpr auto __IO_KEY{"io"};
  /** Fuzzy value key */
  static constexpr auto __FUZZY_VALUE_KEY{"fuzzy_value"};
  /** Comparation */
  std::pair<std::string, std::string> __comparation;

};

#endif /* B0988BAA_981F_4A9D_834D_83E81B0A29A7 */
