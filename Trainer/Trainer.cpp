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
            util::Feature &word = this->wordMap[current];
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
            util::Feature &word = this->wordMap[current];
            if (tweet.senti == util::POSITIVE) {
                word.cm.conditionPos++;

                if (word.posCount > word.negCount) {
                    word.cm.truePos++;
                } else if (word.posCount < word.negCount) {
                    word.cm.falseNeg++;
                }
            } else if (tweet.senti == util::NEGATIVE) {
                word.cm.conditionNeg++;

                if (word.posCount < word.negCount) {
                    word.cm.trueNeg++;
                } else if (word.posCount > word.negCount) {
                    word.cm.falsePos++;
                }
            }
        }
    }
}

void Trainer::FlagOutliers() {
    for (auto & it : this->wordMap) {
        if((it.second.posCount + it.second.negCount) < 10 || int(it.second.cm.accuracy() * 100) < 60)
            it.second.flag = true;
    }

    for (auto & it : this->biwordMap) {
        if((it.second.posCount + it.second.negCount) < 10 || int(it.second.cm.accuracy() * 100) < 75)
            it.second.flag = true;
    }
}

std::unordered_map<std::string, util::Feature>::iterator Trainer::findWord(const std::string &str) {
    auto toReturn = this->wordMap.find(str);
    if(toReturn == this->wordMap.end())
        throw std::invalid_argument("Error in \"std::unordered_map<std::string, util::Feature>::iterator Trainer::findWord(const std::string &str)\" | passed string has not been found");
    return toReturn;
}

void Trainer::trainWith(const std::vector<util::Tweet> &tweetVect) {
    this->countWordSentiFrom(tweetVect);
    this->countBiwordSentiFrom(tweetVect);
    this->calcWordSentiAcc(tweetVect);
    this->calcBiwordSentiAcc(tweetVect);
    this->FlagOutliers();
}

void Trainer::countBiwordSentiFrom(const std::vector<util::Tweet> &tweetVect) {
    for (auto& tweet : tweetVect) {
        std::string current;
        std::stringstream stream(tweet.content);
        std::string previous;
        stream >> previous;
        while (stream >> current) {
            std::string temp = previous + '-' + current;
            util::Feature &biword = this->biwordMap[temp];
            biword.data = temp;
            if (tweet.senti == util::POSITIVE)
                biword.posCount++;
            else if (tweet.senti == util::NEGATIVE)
                biword.negCount++;
            previous = current;
        }
    }
}

void Trainer::calcBiwordSentiAcc(const std::vector<util::Tweet> &tweetVect) {
    for (auto& tweet : tweetVect) {
        std::string current;
        std::stringstream stream(tweet.content);
        std::string previous;
        stream >> previous;
        while (stream >> current) {
            util::Feature &biword = this->biwordMap[previous + '-' + current];
            if (tweet.senti == util::POSITIVE) {
                biword.cm.conditionPos++;

                if (biword.posCount > biword.negCount) {
                    biword.cm.truePos++;
                } else if (biword.posCount < biword.negCount) {
                    biword.cm.falseNeg++;
                }
            } else if (tweet.senti == util::NEGATIVE) {
                biword.cm.conditionNeg++;

                if (biword.posCount < biword.negCount) {
                    biword.cm.trueNeg++;
                } else if (biword.posCount > biword.negCount) {
                    biword.cm.falsePos++;
                }
            }
            previous = current;
        }
    }
}

std::unordered_map<std::string, util::Feature>::iterator Trainer::findBiword(const std::string &str) {
    auto toReturn = this->biwordMap.find(str);
    if(toReturn == this->biwordMap.end())
        throw std::invalid_argument("Error in \"std::unordered_map<std::string, util::Feature>::iterator Trainer::findBiword(const std::string &str)\" | passed string has not been found");
    return toReturn;
}
