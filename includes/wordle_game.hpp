#ifndef WORDLEGAME_HPP
#define WORDLEGAME_HPP

#include <string>
#include <vector>

class WordleGame {
    public:
    WordleGame();
    std::vector<std::string> CreateWordsVector(std::string file_name);
    std::string GenerateRandomWord(std::vector<std::string> words);
    std::string CompareInputWord(std::string input);
    bool ValidComparableString(std::string input);
    std::string GetCorrectWord();
    int GetMaxAttempts();
    int CharacterChecker(char c, unsigned int index);
    void CommenceGame();

    private:
    std::vector<std::string> words_;
    std::string correct_word_;
    const int kMaxAttempts = 6;
};

std::string ToLowerCase(std::string input);




#endif