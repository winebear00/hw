#ifndef BOOK_H
#define BOOK_H
#include <iostream> 
#include <string>
#include <set>
#include <vector> 
#include "product.h"
//artributes: category, name, price, quantity, ISBN number, author
class Book : public Product {
    public:
    Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
    ~Book(); 
    std::set<std::string> keywords() const; 
    std::string displayString() const; 
    std::string getauthor() const; 
    std::string getisbn() const; 
    void dump(std::ostream& os) const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    private:
    std::string isbn_; 
    std::string author_; 
};


#endif 