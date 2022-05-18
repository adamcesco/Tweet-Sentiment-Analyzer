#include <iostream>
#include <fstream>
#include "./Classifier/Classifier.h"

int main() {
    std::vector<util::Tweet> trainingTweets;
    {
        std::ifstream trainingFile("../data/train_dataset_20k.csv");
        if (!trainingFile.is_open())
            throw std::invalid_argument("Error in \"int main()\" | Could not open training dataset file");

        std::string row;
        getline(trainingFile, row);
        while (trainingFile.good()) {
            getline(trainingFile, row);

            util::Tweet current;
            current.readTweetTrainer(row);
            try { current.clean(); }
            catch (const std::invalid_argument& e){ continue; }
            if (!current.empty() && current.identified()) { trainingTweets.push_back(current); }
        }
    }

    Trainer trainer;
    trainer.trainWith(trainingTweets);

    //------------------------------------

    std::vector<util::Tweet> testTweets;
    {
        std::ifstream testingFile("../data/test_dataset_10k.csv");
        if (!testingFile.is_open())
            throw std::invalid_argument("Error in \"int main()\" | Could not open testing dataset file");

        std::string row;
        getline(testingFile, row);
        while (testingFile.good()) {
            getline(testingFile, row);

            util::Tweet current;
            current.readTweetTester(row);
            try { current.clean(); }
            catch (const std::invalid_argument& e){}
            if (current.identified()) { testTweets.push_back(current); }
        }
    }

    std::unordered_map<std::string, util::SENTI> answerKey;
    {
        std::ifstream answerFile("../data/test_dataset_sentiment_10k.csv");
        if (!answerFile.is_open())
            throw std::invalid_argument("Error in \"int main()\" | Could not open testing dataset answer key file");

        std::string senti;
        std::string ID;
        getline(answerFile, senti, ',');
        getline(answerFile, ID);
        while (answerFile.good()) {
            getline(answerFile, senti, ',');
            getline(answerFile, ID);

            while(!ID.empty() && !std::isdigit(ID.back()))
                ID.pop_back();

            answerKey[ID] = util::SENTI(senti[0]);
        }
    }

    Classifier classifier(&trainer, &testTweets);
    classifier.biwordClassify();
    classifier.wordClassify();

    util::ConfusionMatrix cm = Classifier::readConfusionMatrix(classifier, answerKey);
    std::cout << "Classifier Statistics:" << std::endl;
    std::cout << "\tClassifier Accuracy: " << cm.accuracy() << std::endl;
    std::cout << "\tClassifier Recall: " << cm.recall() << std::endl;
    std::cout << "\tClassified correctly: " << cm.truePos + cm.trueNeg << std::endl;
    std::cout << "\tClassified incorrectly: " << cm.falseNeg + cm.falsePos << std::endl;
    std::cout << "\tTotal amount of tweets: " << cm.conditionPos + cm.conditionNeg << std::endl;

    return 0;
}