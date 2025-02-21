#include "mydatastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

MyDataStore::MyDataStore() 
{

}

MyDataStore::~MyDataStore()
{
  for (size_t i=0;i<products_.size();i++)
  {
    delete products_[i];
  }

  for (size_t i=0;i<users_.size();i++)
  {
    delete users_[i];
  }
}

void MyDataStore::addProduct(Product*p)
{

  if(p != nullptr)
  {
    products_.push_back(p);

    //adding products to the keyword map
    std::set<std::string> keywords = p->keywords();
    for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it)
    {
      if (keyword_product_map_.find(*it)==keyword_product_map_.end()){
        std::set<Product*> t;
        t.insert(p);
        keyword_product_map_.insert(std::make_pair(*it, t));
      }
      else {
        keyword_product_map_.find(*it)->second.insert(p);
      }
    }
  }
}

void MyDataStore::addUser(User* u)
{
  if (u != nullptr)
  {
    users_.push_back(u);
    carts_.push_back(std::make_pair(u->getName(), std::vector<Product*>()));
  }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::set<Product*> final_set;

  if (terms.empty())
  {
    return std::vector<Product*>();
  }
  if (type==0) //intersection search (AND)
    {
      std::map<std::string, std::set<Product*>>::iterator term_one = keyword_product_map_.find(terms[0]);
      if (term_one != keyword_product_map_.end())
      {
        final_set=term_one->second;
      }
      else
      {
        return std::vector<Product*>();
      }
      
      for (size_t i=1;i<terms.size();i++)
      {
        term_one = keyword_product_map_.find(terms[i]);
        //std::map<std::string, std::set<Product*>>::iterator it = keyword_product_map_.find(terms[i]);
        if(term_one != keyword_product_map_.end())
        {
          final_set=setIntersection(final_set,term_one->second);
        }
        else
        {
          return std::vector<Product*>();
        }
      }      
    }
    else //union search (OR)
    {
      for(size_t i=0;i<terms.size();i++)
      {
        std::map<std::string, std::set<Product*>>::iterator it = keyword_product_map_.find(terms[i]);
        if (it!=keyword_product_map_.end())
        {
          final_set=setUnion(final_set,it->second);
        }
      }
    }

  return std::vector<Product*>(final_set.begin(),final_set.end());
}

void MyDataStore::addToCart(const std::string& username, int index, const std::vector<Product*>& search_results)
{
  User* user= findUser(username);
  if(!user || index<0 || index>=(int)search_results.size())
  {
    std::cout << "Invalid request." << std::endl;
    return;
  }

  for (size_t i=0;i<carts_.size();i++)
  {
    if (carts_[i].first == username)
    {
      carts_[i].second.push_back(search_results[index]);
      return;
    }
  }
}

void MyDataStore::viewCart(const std::string& username) 
{
  for (size_t i=0; i<carts_.size();i++)
  {
    if (carts_[i].first == username)
    {
      if (carts_[i].second.empty())
      {
        std::cout << "Cart is empty." << std::endl;
        return;
      }

      for (size_t j=0;j<carts_[i].second.size();j++)
      {
        std::cout << "Item " << (j+1) << std::endl;
        std::cout << carts_[i].second[j]->displayString() << std::endl;
        std::cout << std::endl;
      }
      return;
    }
  }
  std::cout << "Invalid username" << std::endl;
}

void MyDataStore::buyCart(const std::string& username)
{
  User* user = findUser(username);
  if (!user)
  {
    std::cout << "Invalid username." << std::endl;
    return;
  }

  for (size_t i=0;i<carts_.size();i++)
  {
    if (carts_[i].first == username)
    {
      std::vector<Product*>& cart = carts_[i].second;
      for (size_t j=0;j<cart.size(); )
      {
        Product* product = cart[j];
        if(product->getQty() > 0 && user->getBalance() >= product->getPrice())
        {
          product->subtractQty(1);
          user->deductAmount(product->getPrice());
          cart.erase(cart.begin()+j);
        }
        else
        {
          j++;
        }
      }
      return;
    }
  }
}

void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>" << std::endl;
  for (size_t i=0;i<products_.size();i++)
  {
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << std::endl;

  ofile << "<users>" << std::endl;
  for (size_t i=0;i<users_.size();i++)
  {
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << std::endl;
}

User* MyDataStore::findUser(const std::string& username)
{
  for(size_t i=0;i<users_.size();i++)
  {
    if (users_[i]->getName() == username)
    {
      return users_[i];
    }
  }
  return nullptr;
}