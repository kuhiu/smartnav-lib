#ifndef F29DD846_2172_450B_9CF1_993DDCF84C9F
#define F29DD846_2172_450B_9CF1_993DDCF84C9F

#include <memory>
class FuzzyCondition {  
public:
  /** FuzzyCondition smart pointer */
  using FuzzyConditionPtr = std::shared_ptr<FuzzyCondition>;
  /** FuzzyCondition constructor */
  FuzzyCondition() = default;
  /** FuzzyCondition destructor */
  virtual ~FuzzyCondition() = default;
  /**
   * @brief Evaluate any condition
   * 
   * @param system_io 
   * @return float 
   */
  virtual float evaluate(std::shared_ptr<std::vector<FuzzyIO>> system_io) const = 0;
  /**
   * @brief Update any condition
   * 
   * @param value 
   * @param system_io 
   */
  virtual void update(float value, std::shared_ptr<std::vector<FuzzyIO>> system_io) = 0;

};

#endif /* F29DD846_2172_450B_9CF1_993DDCF84C9F */
