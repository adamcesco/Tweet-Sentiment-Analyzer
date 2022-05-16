cmake_minimum_required(VERSION 3.16)
project(Tweet-Sentiment-Analyser)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tweet-Sentiment-Analyser main.cpp utilities/StopWords.h utilities/Tweet/Tweet.cpp utilities/Tweet/Tweet.h utilities/Pipelines/pipelines.cpp utilities/Pipelines/pipelines.h external/porter2_stemmer.cpp external/porter2_stemmer.h utilities/Feature/Feature.cpp utilities/Feature/Feature.h Trainer/Trainer.cpp Trainer/Trainer.h Classifier/Classifier.cpp Classifier/Classifier.h)
