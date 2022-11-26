#ifndef __DISTANCESENSORS_H__
#define __DISTANCESENSORS_H__

#include <vector>

class distanceSensors {
public:
	/** DistanceSensor constructor */
	distanceSensors();
	/** DistanceSensor destructor */
	~distanceSensors();
	/**
	 * @brief Get the Distances to objects
	 * 
	 * @return std::vector<int> 
	 */
	std::vector<int> getDistances();
    
private:
	/** Driver directory */
	static constexpr auto __HC_SR04_DRIVER_DIR = "/dev/chardev_MIOgpio_PS";
	/** Number of sensors */
	const int __NRO_SENSORS = 3;
	/** Number of samples to average */
	int __nro_samples_to_average = 3;
	/** Driver file descriptor */
	int __fd;
	/** Distances from distance sensors */
	std::vector<std::vector<float>> __distance_from_sensors; 
	/**
	 * @brief Read distances
	 * 
	 */
	void __readDistance(void);
	
	float __timeToDistance(float time);
	void __meanOfDistances(void);

};


#endif // __DISTANCESENSORS_H__