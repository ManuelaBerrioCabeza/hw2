#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) 
: Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}

set<string> Movie:: keywords() const{
  set<string> keywords = parseStringToWords(convToLower(name_));
  keywords.insert(convToLower(genre_));
  return keywords; 
}

string Movie::displayString() const{
  stringstream ss;
  ss<< name_<< "\n"<< "Genre: "<<genre_<<" Rating: "<< rating_<<"\n"<<price_<<" "<<qty_<<" left.";
  return ss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}