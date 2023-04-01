#include "wordsreader.h"

#include <fstream>

namespace HangmanGame
{
    std::vector<std::string> WordsReader::read()
    {
        std::vector<std::string> words;

        const int wordsCount = 100;
        words.reserve( wordsCount );

        std::ifstream infile("files/100-english-common-words.txt");
        if ( !infile.is_open() )
        {
            return {};
        }

        std::string word;
        while ( infile >> word )
        {
            words.emplace_back( word );
        }
        infile.close();

        return words;
    }
}
