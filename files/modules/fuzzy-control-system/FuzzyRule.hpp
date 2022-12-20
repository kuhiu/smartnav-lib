/* 
  Rule type:

  IF INPUT1=HIGH AND/OR INPUT2=LOW THEN OUT1=LOW

  Where: 
  * "INPUT1=HIGH" is a condition of this rule.
  * "INPUT1=HIGH AND/OR INPUT2=LOW" is a condition of this rule, too.
  * "OUT1=LOW" is a condition of this rule, too.
  * "INPUTx" = Is one input.
  * "HIGH" = Is a fuzzy value of the this input.
*/

#ifndef F553A91F_E257_4635_80E9_4552D015C7A8
#define F553A91F_E257_4635_80E9_4552D015C7A8

#include <string>
#include <utility>
#include <vector>

#include <FuzzyCondition.hpp>


class FuzzyRule {  
public:
  /** FuzzyRule constructor */
  FuzzyRule(std::string name, 
            std::shared_ptr<FuzzyCondition> fuzzy_input_condition, 
            std::shared_ptr<FuzzyCondition> fuzzy_output_condition)
    : __name(name), 
      __fuzzy_input_condition(fuzzy_input_condition),
      __fuzzy_output_condition(fuzzy_output_condition) {};
  /** FuzzyRule destructor*/
  ~FuzzyRule() = default;
  /**
   * @brief Evalueate FuzzyRule 
   * 
   * @return float 
   */
  void evaluate() const { 
    float rule_strength = __fuzzy_input_condition->evaluate(); 
    __fuzzy_output_condition->update(rule_strength);
  }

private:
  /** Rule name */
  std::string __name;
  /** Fuzzy input condition */
  std::shared_ptr<FuzzyCondition> __fuzzy_input_condition;
  /** Fuzzy output condition */
  std::shared_ptr<FuzzyCondition> __fuzzy_output_condition;

};

#endif /* F553A91F_E257_4635_80E9_4552D015C7A8 */
