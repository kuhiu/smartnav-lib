#ifndef B0988BAA_981F_4A9D_834D_83E81B0A29A7
#define B0988BAA_981F_4A9D_834D_83E81B0A29A7

#include <math.h>

#include <string>
#include <vector>

#include "FuzzyCondition.hpp"
#include "FuzzyInput.hpp"
#include "FuzzyOutput.hpp"

class FuzzyComparation : public FuzzyCondition {
public:
  /** FuzzyComparation constructor */
  FuzzyComparation(std::shared_ptr<std::vector<FuzzyInput>> system_inputs, 
                   std::shared_ptr<std::vector<FuzzyOutput>> system_outputs) 
    : __system_inputs(system_inputs), __system_outputs(system_outputs) {};
  /** FuzzyComparation destructor */
  ~FuzzyComparation();
  /**
   * @brief Evaluate and condition
   * 
   * @return float 
   */
  virtual float evaluate() const override {
    for (auto &input : *__system_inputs) {
      if(input.getName() == __comparation.first) {
        for (auto &membership : input.getMemberships()) {
          if(membership->getName() == __comparation.second)
            return membership->getValue();
        }
      }
    }
  }
  /**
   * @brief Update system outputs with value
   * 
   * @param value 
   */
  virtual void update(float value) override {
    for (auto &output : *__system_outputs) {
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
  /** System inputs */
  std::shared_ptr<std::vector<FuzzyInput>> __system_inputs;
  /** System outputs */
  std::shared_ptr<std::vector<FuzzyOutput>> __system_outputs;

};

#endif /* B0988BAA_981F_4A9D_834D_83E81B0A29A7 */
