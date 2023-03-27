#include "MovieDatabase.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Movie.h"
using namespace std;

MovieDatabase::MovieDatabase()
{

}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);    // infile is a name of our choosing
    if (!infile)                  // Did opening the file fail?
    {
        cerr << "Error: Cannot open " << filename << endl;
        return false;
    }
    
    string movieID;
    string movieName;
    int movieReleaseYear = 0;
    vector<string> movieDirectors;
    vector<string> movieActors;
    vector<string> movieGenres;
    float movieRating = 0.0f;
    
    string s;
    while(getline(infile, s))
    {
        if(s.empty()) // if the current line is empty, add the movie to the movie database
        {
            Movie newMovie(movieID, movieName, to_string(movieReleaseYear), movieDirectors, movieActors, movieGenres, movieRating);
            // associate the movieID with the movie
            m_movieID.insert(makeLower(movieID), newMovie);
            
            // assosicate the movie director with the movies they've been in
            for(int i = 0; i < movieDirectors.size(); i++)
            {
                m_movie_Directors.insert(makeLower(movieDirectors[i]), newMovie);
            }
            // associate the movie actor with the movies they've been in
            for(int i = 0; i < movieActors.size(); i++)
            {
                m_movie_Actors.insert(makeLower(movieActors[i]), newMovie);
            }
            // associate the genre with the movies of that genre
            for(int i = 0; i < movieGenres.size(); i++)
            {
                m_movie_Genres.insert(makeLower(movieGenres[i]), newMovie);
            }

            
            movieID.clear();
            movieName.clear();
            movieReleaseYear = 0;
            movieDirectors.clear();
            movieActors.clear();
            movieGenres.clear();
            movieRating = 0;
        }
        else if(movieID.empty())
        {
            movieID = s;
        }
        else if(movieName.empty())
        {
            movieName = s;
        }
        else if(movieReleaseYear == 0)
        {
            movieReleaseYear = stoi(s);
        }
        else if(movieDirectors.empty())
        {
            splitStringByCommas(movieDirectors, s);
        }
        else if(movieActors.empty())
        {
            splitStringByCommas(movieActors, s);
        }
        else if(movieGenres.empty())
        {
            splitStringByCommas(movieGenres, s);
        }
        else
        {
            movieRating = stof(s);
        }
    }
    
    // Add the last movie to the database (if there was no empty line after it)
    if(!movieID.empty())
    {
        Movie newMovie(movieID, movieName, to_string(movieReleaseYear), movieDirectors, movieActors, movieGenres, movieRating);
        m_movieID.insert(makeLower(movieID), newMovie);
        
        for(int i = 0; i < movieDirectors.size(); i++)
        {
            m_movie_Directors.insert(makeLower(movieDirectors[i]), newMovie);
        }
        for(int i = 0; i < movieActors.size(); i++)
        {
            m_movie_Actors.insert(makeLower(movieActors[i]), newMovie);
        }
        for(int i = 0; i < movieGenres.size(); i++)
        {
            m_movie_Genres.insert(makeLower(movieGenres[i]), newMovie);
        }
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<string, Movie>::Iterator it = m_movieID.find(makeLower(id));
    if(it.is_valid())
    {
        return &it.get_value();
    }
    else
    {
        return nullptr;
    }
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> moviesWithDirectors;
    
    TreeMultimap<string, Movie>::Iterator it = m_movie_Directors.find(makeLower(director));
    
    while(it.is_valid())
    {
        moviesWithDirectors.push_back(&it.get_value());
        it.advance();
    }
    return moviesWithDirectors;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> movieWithActors;
    
    TreeMultimap<string, Movie>::Iterator it = m_movie_Actors.find(makeLower(actor));
    while(it.is_valid())
    {
        movieWithActors.push_back(&it.get_value());
        it.advance();
    }
    return movieWithActors;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> movieWithGenres;
    
    TreeMultimap<string, Movie>::Iterator it = m_movie_Genres.find(makeLower(genre));
    while(it.is_valid())
    {
        movieWithGenres.push_back(&it.get_value());
        it.advance();
    }
    return movieWithGenres;
}
