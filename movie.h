#ifndef MOVIE_H
#define MOVIE_H
#include <iostream> 
#include <string>
#include <set>
#include <vector> 
#include "product.h"

//artributes: category, name, price, quantity, ISBN number, author
class Movie : public Product {
    public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie(); 
    std::set<std::string> keywords() const; 
    std::string displayString() const; 
    std::string getgenre() const; 
    std::string getrating() const; 
    void dump(std::ostream& os) const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    private:
    std::string genre_; 
    std::string rating_; 
};


#endif 