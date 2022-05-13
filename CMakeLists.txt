cmake_minimum_required(VERSION 3.16)
project(Tweet-Sentiment-Analyser)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tweet-Sentiment-Analyser main.cpp Utilities/StopWords.h Tweet/Tweet.cpp Tweet/Tweet.h)
