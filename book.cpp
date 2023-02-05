#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <set>
#include "book.h"
#include "util.h"
#include "product.h"
using namespace std;


    
Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
    Product (category, name, price, qty)
{
    isbn_=isbn;
    author_=author; 
}

Book::~Book()
{

} 

//return the keywords that this product should contain 
std::set<std::string> Book::keywords() const
{
    std::set<std::string> newset; 
    newset.insert(convToLower(isbn_));  
    std::set<std::string> authset=parseStringToWords(author_);
    std::set<std::string> nameset=parseStringToWords(name_);
    std::set<std::string> combine=setUnion(authset, nameset);
    newset=setUnion(newset, combine);
    return newset; 
}

std::string Book::displayString() const
{
    stringstream ss;
    ss<<fixed<<setprecision(2)<<price_;
    string p=ss.str(); 
    std::string message=""; 
    message += name_+"\n";
    message += "Author: "+author_+" "+"ISBN: "+isbn_+"\n";
    message += p +" "+to_string(qty_)+" left."+"\n"; 
    return message; 
}

std::string Book::getauthor() const
{
    return author_; 
}

std::string Book::getisbn() const
{
    return isbn_; 
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" <<isbn_<<"\n"<<author_<<endl;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
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

//std::set<std::string> keywords() const; 