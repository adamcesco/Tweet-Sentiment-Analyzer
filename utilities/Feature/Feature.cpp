//
// Created by misc1 on 5/13/2022.
//

#include "Feature.h"

float util::ConfusionMatrix::accuracy() const {
    return float(this->truePos + this->trueNeg) / float(this->truePos + this->trueNeg + this->falsePos + this->falseNeg);
}