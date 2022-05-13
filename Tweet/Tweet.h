//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_TWEET_H
#define TWEET_SENTIMENT_ANALYSER_TWEET_H

#include <string>

enum SENTI {
    GUESS, POSITIVE, NEGATIVE
};

class Tweet {
private:
    std::string content;
    std::string ID;
    SENTI senti;

public:
    Tweet() = default;
};


#endif //TWEET_SENTIMENT_ANALYSER_TWEET_H
