#include <iostream>
#include <string>
#include <iomanip>
#include "movie.h"
#include <set>
#include "util.h"
#include "product.h"
#include <sstream>

using namespace std;  
    
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
    Product (category, name, price, qty)
{
    genre_=genre;
    rating_=rating;  
}

Movie::~Movie()
{

} 

//return the keywords that this product should contain 
std::set<std::string> Movie::keywords() const
{
    set<string> newset;  
    newset.insert(convToLower(genre_)); //insert keyword genre 
    set<string> nameset=parseStringToWords(name_); //get the movie name keywords set  
    newset=setUnion(newset, nameset); //combine two sets 
    return newset; 
}

std::string Movie::displayString() const
{
    string message=""; 
    stringstream ss; 
    ss << fixed << setprecision(2) << price_;
    string p = ss.str();
    message += name_+"\n";
    message += "Genre: "+genre_+" "+"Rating: "+rating_+"\n";
    message += p +" "+to_string(qty_)+" left."+"\n"; 
    return message; 
}

std::string Movie::getgenre() const
{
    return genre_; 
}

std::string Movie::getrating() const
{
    return rating_; 
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" <<genre_<<"\n"<<rating_<<endl;

}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    int size=0;
    int searchTermSize=searchTerms.size();
    set<string> k=keywords();
    vector<string>::iterator it;
    for (it=searchTerms.begin(); it!=searchTerms.end(); ++it)
    {
        if (k.find(*it)!=k.end())
        {
            size++;
        }
        
    }
    if (size==searchTermSize)
    {
        return true; 
    }
    else 
    {
        return false; 
    }

}  