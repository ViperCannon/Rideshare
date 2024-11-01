
#ifndef HW4_DRIVER_H
#define HW4_DRIVER_H
#include <string>

class Driver {
public:
    //default constructor
    Driver();
    //parameterized constructor
    Driver(std::string aDriverFirstName, std::string aDriverLastName, std::string aGender, std::string aAge, std::string aPhoneNumber,
           std::string aRating, std::string aLatitude, std::string aLongitude, std::string aVehicleType,
           std::string aState, std::string aRiderFirstName, std::string aRiderLastName,std::string aRiderPhoneNumber);

    //Accessors
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    std::string getAge() const;
    std::string getPhoneNumber() const;
    std::string getRating() const;
    std::string getLatitude() const;
    std::string getLongitude() const;
    std::string getVehicleType() const;
    std::string getState() const;
    std::string getRiderFirstName() const;
    std::string getRiderLastName() const;
    std::string getRiderPhoneNumber() const;

    //Modifiers
    void setFirstName(std::string aFirstName);
    void setLastName(std::string aLastName);
    void setGender(std::string aGender);
    void setAge(std::string aAge);
    void setPhoneNumber(std::string aPhoneNumber);
    void setRating(std::string aRating);
    void setLatitude(std::string aLatitude);
    void setLongitude(std::string aLongitude);
    void setVehicleType(std::string aVehicleType);
    void setState(std::string aState);
    void setRiderFirstName(std::string aRiderFirstName);
    void setRiderLastName(std::string aRiderLastName);
    void setRiderPhoneNumber(std::string aRiderPhoneNumber);

private:
    //member variables
    std::string firstName;
    std::string lastName;
    std::string gender;
    std::string age;
    std::string phoneNumber;
    std::string rating;
    std::string latitude;
    std::string longitude;
    std::string vehicleType;
    std::string state;
    std::string riderFirstName;
    std::string riderLastName;
    std::string riderPhoneNumber;
};

//overloaded output stream operator for printing Driver objects
std::ostream& operator<< (std::ostream& out, const Driver& m);

#endif //HW4_DRIVER_H