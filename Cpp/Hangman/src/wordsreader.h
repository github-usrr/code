#pragma once

#include <vector>
#include <string>

namespace HangmanGame
{
    class WordsReader
    {
    public:
        static std::vector<std::string> read();
    };
}