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

        void readTweetTester(const std::string &str);

        void readTweetTrainer(const std::string &str);

        void clean();

        bool empty() const;
    };

}


#endif //TWEET_SENTIMENT_ANALYSER_TWEET_H
