cmake_minimum_required(VERSION 3.16)
project(Tweet-Sentiment-Analyser)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tweet-Sentiment-Analyser main.cpp Utilities/StopWords.h Utilities/Tweet/Tweet.cpp Utilities/Tweet/Tweet.h Utilities/pipelines.cpp Utilities/pipelines.h)
