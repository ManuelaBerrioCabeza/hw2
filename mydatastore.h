#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <set>
#include <vector>
#include <map>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore: public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    void addToCart(const std::string& username,int productIndex, std::vector<Product*>& productResults);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
  std::map<std::string, User*> users_;
  std::vector<Product*> products_;
  std::map<std::string, std::set<Product*>> mapKeyword_;
  std::map<std::string, std::vector<Product*>> carts_;

};

#endif
