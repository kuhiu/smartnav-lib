#ifndef AAF78FC2_7624_47D0_9F79_E2435CD45FBD
#define AAF78FC2_7624_47D0_9F79_E2435CD45FBD

#include <math.h>

#include <stdexcept>
#include <vector>

#include <nlohmann/json.hpp>

#include <FuzzyCondition.hpp>
#include <FuzzyComparation.hpp>

class FuzzyAnd : public FuzzyCondition {
public:
  /** FuzzyAnd constructor */
  FuzzyAnd(std::vector<FuzzyConditionPtr> condition) : __conditions(condition) {};
  /** FuzzyAnd destructor */
  ~FuzzyAnd() = default;
  /**
   * @brief Evaluate and condition
   * 
   * @param system_io 
   * @return float 
   */
  virtual float evaluate(std::shared_ptr<std::vector<FuzzyIO>> system_io) const override {
    float strength = __UPPER_LIMIT;
    if(__conditions.empty())
      throw std::runtime_error("And condition is empty.");
    else if(__conditions.size() == 1)
      throw std::runtime_error("And condition has only one input.");
    for(auto &condition : __conditions)
      strength = fmin(strength, condition->evaluate(system_io));
    return strength;
  };
  /**
   * @brief Update and with a new value
   * 
   * @param value 
   * @param system_io 
   */
  virtual void update(float value, std::shared_ptr<std::vector<FuzzyIO>> system_io) override {
    if(__conditions.empty())
      throw std::runtime_error("And condition is empty.");
    else if(__conditions.size() == 1)
      throw std::runtime_error("And condition has only one input.");
    for(auto &condition : __conditions)
      condition->update(value, system_io);
  };

  /**
   * @brief Try to parse and condition
   * 
   * @param and_json 
   * @return FuzzyConditionPtr 
   */
  static FuzzyConditionPtr parse(nlohmann::json and_json) {
    std::ostringstream err;
    FuzzyConditionPtr comparation;
    std::vector<FuzzyConditionPtr> comparations;

    if(!and_json.contains(__AND_KEY)) {
      err << "And condition not contain and object: " << and_json.dump();
      throw std::runtime_error(err.str());
    }
    if(!and_json.at(__AND_KEY).is_array()) {
      err << "And condition is not an array: " << and_json.dump();
      throw std::runtime_error(err.str());
    }

    for (auto &comparation_json : and_json.at(__AND_KEY)) {
      try {
        comparation = FuzzyAnd::parse(comparation_json);
      }
      catch(const std::exception& e) {
        // And comparation could not be parsed as and
      }
      try {
        comparation = FuzzyComparation::parse(comparation_json);
      }
      catch(const std::exception& e) {
        // And comparation could not be parsed as comparation
      }

      if(comparation == nullptr) {
        err << "And condition is not an array: " << and_json.dump();
        throw std::runtime_error(err.str());
      }
      else 
        comparations.push_back(comparation);
    }
    return (FuzzyConditionPtr(std::make_shared<FuzzyAnd>(comparations)));
  };

private:
  /** And key */
  static constexpr auto __AND_KEY{"and"};
  /** Max evaluate result */
  const float __UPPER_LIMIT = 1.0;
  /** Fuzzy conditions */
  std::vector<FuzzyConditionPtr> __conditions;
  
};


#endif /* AAF78FC2_7624_47D0_9F79_E2435CD45FBD */
