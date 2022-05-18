//
// Created by misc1 on 5/13/2022.
//

#include "Classifier.h"
#include <sstream>

Classifier::Classifier(Trainer *trainingData, std::vector<util::Tweet> *tweets) {
    this->trainingData = trainingData;
    this->tweets = tweets;
}

void Classifier::classifyWithWordAcc() {
    for (auto& tweet : *this->tweets) {
        if(tweet.senti != util::GUESS)
            continue;

        float grade = 0.0;
        int counter = 0;
        {
            std::string current;
            std::stringstream stream(tweet.content);
            while (stream >> current) {
                std::unordered_map<std::string, util::Feature>::iterator iter;
                try {
                    iter = this->trainingData->findWord(current);
                }
                catch (const std::invalid_argument &e) {
                    continue;
                }
                if(iter->second.flag == true)
                    continue;

                if (iter->second.posCount > iter->second.negCount) {
                    counter++;
                    grade += iter->second.cm.accuracy();
                } else if (iter->second.posCount < iter->second.negCount) {
                    counter++;
                    grade -= iter->second.cm.accuracy();
                }
            }
        }

        tweet.senti = util::GUESS;

        if(counter > 0){
            int gradeInt = int(grade * 100);

            if (gradeInt < 0)
                tweet.senti = util::NEGATIVE;
            else if (gradeInt > 0)
                tweet.senti = util::POSITIVE;
        }
    }
}

util::ConfusionMatrix Classifier::readConfusionMatrix(const Classifier &classifier, const std::unordered_map<std::string, util::SENTI> &sentimentMap) {
    util::ConfusionMatrix confusionMatrix;
    for (const auto& tweet : *classifier.tweets) {
        util::SENTI senti = sentimentMap.at(tweet.ID);
        if(senti == util::POSITIVE)
            confusionMatrix.conditionPos++;
        else if(senti == util::NEGATIVE)
            confusionMatrix.conditionNeg++;
        else
            continue;

        if(tweet.senti == util::GUESS) {
            if(senti == util::POSITIVE)
                confusionMatrix.truePos++;
            else
                confusionMatrix.falsePos++;
        }
        else if(tweet.senti == util::POSITIVE) {
            if(tweet.senti == senti)
                confusionMatrix.truePos++;
            else
                confusionMatrix.falsePos++;
        }
        else if(tweet.senti == util::NEGATIVE){
            if(tweet.senti == senti)
                confusionMatrix.trueNeg++;
            else
                confusionMatrix.falseNeg++;
        }
    }

    return confusionMatrix;
}

void Classifier::classifyWithBiwordAcc() {
    for (auto& tweet : *this->tweets) {
        if(tweet.senti != util::GUESS)
            continue;

        float grade = 0.0;
        int counter = 0;
        {
            std::string current;
            std::stringstream stream(tweet.content);
            std::string previous;
            stream >> previous;
            while (stream >> current) {
                std::unordered_map<std::string, util::Feature>::iterator iter;
                try {
                    iter = this->trainingData->findBiword(previous + '-' + current);
                }
                catch (const std::invalid_argument &e) {
                    continue;
                }
                if(iter->second.flag == true) {
                    previous = current;
                    continue;
                }

                if (iter->second.posCount > iter->second.negCount) {
                    counter++;
                    grade += iter->second.cm.accuracy();
                } else if (iter->second.posCount < iter->second.negCount) {
                    counter++;
                    grade -= iter->second.cm.accuracy();
                }
                previous = current;
            }
        }

        tweet.senti = util::GUESS;

        if(counter > 0){
            int gradeInt = int(grade * 100);

            if (gradeInt < 0)
                tweet.senti = util::NEGATIVE;
            else if (gradeInt > 0)
                tweet.senti = util::POSITIVE;
        }
    }
}

void Classifier::classify() {
    this->classifyWithBiwordAcc();
    this->classifyWithWordAcc();
}
