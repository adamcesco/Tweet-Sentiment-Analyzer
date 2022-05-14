//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_PIPELINES_H
#define TWEET_SENTIMENT_ANALYSER_PIPELINES_H

#include <string>
namespace pipelines {
    void removeAbsLinks(std::string &text);
    void removeUsernames(std::string& text);
    std::string removeNonAlphas(const std::string& text);
    std::string stemText(const std::string& text);
    std::string removeRepeatingChars(const std::string& text);
    std::string removeStopWords(const std::string& text);
};


#endif //TWEET_SENTIMENT_ANALYSER_PIPELINES_H
