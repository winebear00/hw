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
    map<string, User*>::iterator it1;
    vector<Product*>::iterator it2; 
    for (it1=users_.begin(); it1!=users_.end(); ++it1)
    {
        delete it1->second; 
    }
    for (it2=allproduct_.begin(); it2!=allproduct_.end(); ++it2)
    {
        delete *it2; 
    }

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


void MyDataStore::addToCart(string user, Product* p)
{
    //check if the name in the map
    //check if the user in the users map 
    if (users_.find(user)==users_.end()) 
    {
        cout<<"Invalid request"<<endl; 
        return; 
    }
    if (cart_.find(user)!=cart_.end() && p->getQty()>0)
    {
        cart_[user].push_back(p);
    }
    else if (cart_.find(user)==cart_.end() && p->getQty()>0)
    {
        vector<Product*> list;
        list.push_back(p);
        cart_.insert(make_pair(user, list)); 
    }
}


void MyDataStore::viewCart(std::string user)
{
    if (users_.find(user)==users_.end()) 
    {
        cout<<"Invalid username"<<endl; 
        return; 
    }
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
    //std::map<std::string, User*> users_; 
    //if the user is not in the user database, do nothing 
    if (users_.find(user)==users_.end()) 
    {
        cout<<"Invalid username"<<endl; 
        return; 
    }
    vector<Product*> p=cart_[user];
    vector<Product*>::iterator it;
    vector<Product*> newcart; 
    for (it=p.begin(); it!=p.end(); ++it)
    {
        if (users_[user]->getBalance()>= ((*it)->getPrice()) && (*it)->getQty()>0) 
        {
            users_[user]->deductAmount((*it)->getPrice());
            (*it)->subtractQty(1);
            cout<<"print the balance: "<<users_[user]->getBalance()<<endl;
        }
        else
        {
            newcart.push_back(*it); 
            
        }
    }
    if (newcart.size()==0)
    {
        cout<<"buy all the products in cart, clear the cart"<<endl; 
        cart_.erase(user); 
    }
    else
    {
        cout<<"not enough money or stock"<<endl;
        p=newcart; 
    }

}

int MyDataStore::getCartSize (string name)
{
    vector<Product*> p=cart_[name];
    return p.size(); 
}
