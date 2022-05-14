//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_TRAINER_H
#define TWEET_SENTIMENT_ANALYSER_TRAINER_H

#include <unordered_map>
#include <vector>
#include "../utilities/Word/Word.h"
#include "../utilities/Tweet/Tweet.h"

class Trainer {
private:
    std::unordered_map<std::string, util::Word> wordMap;

public:
    void countWordSentiFrom(const std::vector<util::Tweet> &tweetVect);
    void calcWordSentiAcc(const std::vector<util::Tweet> &tweetVect);
    void cleanOutliers();
    std::unordered_map<std::string, util::Word>::iterator find(const std::string& str);
};


#endif //TWEET_SENTIMENT_ANALYSER_TRAINER_H
