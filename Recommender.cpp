#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include "User.h"
using namespace std;

Recommender::Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database)
{
    m_udb = &user_database;
    m_mb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    
    vector<MovieAndRank> movie_recs;
    // get the user from the email address
    User* uToRecommend = m_udb->get_user_from_email(user_email);
    if(uToRecommend == nullptr)
    {
        return movie_recs;
    }
    // get the user watch history
    vector<string> userWatchHistoryCopy = uToRecommend->get_watch_history();
    // get the user watch history into a set so that it is faster to search through
    set<string> userWatchHistory;
    for(int i = 0; i < userWatchHistoryCopy.size(); i++)
    {
        userWatchHistory.insert(userWatchHistoryCopy[i]);
    }
    
    unordered_map<string, int> moviesWithScores;
    set<string>::iterator s_it;
    for(s_it = userWatchHistory.begin(); s_it != userWatchHistory.end(); s_it++)
    {
        Movie* processMovie = m_mb->get_movie_from_id(*s_it);
        
        // make sure you aren't following nullptr
        if(processMovie == nullptr)
        {
            return movie_recs;
        }
        
        // for each movie in the user's watch history, get a vector of the associated genres
        vector<string> genres_in_movie = processMovie->get_genres();
        for(int k = 0; k < genres_in_movie.size(); k++)
        {
            // for each genre, get a vector of assosiated movies
            vector<Movie*> movies_with_genres = m_mb->get_movies_with_genre(genres_in_movie[k]);
            for(int j = 0; j < movies_with_genres.size(); j++)
            {
                // if the movie isn't already watched by the user, map it into movieWithScores and add 1 to the score
                set<string>::iterator already_watched = userWatchHistory.find(movies_with_genres[j]->get_id());
                if(already_watched == userWatchHistory.end())
                {
                    moviesWithScores[movies_with_genres[j]->get_id()] += 1;
                }
            }
        }
        // for each movie in the user's watch history, get a vector of the associated actors
        vector<string> actors_in_movie = processMovie->get_actors();
        for(int k = 0; k < actors_in_movie.size(); k++)
        {
            // for each actor, get a vector of assosiated movies
            vector<Movie*> movies_with_actors = m_mb->get_movies_with_actor(actors_in_movie[k]);
            for(int j = 0; j < movies_with_actors.size(); j++)
            {
                // if the movie isn't already watched by the user, map it into movieWithScores and add 30 to the score
                set<string>::iterator already_watched = userWatchHistory.find(movies_with_actors[j]->get_id());
                if(already_watched == userWatchHistory.end())
                {
                    moviesWithScores[movies_with_actors[j]->get_id()] += 30;
                }
            }
        }
        // for each movie in the user's watch history, get a vector of the associated directors
        vector<string> directors_in_movie = processMovie->get_directors();
        for(int k = 0; k < directors_in_movie.size(); k++)
        {
            // for each director, get a vector of assosiated movies
            vector<Movie*> movies_with_director = m_mb->get_movies_with_director(directors_in_movie[k]);
            for(int j = 0; j < movies_with_director.size(); j++)
            {
                // if the movie isn't already watched by the user, map it into movieWithScores and add 20 to the score
                set<string>::iterator already_watched = userWatchHistory.find(movies_with_director[j]->get_id());
                if(already_watched == userWatchHistory.end())
                {
                    moviesWithScores[movies_with_director[j]->get_id()] += 20;
                }
            }
        }
    }
    
    
    map<Rec_Movie, pair<string, int>> m_recs;
    
    unordered_map<string, int>::iterator umI = moviesWithScores.begin();
    
    // traverse the unorderedmap that maps movieID's and scores
    while(umI != moviesWithScores.end())
    {
        // get movie and score from the unorderedmap
        Movie* movie = m_mb->get_movie_from_id(umI->first);
        int score = umI->second;
        Rec_Movie r_m(score, movie->get_rating(), movie->get_title());
        // map each Rec_Movie to a map that maps rec_movies to a pair of movie id's and scores
        // (can't map directly to MovieAndRank because it doesn't have a default constructor)
        // when inserting r_m into this map, it will automatically be sorted via our custom operator<() function
        m_recs[r_m] = {movie->get_id(), score};
        umI++;
    }
    
    int count = 0;
    map<Rec_Movie, pair<string, int>>::iterator findMatches;
    // loop through the m_recs map, and append the first movie_count nums into the movie_recs vector
    for(findMatches = m_recs.begin(); findMatches != m_recs.end(); findMatches++)
    {
        if(count == movie_count)
        {
            break;
        }
        MovieAndRank m_and_r(findMatches->second.first, findMatches->second.second);
        movie_recs.push_back(m_and_r);
        count++;
    }
    
    return movie_recs;
}

