#include "distanceSensors.hpp"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sstream>
#include <stdexcept>

distanceSensors::distanceSensors() {

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
}

distanceSensors::~distanceSensors() {
	close(__fd);
}

std::vector<int> distanceSensors::getDistances() {
  __readDistance();
  __meanOfDistances();
	return __samples;
}

void distanceSensors::__readDistance(void) {
	int samples_from_sensors[__NRO_SENSORS]; 

	for( int i=0; i < __nro_samples_to_average; i++ ){
		if ( read(__fd, samples_from_sensors, __NRO_SENSORS*sizeof(int)) == -1){
			throw std::runtime_error("Error reading distance sensors");
		}
		for(int j=0; j < __NRO_SENSORS; j++) 
			__distance_from_sensors[j][i] = __timeToDistance((float)samples_from_sensors[i]);
	}
}

float distanceSensors::__timeToDistance(float time) {
    float distance = time*(float)0.01715;

    if ( (distance > 500) || (distance < 0) )
        return 500;
    return distance;    
}

void distanceSensor::__meanOfDistances(void) {
    std::ostringstream err;
    if (__sampleMean_s1.empty() ) {
        err << "__sampleMean_s1 empty ";
        throw std::runtime_error(err.str());
    }
    if (__sampleMean_s2.empty() ) {
        err << "__sampleMean_s2 empty ";
        throw std::runtime_error(err.str());
    }
    if (__sampleMean_s3.empty() ) {
        err << "__sampleMean_s3 empty ";
        throw std::runtime_error(err.str());
    }
    __samples[0] = std::accumulate(__sampleMean_s1.begin(), __sampleMean_s1.end(), 0.0) / __sampleMean_s1.size();
    __samples[1] = std::accumulate(__sampleMean_s2.begin(), __sampleMean_s2.end(), 0.0) / __sampleMean_s2.size();
    __samples[2] = std::accumulate(__sampleMean_s3.begin(), __sampleMean_s3.end(), 0.0) / __sampleMean_s3.size();

    __sampleMean_s1.clear();
    __sampleMean_s1.shrink_to_fit();
    __sampleMean_s2.clear();
    __sampleMean_s2.shrink_to_fit();
    __sampleMean_s3.clear();
    __sampleMean_s3.shrink_to_fit();
}

