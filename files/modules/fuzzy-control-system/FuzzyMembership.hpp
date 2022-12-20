#ifndef E2FEBB06_2742_47AF_A486_87D711A3E209
#define E2FEBB06_2742_47AF_A486_87D711A3E209

#include <string>

class FuzzyMembership {
public:
	/** FuzzyMembership constructor */
	FuzzyMembership(const std::string &name) : __name(name) {};
	/** FuzzyMembership destructor */
	virtual ~FuzzyMembership() = default;
	/**
	 * @brief Compute degree of membership
	 * 
	 * @param value 
	 */
	virtual void compute_degree_of_membership(float value) = 0;
	/**
	 * @brief Get the Name object
	 * 
	 * @return std::string 
	 */
	std::string getName() const;
	/**
	 * @brief Get the Value object
	 * 
	 * @return float 
	 */
	float getValue() const { return __fuzzy_value; };
	/**
	 * @brief Set the Value object
	 * 
	 * @param value 
	 */
	void setValue(float value) { __fuzzy_value = value; }

protected:
  /** Max membership value */
  const float __UPPER_LIMIT = 1.0;
	/** Fuzzy value */
	float __fuzzy_value;                 
	/** FuzzyMembership name */
  std::string __name;   
	
};



#endif /* E2FEBB06_2742_47AF_A486_87D711A3E209 */
