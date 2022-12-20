#ifndef AC7E2957_4A9D_46EE_A10F_D46F2E695892
#define AC7E2957_4A9D_46EE_A10F_D46F2E695892

#include <memory>
#include <string>
#include <vector>

#include <FuzzyMembership.hpp>

class FuzzyOutput {
public:
	/** FuzzyOutput constructor */
	FuzzyOutput(const std::string &name, std::vector<std::shared_ptr<FuzzyMembership>> memberships) : 
		__name(name), __memberships(memberships) {};
	/** FuzzyOutput destructor */
	~FuzzyOutput() = default;
	/**
	 * @brief Name getter 
	 * 
	 * @return std::string 
	 */
	std::string getName() const { return __name; }
	/**
	 * @brief Membership defuzzification
	 * 
	 * @return float 
	 */
	float __defuzzification() {
		float sum_of_products = 0;   
		float sum_of_areas = 0;     
		float area;
		float centroid;

		for( auto &membership : __memberships){
			area = __compute_area_of_trapezoid(mf);
			centroid = mf.getPoint1() + (mf.getPoint2() - mf.getPoint1())/2;
			sum_of_products += area * centroid;
			sum_of_areas += area;
		}
		return (sum_of_products/sum_of_areas);  
	}
  /**
   * @brief Get the memberships object
   * 
   * @return std::vector<std::shared_ptr<FuzzyMembership>> 
   */
  std::vector<std::shared_ptr<FuzzyMembership>> getMemberships() const { return __memberships; }; 
	
private:
	/** Output name */
	std::string __name;
	/** Memberships function */
	std::vector<std::shared_ptr<FuzzyMembership>> __memberships;

};

#endif /* AC7E2957_4A9D_46EE_A10F_D46F2E695892 */
