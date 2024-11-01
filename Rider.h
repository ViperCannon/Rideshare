
#ifndef HW4_RIDER_H
#define HW4_RIDER_H
#include <string>

class Rider {
public:
    //default constructor
    Rider();
    //parameterized constructor
    Rider(std::string aRiderFirstName, std::string aRiderLastName, std::string aGender, std::string aAge, std::string aPhoneNumber,
          std::string aRating, std::string aPickUpLocation, std::string aPickupLatitude, std::string aPickupLongitude,
          std::string aDropoffLocation, std::string aDropoffLatitude, std::string aDropoffLongitude, std::string aVehiclePreference,
          std::string aState, std::string aDriverFirstName, std::string aDriverLastName, std::string aDriverPhoneNumber);
    //Accessors
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    std::string getAge() const;
    std::string getPhoneNumber() const;
    std::string getRating() const;
    std::string getPickUpLocation() const;
    std::string getPickupLatitude() const;
    std::string getPickupLongitude() const;
    std::string getDropoffLocation() const;
    std::string getDropoffLatitude() const;
    std::string getDropoffLongitude() const;
    std::string getVehiclePreference() const;
    std::string getState() const;
    std::string getDriverFirstName() const;
    std::string getDriverLastName() const;
    std::string getDriverPhoneNumber() const;

    //Modifiers
    void setFirstName(std::string aFirstName);
    void setLastName(std::string aLastName);
    void setGender(std::string aGender);
    void setAge(std::string aAge);
    void setPhoneNumber(std::string aPhoneNumber);
    void setRating(std::string aRating);
    void setPickUpLocation(std::string aPickUpLocation);
    void setPickupLatitude(std::string aPickupLatitude);
    void setPickupLongitude(std::string aPickupLongitude);
    void setDropoffLocation(std::string aDropoffLocation);
    void setDropoffLatitude(std::string aDropoffLatitude);
    void setDropoffLongitude(std::string aDropoffLongitude);
    void setVehiclePreference(std::string aVehiclePreference);
    void setState(std::string aState);
    void setDriverFirstName(std::string aDriverFirstName);
    void setDriverLastName(std::string aDriverLastName);
    void setDriverPhoneNumber(std::string aDriverPhoneNumber);

private:
    //member variables
    std::string firstName;
    std::string lastName;
    std::string gender;
    std::string age;
    std::string phoneNumber;
    std::string rating;
    std::string pickUpLocation;
    std::string pickupLatitude;
    std::string pickupLongitude;
    std::string dropoffLocation;
    std::string dropoffLatitude;
    std::string dropoffLongitude;
    std::string vehiclePreference;
    std::string state;
    std::string driverFirstName;
    std::string driverLastName;
    std::string driverPhoneNumber;
};
//overloaded output stream operator for printing Driver objects
std::ostream& operator<< (std::ostream& out, const Rider& m);


#endif //HW4_RIDER_H