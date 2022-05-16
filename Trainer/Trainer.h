//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_TRAINER_H
#define TWEET_SENTIMENT_ANALYSER_TRAINER_H

#include <unordered_map>
#include <vector>
#include "../utilities/Feature/Feature.h"
#include "../utilities/Tweet/Tweet.h"

class Trainer {
private:
    std::unordered_map<std::string, util::Feature> wordMap;

public:
    void countWordSentiFrom(const std::vector<util::Tweet> &tweetVect);
    void calcWordSentiAcc(const std::vector<util::Tweet> &tweetVect);
    void cleanOutliers();
    std::unordered_map<std::string, util::Feature>::iterator find(const std::string& str);
};


#endif //TWEET_SENTIMENT_ANALYSER_TRAINER_H
