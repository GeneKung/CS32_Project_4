#include "UserDatabase.h"
#include "User.h"
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;
#include "MovieDatabase.h"
#include "Movie.h"



void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations) {
    // get up to ten movie recommendations for the user
    vector<MovieAndRank> recommendations =
    r.recommend_movies(user_email, num_recommendations);
    
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i + 1 << ". " << m->get_title() << " (" << m->get_release_year() << ")\n Rating: " << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n";
        }
    }
}


int main()
{
    UserDatabase udb;
    MovieDatabase mdb;
    // /u/cs/ugrad/kung

    
    if(udb.load("/Users/genekung/Desktop/Cs32/P_4/P_4/Users.txt"))
    {
        cout << "sucess" << endl;
    }
    
    if(mdb.load("/Users/genekung/Desktop/CS32/P_4/P_4/Movies.txt"))
    {
        cout << "sucess" << endl;
    }
     
    /*
    if(udb.load("/u/cs/ugrad/kung/Users.txt"))
    {
        cout << "sucess" << endl;
    }
    
    if(mdb.load("/u/cs/ugrad/kung/Movies.txt"))
    {
        cout << "sucess" << endl;
    }
     */
    
    Recommender rec(udb, mdb);
    
    findMatches(rec, mdb, "ScRobe46@msn.com", 10);
    
}



const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

void printUserInfo(User* u) {
    if (u == nullptr) {
        cout << "No user in the database has that email address." << endl;
        return;
    }
    else {
        cout << "Name: " << u->get_full_name() << endl;
    }
    cout << "Email: " << u->get_email() << endl;
    cout << "Movie Ids: " << endl;
    vector<string> movieIDs = u->get_watch_history();
    for (string s : movieIDs) {
        cout << s << endl;
    }
    cout << endl;
}
 
void printMovieInfo(Movie* m) {
    if (m == nullptr) {
        cout << "No user in the database with that key." << endl;
        return;
    }
    cout << "ID: " << m->get_id() << endl;
    cout << "Title: " << m->get_title() << endl;
    cout << "Year: " << m->get_release_year() << endl;
    for (string s : m->get_directors()) {
        cout << s << ", ";
    }
    cout << endl;
    for (string s : m->get_actors()) {
        cout << s << ", ";
    }
    cout << endl;
    for (string s : m->get_genres()) {
        cout << s << ", ";
    }
    cout << endl;
    cout << "Rating: " << m->get_rating();
    cout << endl << endl;
}


/*
int main()
{
    
    MovieDatabase db;
    if(db.load("/Users/genekung/Desktop/CS32/Movies.txt"))
    {
        
        vector<Movie*> moviesWithDirectors = db.get_movies_with_actor("arNOLD schwarzenegger");
        
        
        //vector<Movie*>  moviesWithDirectors = db.get_movies_with_genre("DRAMA");
        for(int i = 0; i < moviesWithDirectors.size(); i++)
        {
            cout << moviesWithDirectors[i]->get_title() << endl;
        }
        
        //Movie* testMovie1 = db.get_movie_from_id("ID10782");
        //printMovieInfo(testMovie1);
        //Movie* testMovie2 = db.get_movie_from_id("ID25779");
        //printMovieInfo(testMovie2);
        // cout << testMovie2->get_title() << endl;
        
    }

    
    UserDatabase udb;
    if(udb.load("/Users/genekung/Desktop/CS32/P_4/P_4/Users.txt"))
    {
        
        User* testUser1 = udb.get_user_from_email("RHutchins32@gmail.com");
        printUserInfo(testUser1);
        
        User* testUser2 = udb.get_user_from_email("GreyKinney73108@charter.net");
        printUserInfo(testUser2);
        
    }
    
    
    
    if (0&&!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    
    for (;;)
    {
        cout << "Enter user email address (or quit): ";
        string email;
        getline(cin, email);
        if (email == "quit")
            return 0;
        User* u = udb.get_user_from_email(email);
        if (u == nullptr)
            cout << "No user in the database has that email address." << endl;
        else
            cout << "Found " << u->get_full_name() << endl;
    }
    
    
}

*/
