#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>
#include "product.h"

Clothing::Clothing(const std::string& name, double price, int qty, const std::string& brand, const std::string& size) :
    Product("clothing", name, price, qty), 
    brand_(brand), 
    size_(size)
{

}

std::set<std::string> Clothing::keywords() const 
{
  std::set<std::string> keywords = parseStringToWords(name_);
  std::set<std::string> brand_keywords = parseStringToWords(brand_);
  std::set<std::string> size_keywords = parseStringToWords(size_);

  keywords.insert(brand_keywords.begin(), brand_keywords.end());
  keywords.insert(size_keywords.begin(), size_keywords.end());

  return keywords;
}

std::string Clothing::displayString() const
{
  std::ostringstream os;
  os << name_ << std::endl; 
  os << "Size: " << size_ << " Brand: " << brand_ << std::endl; 
  os << std::fixed << std::setprecision(2) << price_ << " " << qty_ << "left." << std::endl;
  return os.str();
}

void Clothing::dump(std::ostream& os) const 
{
  os << "clothing" << std::endl; 
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << size_ << std::endl;
  os << brand_ << std::endl;
}
