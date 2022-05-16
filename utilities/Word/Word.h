//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_WORD_H
#define TWEET_SENTIMENT_ANALYSER_WORD_H

#include <string>

namespace util{
    struct ConfusionMatrix {
        int conditionPos = 0;
        int conditionNeg = 0;
        int trueNeg = 0;
        int truePos = 0;
        int falseNeg = 0;
        int falsePos = 0;

        float accuracy() const;
    };

    struct Word {
        std::string data;
        int negCount = 0;
        int posCount = 0;
        ConfusionMatrix cm;

        Word() = default;
        Word(std::string data) { this->data = data; }
    };

}


#endif //TWEET_SENTIMENT_ANALYSER_WORD_H
