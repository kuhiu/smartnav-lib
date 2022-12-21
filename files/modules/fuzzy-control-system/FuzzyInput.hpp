#ifndef A1CF177A_D590_4AAB_8FFF_1D4A89E5B341
#define A1CF177A_D590_4AAB_8FFF_1D4A89E5B341

#include <memory>
#include <string>
#include <vector>

#include <FuzzyIO.hpp>
#include <FuzzyMembership.hpp>

class FuzzyInput : public FuzzyIO {
public:
  /** FuzzyInput constructor */
  FuzzyInput(const std::string &name, std::vector<std::shared_ptr<FuzzyMembership>> memberships) : 
    FuzzyIO(name, memberships) {};
  /** FuzzyInput destructor */
  ~FuzzyInput() = default;
  /**
   * @brief Input fuzzification
   * 
   */
	void fuzzyfication(float input_value) {
    for ( auto &membership : __memberships )
      membership->compute_degree_of_membership(input_value);
	};

};



#endif /* A1CF177A_D590_4AAB_8FFF_1D4A89E5B341 */
