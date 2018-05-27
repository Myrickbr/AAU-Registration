#include <iostream>
#include <map>
#include <string>
#include<vector>
#include "RegistrationEntry.h"
using std::cout;
using std::endl;
class RegistrationList
{
public:
    RegistrationList() : itr_current_entry_(m_entries_.end()) {}

    void add(std::string & first_name,
             std::string & last_name,
             int & yearOfBirth,
             std::string & regStatus);
    void display_current_entry();
    void display_search_view();
    void move_to_next();
    void move_to_previous();
    void search_move_to_next();
    void search_move_to_previous();
    void display_statistics();
    void edit_current(std::string & edit_string, const char & letter);
    void delete_();
    void find(std::string & search_term, const std::string & c);
    bool empty() const { return m_entries_.empty(); }
    bool search_empty()const {return search_results.empty();}
    void read_file(const std::string & file_name);
    void write_file(const std::string & file_name) const;

private:
    void run_search_view();
    void execute_search_command(char command, bool & done);
    std::map<std::string, RegistrationEntry> m_entries_;
    std::map<std::string, RegistrationEntry>::iterator
        itr_current_entry_;
    std::map<std::string, RegistrationEntry> search_results;
};

inline std::string set_player_rank(int & year_of_birth)
{
    if(year_of_birth > 2012)
        return "U6";
    else if(year_of_birth > 2010)
        return "U8";
    else if(year_of_birth > 2008)
        return "U10";
    else if(year_of_birth > 2006)
        return "U12";
    else if(year_of_birth > 2004)
        return"U14";
    else if(year_of_birth > 2001)
        return "U17";
    else
        return "NA";
}
inline void RegistrationList::add( std::string & first_name,
                                   std::string & last_name,
                                   int & yearOfBirth,
                                   std::string & regStatus)
{
    std::string category = set_player_rank(yearOfBirth);
    auto result =
      //  m_entries_.insert({name, PhoneBookEntry(name, number)});
        m_entries_.insert({last_name, {first_name, last_name, yearOfBirth,regStatus, category}});
    itr_current_entry_ = result.first;
    write_file("Registration.txt");
}
inline void RegistrationList::edit_current(
         std::string & edit_string, const char & letter)
{
    if(letter == 'a')
    {
        //First create a copy of new object
        RegistrationEntry newEntry;
        newEntry = itr_current_entry_->second;
        //Then erase element
        m_entries_.erase(itr_current_entry_);
        //Then insert into map
        auto result = m_entries_.insert({edit_string,{newEntry}});
        itr_current_entry_ = result.first;
        write_file("Registration.txt");
    }
    else if(letter =='b')
    {
        int number = stoi(edit_string);
        itr_current_entry_->second.year_of_birth = number;
        std::string category = set_player_rank(number);
        itr_current_entry_->second.category = category;
        write_file("Registration.txt");
    }
    else if(letter =='c')
    {
        itr_current_entry_->second.registration_status = edit_string;
        write_file("Registration.txt");
    }
    else if(letter == 'f')
    {
        itr_current_entry_->second.first_name = edit_string;
        write_file("Registration.txt");
    }
    else
    {
        std::cout << "WARNING: NOT VALID EDIT COMMAND" << std::endl;
    }

}
inline void RegistrationList::display_current_entry()
{
    if (m_entries_.empty())
        return;
    int counter = 1;
    int pos;
    //We need to display number, name, and rank
    for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr)
    {
        itr->second.category = set_player_rank(itr->second.year_of_birth);
        std::cout << counter << ". " << itr->second.first_name << " "
        << itr->first << "  " << itr->second.category << "  " <<
        itr->second.registration_status;
        if(itr_current_entry_ == itr)
        {
            pos = counter;
            std::cout << "  (*)";
        }
        std::cout << std::endl;
        ++counter;
    }

    std::cout << std::endl;
    std::cout << "(* Entry " << pos << "/" << counter-1 << " *)" << std::endl;

}
inline void RegistrationList::run_search_view()
{
    bool done = false;
    while(!done)
    {
        display_search_view();
        std::cout << "choice: ";
        char command;
        std::cin >> command;
        std::cin.get(); // new line char
        execute_search_command(command, done);
        std::cout << std::endl;
    }
}
inline void RegistrationList::execute_search_command(char command, bool & done)
{
    switch (command) {
        case 'n': {
            RegistrationList searchList;
            searchList.search_move_to_next();
            break;
         }
        case 'p': {
            RegistrationList searchList;
            searchList.search_move_to_previous();
            break;
         }
        case 'e': {
            search_results.clear();
            done = true;
            break;
        }
    }
}
inline void RegistrationList::display_search_view()
{
    std::system("cls");
    std::string long_separator(60, '~');
    std::string short_separator(60, '~');
    if (m_entries_.empty())
        return;
    int counter = 1;
    int pos;
    //We need to display number, name, rank, and status
    for(auto itr = search_results.begin(); itr != search_results.end(); ++itr)
    {
        itr->second.category = set_player_rank(itr->second.year_of_birth);
        std::cout << counter << ". " << itr->second.first_name << " "
        << itr->first << "  " << itr->second.category << "  " <<
        itr->second.registration_status;
        if(itr_current_entry_ == itr)
        {
            pos = counter;
            std::cout << "  (*)";
        }
        std::cout << std::endl;
        ++counter;
    }

    std::cout << std::endl;
    std::cout << "(* Entry " << pos << "/" << counter-1 << " *)" << std::endl;

    std::cout << long_separator << std::endl
         << "  next  exit_search_view(e) "
         << "  previous   \n"
         << short_separator << std::endl;

}

inline void RegistrationList::move_to_next()
{
    if (m_entries_.empty())
        return;
    ++itr_current_entry_;
    if (itr_current_entry_ == m_entries_.end())
        itr_current_entry_ = m_entries_.begin();
}
inline void RegistrationList::move_to_previous()
{
    if(m_entries_.empty())
        return;
    if(itr_current_entry_ == m_entries_.begin())
    {
        itr_current_entry_ = m_entries_.end();
        --itr_current_entry_;
    }
    else
        --itr_current_entry_;

}
inline void RegistrationList::search_move_to_next()
{
     if (search_results.empty())
        return;
    ++itr_current_entry_;
    if (itr_current_entry_ == search_results.end())
        itr_current_entry_ = search_results.begin();
}
inline void RegistrationList::search_move_to_previous()
{
    if(search_results.empty())
        return;
    if(itr_current_entry_ == search_results.begin())
    {
        itr_current_entry_ = search_results.end();
        --itr_current_entry_;
    }
    else
        --itr_current_entry_;
}
inline void RegistrationList::delete_()
{
    cout << "Are you sure you want to delete this entry(Y or N)?: ";
    std::string response;
    getline(std::cin, response);
    if(response == "Y" || response == "y")
    {
        m_entries_.erase(itr_current_entry_);
    }
    else
    {

    }
}
inline void RegistrationList::display_statistics()
{
    std::vector<int> number_players = {0,0,0,0,0,0};
    std::vector<int> number_paid = {0,0,0,0,0,0};
    //std::vector<int> number_not_paid;
    std::cout << "       " << "Number of Players" << "        "
         << "Number paid" << "      " << "Number not paid" << std::endl;
    //Use iterator to run through map, obtain counts

    for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr)
    {
        if(itr->second.category == "U6")
        {
            if(itr->second.registration_status == "paid"||
               itr->second.registration_status == "Paid")
            {
                ++number_paid[0];
            }
            ++number_players[0];
        }
        else if(itr->second.category == "U8")
        {
            if(itr->second.registration_status == "paid"||
               itr->second.registration_status == "Paid")
            {
                ++number_paid[1];
            }
            ++number_players[1];
        }
        else if(itr->second.category == "U10")
        {
            if(itr->second.registration_status == "paid"||
               itr->second.registration_status == "Paid")
            {
                ++number_paid[2];
            }
            ++number_players[2];
        }
        else if(itr->second.category == "U12")
        {
            if(itr->second.registration_status == "paid"||
               itr->second.registration_status == "Paid")
            {
                ++number_paid[3];
            }
            ++number_players[3];
        }
        else if(itr->second.category == "U14")
        {
            if(itr->second.registration_status == "paid"||
               itr->second.registration_status == "Paid")
            {
                ++number_paid[4];
            }
            ++number_players[4];
        }
        else
        {
            if(itr->second.registration_status == "paid"||
               itr->second.registration_status == "Paid")
            {
                ++number_paid[5];
            }
            ++number_players[5];
        }

    }

    int total_players = 0;
    int total_paid = 0;
    for(int x = 0; x < number_players.size();++x)
    {

        total_players += number_players[x];
        total_paid += number_paid[x];
    }
    //Now time to display
    int numberOfCategories = 6;
    int age_group = 6;
    int num_not_paid;
    int tot_num_not_paid = total_players - total_paid;
    for(int x = 0; x< numberOfCategories;++x)
    {
        num_not_paid = number_players[x] - number_paid[x];
        std::cout << 'U' << age_group << "          "
                    << number_players[x] << "                      "
                    << number_paid[x] << "                    "
                    << num_not_paid << std::endl;
        if(x == 4)
        {
            age_group += 3;
        }
        else
        {
            age_group += 2;
        }
    }
    char dummy;
    std::cout << "Total" << "        " << total_players
              << "                      "  << total_paid
              << "                    "  << tot_num_not_paid << std::endl;
    std::cout << "Press 'E' and enter to continue: ";
    std::cin >> dummy;
}

inline void RegistrationList::find(std::string & search_term, const std::string & c)
{
    //We must search through every key of the map
    //If found, print out all results using search view
    if(c == "L")
    {
        RegistrationEntry temp_entry;
        for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr)
        {
            itr_current_entry_ = m_entries_.find(search_term);
            temp_entry = itr_current_entry_->second;
            auto result = search_results.insert({search_term,{temp_entry}});
            itr_current_entry_ = result.first;

            //Now we must call the search display
        }
        run_search_view();
    }
    else
    {
        RegistrationEntry temp_entry;
        for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr)
        {
            RegistrationEntry temp;
            temp = itr_current_entry_->second;
            if(search_term == temp.first_name ||
               search_term == temp.last_name ||
               search_term == temp.category ||
               search_term == temp.registration_status)
            {
                std::string temp_string = itr_current_entry_->first;
                auto result = search_results.insert({temp_string,{temp}});
                itr_current_entry_ = result.first;
            }

            //Now we must call the search display
        }
        run_search_view();
    }
}
