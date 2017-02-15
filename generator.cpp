#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "token.h"

const std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
                         "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "
                         "veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
                         "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "
                         "velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "
                         "occaecat cupidatat non proident, sunt in culpa qui officia deserunt "
                         "mollit anim id est laborum.";

int main()
{
    auto input = std::stringstream{text};

    Token prefix;
    input >> prefix;

    const Token start_word = prefix;

    std::unordered_map<Token, std::vector<Token>> prefix_suffixes;

    for (Token suffix; input >> prefix; prefix = suffix) {
        prefix_suffixes[prefix].push_back(suffix);
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
