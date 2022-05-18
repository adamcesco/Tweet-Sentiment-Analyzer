//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_CLASSIFIER_H
#define TWEET_SENTIMENT_ANALYSER_CLASSIFIER_H

#include "../Trainer/Trainer.h"

class Classifier {
private:
    Trainer* trainingData;
    std::vector<util::Tweet>* tweets;

    void classifyWithWordAcc();
    void classifyWithBiwordAcc();
public:
    Classifier(Trainer* trainingData, std::vector<util::Tweet>* tweets);
    void classify();
    static util::ConfusionMatrix readConfusionMatrix(const Classifier& classifier, const std::unordered_map<std::string, util::SENTI> &sentimentMap);
};


#endif //TWEET_SENTIMENT_ANALYSER_CLASSIFIER_H
