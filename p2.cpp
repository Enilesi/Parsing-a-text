#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

class Word {
    private:
        std::string word;
    public:
        Word(const std::string& w) : word(w) {}
        std::string getWord() const { return word; }
};

class Sentence {
    private:
        std::string sentence;
    public:
        Sentence(const std::string& sen) : sentence(sen) {}
        std::string getSentence() const { return sentence; }
};

class Character {
    private:
        char character;
    public:
        Character(const char c) : character(c) {}
        char getCharacter() const { return character; }
};

class ProcessTexts {
    private:
        std::string text;
    public:
        void inputText() {
            std::cout << "Enter the text: " << std::endl;
            std::getline(std::cin, text);
        }
        std::string get_text() const { return text; }
};

class ProcessSentences {
    private:
        std::vector<Sentence> sentences;
        std::string sentenceDelimiters = ".!?";

        void delWhitespAtBegining(std::string &currentSentence) {
            currentSentence.erase(0, currentSentence.find_first_not_of(' '));
        }

        void deleteUnecesarySpaces(std::string &currentSentence) {
            std::string::iterator new_end = 
            std::unique(currentSentence.begin(), currentSentence.end(),
            [=](char lhs, char rhs){ return (lhs == rhs) && (lhs == ' '); });
            currentSentence.erase(new_end, currentSentence.end());
            delWhitespAtBegining(currentSentence);
        }

    public:
        void processTextIntoSentences(const std::string &text) {
            std::string currentSentence;
            for (char c : text) {
                currentSentence += c;
                if (sentenceDelimiters.find(c) != std::string::npos) {
                    deleteUnecesarySpaces(currentSentence);
                    sentences.push_back(Sentence(currentSentence));
                    currentSentence.clear();
                }
            }
            if (!currentSentence.empty()) {
                deleteUnecesarySpaces(currentSentence);
                sentences.push_back(Sentence(currentSentence));
            }
        }

        std::vector<Sentence> getSentences() const { return sentences; }

        int countSentences() const { return sentences.size(); }
};

class ProcessWords {
    private:
        std::vector<Word> words;
        std::string wordDelimiters = " .!?#%&*+=-_{}[]'\"\n/()";

        void deleteDelim(std::string &currentWord) {
            if (!currentWord.empty() && wordDelimiters.find(currentWord.back()) != std::string::npos) {
                currentWord.erase(currentWord.size() - 1);
            }
        }

    public:
        void processSentenceIntoWords(const std::vector<Sentence> &sentences) {
            for (const auto& sentence : sentences) {
                std::string currentWord;
                std::string sentenceText = sentence.getSentence();
                for (char c : sentenceText) {
                    if (wordDelimiters.find(c) == std::string::npos) {
                        currentWord += c;
                    } else {
                        if (!currentWord.empty()) {
                            deleteDelim(currentWord);
                            words.push_back(Word(currentWord));
                            currentWord.clear();
                        }
                    }
                }
                if (!currentWord.empty()) {
                    deleteDelim(currentWord);
                    words.push_back(Word(currentWord));
                }
            }
        }

        std::vector<Word> getWords() const { return words; }

        int countWords() const { return words.size(); }
};

class ProcessCharacters {
    private:
        std::vector<Character> characters;

    public:
        void processSentencesIntoCharacters(const std::vector<Sentence> &sentences) {
            for (const auto& sentence : sentences) {
                std::string sentenceText = sentence.getSentence();
                for (char c : sentenceText) {
                    characters.push_back(Character(c));
                }
            }
        }

        std::vector<Character> getCharacters() const { return characters; }

        int countCharacters() const { return characters.size(); }
};

class Statistics {
    public:
        double averageWordLength(const std::vector<Word> &words) const {
            int totalLength = 0;
            for (const auto& word : words) {
                totalLength += word.getWord().length();
            }
            return words.empty() ? 0.0 : static_cast<double>(totalLength) / words.size();
        }

        void mostRecurredWord(const std::vector<Word> &words) const {
            std::unordered_map<std::string, int> wordCount;
            for (const auto& word : words) {
                wordCount[word.getWord()]++;
            }

            std::string mostCommonWord;
            int maxCount = 0;
            for (const auto& entry : wordCount) {
                if (entry.second > maxCount) {
                    maxCount = entry.second;
                    mostCommonWord = entry.first;
                }
            }
            std::cout << "Most recurred word: " << mostCommonWord << " (occurrences: " 
                      << maxCount << ")" << std::endl;
        }

        void mostRecurredLetter(const std::vector<Character> &characters) const {
            std::unordered_map<char, int> letterCount;
            for (const auto& character : characters) {
                char c = character.getCharacter();
                if (isalpha(c)) {
                    letterCount[tolower(c)]++;
                }
            }

            char mostCommonLetter = '\0';
            int maxCount = 0;
            for (const auto& entry : letterCount) {
                if (entry.second > maxCount) {
                    maxCount = entry.second;
                    mostCommonLetter = entry.first;
                }
            }
            std::cout << "Most recurred letter: " << mostCommonLetter << " (occurrences: " 
                      << maxCount << ")" << std::endl;
        }
};

class Menu {
    private:
        ProcessTexts textProcessor;
        ProcessSentences sentenceProcessor;
        ProcessWords wordProcessor;
        ProcessCharacters characterProcessor;
        Statistics statistics;
        bool isTextAdded = false;
        bool isTextProcessed = false;

    public:
        void displayMenu() {
            std::cout << std::endl;
            std::cout << "Menu:" << std::endl;
            std::cout << "0 - Exit program" << std::endl;
            std::cout << "1 - Add text" << std::endl;
            std::cout << "2 - Process sentences, characters, and words" << std::endl;
            std::cout << "3 - Display number of sentences" << std::endl;
            std::cout << "4 - Display number of words" << std::endl;
            std::cout << "5 - Display number of characters" << std::endl;
            std::cout << "6 - Display the most recurrent word" << std::endl;
            std::cout << "7 - Display the most recurrent letter" << std::endl;
            std::cout << "8 - Display the average length of a word" << std::endl;
            std::cout << "9 - Display full text" << std::endl;
            std::cout << "10 - Display words" << std::endl;
            std::cout << "11 - Display sentences" << std::endl;
            std::cout << "12 - Display characters" << std::endl;
            std::cout << std::endl;
        }

        void displayFullText() {
            std::cout << "Text introduced: " << textProcessor.get_text() << std::endl;
        }

        void displayWords() {
            for (const auto& word : wordProcessor.getWords()) {
                std::cout << word.getWord() << std::endl;
            }
        }

        void displaySentences() {
            for (const auto& sentence : sentenceProcessor.getSentences()) {
                std::cout << sentence.getSentence() << std::endl;
            }
        }

        void displayCharacters() {
            for (const auto& character : characterProcessor.getCharacters()) {
                std::cout << character.getCharacter() << std::endl;
            }
        }

        void executeOption(int option) {
            switch (option) {
                case 0:
                    std::cout << "Exiting program." << std::endl;
                    break;
                case 1:
                    textProcessor.inputText();
                    isTextAdded = true;
                    isTextProcessed = false;
                    break;
                case 2:
                    if (!isTextAdded) {
                        std::cout << "Add a text first." << std::endl;
                    } else {
                        sentenceProcessor.processTextIntoSentences(textProcessor.get_text());
                        wordProcessor.processSentenceIntoWords(sentenceProcessor.getSentences());
                        characterProcessor.processSentencesIntoCharacters(sentenceProcessor.getSentences());
                        isTextProcessed = true;
                        std::cout << "Text processed successfully." << std::endl;
                    }
                    break;
                case 3:
                    if (isTextProcessed) {
                        displayFullText();
                        std::cout << "Number of sentences: " << sentenceProcessor.countSentences() 
                                  << std::endl;
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 4:
                    if (isTextProcessed) {
                        displayFullText();
                        std::cout << "Number of words: " << wordProcessor.countWords() << std::endl;
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 5:
                    if (isTextProcessed) {
                        displayFullText();
                        std::cout << "Number of characters: " << characterProcessor.countCharacters() 
                                  << std::endl;
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 6:
                    if (isTextProcessed) {
                        displayFullText();
                        statistics.mostRecurredWord(wordProcessor.getWords());
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 7:
                    if (isTextProcessed) {
                        displayFullText();
                        statistics.mostRecurredLetter(characterProcessor.getCharacters());
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 8:
                    if (isTextProcessed) {
                        displayFullText();
                        std::cout << "Average word length: " 
                                  << statistics.averageWordLength(wordProcessor.getWords()) << std::endl;
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 9:
                    if (isTextProcessed) {
                        displayFullText();
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 10:
                    if (isTextProcessed) {
                        displayWords();
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 11:
                    if (isTextProcessed) {
                        displaySentences();
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                case 12:
                    if (isTextProcessed) {
                        displayCharacters();
                    } else {
                        std::cout << "Process the text first." << std::endl;
                    }
                    break;
                default:
                    std::cout << "Invalid option. Try again!" << std::endl;
                    break;
            }
        }

        void displayWelcome(){
            std::cout << std::endl;
            std::cout << "Hello!:)) This is my program:" << std::endl;
        }

        void run() {
            int option;
            displayWelcome();
            do {
                displayMenu();
                std::cout << "Select an option: ";
                std::cin >> option;
                std::cin.ignore();
                executeOption(option);
            } while (option != 0);
        }
};

int main() {
    Menu menu;
    menu.run();
    return 0;
}
