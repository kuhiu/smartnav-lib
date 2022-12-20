#ifndef __FUZZYCONTROLSYSTEM_H__
#define __FUZZYCONTROLSYSTEM_H__

#include <exception>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "FuzzyRule.hpp"
#include "FuzzyInput.hpp"
#include "FuzzyOutput.hpp"

class FuzzyControlSystem {
public:
	/** FuzzyControlSystem constructor */
	FuzzyControlSystem(	std::vector<FuzzyInput> system_inputs,
											std::vector<FuzzyOutput> system_outputs,
											std::vector<FuzzyRule> system_rules ) : 
											__system_inputs(system_inputs),
											__system_outputs(system_outputs),
											__system_rules(system_rules) {};
	/** FuzzyControlSystem destructor */
	~FuzzyControlSystem() = default;
	/**
	 * @brief Update system input
	 * 
	 * @param inputs_to_update 
	 * @return std::vector<fuzzyOutput> Return fuzzy_outputs
	 */
	std::vector<FuzzyOutput> evaluate(std::vector<std::string> inputs_name, std::vector<float> values) {
		bool found = false;
		int input_index = 0;
		// Check input name 
		for (auto &system_input : __system_inputs) {
			for (auto &input_name : inputs_name) {
				if (system_input.getName() == input_name) {
					// Input fuzzification
					system_input.fuzzyfication(values[input_index]);	
					found = true;
				}
				input_index++;
			}
			if (found == false) {
				std::stringstream err;
				err << "This input: " << inputs_name[input_index] << " is not defined in the fuzzy system.";
				throw std::runtime_error(err.str().c_str());
			}
		}
		// Rules evaluation
		for (auto &rule : __system_rules) {
			rule.evaluate();
		}



		return __system_outputs;
	}

private:
	/** System inputs */
	std::vector<FuzzyInput> __system_inputs;
	/** System outputs */
	std::vector<FuzzyOutput> __system_outputs;
	/** System rules */
	std::vector<FuzzyRule> __system_rules; 

};

#endif // __FUZZYCONTROLSYSTEM_H__