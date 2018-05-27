
#include "RegistrationList.h"

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <iostream>
using std::cout;
using std::endl;
#include <map>
using std::pair;
#include <string>
using std::string;

void RegistrationList::read_file(const std::string & file_name)
{
    ifstream inputHandler(file_name);
    if (!inputHandler) // no file -- one will be created when write_file is called
        return;
        string yearOfBirth;
    //Read file until no longer able to input
    while(inputHandler.good()) {
        RegistrationEntry new_entry;
        inputHandler >> new_entry.first_name >>
        new_entry.last_name >> yearOfBirth >>
        new_entry.registration_status;

        new_entry.year_of_birth = atoi(yearOfBirth.c_str());
        m_entries_.insert(m_entries_.end(),{new_entry.last_name, new_entry});
    }
    itr_current_entry_ = m_entries_.begin();
    inputHandler.close();
}

void RegistrationList::write_file(const std::string & file_name) const
{
   ofstream outputHandler;
   outputHandler.open(file_name, ofstream::app);

   outputHandler << '\n' << itr_current_entry_->second.first_name << " "
                 <<  itr_current_entry_->first << " " << itr_current_entry_->second.year_of_birth
                 << " " << itr_current_entry_->second.registration_status;
   outputHandler.close();
}

