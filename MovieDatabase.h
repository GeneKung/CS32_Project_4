#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
    public:
        MovieDatabase();
        bool load(const std::string& filename);
        Movie* get_movie_from_id(const std::string& id) const;
        std::vector<Movie*> get_movies_with_director(const std::string& director) const;
        std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
        std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

    private:
    
        TreeMultimap<std::string, Movie> m_movieID;
        TreeMultimap<std::string, Movie> m_movie_Directors;
        TreeMultimap<std::string, Movie> m_movie_Actors;
        TreeMultimap<std::string, Movie> m_movie_Genres;

        
        void splitStringByCommas(std::vector<std::string>& movie_info, std::string line)
        {
            std::string info = "";
            for(int i = 0; i < line.size(); i++)
            {
                if(line[i] != ',')
                {
                    info += line[i];
                }
                else
                {
                    movie_info.push_back(info);
                    info = "";
                }
            }
            movie_info.push_back(info);
        }
         
        std::string makeLower(const std::string &s) const
        {
            std::string lower = "";
            for(int i = 0; i < s.size(); i++)
            {
                lower += tolower(s[i]);
            }
            return lower;
        }

};

#endif // MOVIEDATABASE_INCLUDED
