#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <map> 
#include <vector>
#include "mydatastore.h"
#include "util.h"
#include "datastore.h"
#include "product.h"

using namespace std; 

MyDataStore::~MyDataStore()
{
    
}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
    set<string> keywords = p->keywords();
    for(set<string>::iterator it = keywords.begin(); it != keywords.end(); it++){
        product_[*it].insert(p);
    }
    vector<Product*>::iterator it=find(allproduct_.begin(), allproduct_.end(), p);
    if (it==allproduct_.end())
    {
        allproduct_.push_back(p); //add the product to the vector 
    }

}


/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u)
{
    string name=u->getName();
    users_.insert(make_pair(name, u));
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    vector<string>::iterator it; 
    set<Product*> proset=product_[terms[0]]; 
    if (type==0)
    {
        for (it=terms.begin(); it!=terms.end(); ++it)
        {
            set<Product*> proset2=product_[*it];
            proset=setIntersection(proset, proset2);
        }
        set<Product*>::iterator it2;
        vector<Product*> result;
        for (it2=proset.begin(); it2!=proset.end(); ++it2)
        {
            result.push_back(*it2); 
        }
        return result; 
        
    }
    else 
    {
        for (it=terms.begin(); it!=terms.end(); ++it)
        {
            set<Product*> proset2=product_[*it];
            proset=setUnion(proset, proset2);
        }
        set<Product*>::iterator it2;
        vector<Product*> result;
        for (it2=proset.begin(); it2!=proset.end(); ++it2)
        {
            result.push_back(*it2); 
        }
        return result; 
    }
    
}


/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
    vector<Product*>::iterator it;
    map<string, User*>::iterator it2; 
    for (it=allproduct_.begin(); it!=allproduct_.end(); ++it)
    {
        (*it)->dump(ofile); 
    }
    for (it2=users_.begin(); it2!=users_.end(); ++it2)
    {
        (it2->second)->dump(ofile);
    }
  
}
// std::vector<Product*> allproduct_; 
//virtual void dump(std::ostream& os) const;
//std::map<std::string, User*> users_; 

void MyDataStore::addToCart(string user, Product* p)
{
    vector<Product*> list;
    list.push_back(p);
    cart_.insert(make_pair(user, list)); 
}

void MyDataStore::viewCart(std::string user)
{
    int number=0; //show the order 
    vector<Product*> p=cart_[user];
    vector<Product*>::iterator it; 
    for (it=p.begin(); it!=p.end(); ++it)
    {
        number++; 
        cout<<"Item "<<number<<endl;
        cout<<(*it)->displayString()<<endl;
        cout<<endl; 
    }

}

void MyDataStore::buyCart(std::string user)
{
    //find out the user's balance
    double balance=users_[user]->getBalance();
    vector<Product*> p=cart_[user];
    vector<Product*>::iterator it;
    for (it=p.begin(); it!=p.end(); ++it)
    {
        if (balance>= ((*it)->getPrice()) && (*it)->getQty()>0) 
        {
            balance-=(*it)->getPrice();
            (*it)->subtractQty(1);
            //p.erase(*it); 
        }
    }

}

int MyDataStore::getCartSize (string name)
{
    vector<Product*> p=cart_[name];
    return p.size(); 
}
