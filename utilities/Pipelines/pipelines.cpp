//
// Created by misc1 on 5/13/2022.
//

#include <sstream>
#include "pipelines.h"
#include "../../external/porter2_stemmer.h"
#include "../StopWords.h"

void pipelines::removeAbsLinks(std::string &text) {
    if(text.empty())
        throw std::invalid_argument("Error in \"void pipelines::removeAbsLinks(std::string &text)\" | Passed string is empty");

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

void pipelines::removeUsernames(std::string &text) {
    if(text.empty())
        throw std::invalid_argument("Error in \"void pipelines::removeUsernames(std::string &text)\" | Passed string is empty");

    for (std::size_t start = text.find('@'); start != std::string::npos; start = text.find('@')){
        std::size_t end = text.find_first_of(' ', start);
        text.replace(start, end - start, " ");
    }
}

std::string pipelines::removeNonAlphas(const std::string &text) {
    if(text.empty())
        throw std::invalid_argument("Error in \"std::string pipelines::removeNonAlphas(const std::string &text)\" | Passed string is empty");

    std::string toReturn;
    for (const char& it : text) {
        if (std::isalpha(it))
            toReturn += tolower(it);
        else if (it != '\'')
            toReturn += ' ';
    }
    return toReturn;
}

std::string pipelines::stemText(const std::string &text) {
    if(text.empty())
        throw std::invalid_argument("Error in \"std::string pipelines::stemText(const std::string &text)\" | Passed string is empty");

    std::string toReturn;
    std::string current;
    std::stringstream stream(text);
    while(stream >> current){
        Porter2Stemmer::stem(current);
        toReturn += current + ' ';
    }
    return toReturn;
}

std::string pipelines::removeRepeatingChars(const std::string &text) {
    if(text.empty())
        throw std::invalid_argument("Error in \"std::string pipelines::removeRepeatingChars(const std::string &text)\" | Passed string is empty");

    std::string toReturn;
    toReturn = text[0];
    for (const auto& it : text) {
        if(it != toReturn.back())
            toReturn += it;
    }

    return toReturn;
}

std::string pipelines::removeStopWords(const std::string &text) {
    if(text.empty())
        throw std::invalid_argument("Error in \"std::string pipelines::removeStopWords(const std::string &text)\" | Passed string is empty");

    std::string toReturn;
    util::StopWords stopWords;

    std::string current;
    std::stringstream stream(text);
    while(stream >> current){
        if(stopWords.corpusSet.find(current) == stopWords.corpusSet.end())
            toReturn += current + ' ';
    }
    return toReturn;
}
