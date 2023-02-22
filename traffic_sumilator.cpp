#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

enum class VehicleType { Car, Bus, Truck };

struct Vehicle {
    VehicleType type;
    int speed; // in meters per second
    int distanceTraveled; // in meters
    bool isStopped;
    int stopTime; // in seconds
};

struct TrafficLight {
    int greenTime; // in seconds
    int redTime; // in seconds
    int timeRemaining; // in seconds
};

class Road {
private:
    int length; // in meters
    int numLanes;
    vector<Vehicle> vehicles;
    TrafficLight trafficLight;
public:
    Road(int length, int numLanes) : length(length), numLanes(numLanes), trafficLight({30, 10, 30}) {}

    void addVehicle(Vehicle vehicle) {
        vehicles.push_back(vehicle);
    }

    void updateVehicles() {
        // Update the position of each vehicle
        for (auto& vehicle : vehicles) {
            if (vehicle.isStopped) {
                if (vehicle.stopTime > 0) {
                    vehicle.stopTime--;
                } else {
                    vehicle.isStopped = false;
                    vehicle.speed = rand() % 20 + 10; // Random speed between 10 and 30 meters per second
                }
            } else {
                vehicle.distanceTraveled += vehicle.speed;
            }
        }

        // Check if any vehicles have reached the end of the road
        for (auto it = vehicles.begin(); it != vehicles.end(); ) {
            if (it->distanceTraveled >= length) {
                it = vehicles.erase(it);
            } else {
                ++it;
            }
        }

        // Check if the traffic light needs to change
        trafficLight.timeRemaining--;
        if (trafficLight.timeRemaining == 0) {
            trafficLight.timeRemaining = (trafficLight.greenTime + trafficLight.redTime);
        }
    }

    void simulate() {
        while (true) {
            // Add new vehicles to the road
            if (rand() % 10 == 0) {
                Vehicle vehicle;
                vehicle.type = static_cast<VehicleType>(rand() % 3);
                vehicle.speed = rand() % 20 + 10;
                vehicle.distanceTraveled = 0;
                vehicle.isStopped = false;
                vehicle.stopTime = 0;
                addVehicle(vehicle);
            }

            // Update the state of each vehicle
            updateVehicles();

            // Print the current state of the road
            printState();

            // Wait for a short amount of time
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void printState() {
        system("cls"); // Clear the console

        // Print the traffic light state
        cout << "Traffic Light: ";
        if (trafficLight.timeRemaining < trafficLight.greenTime) {
            cout << "Green" << endl;
        } else {
            cout << "Red" << endl;
        }

        // Print the state of each lane
        for (int i = 0; i < numLanes; i++) {
            cout << "Lane " << i+1 << ": ";
            for (auto& vehicle : vehicles) {
                if (vehicle.distanceTraveled <= i*length/numLanes && (vehicle.distanceTraveled+5) >= i*length/numLanes) {
                    if (vehicle.isStopped || (trafficLight.timeRemaining > trafficLight.greenTime && (vehicle.distanceTraveled+10) >= i*length/numLanes)) {
cout << "X";
} else {
switch (vehicle.type) {
case VehicleType::Car:
cout << "C";
break;
case VehicleType::Bus:
cout << "B";
break;
case VehicleType::Truck:
cout << "T";
break;
}
}
} else {
cout << "-";
}
}
cout << endl;
}
}
};

int main() {
srand(time(nullptr)); // Seed the random number generator
Road road(500, 2); // Create a road with a length of 500 meters and 2 lanes

road.simulate();

return 0;}