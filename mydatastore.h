#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include <vector>
#include <set>
#include <map>

class MyDataStore : public DataStore{
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    void addToCart(const std::string& username, int index, const std::vector<Product*>& search_results);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::vector<std::pair<std::string, std::vector<Product*>>> carts_;

    std::map<std::string, std::set<Product*>> keyword_product_map_;

    User* findUser(const std::string& username);
};

#endif

