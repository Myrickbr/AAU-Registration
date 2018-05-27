#ifndef _RegistrationList_h_
#define _RegistrationList_h_

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "RegistrationList.h"

const char clear_command[] = "cls"; // for Windows
//const char clear_command[] = "clear"; // for Linux and possibly Mac's

const char cs_file_name[] = "Registration.txt";

class Registration
{
public:
    void run();

private:
    void display_entry_and_browsing_view();
    void display_search_results_view();
    void execute(char command, bool & done);

    RegistrationList entry_list_;
};

#endif
