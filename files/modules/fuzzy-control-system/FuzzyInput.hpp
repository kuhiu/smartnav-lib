#ifndef A1CF177A_D590_4AAB_8FFF_1D4A89E5B341
#define A1CF177A_D590_4AAB_8FFF_1D4A89E5B341

#include <memory>
#include <string>
#include <vector>

#include <FuzzyIO.hpp>
#include <FuzzyMembershipTrapezoidal.hpp>

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
  /**
   * @brief Try to parse input
   * 
   * @param io input to parse
   * @return FuzzyInput 
   */
  static FuzzyInput parse(nlohmann::json input_json) {
    std::ostringstream err;
    std::string name;
    std::vector<std::shared_ptr<FuzzyMembership>> memberships;

    // Check if it contains the name of io
    if(!input_json.contains(__NAME_KEY)) {
      err << "Invalid input arguments: " << input_json.dump();
      throw std::runtime_error(err.str());
    }
    // Check if it contains the membership functions
    if(!input_json.contains(__MEMBERSHIPS_FUNCTIONS_KEY)) {
      err << "Invalid input arguments: " << input_json.dump();
      throw std::runtime_error(err.str());
    }
    // Check if name is a string
    if(!input_json.at(__NAME_KEY).is_string()) {
      err << "Invalid type of input name: " << input_json.at(__NAME_KEY).dump();
      throw std::runtime_error(err.str());
    }
    // Check if membership vector 
    if(!input_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).is_array()) {
      err << "Invalid type of input membership function: " << input_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).dump();
      throw std::runtime_error(err.str());
    }
    name = input_json.at(__NAME_KEY);
    // Parse inputs
    for (const auto &membership : input_json.at(__MEMBERSHIPS_FUNCTIONS_KEY)) {
      try {
        // Membership type 
        if(membership.contains(FuzzyMembershipTrapezoidal::__MB_TRAPEZOIDAL_KEY)  ) {
          auto fuzzy_membership_trapezoidal = FuzzyMembershipTrapezoidal::parse(membership);
          memberships.push_back(fuzzy_membership_trapezoidal);
        }
      }
      catch(const std::exception& e) {
        err << "Error parsing as FuzzyInput: " << input_json.dump();
        std::runtime_error(err.str());
      }
    }
    return (FuzzyInput(name, memberships));
  };

};



#endif /* A1CF177A_D590_4AAB_8FFF_1D4A89E5B341 */
