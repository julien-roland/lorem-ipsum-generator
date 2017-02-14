#include <string>
#include <iterator>
#include <iostream>
#include <map>
#include <fstream>
#include <cstring>

#include "token.h"

void count(std::ifstream &ifs)
{
    std::map<std::string, int> word_counts;

    Token token;
    token.reserve(50);
    while (ifs >> token)
        ++word_counts[token];

    for (const auto& word_count : word_counts)
        std::cout << word_count.first << ": " << word_count.second << '\n';

    std::cout << std::flush;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << argv[0] << " filename" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "Couldn't open '" << argv[1] << "' for reading : "
                  << std::strerror(errno) << std::endl;
        return 1;
    }

    count(ifs);

    return 0;
}
