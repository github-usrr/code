#include "core.h"
#include "wordsreader.h"

#include <random>
#include <iostream>

namespace HangmanGame
{
    void Core::exec()
    {
        // read words
        std::vector<std::string> words = std::move( WordsReader::read() );

        if ( words.empty() )
        {
            std::cout << "Error! Words haven't been read";
            return;
        }
            
        // distribution in range [0, words.size()-1]
        std::mt19937 rng( std::random_device{}() );
        std::uniform_int_distribution<std::mt19937::result_type> dist( 0, words.size()-1 );

        // get random word
        std::string word = words[ dist(rng) ];
        std::string ans(  word.length(), '_' );
        
        std::cout << "Word length is " << word.length();

        // main loop
        int attempts = 6;
        while ( ans != word && attempts )
        {
            std::cout << "\nAttempts: " << attempts;
            std::cout << "\n\nEnter char: ";
            char c;
            std::cin >> c;

            for (int i = 0; i < word.length(); ++i)
            {
                if (word[i] == c)
                    ans[i] = c;
            }

            std::cout << "\nResult: " << ans;
            --attempts;
        }

        // result
        if ( ans == word )
        {
            std::cout << "\nYou won!\n";
        }
        else
        {
            std::cout << "\nYou lost!\n";
            std::cout << "\nWord is: " << word << std::endl;
        }
    }
}