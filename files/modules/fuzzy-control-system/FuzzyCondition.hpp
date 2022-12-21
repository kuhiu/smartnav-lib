#ifndef F29DD846_2172_450B_9CF1_993DDCF84C9F
#define F29DD846_2172_450B_9CF1_993DDCF84C9F

class FuzzyCondition {  
public:
  /** FuzzyCondition constructor */
  FuzzyCondition() = default;
  /** FuzzyCondition destructor */
  virtual ~FuzzyCondition() = default;
  /**
   * @brief Evaluate any condition
   * 
   * @return * float 
   */
  virtual float evaluate() const = 0;
  /**
   * @brief Update any condition
   * 
   * @param value 
   */
  virtual void update(float value) = 0;

};

#endif /* F29DD846_2172_450B_9CF1_993DDCF84C9F */
