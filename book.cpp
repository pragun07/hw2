#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>
#include "product.h"

Book::Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author) :
    Product("book", name, price, qty), 
    isbn_(isbn),
    author_(author)
{

}

std::set<std::string> Book::keywords() const 
{
  std::set<std::string> keywords = parseStringToWords(name_);
  std::set<std::string> author_keywords = parseStringToWords(author_);
  keywords.insert(author_keywords.begin(), author_keywords.end());

  keywords.insert(isbn_);

  return keywords;
}

std::string Book::displayString() const
{
  std::ostringstream os;
  os << name_ << std::endl; 
  os << "Author: " << author_ << " ISBN: " << isbn_ << std::endl; 
  os << std::fixed << std::setprecision(2) << price_ << " " << qty_ << "left." << std::endl;
  return os.str();
}

void Book::dump(std::ostream& os) const 
{
  os << "book" << std::endl; 
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << isbn_ << std::endl;
  os << author_ << std::endl;
}