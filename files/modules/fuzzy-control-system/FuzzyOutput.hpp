#ifndef AC7E2957_4A9D_46EE_A10F_D46F2E695892
#define AC7E2957_4A9D_46EE_A10F_D46F2E695892

#include <memory>
#include <string>
#include <vector>

#include <FuzzyMembership.hpp>

class FuzzyOutput : public FuzzyIO {
public:
	/** FuzzyOutput constructor */
	FuzzyOutput(const std::string &name, std::vector<std::shared_ptr<FuzzyMembership>> memberships) : 
		FuzzyIO(name, memberships) {};
	/** FuzzyOutput destructor */
	~FuzzyOutput() = default;
	/**
	 * @brief Membership defuzzification
	 * 
	 * @return float 
	 */
	float defuzzification() {
		float area;
		float centroid;
		float sum_of_areas = 0;     
		float sum_of_products = 0;   

		for( auto &membership : __memberships){
			area = membership->compute_area_of_membership();
			centroid = membership->compute_centroid_of_membership();
			sum_of_products += area * centroid;
			sum_of_areas += area;
		}
		return (sum_of_products/sum_of_areas);  
	}
  /**
   * @brief Try to parse output
   * 
   * @param io input to parse
   * @return FuzzyInput 
   */
  static FuzzyOutput parse(nlohmann::json output_json) {
    std::ostringstream err;
    std::string name;
    std::vector<std::shared_ptr<FuzzyMembership>> memberships;

    // Check if it contains the name of io
    if(!output_json.contains(__NAME_KEY)) {
      err << "Invalid output arguments: " << output_json.dump();
      throw std::runtime_error(err.str());
    }
    // Check if it contains the membership functions
    if(!output_json.contains(__MEMBERSHIPS_FUNCTIONS_KEY)) {
      err << "Invalid output arguments: " << output_json.dump();
      throw std::runtime_error(err.str());
    }
    // Check if name is a string
    if(!output_json.at(__NAME_KEY).is_string()) {
      err << "Invalid type of output name: " << output_json.at(__NAME_KEY).dump();
      throw std::runtime_error(err.str());
    }
    // Check if membership vector 
    if(!output_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).is_array()) {
      err << "Invalid type of output membership function: " << output_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).dump();
      throw std::runtime_error(err.str());
    }
    name = output_json.at(__NAME_KEY);
    // Parse inputs
    for (const auto &membership : output_json.at(__MEMBERSHIPS_FUNCTIONS_KEY)) {
      try {
        // Membership type 
        if(membership.contains(FuzzyMembershipTrapezoidal::__MB_TRAPEZOIDAL_KEY)  ) {
          auto fuzzy_membership_trapezoidal = FuzzyMembershipTrapezoidal::parse(membership);
          memberships.push_back(fuzzy_membership_trapezoidal);
        }
      }
      catch(const std::exception& e) {
        err << "Error parsing as FuzzyInput: " << output_json.dump();
        std::runtime_error(err.str());
      }
    }
    return (FuzzyOutput(name, memberships));
  };

};

#endif /* AC7E2957_4A9D_46EE_A10F_D46F2E695892 */
