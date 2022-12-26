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

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <FuzzyAnd.hpp>
#include <FuzzyComparation.hpp>
#include <FuzzyCondition.hpp>

class FuzzyRule {  
public:
  /** FuzzyRule constructor */
  FuzzyRule(std::string name, 
            FuzzyCondition::FuzzyConditionPtr fuzzy_input_condition, 
            FuzzyCondition::FuzzyConditionPtr fuzzy_output_condition)
    : __name(name), 
      __fuzzy_input_condition(fuzzy_input_condition),
      __fuzzy_output_condition(fuzzy_output_condition) {};
  /** FuzzyRule destructor*/
  ~FuzzyRule() = default;
  /**
   * @brief Evaluate the inputs and update the outputs 
   * 
   * @param system_input 
   * @param system_output 
   */
  void evaluate(std::vector<FuzzyInput> &system_input, std::vector<FuzzyOutput> &system_output) const { 
    float rule_strength = __fuzzy_input_condition->evaluate(system_input); 
    __fuzzy_output_condition->update(rule_strength, system_output);
  }
  /**
   * @brief Try to parse rule
   * 
   * @param rule_json Rule to parse
   * @return FuzzyRule 
   */
  static FuzzyRule parse(nlohmann::json rule_json) {
    std::ostringstream err;
    std::string name;
    FuzzyCondition::FuzzyConditionPtr fuzzy_input_condition;
    FuzzyCondition::FuzzyConditionPtr fuzzy_output_condition;

    if(!rule_json.contains(__NAME_KEY)) {
      err << "Rule not contain name object: " << rule_json.dump();
      throw std::runtime_error(err.str());
    }
    if(!rule_json.contains(__INPUT_COND_KEY)) {
      err << "Rule not contain input condition object: " << rule_json.dump();
      throw std::runtime_error(err.str());
    }
    if(!rule_json.contains(__OUTPUT_COND_KEY)) {
      err << "Rule not contain output condition object: " << rule_json.dump();
      throw std::runtime_error(err.str());
    }

    name = rule_json.at(__NAME_KEY);

    try {
      // Try to parse input condition as and
      fuzzy_input_condition = FuzzyAnd::parse(rule_json.at(__INPUT_COND_KEY));
    }
    catch(const std::exception& e) {
      // The input condition could not be parsed as and
    }

    try {
      // Try to parse input condition as comparation
      fuzzy_input_condition = FuzzyComparation::parse(rule_json.at(__INPUT_COND_KEY));
    }
    catch(const std::exception& e) {
      // The input condition could not be parsed as and
    }
  
    if (fuzzy_input_condition == nullptr) {
      err << "The input condition could not be parsed: " << rule_json.at(__INPUT_COND_KEY).dump();
      throw std::runtime_error(err.str());
    }

    try {
      // Try to parse output condition as and
      fuzzy_output_condition = FuzzyAnd::parse(rule_json.at(__OUTPUT_COND_KEY));
    }
    catch(const std::exception& e) {
      // The output condition could not be parsed as and
    }

    try {
      // Try to parse output condition as comparation
      fuzzy_output_condition = FuzzyComparation::parse(rule_json.at(__OUTPUT_COND_KEY));
    }
    catch(const std::exception& e) {
      // The input condition could not be parsed as and
    }
  
    if (fuzzy_output_condition == nullptr) {
      err << "The output condition could not be parsed: " << rule_json.at(__OUTPUT_COND_KEY).dump();
      throw std::runtime_error(err.str());
    }

    return (FuzzyRule(name, fuzzy_input_condition, fuzzy_output_condition));
  }

private:
  /** Name key */
  static constexpr auto __NAME_KEY{"name"};
  /** Input condition key */
  static constexpr auto __INPUT_COND_KEY{"input_conditions"};
  /** Output condition key */
  static constexpr auto __OUTPUT_COND_KEY{"output_conditions"};
  /** Rule name */
  std::string __name;
  /** Fuzzy input condition */
  FuzzyCondition::FuzzyConditionPtr __fuzzy_input_condition;
  /** Fuzzy output condition */
  FuzzyCondition::FuzzyConditionPtr __fuzzy_output_condition;

};

#endif /* F553A91F_E257_4635_80E9_4552D015C7A8 */
