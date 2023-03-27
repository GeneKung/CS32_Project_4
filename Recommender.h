#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>

#include "treemm.h"

#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include <map>
#include <set>

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
    public:
        Recommender(const UserDatabase& user_database,
                    const MovieDatabase& movie_database);
        std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                                   int movie_count) const;
    private:
        struct Rec_Movie
        {
 
            int curr_score;
            float curr_rating;
            std::string curr_title;

            Rec_Movie(int score, float rating, std::string title)
            {
                curr_score = score;
                curr_rating = rating;
                curr_title = title;
            }
            bool operator<(const Rec_Movie &b) const
            {
                if (curr_score != b.curr_score)
                {
                    return curr_score > b.curr_score;
                }
                else if (curr_rating != b.curr_rating)
                {
                    return curr_rating > b.curr_rating;
                }
                else
                {
                    return curr_title < b.curr_title;
                }
            }
        };
    
        const UserDatabase* m_udb;
        const MovieDatabase* m_mb;
       
};

#endif // RECOMMENDER_INCLUDED
