#include <string>
#include <iterator>
#include <functional>
#include <cctype>

struct Token : public std::string {};

namespace std
{
    template<> struct hash<Token> : hash<string> {};
}

inline std::istream& operator>>(std::istream& is, Token& token)
{
    auto it = std::istreambuf_iterator<char>{is};
    auto end = std::istreambuf_iterator<char>{};

    while (it != end && std::isspace(*it))
        ++it;

    if (it == end) {
        is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        return is;
    }

    token.erase();
    if (!std::isalpha(*it)) {
        token.push_back(*it++);
    } else {
        while (it != end && std::isalpha(*it))
            token.push_back(*it++);
    }

    if (it == end)
        is.setstate(std::ios_base::eofbit);

    return is;
}
