#include "wordle_game.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

WordleGame::WordleGame() {
    words_ = CreateWordsVector("/Users/rohan_v/Documents/GitHub/WorldleGame/example-data/word-list.dat");
    correct_word_ = GenerateRandomWord(words_);
}

void WordleGame::CommenceGame() {
    int current_try = 1;
    bool winning_game = false;
    std::string previous_guess = "_ _ _ _ _";
    while (current_try <= kMaxAttempts) {
        std::cout << "==================" << "\n";;
        std::cout << "Current Attempt: " << current_try << "\n";; 
        std::cout << previous_guess << "\n";;
        std::cout << "\n";

        std::string input;
        std::cin >> input;
        
        if (ToLowerCase(input) == correct_word_) {
            std::cout << "Nice job" << std::endl; 
            winning_game = true;
            break;
        } else {
            if (ValidComparableString(input)) {
                previous_guess = CompareInputWord(input);
            }
            current_try++;
        }
    }   
    std::cout << correct_word_ << std::endl;
}

std::string WordleGame::GetCorrectWord() {
    return correct_word_;
}

int WordleGame::GetMaxAttempts() {
    return kMaxAttempts;
}

std::vector<std::string> WordleGame::CreateWordsVector(std::string file_name) {
    std::ifstream ifs(file_name);
    std::vector<std::string> words;
    std::string s;
    if (!ifs.is_open()) {
        throw std::invalid_argument("Bad File");
    }

    while (ifs >> s) {
        words.push_back(ToLowerCase(s));
    }
    return words;
}

std::string WordleGame::GenerateRandomWord(std::vector<std::string> words) {
    // int random_number = rand() % words.size();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distributionInteger(0, words.size()); 

    return words.at(distributionInteger(generator));
}

std::string ToLowerCase(std::string input) {
    if (input == "" || input.size() == 0) {
        return "";
    }
    std::string new_string = "";
    for (unsigned int i = 0; i < input.size(); i++) {
        new_string += tolower(input.at(i));
    }
    return new_string;
}

std::string WordleGame::CompareInputWord(std::string input) {
    std::string comparison = "";
    for (unsigned int i = 0; i < correct_word_.size(); i++) {
        // character is right and in the same position
        char c = input.at(i);
        if (CharacterChecker(c, i) == 0) {
            if (i != correct_word_.size() - 1) {
                comparison.push_back(c);
                comparison += " ";
            } else {
                comparison.push_back(c);
            }
        } else if (CharacterChecker(c, i) == 1) {
            if (i != correct_word_.size() - 1) {
                comparison.push_back(std::toupper(c));
                comparison += " ";
            } else {
                comparison.push_back(std::toupper(c));
            }
        } else {
            if (i != correct_word_.size() - 1) {
                comparison.push_back(std::toupper('_'));
                comparison += " ";
            } else {
                comparison.push_back(std::toupper('_'));
            }
        }
    }
    return comparison;
}

bool WordleGame::ValidComparableString(std::string input) {
    return (input.size() == correct_word_.size());
}

int WordleGame::CharacterChecker(char c, unsigned int index) {
    if (correct_word_.at(index) == c) {
        return 0;
    }

    for (unsigned int i = 0; i < correct_word_.size(); i++) {
        if (correct_word_.at(i) == c) {
            return 1;
        }
    }
    return 2;
}