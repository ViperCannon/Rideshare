#include "Driver.h"
#include <iostream>

//default constructor
Driver::Driver() {
    //initialize member variables with "null" values
    age = "null";
    rating = "null";
    latitude = "null";
    longitude = "null";
    firstName = "null";
    lastName = "null";
    gender = "null";
    phoneNumber = "null";
    vehicleType = "null";
    state = "null";
    riderFirstName = "null";
    riderLastName = "null";
    riderPhoneNumber = "null";

}

//parameterized constructor
Driver::Driver(std::string aDriverFirstName, std::string aDriverLastName, std::string aGender, std::string aAge, std::string aPhoneNumber,
               std::string aRating, std::string aLatitude, std::string aLongitude, std::string aVehicleType,
               std::string aState, std::string aRiderFirstName, std::string aRiderLastName,std::string aRiderPhoneNumber) {
    //initialize member variables with provided values
    firstName = aDriverFirstName;
    lastName = aDriverLastName;
    gender = aGender;
    age = aAge;
    phoneNumber = aPhoneNumber;
    rating = aRating;
    latitude = aLatitude;
    longitude = aLongitude;
    vehicleType = aVehicleType;
    state = aState;
    //set rider information if provided
    if (aRiderFirstName != "null") {
        riderFirstName = aRiderFirstName;
        riderLastName = aRiderLastName;
        riderPhoneNumber = aRiderPhoneNumber;
    }
}
//getter functions
std::string Driver::getFirstName() const {
    return firstName;
}

std::string Driver::getLastName() const {
    return lastName;
}

std::string Driver::getGender() const {
    return gender;
}

std::string Driver::getAge() const {
    return age;
}

std::string Driver::getPhoneNumber() const {
    return phoneNumber;
}

std::string Driver::getRating() const {
    return rating;
}

std::string Driver::getLatitude() const {
    return latitude;
}

std::string Driver::getLongitude() const {
    return longitude;
}

std::string Driver::getVehicleType() const {
    return vehicleType;
}

std::string Driver::getState() const {
    return state;
}

std::string Driver::getRiderFirstName() const {
    return riderFirstName;
}

std::string Driver::getRiderLastName() const {
    return riderLastName;
}

std::string Driver::getRiderPhoneNumber() const {
    return riderPhoneNumber;
}

//setter functions
void Driver::setFirstName(std::string aFirstName) {
    firstName = aFirstName;
}

void Driver::setLastName(std::string aLastName) {
    lastName = aLastName;
}

void Driver::setGender(std::string aGender) {
    gender = aGender;
}

void Driver::setAge(std::string aAge) {
    age = aAge;
}
void Driver::setPhoneNumber(std::string aPhoneNumber) {
    phoneNumber = aPhoneNumber;
}
void Driver::setRating(std::string aRating) {
    rating = aRating;
}
void Driver::setLatitude(std::string aLatitude) {
    latitude = aLatitude;
}
void Driver::setLongitude(std::string aLongitude) {
    longitude = aLongitude;
}
void Driver::setVehicleType(std::string aVehicleType) {
    vehicleType = aVehicleType;
}
void Driver::setState(std::string aState) {
    state = aState;
}
void Driver::setRiderFirstName(std::string aRiderFirstName) {
    riderFirstName = aRiderFirstName;
}
void Driver::setRiderLastName(std::string aRiderLastName) {
    riderLastName = aRiderLastName;
}
void Driver::setRiderPhoneNumber(std::string aRiderPhoneNumber) {
    riderPhoneNumber = aRiderPhoneNumber;
}

//output stream operator to print Driver object
std::ostream& operator<< (std::ostream& out, const Driver& m) {
    out << m.getFirstName() << " " << m.getLastName() << " " << m.getGender() << " " << m.getAge() << " " << m.getPhoneNumber() << " " << m.getRating() << " "
        << m.getLatitude() << " " << m.getLongitude() << " " << m.getVehicleType() << " " << m.getState();
    //if the state is "Available," print driver information as "null"
    if (m.getState() == "Available") {
        out << " " << "null null null";
    }
    else {
        out << " " << m.getRiderFirstName() << " " << m.getRiderLastName() << " " << m.getRiderPhoneNumber();
    }

    return out;
}