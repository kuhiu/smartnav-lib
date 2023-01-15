#include "DistanceSensors.hpp"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <numeric>
#include <sstream>
#include <stdexcept>

#define HCSR04_IOC_NMAGICO 'c'
#define HCSR04_IOC_TRIGGER _IO(HCSR04_IOC_NMAGICO, 1)

//#define DEBUG_DISTANCE 1
#ifdef DEBUG_DISTANCE
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

DistanceSensors::DistanceSensors() {
	DEBUG_PRINT("Distance sensor constructor.\n");
	if ( (__fd = open(__HC_SR04_DRIVER_DIR, O_RDONLY)) == -1){
		std::stringstream err;
		err << "Open fail: " << strerror(errno);
		throw std::runtime_error(err.str());
	}

	for(int i=0; i < __NRO_SENSORS; i++) {
		sma_vec.push_back(SimpleMovingAverage(3));
	}

	DEBUG_PRINT("Run read distance thread.\n");	
	__is_running = true;
	__reading_thread = std::thread(&DistanceSensors::__readDistance, this);
}

DistanceSensors::~DistanceSensors() {
	__is_running = false;
	__reading_thread.join();
	close(__fd);
	DEBUG_PRINT("Read distance thread stopped.\n");
}

std::vector<int> DistanceSensors::getDistances() { 
	std::vector<int> ret;

	for (auto &sma : sma_vec)
		ret.push_back(sma.getMean());

	return ret; 
}

void DistanceSensors::__readDistance() {
	int samples_from_sensors[__NRO_SENSORS]; 
	
	while(__is_running) {

		for (int i=0; i < __NRO_SENSORS; i++) {
			// Read the distance of each sensor 
			samples_from_sensors[i] = ioctl(__fd, HCSR04_IOC_TRIGGER, (i+1));
			if ( samples_from_sensors[i] == -1) {
				throw std::runtime_error("Error reading distance sensors");
			}
			DEBUG_PRINT("Sensor %d. Time %d. Distance %f.\n", i, samples_from_sensors[i], __timeToDistance((float)samples_from_sensors[i]));
			sma_vec[i].addData(__timeToDistance((float)samples_from_sensors[i]));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}

float DistanceSensors::__timeToDistance(float time) {
    float distance = time*(float)0.01715;

    if ( (distance > 500) || (distance < 0) )
        return 500;
    return distance;    
}

