#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>

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
    //book author's name, book's ISBN number, clothes brand, movie's genre
    //punctuation, key words needs to be at least 2 or more than 2 words 
    //ispunct (char) return boolean 
    
    string word;
    stringstream ss(convToLower(rawWords));
    set<string> keyWords;
    while (ss>>word) //parse each word from the rawWords 
    {
        //cout<<"print word= " <<word<<endl;
        bool haspunc=false; 
        for (size_t i=0; i<word.length(); i++) //check the punctuation 
        {
            haspunc=false; 
            if (ispunct(word[i]))
            {
                haspunc=true; 
                string newWord=word.substr(0, i); 
                if (newWord.length()>=2)
                {
                    keyWords.insert(newWord); 
                }
                word=word.substr(i+1); 
                i = 0;
                //cout<<"print the rest word= "<<word<<endl;
            }
        }
        if (haspunc==false && word.length()>=2)
        {
            keyWords.insert(word); 
        }
    }
    return keyWords;
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
