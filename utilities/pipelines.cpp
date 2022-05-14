//
// Created by misc1 on 5/13/2022.
//

#include <sstream>
#include "pipelines.h"
#include "string.h"
#include "../external/porter2_stemmer.h"
#include "../utilities/StopWords.h"

void pipeline::removeAbsLinks(std::string &text) {
    std::size_t end = 0;
    auto findNext = [&text, end]() -> std::size_t{
        std::size_t num = text.find("http", end);
        num = (num == std::string::npos) ? text.find("www.", end) : num;
        return num;
    };

    for (std::size_t start = findNext(); start != std::string::npos; start = findNext()){
        end = text.find_first_of(' ', start);
        text.replace(start, end - start, " ");
    }
}

void pipeline::removeUsernames(std::string &text) {
    for (int start = text.find('@'); start != std::string::npos; start = text.find('@')){
        int end = text.find_first_of(' ', start);
        text.replace(start, end - start, " ");
    }
}

std::string pipeline::removeNonAlphas(const std::string &text) {
    std::string toReturn;
    for (const char& it : text) {
        if (it == ' ' || std::isalpha(it))
            toReturn += it;
    }
    return toReturn;
}

std::string pipeline::stemText(const std::string &text) {
    std::string toReturn;
    std::string current;
    std::stringstream stream(text);
    while(stream >> current){
        Porter2Stemmer::stem(current);
        toReturn += current;
    }
    return toReturn;
}

std::string pipeline::removeRepeatingChars(const std::string &text) {
    std::string toReturn;
    toReturn = text[0];
    for (const auto& it : text) {
        if(it != toReturn.back())
            toReturn += it;
    }

    return toReturn;
}

std::string pipeline::removeStopWords(const std::string &text) {
    std::string toReturn;
    util::StopWords stopWords;

    std::string current;
    std::stringstream stream(text);
    while(stream >> current){
        if(stopWords.corpusSet.find(current) == stopWords.corpusSet.end())
            toReturn += current;
    }
    return toReturn;
}
