//
// Created by misc1 on 5/13/2022.
//

#ifndef TWEET_SENTIMENT_ANALYSER_FEATURE_H
#define TWEET_SENTIMENT_ANALYSER_FEATURE_H

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
        float recall() const;
    };

    struct Feature {
        std::string data;
        int negCount = 0;
        int posCount = 0;
        bool flag = false;
        ConfusionMatrix cm;

        Feature() = default;
        Feature(std::string data) { this->data = data; }
    };

}


#endif //TWEET_SENTIMENT_ANALYSER_FEATURE_H
