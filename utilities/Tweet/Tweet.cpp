//
// Created by misc1 on 5/13/2022.
//

#include "Tweet.h"
#include <stdexcept>
#include <sstream>
#include "../Pipelines/pipelines.h"

void util::Tweet::readTweetTester(const std::string &str) {
    this->senti = GUESS;

    int counter = 0;
    std::stringstream stream(str);
    std::string cell;
    while(getline(stream, cell, ',')){
        if(counter == 0)
            this->ID = cell;
        else if(counter == 4)
            this->content = cell;

        counter++;
    }
}

void util::Tweet::readTweetTrainer(const std::string &str) {
    this->senti = SENTI(str[0]);

    int counter = 0;
    std::stringstream stream(str);
    std::string cell;
    while(getline(stream, cell, ',')){
        if(counter == 1)
            this->ID = cell;
        else if(counter == 5)
            this->content = cell;

        counter++;
    }
}

void util::Tweet::clean() {
    pipelines::removeAbsLinks(this->content);
    pipelines::removeUsernames(this->content);
    this->content = pipelines::removeNonAlphas(this->content);
    this->content = pipelines::stemText(this->content);
    this->content = pipelines::removeStopWords(this->content);
    this->content = pipelines::removeRepeatingChars(this->content);
}
