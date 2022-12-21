#ifndef AC7E2957_4A9D_46EE_A10F_D46F2E695892
#define AC7E2957_4A9D_46EE_A10F_D46F2E695892

#include <memory>
#include <string>
#include <vector>

#include <FuzzyMembership.hpp>

class FuzzyOutput : FuzzyIO {
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
	
};

#endif /* AC7E2957_4A9D_46EE_A10F_D46F2E695892 */
