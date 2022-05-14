//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_TWEET_H
#define TWEET_SENTIMENT_ANALYSER_TWEET_H

#include <string>

namespace util{
    enum SENTI {
        GUESS = '\0', POSITIVE = '4', NEGATIVE = '0'
    };

    struct Tweet {
        std::string content;
        std::string ID;
        SENTI senti = GUESS;

        Tweet() = default;

        void readTweetTester(char *str);

        void readTweetTrainer(char *str);

        void clean();
    };

}


#endif //TWEET_SENTIMENT_ANALYSER_TWEET_H
