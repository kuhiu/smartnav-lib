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
	/**
	 * @brief Try to parse membership function
	 * 
	 * @param input_json 
	 * @return FuzzyMembershipTrapezoidal 
	 */
	static std::shared_ptr<FuzzyMembershipTrapezoidal> parse(nlohmann::json memb_function) {
		std::ostringstream err;
		std::string name;
		TrapezoidalPoints trapezoidal_points;

		// Check if it contains the name of membership
    if(!memb_function.contains(__NAME_KEY)) {
      err << "Membership function not contains name: " << memb_function.dump();
      throw std::runtime_error(err.str());
    }
		// Check if it contains the trapezoidal object
    if(!memb_function.contains(__MB_TRAPEZOIDAL_KEY)) {
      err << "Membership function not contains trapezoidal object: " << memb_function.dump();
      throw std::runtime_error(err.str());
    }
		// Check if trapezoidal object type
    if(!memb_function.at(__MB_TRAPEZOIDAL_KEY).is_array()) {
      err << "Trapezoidal object not contains an array: " << memb_function.dump();
      throw std::runtime_error(err.str());
    }
		// Check if trapezoidal object contains all points
    if(!memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_X1_KEY) || 
			 !memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_X2_KEY) ||
			 !memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_RIGHT_SLOPE_KEY) ||
			 !memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_LEFT_SLOPE_KEY)) {
      err << "Trapezoidal object not contains points: " << memb_function.dump();
      throw std::runtime_error(err.str());
    }
		name = memb_function.at(__NAME_KEY);
		trapezoidal_points.x1 = memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_X1_KEY);
		trapezoidal_points.x2 = memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_X2_KEY);
		trapezoidal_points.right_slope = memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_RIGHT_SLOPE_KEY);
		trapezoidal_points.left_slope = memb_function.at(__MB_TRAPEZOIDAL_KEY).contains(__MB_LEFT_SLOPE_KEY);
		return (std::make_shared<FuzzyMembershipTrapezoidal>(name, trapezoidal_points));
	}

  /** Trapezoidal memebership function key */
  static constexpr auto __MB_TRAPEZOIDAL_KEY{"trapezoidal"};
	
private:
  /** Trapezoidal Points keys */
  static constexpr auto __MB_X1_KEY{"x1"};
	static constexpr auto __MB_X2_KEY{"x2"};
	static constexpr auto __MB_RIGHT_SLOPE_KEY{"right_slope"};
	static constexpr auto __MB_LEFT_SLOPE_KEY{"left_slope"};
	/** Trapezoidal membership function */
	TrapezoidalPoints __trapezoidal_points;

};



#endif /* FEF550E2_5D36_4158_9C26_037747CBD30B */
