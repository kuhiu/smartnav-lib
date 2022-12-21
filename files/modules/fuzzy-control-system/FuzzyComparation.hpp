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
  FuzzyComparation(std::pair<std::string, std::string> comparation, 
                   std::shared_ptr<std::vector<FuzzyIO>> system_io) 
    : __comparation(comparation), __system_io(system_io) {};
  /** FuzzyComparation destructor */
  ~FuzzyComparation();
  /**
   * @brief Evaluate and condition
   * 
   * @return float 
   */
  virtual float evaluate() const override {
    bool input_found = false;
    for (auto &input : *__system_io) {
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
  virtual void update(float value) override {
    for (auto &output : *__system_io) {
      if(output.getName() == __comparation.first) {
        for (auto &membership : output.getMemberships()) {
          if(membership->getName() == __comparation.second) 
            membership->setValue(fmax(value, membership->getValue()));
        }
      }
    }
  } 

private:
  /** Comparation */
  std::pair<std::string, std::string> __comparation;
  /** System input/output */
  std::shared_ptr<std::vector<FuzzyIO>> __system_io;

};

#endif /* B0988BAA_981F_4A9D_834D_83E81B0A29A7 */
