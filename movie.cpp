#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>
#include "product.h"

Movie::Movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating) :
    Product("movie", name, price, qty), 
    genre_(genre), 
    rating_(rating)
{

}

std::set<std::string> Movie::keywords() const 
{
  std::set<std::string> keywords = parseStringToWords(name_);
  std::set<std::string> genre_keywords = parseStringToWords(genre_);
  keywords.insert(genre_keywords.begin(), genre_keywords.end());

  return keywords;
}

std::string Movie::displayString() const
{
  std::ostringstream os;
  os << name_ << std::endl; 
  os << "Genre: " << genre_ << " Rating: " << rating_ << std::endl; 
  os << std::fixed << std::setprecision(2) << price_ << " " << qty_ << "left." << std::endl;
  return os.str();
}

void Movie::dump(std::ostream& os) const 
{
  os << "movie" << std::endl; 
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << genre_ << std::endl;
  os << rating_ << std::endl;
}
