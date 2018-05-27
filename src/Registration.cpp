#include "Registration.h"

using namespace std;

void Registration::run()
{
    entry_list_.read_file(cs_file_name);
    bool done = false;
    while (!done) {
        display_entry_and_browsing_view();
        cout << "choice: ";
        char command;
        cin >> command;
        cin.get(); // new line char
        execute(command, done);
        cout << endl;
    }
}

void Registration::display_entry_and_browsing_view()  {
    string long_separator(60, '~');
    string short_separator(60, '~');

    system(clear_command);

    entry_list_.display_current_entry();

    cout << long_separator << endl
         << "  next  edit  display_stats  search_for_players  quit\n"
         << "  previous  add_player    delete\n"
         << short_separator << endl;
}
void Registration::display_search_results_view(){
    string long_separator(60, '~');
    string short_separator(60, '~');

    //entry_list_.display_search_entry();
    system(clear_command);
     cout << long_separator << endl
         << "  next  search  edit   exit_search_view  quit\n"
         << "  previous  add_player  print_list  delete(x)\n"
         << short_separator << endl;
}

void Registration::execute(char command, bool & done)
{
    switch (command) {
        case 'n': {
            entry_list_.move_to_next();
            break;
         }
        case 'p': {
            entry_list_.move_to_previous();
            break;
         }
        case 'e': {
            if (entry_list_.empty())
                return;
            bool running = true;
            while(running)
            {
                cout << "A.) Change Name " << endl;
                cout << "B.) Change Year of Birth " << endl;
                cout << "C.) Change registration status " << endl;
                cout << "Choose option you would like to edit: ";
                string response;
                getline(cin, response);
                if(response == "a" || response == "A")
                {
                    string answer;
                    cout << "Edit first(f) or last(l) name?: ";
                    getline(cin, answer);
                    if(answer == "f" || answer == "F")
                    {
                        cout << "Type new first name: ";
                        string newFirstName;
                        getline(cin, newFirstName);
                        entry_list_.edit_current(newFirstName, 'f');
                        running = false;
                    }
                    else if(answer == "l" || answer == "L")
                    {
                        cout << "Type new last name: ";
                        string newName;
                        getline(cin, newName);
                        entry_list_.edit_current(newName, 'a');
                        running = false;
                    }
                }
                else if(response == "b" || response == "B")
                {
                    cout << "Type new year of birth: ";
                    string newDob;
                    getline(cin, newDob);
                    entry_list_.edit_current(newDob, 'b');
                    running = false;
                }
                else if(response == "c" || response == "C")
                {
                    cout << "Type new register status: ";
                    string newReg;
                    getline(cin, newReg);
                    entry_list_.edit_current(newReg, 'c');
                    running = false;
                }
                else
                {
                    cout << "Not a valid command!!" << endl;
                }
            }
            break;
        }
        case 's': {
            bool running = true;
            string command;
            while(running)
            {
                 cout << "Would you like to search for a last name(L) or other(O)?: ";
                 getline(cin,command);
                 if(command == "l" || command == "L")
                 {
                    cout << "Enter what you would like to search: ";
                    string search_term;
                    getline(cin, search_term);
                    entry_list_.find(search_term, "L");
                    running = false;
                 }
                 else if(command == "o" || command == "O")
                 {
                    cout << "Enter what you would like to search: ";
                    string search_term;
                    getline(cin, search_term);
                    entry_list_.find(search_term, "O");
                    running = false;
                 }
                 else
                 {
                     cout << "NOT A VALID COMMAND" << endl;
                 }
            }
            break;
        }
        case 'a': {
            cout << "Enter player first name: ";
            string first_name;
            getline(cin, first_name);
            cout << "Enter last name: ";
            string last_name;
            getline(cin, last_name);
            cout << "Enter Registration Status(Paid/Unpaid): ";
            string regStatus;
            getline(cin, regStatus);
            cout << "Enter year of birth: ";
            int yearOfBirth;
            cin >> yearOfBirth;
            entry_list_.add(first_name, last_name, yearOfBirth, regStatus);
            break;
        }
        case 'd': {
            entry_list_.display_statistics();
            break;
        }
        case 'q': {
            entry_list_.write_file(cs_file_name);
            done = true;
            break;
        }
        case 'x': {
            entry_list_.delete_();
            break;
        }
        default :{
           cout << "Not a valid command!";
           string letter;
           cout << "Press any key and enter to continue: ";
           cin >> letter;
            break;

        }
    }
}

