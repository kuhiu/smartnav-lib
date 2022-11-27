#include "DistanceSensors.hpp"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <numeric>
#include <sstream>
#include <stdexcept>

DistanceSensors::DistanceSensors() {

	if ( (__fd = open(__HC_SR04_DRIVER_DIR, O_RDONLY)) == -1){
		std::stringstream err;
		err << "Open fail: " << strerror(errno);
		throw std::runtime_error(err.str());
	}

	for(int i=0; i < __NRO_SENSORS; i++) {
		std::vector<float> __new_sensor;
		for(int j=0; j < __nro_samples_to_average; j++) {
			float __new_sample = {0.0};
			__new_sensor.push_back(__new_sample);
		}
		__distance_from_sensors.push_back(__new_sensor);
	}
	__is_running = true;
	__reading_thread = std::thread(&DistanceSensors::__reading_thread, this);
}

DistanceSensors::~DistanceSensors() {
	__is_running = false;
	__reading_thread.join();
	close(__fd);
}

std::vector<int> DistanceSensors::getDistances() { 
	// Thread safe
	std::lock_guard<std::mutex> lock(__measures_guard);
	return __averageOfDistances(); 
}

void DistanceSensors::__readDistance() {
	while(__is_running) {
		static int sample_index = 0;
		int samples_from_sensors[__NRO_SENSORS]; 

		if (sample_index == __nro_samples_to_average) 
			sample_index = 0;

		/** Read the distance sensors */
		if ( read(__fd, samples_from_sensors, __NRO_SENSORS*sizeof(int)) == -1) {
			throw std::runtime_error("Error reading distance sensors");
		}

		{	// Thread safe
			std::lock_guard<std::mutex> lock (__measures_guard);
			for(int sensor_index=0; sensor_index < __NRO_SENSORS; sensor_index++) 
				__distance_from_sensors[sensor_index][sample_index] = __timeToDistance((float)samples_from_sensors[sensor_index]);
		}
		sample_index++;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}

float DistanceSensors::__timeToDistance(float time) {
    float distance = time*(float)0.01715;

    if ( (distance > 500) || (distance < 0) )
        return 500;
    return distance;    
}

std::vector<int> DistanceSensors::__averageOfDistances(void) {
	std::vector<int> averages;

	for(int sensor_index=0; sensor_index < __NRO_SENSORS; sensor_index++) {
		 int average = std::accumulate(	__distance_from_sensors[sensor_index].begin(), 
																		__distance_from_sensors[sensor_index].end(), 
																		0.0);
		average /= __distance_from_sensors[sensor_index].size();
		averages.push_back(average);
	}
	return averages;
}

