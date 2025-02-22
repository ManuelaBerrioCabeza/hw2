#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <iomanip>

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore(){
  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); it++){
    delete it->second;
  }

  for(size_t i =0; i<products_.size(); i++){
    delete products_[i];
    
  }

}

void MyDataStore::addProduct(Product* product){
  if(product){
    products_.push_back(product);
    set<string> keywords = product->keywords();
    for(set<string>::iterator it = keywords.begin();it!=keywords.end(); it++){
      mapKeyword_[*it].insert(product);

    }
  }

}

void MyDataStore::addUser(User* user){
  if (user){
    users_[convToLower(user->getName())]=user;
  }

}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  vector<Product*> result;
  if(terms.empty()){
    return result;

  }
  set<Product*> searchResults;
  bool term1 = true;
  for(size_t i =0; i<terms.size(); i++){
    string term = convToLower(terms[i]);
    if (mapKeyword_.find(term)!=mapKeyword_.end()){
      if(term1){
        searchResults=mapKeyword_[term];
        term1 = false;
      }
      else{
        if(type==0){
          searchResults=setIntersection(searchResults, mapKeyword_[term]);
        }
        else if (type ==1){
          searchResults= setUnion(searchResults, mapKeyword_[term]);
        }
      }
    }
    else if(type==0){
      return result;
    }
  }

  for (set<Product*>::iterator it=searchResults.begin(); it != searchResults.end(); it++){
    if(*it){
    result.push_back(*it);
    }
  }
  return result;


}

void MyDataStore::addToCart(const string& username,int hit_result_index, vector<Product*>& hit_results){
  string newUsername= convToLower(username);
  if(users_.find(newUsername)==users_.end()||hit_result_index-1<0||hit_result_index-1>=(int)hit_results.size()){
    cout<<"Invalid request"<<endl;
    return;

  }
  carts_[newUsername].push_back(hit_results[hit_result_index-1]);

}

void MyDataStore::viewCart(const string& username){
  string newUsername= convToLower(username);
  if(users_.find(newUsername)==users_.end()){
    cout<<"Invalid username"<<endl;
    return;
  }
  vector<Product*>& cart = carts_[newUsername];
  for(size_t i =0; i<cart.size();i++){
    cout<<"Item "<<i+1<<endl;
    cout<<cart[i]->displayString()<<endl;

  }

}

void MyDataStore::buyCart(const string& username){
  string newUsername= convToLower(username);
  if(users_.find(newUsername)==users_.end()){
    cout<<"Invalid username"<<endl;
    return;
  }
  User* user=users_[newUsername];
  vector<Product*>& cart=carts_[newUsername];
  vector<Product*> restCart;

  for(size_t i =0; i<cart.size();i++){
    Product* product = cart[i];
    if(product && product->getQty()>0 && user->getBalance()>= product->getPrice()){
      product->subtractQty(1);
      user->deductAmount(product->getPrice());
    }
    else{
      restCart.push_back(product);
    }
  }
  cart=restCart;

}

void MyDataStore::dump(std::ostream& ofile){
  ofile<<"<products>"<<endl;
  if(products_.empty()){
    ofile<<"</products>"<<endl;
  }

  else{
    for(size_t i=0; i<products_.size(); i++){
      if(products_[i]){
        products_[i]->dump(ofile);
      }
    }
    ofile<<"</products>"<<endl;
  }
  
  ofile<<"<users>"<<endl;
  if(users_.empty()){
    ofile<<"</users>"<<endl;
  }
  else{  
    for(map<string, User*> :: iterator it=users_.begin(); it!=users_.end();it++){
      if(it->second){
        it->second->dump(ofile);
      }  
    }
    ofile<<"</users>"<<endl;
  }

}