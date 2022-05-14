//
// Created by misc1 on 5/13/2022.
//

#include "Trainer.h"
#include <sstream>

void Trainer::countWordSentiFrom(const std::vector<util::Tweet> &tweetVect) {
    for (auto& tweet : tweetVect) {
        std::string current;
        std::stringstream stream(tweet.content);
        while (stream >> current) {
            util::Word &word = this->wordMap[current];
            word.data = current;
            if (tweet.senti == util::POSITIVE)
                word.posCount++;
            else if (tweet.senti == util::NEGATIVE)
                word.negCount++;
        }
    }
}

void Trainer::calcWordSentiAcc(const std::vector<util::Tweet> &tweetVect) {
    for (auto& tweet : tweetVect) {
        std::string current;
        std::stringstream stream(tweet.content);
        while (stream >> current) {
            util::Word &word = this->wordMap[current];
            if (tweet.senti == util::POSITIVE) {
                if (word.posCount > word.negCount) {
                    word.cm.truePos++;
                } else if (word.posCount < word.negCount) {
                    word.cm.falseNeg++;
                }
            } else if (tweet.senti == util::NEGATIVE) {
                if (word.posCount < word.negCount) {
                    word.cm.trueNeg++;
                } else if (word.posCount > word.negCount) {
                    word.cm.falsePos++;
                }
            }
        }
    }
}

void Trainer::cleanOutliers() {
    for (auto it = this->wordMap.cbegin(); it != this->wordMap.cend(); ++it) {
        if(int(it->second.cm.accuracy() * 100) < 54)
            it = wordMap.erase(it);
    }
}

std::unordered_map<std::string, util::Word>::iterator Trainer::find(const std::string &str) {
    auto toReturn = this->wordMap.find(str);
    if(toReturn == this->wordMap.end())
        throw std::invalid_argument("Error in \"std::unordered_map<std::string, util::Word>::iterator Trainer::find(const std::string &str)\" | passed string has not been found");
    return toReturn;
}
