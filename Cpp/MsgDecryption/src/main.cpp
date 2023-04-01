#include <iostream>
#include <sstream>
#include <algorithm>

std::string decryptMsg( const std::string & msg )
{
    std::string res;
    std::string errStr = "Error! Incorrect string";

    if ( std::count(msg.begin(), msg.end(), ' ') ) // if msg has spaces
        throw errStr; 

    std::stringstream sst(msg);

    char c;
    while ( sst >> c ) // take char
    {   
        if ( c == '[' ) // handle chars inside [ ]
        {
            char nextChar = sst.peek(); // peek() looks at next char, doesn't extract it
            if ( nextChar == ']' )
            {
                sst >> nextChar; // extract char
                continue;
            }

            if ( std::isdigit(nextChar) )
            {
                int num;
                sst >> num;

                if (num > 0) // number should be positive
                {
                    std::string substr;

                    char substrChar;
                    while ( sst >> substrChar && substrChar != ']' )
                    {
                        if ( std::isupper(substrChar) )
                            substr.append(1, substrChar);
                        else
                            throw errStr;
                    }

                    if ( !substr.empty()       // substr after number shouldn't be empty
                        && substrChar == ']' ) // and last char (after substr) should be ']'
                    {
                        for (int i = 0; i < num; ++i)
                        {
                            res.append( substr );
                        }
                    }
                    else
                        throw errStr;
                }
                else
                    throw errStr;
            }
            else
                throw errStr;
        }

        else // handle chars outside [ ]
        {
            if ( std::isupper(c) )
                res.append(1, c);
            else
                throw errStr;
        }
    }

    return res;
}

int main()
{
    std::cout << "\nEnter encrypted message without spaces: ";

    std::string msg;
    std::getline(std::cin, msg);

    try
    {
        std::string result = decryptMsg(msg);
        std::cout << "\nDecrypted message: " << result << std::endl;
    }
    catch( const std::string & errStr )
    {
        std::cerr << std::endl << errStr << std::endl;
    }

	return 0;
}

