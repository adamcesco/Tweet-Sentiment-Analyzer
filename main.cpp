#include <iostream>
#include <fstream>
#include "./Classifier/Classifier.h"

int main() {
    Trainer trainer;

    std::vector<util::Tweet> trainingTweets;
    {
        std::ifstream trainingFile("../data/train_dataset_20k.csv");
        if (!trainingFile.is_open())
            throw std::invalid_argument("Error in \"int main()\" | Could not open training dataset file");

        bool firstRow = true;
        while (trainingFile.good()) {
            std::string row;
            getline(trainingFile, row);

            if(firstRow == true) {
                firstRow = false;
                continue;
            }

            util::Tweet current;
            current.readTweetTrainer(row);
            current.clean();
            trainingTweets.push_back(current);
        }
    }

    trainer.countWordSentiFrom(trainingTweets);
    trainer.calcWordSentiAcc(trainingTweets);
    trainer.cleanOutliers();

    //------------------------------------

    std::vector<util::Tweet> testTweets;
    {
        std::ifstream testingFile("../data/test_dataset_10k.csv");
        if (!testingFile.is_open())
            throw std::invalid_argument("Error in \"int main()\" | Could not open testing dataset file");

        bool firstRow = true;
        while (testingFile.good()) {
            std::string row;
            getline(testingFile, row);
            if(firstRow == true) {
                firstRow = false;
                continue;
            }

            util::Tweet current;
            current.readTweetTester(row);
            current.clean();
            testTweets.push_back(current);
        }
    }

    std::unordered_map<std::string, util::SENTI> answerKey;
    {
        std::ifstream answerFile("../data/test_dataset_sentiment_10k.csv");
        if (!answerFile.is_open())
            throw std::invalid_argument("Error in \"int main()\" | Could not open testing dataset answer key file");

        bool firstRow = true;
        while (answerFile.good()) {
            std::string senti;
            getline(answerFile, senti, ',');

            std::string ID;
            getline(answerFile, ID);

            if(firstRow == true) {
                firstRow = false;
                continue;
            }
            while(!ID.empty() && !std::isdigit(ID.back()))
                ID.pop_back();

            answerKey[ID] = util::SENTI(senti[0]);
        }
    }

    Classifier classifier(&trainer, &testTweets);
    classifier.wordBasedClassification();
    util::ConfusionMatrix cm = Classifier::readConfusionMatrix(classifier, answerKey);
    std::cout << "Classifier Statistics:" << std::endl;
    std::cout << "\tClassifier Accuracy: " << cm.accuracy() << std::endl;
    std::cout << "\tClassified correctly: " << cm.truePos + cm.trueNeg << std::endl;
    std::cout << "\tClassified incorrectly: " << cm.falseNeg + cm.falsePos << std::endl;
    std::cout << "\tTotal amount of tweets: " << cm.conditionPos + cm.conditionNeg << std::endl;

    return 0;
}