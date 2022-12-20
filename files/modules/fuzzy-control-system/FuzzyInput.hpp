#ifndef A1CF177A_D590_4AAB_8FFF_1D4A89E5B341
#define A1CF177A_D590_4AAB_8FFF_1D4A89E5B341

#include <memory>
#include <string>
#include <vector>

#include <FuzzyMembership.hpp>

class FuzzyInput {
public:
  /** FuzzyInput constructor */
  FuzzyInput(const std::string &name, std::vector<std::shared_ptr<FuzzyMembership>> memberships) : 
    __name(name), __memberships(memberships) {};
  /** FuzzyInput destructor */
  ~FuzzyInput() = default;
  /**
   * @brief Input fuzzification
   * 
   */
	void fuzzyfication(float input) {
    for ( auto &membership : __memberships )
      membership->compute_degree_of_membership(input);
	};
  /**
   * @brief Get the Name object
   * 
   * @return std::string 
   */
  std::string getName() const { return __name; };
  /**
   * @brief Get the memberships object
   * 
   * @return std::vector<std::shared_ptr<FuzzyMembership>> 
   */
  std::vector<std::shared_ptr<FuzzyMembership>> getMemberships() const { return __memberships; }; 

private:
	/** Input name */
	std::string __name;
	/** Memberships function */
	std::vector<std::shared_ptr<FuzzyMembership>> __memberships;

};



#endif /* A1CF177A_D590_4AAB_8FFF_1D4A89E5B341 */
