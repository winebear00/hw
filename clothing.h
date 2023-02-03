#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream> 
#include <string>
#include <set>
#include <vector> 
#include "product.h"


//artributes: category, name, price, quantity, ISBN number, author
class Clothing : public Product {
    public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    ~Clothing(); 
    std::set<std::string> keywords() const; 
    std::string displayString() const; 
    std::string getsize() const; 
    std::string getbrand() const; 
    void dump(std::ostream& os) const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    private:
    std::string size_; 
    std::string brand_; 
};


#endif 