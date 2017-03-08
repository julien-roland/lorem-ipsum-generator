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

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " n" << std::endl;
        std::exit(1);
    }

    int nword = std::atoi(argv[1]);

    auto input = std::stringstream{text};

    Token prefix;
    input >> prefix;

    const Token start_word = prefix;

    std::unordered_map<Token, std::vector<Token>> prefix_suffixes;

    for (Token suffix; input >> suffix; prefix = suffix) {
        prefix_suffixes[prefix].push_back(suffix);
    }

    std::srand(std::time(0));

    prefix = start_word;
    std::cout << prefix;
    for (int i = 0 ; i < nword || prefix != "."; ++i) {
        const auto& suffixes = prefix_suffixes[prefix];
        prefix = suffixes.at(std::rand() % suffixes.size());
        if (prefix.length() > 1)
            std::cout << ' ';
        std::cout << prefix;
    }
    std::cout << std::endl;

    return 0;
}
