#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

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
        end = input.find_first_of("., ", begin);
        end = (end == std::string::npos) ? input.size() : end;
        return *this;
    }

    std::string item() {
        return input.substr(begin, end-begin);
    }
};

int main(int argc, char* argv[])
{
    if (argc != 2)
        std::cerr << argv[0] << " filename" << std::endl;

    std::ifstream f(argv[1]);
    if (!f)
        std::cerr << "Couldn't open '" << argv[1] << "' for reading : "
                  << std::strerror(errno) << std::endl;

    std::string text((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
    Lexer lexer{text};

    std::map<std::string, int> word_counts;
    while (lexer.next_item()) {
        ++word_counts[lexer.item()];
    }

    for (const auto& word_count : word_counts) {
        std::cout << word_count.first << ": " << word_count.second << '\n';
    }
    std::cout << std::flush;

    return 0;
}
