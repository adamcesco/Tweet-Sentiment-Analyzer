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
    std::unordered_map<std::string, util::Feature> biwordMap;

    void countWordSentiFrom(const std::vector<util::Tweet> &tweetVect);
    void countBiwordSentiFrom(const std::vector<util::Tweet> &tweetVect);
    void calcWordSentiAcc(const std::vector<util::Tweet> &tweetVect);
    void calcBiwordSentiAcc(const std::vector<util::Tweet> &tweetVect);
    void FlagOutliers();
public:
    void trainWith(const std::vector<util::Tweet> &tweetVect);
    std::unordered_map<std::string, util::Feature>::iterator findWord(const std::string& str);
    std::unordered_map<std::string, util::Feature>::iterator findBiword(const std::string& str);
};


#endif //TWEET_SENTIMENT_ANALYSER_TRAINER_H
