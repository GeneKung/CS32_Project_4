#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <vector>
#include <cctype>
using namespace std;

UserDatabase::UserDatabase()
{
    m_loaded = false;
}

bool UserDatabase::load(const string& filename)
{

    ifstream infile(filename);    // infile is a name of our choosing
    if (!infile)                // Did opening the file fail?
    {
         cerr << "Error: Cannot open " << filename << endl;
         return false;
    }

    string s;
    string name;
    string email;
    int numMovies = 0;
    vector <string> watch_history;

    int count = 0;

    while(getline(infile, s))
    {
        if(s.empty()) // if the current line is empty, add the user to userdatabase
         {
             User newUser(name, email, watch_history);
             userDataBase.insert(email, newUser);
             
             name.clear();
             email.clear();
             numMovies = 0;
             watch_history.clear();
             count++;
         }
         else if(name.empty())
         {
             name = s;
         }
         else if(email.empty())
         {
             email = s;
         }
         else if(numMovies == 0)
         {
             numMovies = stoi(s);
         }
         else
         {
             watch_history.push_back(s);
         }
    }
    
    // Add the last user to the database (if there was no empty line after it)
    if (!name.empty() && !email.empty() && numMovies > 0)
    {
        User newUser(name, email, watch_history);
        userDataBase.insert(email, newUser);
    }
    return true;
 
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User>:: Iterator it = userDataBase.find(email);
    if(it.is_valid()) // not nullptr
    {
        return &it.get_value();
    }
    else
    {
        return nullptr;
    }
}

