#include <iostream>
#include "Rider.h"
#include "Driver.h"
#include <fstream>
#include <cmath>
#include <list>

//function for parsing the driver file
std::list<Driver> readFromDriverFile(const std::string& driversFile) {
    //empty list to store Driver objects
    std::list<Driver> drivers;
    std::ifstream inputFile(driversFile);

    //check if the file was successfully opened.
    if (!inputFile.is_open()) {
        std::cerr << "Can't open" << std::endl;
        exit(1);
    }

    while (true) {
        //define variables to store driver attributes
        std::string firstName, lastName, gender, age, phoneNumber, rating, latitude, longitude, vehicleType, state, riderFirstName, riderLastName, riderPhoneNumber;
        if (!(inputFile >> firstName >> lastName >> gender >> age >> phoneNumber >> rating >> latitude >> longitude >> vehicleType >> state >> riderFirstName >> riderLastName >> riderPhoneNumber)) {
            break;
        }
        //create driver object with the parsed attributes and add it to the list
        Driver group = Driver(firstName, lastName, gender, age, phoneNumber, rating, latitude, longitude, vehicleType, state, riderFirstName, riderLastName, riderPhoneNumber);
        drivers.push_back(group);
    }

    inputFile.close();
    return drivers;
}

//function for parsing the rider file
std::list<Rider> readFromRiderFile(const std::string& ridersFile) {
    std::list<Rider> riders;
    std::ifstream inputFile(ridersFile);

    //check if the file was successfully opened.
    if (!inputFile.is_open()) {
        std::cerr << "Can't open" << std::endl;
        exit(1);
    }

    while (true) {
        //define variables to store rider attributes
        std::string firstName, lastName, gender, age, phoneNumber, rating, pickUpLocation, pickUpLatitude, pickUpLongitude,dropOffLocation, dropOffLatitude, dropOffLongitude, vehiclePreference, state, driverFirstName, driverLastName, driverPhoneNumber;

        if (!(inputFile >> firstName >> lastName >> gender >> age >> phoneNumber >> rating >> pickUpLocation >> pickUpLatitude >> pickUpLongitude >> dropOffLocation >> dropOffLatitude >> dropOffLongitude >> vehiclePreference >> state >> driverFirstName >> driverLastName >> driverPhoneNumber)) {
            break;
        }

        //create rider object with the parsed attributes and add it to the list
        Rider group = Rider(firstName, lastName, gender, age, phoneNumber, rating, pickUpLocation, pickUpLatitude, pickUpLongitude,dropOffLocation, dropOffLatitude, dropOffLongitude, vehiclePreference, state, driverFirstName, driverLastName, driverPhoneNumber);
        riders.push_back(group);
    }
    inputFile.close();
    return riders;
}

// calculate the distance between two coordinates using Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}

//function to update rider information
void updateRiders(const std::list<Rider>& riders, const std::string& outputFile) {
    std::list<Rider> riderCopy = riders;
    std::ofstream output2(outputFile);
    std::list<Rider>::iterator rider;
    for (rider = riderCopy.begin(); rider != riderCopy.end(); ++rider) {
        output2 << *rider << std::endl;
    }

    output2.close();
}

//function to update driver information
void updateDrivers(const std::list<Driver>& drivers, const std::string& outputFile) {
    std::list<Driver> driverCopy = drivers;
    std::ofstream output1(outputFile);
    std::list<Driver>::iterator driver;
    for (driver = driverCopy.begin(); driver != driverCopy.end(); ++driver) {
        output1 << *driver << std::endl;
    }

    output1.close();
}

//function for handling ride requests and returns new driver for cancel request made by a driver
Driver request(std::list<Driver> aDrivers, std::list<Rider> aRiders, const std::string& ridersPhoneNumber, const std::string& outputFile0, const std::string& outputFile1, const std::string& outputFile2, bool append) {
    double distTemp = -1;
    Driver* driver1 = nullptr;
    Rider* rider1;
    std::ofstream output0;
    bool foundDriver = false;
    bool foundRider = false;

    //appending the output file
    if (append) {
        output0.open(outputFile0, std::ios_base::app);
    }
    //overwriting the output file
    else {
        output0.open(outputFile0);
    }

    //iterating through rider list to find rider with the matching phone number
    std::list<Rider>::iterator rider;
    for (rider = aRiders.begin(); rider != aRiders.end(); ++rider) {
        if (rider->getPhoneNumber() == ridersPhoneNumber) {
            rider1 = &*rider;
            foundRider = true;

            break;
        }
    }

    if (foundRider) {
        //rider already requested a driver
        if (rider1->getState() == "Driver_on_the_way") {
            output0 << "You have already requested a ride and your driver is on the way to the pickup location." << std::endl;
        }
        //rider already in the car
        else if (rider1->getState() == "During_the_trip") {
            output0 << "You can not request a ride at this moment as you are already on a trip." << std::endl;
        }
        //searching for driver for rider
        else {
            std::list<Driver>::iterator driver;
            for (driver = aDrivers.begin(); driver != aDrivers.end(); ++driver) {
                if (driver->getState() == "Available" && driver->getVehicleType() == rider1->getVehiclePreference()) {
                    if (distTemp == -1) {
                        foundDriver = true;
                        driver1 = &*driver;
                        distTemp = calculateDistance(std::stod(rider1->getPickupLatitude()), std::stod(rider1->getPickupLongitude()), std::stod(driver1->getLatitude()), std::stod(driver1->getLongitude()));
                    } else if (distTemp > calculateDistance(std::stod(rider1->getPickupLatitude()), std::stod(rider1->getPickupLongitude()), std::stod(driver->getLatitude()), std::stod(driver->getLongitude()))) {
                        driver1 = &*driver;
                        distTemp = calculateDistance(std::stod(rider1->getPickupLatitude()), std::stod(rider1->getPickupLongitude()), std::stod(driver1->getLatitude()), std::stod(driver1->getLongitude()));
                    }
                }
            }

            distTemp = trunc(distTemp*10) / 10;

            //outputting for the rider
            output0 << "Ride requested for user " << rider1->getFirstName() << ", looking for ";
            if (rider1->getVehiclePreference() == "Economy") {
                output0 << "an ";
            }
            else {
                output0 << "a ";
            }

            output0 << rider1->getVehiclePreference() << " vehicle." << std::endl
                    << "Pick Up Location: " << rider1->getPickUpLocation() << ", Drop Off Location: " << rider1->getDropoffLocation() << "." << std::endl;

            //outputting driver details for the rider
            if (foundDriver) {
                output0 << "We have found the closest driver " << driver1->getFirstName() << "(" << driver1->getRating() << ") " << "for you." << std::endl
                        << driver1->getFirstName() << " is now " << distTemp << " miles away from you." << std::endl;

                //updating rider
                rider1->setDriverFirstName(driver1->getFirstName());
                rider1->setDriverLastName(driver1->getLastName());
                rider1->setDriverPhoneNumber(driver1->getPhoneNumber());
                rider1->setState("Driver_on_the_way");

                //updating driver
                driver1->setRiderFirstName(rider1->getFirstName());
                driver1->setRiderLastName(rider1->getLastName());
                driver1->setRiderPhoneNumber(rider1->getPhoneNumber());
                driver1->setState("On_the_way_to_pickup");
            }
            //outputting no driver found
            else {
                output0 << "Sorry we can not find a driver for you at this moment." << std::endl;
            }

        }

    }
    else {
        output0 << "Account does not exist." << std::endl;
    }

    output0.close();
    updateRiders(aRiders, outputFile2);
    updateDrivers(aDrivers, outputFile1);
    return *driver1;
}

//function for handling ride cancellations
void cancel(std::list<Driver> aDrivers, std::list<Rider> aRiders, const std::string& phoneNumber, const std::string& outputFile0, const std::string& outputFile1, const std::string& outputFile2) {
    Driver *driver1;
    Driver newDriver;
    Rider *rider1;
    bool isRider = false;
    std::ofstream output0(outputFile0);
    bool foundAccount = false;
    std::list<Rider>::iterator del;

    //iterating through driver list to see if phone number matches
    std::list<Driver>::iterator driver;
    for (driver = aDrivers.begin(); driver != aDrivers.end(); ++driver) {
        if (driver->getPhoneNumber() == phoneNumber) {
            driver1 = &*driver;
            foundAccount = true;
            break;
        }

    }

    //driver made request to cancel and assigning the rider
    if (foundAccount) {
        std::list<Rider>::iterator rider;
        for (rider = aRiders.begin(); rider != aRiders.end(); ++rider) {
            if (rider->getPhoneNumber() == driver1->getRiderPhoneNumber()) {
                rider1 = &*rider;
                break;
            }

        }

    }
    //checking if rider requested the cancellation since a driver did not
    else {
        std::list<Rider>::iterator rider;
        for (rider = aRiders.begin(); rider != aRiders.end(); ++rider) {
            if (rider->getPhoneNumber() == phoneNumber) {
                rider1 = &*rider;
                del = rider;
                isRider = true;
                foundAccount = true;
                break;
            }

        }
        //checking if rider's phone number is same as driver's phone number
        for (driver = aDrivers.begin(); driver != aDrivers.end(); ++driver) {
            if (driver->getPhoneNumber() == rider1->getDriverPhoneNumber()) {
                driver1 = &*driver;
                break;
            }

        }

    }

    if (foundAccount) {
        //outputting and updating for successful rider cancel
        if (isRider && rider1->getState() == "Driver_on_the_way") {
            output0 << "Ride request for user " << rider1->getFirstName() << " is now canceled by the user."
                    << std::endl;

            driver1->setRiderFirstName("null");
            driver1->setRiderLastName("null");
            driver1->setRiderPhoneNumber("null");
            driver1->setState("Available");

            //deleting rider after rider cancelled
            aRiders.erase(del);
        }
        //outputting and updating for driver successfully canceling
        //also attempts to find another driver for rider
        else if (!isRider && driver1->getState() == "On_the_way_to_pickup") {
            output0 << "Your driver " << driver1->getFirstName()
                    << " has cancelled the ride request. We will now find a new driver for you." << std::endl;

            rider1->setDriverFirstName("null");
            rider1->setDriverLastName("null");
            rider1->setDriverPhoneNumber("null");
            rider1->setState("Ready_to_request");

            newDriver = request(aDrivers, aRiders, rider1->getPhoneNumber(), outputFile0, outputFile1, outputFile2, true);

            driver1->setRiderFirstName("null");
            driver1->setRiderLastName("null");
            driver1->setRiderPhoneNumber("null");
            driver1->setState("Available");

            rider1->setDriverFirstName(newDriver.getFirstName());
            rider1->setDriverLastName(newDriver.getLastName());
            rider1->setDriverPhoneNumber(newDriver.getPhoneNumber());
            rider1->setState("Driver_on_the_way");

            std::list<Driver>::iterator request;
            for (request = aDrivers.begin(); request != aDrivers.end(); ++request) {
                if (request->getPhoneNumber() == newDriver.getPhoneNumber()) {
                    driver1 = &*request;
                    break;
                }

            }

            driver1->setRiderFirstName(rider1->getFirstName());
            driver1->setRiderLastName(rider1->getLastName());
            driver1->setRiderPhoneNumber(rider1->getPhoneNumber());
            driver1->setState("On_the_way_to_pickup");
        }
        //rider unsuccessfully tries to cancel
        else if (isRider) {
            output0 << "You can only cancel a ride request if your driver is currently on the way to the pickup location." << std::endl;
        }
        //driver unsuccessfully tries to cancel
        else {
            output0 << "You can only cancel a ride request if you are currently on the way to the pickup location." << std::endl;
        }

    }
    else {
        output0 << "Account does not exist." << std::endl;
    }

    output0.close();
    updateRiders(aRiders, outputFile2);
    updateDrivers(aDrivers, outputFile1);
}

//main code
int main(int argc, char* argv[]) {
    if (argc != 8) {
        std::cerr << "Usage: " << argv[0] << " drivers.txt riders.txt output0.txt output1.txt output2.txt phoneNumber command" << std::endl;
        std::cerr << R"(Where command is either "request" or "cancel")" << std::endl;
        return 1;
    }

    const std::string driversFile = argv[1];
    const std::string ridersFile = argv[2];
    const std::string output0File = argv[3];
    const std::string output1File = argv[4];
    const std::string output2File = argv[5];
    const std::string phoneNumber = argv[6];
    const std::string command = argv[7];

    //checking valid phone number
    if (phoneNumber.length() != 12 || phoneNumber[3] != '-' || phoneNumber[7] != '-') {
        std::ofstream output0(output0File);
        output0 << "Phone number is invalid." << std::endl;
        return 1;
    }

    std::list<Driver> drivers = readFromDriverFile(driversFile);
    std::list<Rider> riders = readFromRiderFile(ridersFile);

    if (command == "request") {
        request(drivers, riders, phoneNumber, output0File, output1File, output2File, false);

    }
    else  if (command == "cancel"){
        cancel(drivers, riders, phoneNumber, output0File, output1File, output2File);
    }
    //error checking
    else {
        std::cerr << "Usage: " << argv[0] << " drivers.txt riders.txt output0.txt output1.txt output2.txt phoneNumber command" << std::endl;
        std::cerr << R"(Where command is either "request" or "cancel")" << std::endl;
        return 1;
    }

    return 0;
}