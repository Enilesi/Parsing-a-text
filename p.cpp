#include <iostream>
#include <algorithm>
#include <string>
#include <vector>




class Search {
private:
    std::string delimiters = std::string(" .,?!\n;:\"'{}[]()_-+=*&^%$#");
public :
    std::string lowerTheText(const std::string& text) {
        std::string lower_text = text;
        std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(), ::tolower);
        return lower_text;
    }

    void transformWordAndText(std::string& text, std::string& word) {
        text = lowerTheText(text);
        word = lowerTheText(word);
    }

    bool isDelimiter(char c ){
    return (delimiters.find(c) != std::string::npos);
    }

    bool isLeftBoundary(const std::string& s, size_t pos){
        return pos == 0 ||isDelimiter(s[pos-1]);
    }

    bool isRightBoundary(const std::string& s, size_t pos){
        return pos==s.size() ||isDelimiter(s[pos]);
    }


    std::vector<int> findWordPositions(const std::string& text, const std::string& word) {
        std::vector<int> positions;
        std::string loweredText = text;
        std::string loweredKeyword = word;
        transformWordAndText(loweredText, loweredKeyword);

        size_t pos = loweredText.find(loweredKeyword, 0);
    
        while (pos != std::string::npos) {
            size_t word_end =pos + word.size();
            size_t next_pos = pos+1;
            if(isLeftBoundary(loweredText,pos) && isRightBoundary(loweredText,word_end)){
                next_pos = word_end;
                positions.push_back(pos);

            }
            
            pos = loweredText.find(loweredKeyword, next_pos);
        }
        return positions;
    }

    void printWordPositions(const std::string& text, const std::string& word) {
        std::vector<int> positions = findWordPositions(text, word);
        switch (positions.size()) {
            case 0:
                std::cout << word << " is not part of the introduced text" << std::endl;
                break;
            case 1:
                std::cout << word << " was found at the position: "<<positions[0];
                break;
            default:
                std::cout << word << " was found at positions: ";
                for (int pos : positions) {
                    std::cout << pos << " ";
                }
                std::cout << std::endl;
                break;
        }

    }

};


int main() {
    std::string text, searchedWord;
    std::cout << "Add a text: \n";
    std::getline(std::cin, text);
    std::cout << "\nAdd a word: \n";
    std::cin >> searchedWord;
    std::cout << "\n";

    auto search = Search();
    search.printWordPositions(text, searchedWord);

    return 0;
}
