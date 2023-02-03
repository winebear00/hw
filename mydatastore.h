#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map> 
#include "product.h"
#include "user.h"
#include "datastore.h"


class MyDataStore: public DataStore {
    
    public:
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string user, Product* p);
    void viewCart(std::string user);
    void buyCart(std::string user); 

    
    //get function 
    int getCartSize (std::string name); //get the size 

    private:
    std::map<std::string, User*> users_; 
    std::map<std::string, std::set<Product*>> product_; 
    std::map<std::string, std::vector<Product*>> cart_; 
    std::vector<Product*> allproduct_; 
    

};



#endif