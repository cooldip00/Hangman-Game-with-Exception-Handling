#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class InvalidInputException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid input! Please enter a single alphabetical character.";
    }
};

class LetterNotInWordException : public exception {
public:
    const char* what() const noexcept override {
        return "The guessed letter is not in the word.";
    }
};

bool isValidInput(char input) {
    return isalpha(input) && input != '\0';
}

void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void playHangman(const string& word) {
    vector<bool> guessed(word.length(), false);
    int remainingGuesses = 6;
    char guess;
    bool wordGuessed = false;

    cout << "Welcome to Hangman!" << endl;

    while (remainingGuesses > 0 && !wordGuessed) {
        displayWord(word, guessed);
        cout << "Remaining guesses: " << remainingGuesses << endl;
        cout << "Enter your guess: ";
        cin >> guess;

        try {
            if (!isValidInput(guess)) {
                throw InvalidInputException();
            }

            guess = tolower(guess);
            bool correctGuess = false;

            for (size_t i = 0; i < word.length(); ++i) {
                if (tolower(word[i]) == guess) {
                    guessed[i] = true;
                    correctGuess = true;
                }
            }

            if (!correctGuess) {
                throw LetterNotInWordException();
            }

            wordGuessed = true;
            for (bool g : guessed) {
                if (!g) {
                    wordGuessed = false;
                    break;
                }
            }
        } catch (InvalidInputException& e) {
            cout << e.what() << endl;
        } catch (LetterNotInWordException& e) {
            cout << e.what() << endl;
            --remainingGuesses;
        }
    }

    if (wordGuessed) {
        cout << "Congratulations! You guessed the word: " << word << endl;
    } else {
        cout << "Sorry, you ran out of guesses. The word was: " << word << endl;
    }
}

int main() {
    vector<string> words = {"programming", "hangman", "exception", "handling", "code"};
    srand(static_cast<unsigned int>(time(0)));
    string word = words[rand() % words.size()];

    playHangman(word);

    return 0;
}