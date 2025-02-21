#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> keywords;
    string current_word= "";

    rawWords=convToLower(rawWords); //storing keywords in common case (lowercase)

    for (size_t i=0;i<rawWords.length();i++)
    {
        char character = rawWords[i];
        //checking if the character is alphanumeric
        if ((character>='a' && character<='z') || (character>='0' && character<='9'))
        {
            current_word+=character;
        }
        else if (current_word != "") //additional condition just to be extra sure
        {
            if (current_word.length()>=2)
            {
                keywords.insert(current_word);
            }

            //reseting current word to an empty string for next iteration
            current_word= "";
        }
    }
    if(current_word!=""){
      keywords.insert(current_word);
    }
    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
