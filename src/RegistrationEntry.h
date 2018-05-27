#ifndef _RegistrationEntry_h_
#define _RegistrationEntry_h_

#include <fstream>
#include <string>

class RegistrationEntry
{
public:
    RegistrationEntry() : first_name("no name"), last_name("no name"),
     number("no number"), year_of_birth(0), category("NA"), registration_status("NA") {}
     //Constructor for when adding users
     RegistrationEntry(std::string & name0,
                       std::string & name1,
                       int & year_of_birth0,
                       std::string & reg_status0,
                       std::string & category0) :
        first_name(name0), last_name(name1), year_of_birth(year_of_birth0),
        registration_status(reg_status0), category(category0) {}

    //Data stored in each player object
    std::string first_name;
    std::string last_name;
    std::string number;
    int year_of_birth;
    std::string category;
    std::string registration_status;
};

inline std::istream & operator>>(std::istream & in,
                                 RegistrationEntry & e)
{
    getline(in, e.first_name);
    getline(in, e.last_name);
    getline(in, e.number);
    return in;
}

//We want this operator to be able to print
//player objects properly, position first then
//the first name and last name
inline std::ostream & operator<<(std::ostream & out,
                                  RegistrationEntry & e)
{
    out << e.number << ". " << e.first_name
        << e.last_name <<  std::endl;
    /*out << e.name << std::endl
        << e.number << std::endl; */
    return out;
}


#endif
