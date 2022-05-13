//
// Created by misc1 on 5/13/2022.
//

#include "Tweet.h"
#include "string.h"
#include <stdexcept>

void Tweet::readTweetTester(char* str) {
    char* token = strtok(str, ",");
    int counter = 0;
    while(token != NULL){
        token = strtok(str, ",");
        if(counter == 0)
            this->ID = token;
        else if(counter == 4)
            this->content = token;
        counter++;
    }
}

void Tweet::readTweetTrainer(char *str) {
    if(str == nullptr)
        throw std::invalid_argument("Error in \"void Tweet::readTweetTrainer(char *str)\" | passed char * is nullptr");
    this->senti = SENTI(str[0]);
    char* token = strtok(str, ",");
    int counter = 0;
    while(token != NULL){
        token = strtok(str, ",");
        if(counter == 1)
            this->ID = token;
        else if(counter == 5)
            this->content = token;
        counter++;
    }
}

void Tweet::clean() {

}
