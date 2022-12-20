#ifndef AAF78FC2_7624_47D0_9F79_E2435CD45FBD
#define AAF78FC2_7624_47D0_9F79_E2435CD45FBD

#include <math.h>

#include <stdexcept>
#include <vector>

#include <FuzzyCondition.hpp>

class FuzzyAnd : public FuzzyCondition {
public:
  /** FuzzyAnd constructor */
  FuzzyAnd(std::vector<FuzzyCondition> conditions) : __conditions(conditions) {};
  /** FuzzyAnd destructor */
  ~FuzzyAnd() = default;
  /**
   * @brief Evaluate and condition
   * 
   * @return float 
   */
  virtual float evaluate() const override {
    float strength = __UPPER_LIMIT;
    if(__conditions.empty())
      throw std::runtime_error("And condition is empty.");
    else if(__conditions.size() == 1)
      throw std::runtime_error("And condition has only one input.");
    for(auto &condition : __conditions)
      strength = fmin(strength, condition.evaluate());
    return strength;
  };

  virtual void update(float value) override {
    if(__conditions.empty())
      throw std::runtime_error("And condition is empty.");
    else if(__conditions.size() == 1)
      throw std::runtime_error("And condition has only one input.");
    for(auto &condition : __conditions)
      condition.update(value);
  };

private:
  /** Max evaluate result */
  const float __UPPER_LIMIT = 1.0;
  /** Fuzzy conditions */
  std::vector<FuzzyCondition> __conditions;
  
};


#endif /* AAF78FC2_7624_47D0_9F79_E2435CD45FBD */
