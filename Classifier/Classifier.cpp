//
// Created by misc1 on 5/13/2022.
//

#include "Classifier.h"
#include <sstream>

Classifier::Classifier(Trainer *trainingData, std::vector<util::Tweet> *tweets) {
    this->trainingData = trainingData;
    this->tweets = tweets;
}

void Classifier::wordBasedClassification() {
    for (auto& tweet : *this->tweets) {
        std::string current;
        std::stringstream stream(tweet.content);
        float grade = 0.0;
        while (stream >> current) {
            std::unordered_map<std::string, util::Word>::iterator iter;
            try {
                iter = this->trainingData->find(current);
            }
            catch (const std::invalid_argument& e){
                continue;
            }

            if(iter->second.posCount > iter->second.negCount){
                grade -= iter->second.cm.accuracy();
            }
            else if(iter->second.posCount < iter->second.negCount){
                grade += iter->second.cm.accuracy();
            }

        }

        int gradeInt = grade * 100;

        if(gradeInt < 0)
            tweet.senti = util::NEGATIVE;
        else if(gradeInt > 0)
            tweet.senti = util::POSITIVE;
    }
}

util::ConfusionMatrix Classifier::readConfusionMatrix(const Classifier &classifier, std::unordered_map<std::string, util::SENTI> sentimentMap) {
    util::ConfusionMatrix confusionMatrix;
    for (const auto& tweet : *classifier.tweets) {
        util::SENTI senti = sentimentMap[tweet.ID];
        if(senti == util::POSITIVE)
            confusionMatrix.conditionPos++;
        else if(senti == util::NEGATIVE)
            confusionMatrix.conditionNeg++;

        if(senti == util::POSITIVE) {
            if(tweet.senti == senti)
                confusionMatrix.truePos++;
            else
                confusionMatrix.falsePos++;
        }
        else if(senti == util::NEGATIVE){
            if(tweet.senti == senti)
                confusionMatrix.trueNeg++;
            else
                confusionMatrix.falseNeg++;
        }

    }

    return confusionMatrix;
}
