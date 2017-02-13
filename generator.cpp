#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>

const std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

struct Lexer {
    std::string::size_type begin = 0;
    std::string::size_type end = 0;

    const std::string& input;

    Lexer(const std::string& input): input(input) {}

    operator bool() { return begin < input.size(); }

    void ignore (char c) {
        while (*this && input[begin] == c)
            ++begin;
        end = begin + 1;
    }

    Lexer& next_item() {
        begin = end;
        end = begin + 1;
        if (!*this)
            return *this;
        ignore(' ');
        if (!*this)
            return *this;
        switch (input[begin]) {
            case ',':
            case '.':
                return *this;
        }
        end = text.find_first_of("., ", begin);
        end = (end == std::string::npos) ? input.size() : end;
        return *this;
    }

    std::string item() {
        return input.substr(begin, end-begin);
    }
};


int main()
{

    Lexer lexer{text};
    if (!lexer.next_item())
        return 1;
    std::string prefix = lexer.item();
    std::string start_word = prefix;

    std::map<std::string, std::vector<std::string>> prefix_suffixes;
    while (lexer.next_item()) {
        auto suffix = lexer.item();
        prefix_suffixes[prefix].push_back(suffix);
        prefix = suffix;
    }

    prefix = start_word;
    std::cout << prefix;
    std::srand(std::time(0));
    for (int i = 0 ; i < 10000000 || prefix != "."; ++i) {
        const auto& suffixes = prefix_suffixes[prefix];
        prefix = suffixes.at(std::rand() % suffixes.size());
        if (prefix.length() > 1)
            std::cout << ' ';
        std::cout << prefix;
    }
    std::cout << std::endl;

    return 0;
}
