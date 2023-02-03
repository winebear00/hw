#include <iostream>
#include <string>
#include <iomanip>
#include "clothing.h"
#include "product.h"
#include <set>
#include "util.h"


using namespace std;  
    
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
    Product (category, name, price, qty)
{
    size_=size;
    brand_=brand; 
}

Clothing::~Clothing()
{

} 

//return the keywords that this product should contain 
std::set<std::string> Clothing::keywords() const
{
    set<string> newset;  
    set<string> brandset=parseStringToWords(brand_);
    set<string> nameset=parseStringToWords(name_);
    set<string> combine=setUnion(brandset, nameset);
    newset=setUnion(newset, combine);
    return newset; 
}

std::string Clothing::displayString() const
{
    string message=""; 
    message=name_+"\n";
    message="Size: "+size_+" "+"Brand: "+brand_+"\n";
    message=to_string(price_)+" "+to_string(qty_)+" left."+"\n"; 
    return message; 
}

std::string Clothing::getsize() const
{
    return size_; 
}

std::string Clothing::getbrand() const
{
    return brand_; 
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" <<size_<<"\n"<<brand_<<endl;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
    int size=0;
    int searchTermSize=searchTerms.size();
    set<string> k=keywords();
    vector<string>::iterator it;
    for (it=searchTerms.begin(); it!=searchTerms.end(); ++it)
    {
        if (k.find(*it)!=k.end())
        {
            size ++; 
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