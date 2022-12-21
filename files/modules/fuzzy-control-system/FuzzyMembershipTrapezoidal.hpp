#ifndef FEF550E2_5D36_4158_9C26_037747CBD30B
#define FEF550E2_5D36_4158_9C26_037747CBD30B

#include <math.h>

#include <string>

#include "FuzzyMembership.hpp"

class FuzzyMembershipTrapezoidal : public FuzzyMembership {
public:
	/*	
	TrapezoidalPoints
							-------------				
		slope1  /								\  slope2
					 -------------------
				 x1							     x2
	*/
	struct TrapezoidalPoints {
		/** Smallest x point */
		float x1;
		/** Higher x point */
		float x2;             
		/** Right slope */
		float right_slope;             
		/** Left slope */
		float left_slope; 
	};
	/** FuzzyMembershipTrapezoidal constructor */
	FuzzyMembershipTrapezoidal(const std::string &name, TrapezoidalPoints trapezoidal_points) 
		: __trapezoidal_points(trapezoidal_points), FuzzyMembership(name) {};
	/** FuzzyMembershipTrapezoidal destructor */
	virtual ~FuzzyMembershipTrapezoidal() = default;
	/**
	 * @brief Compute area of the trapezoid
	 * 
	 * @param value 
	 * @return float 
	 */
	virtual float compute_area_of_membership() {
		// area = height*(base+top)/2
		float base = __trapezoidal_points.x2 - __trapezoidal_points.x1; // a
		float dx1 = __fuzzy_value / __trapezoidal_points.right_slope;	// Ax = Ay * slope
		float dx2 = __fuzzy_value / __trapezoidal_points.left_slope;
		float top = base-dx1-dx2;	// b 
		return (__fuzzy_value*(base + top)/2);
	}
	/**
	 * @brief Compute centroid of membership
	 * 
	 * @return float 
	 */
	virtual float compute_centroid_of_membership() { return (__trapezoidal_points.x1 + ((__trapezoidal_points.x2 - __trapezoidal_points.x1)/2)); }
	/**
	 * @brief Evaluate membership function (membership degree)
	 * 
	 * @param value 
	 */
	virtual void compute_degree_of_membership(float input_value) override {
		float delta_1 = input_value - __trapezoidal_points.x1;
		float delta_2 = __trapezoidal_points.x2 - input_value;

		if ((delta_1 <= 0) || (delta_2 <= 0)) 
			// The input is out of the membership function
			__fuzzy_value = 0.0;                    
		else{
			__fuzzy_value = fmin(	(__trapezoidal_points.left_slope  * delta_1), 
									(__trapezoidal_points.right_slope * delta_2));
			__fuzzy_value = fmin( __fuzzy_value, __UPPER_LIMIT);       
		}
	}

private:
	/** Trapezoidal membership function */
	TrapezoidalPoints __trapezoidal_points;

};



#endif /* FEF550E2_5D36_4158_9C26_037747CBD30B */
