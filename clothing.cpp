#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand) 
: Product(category, name, price, qty), size_(size), brand_(brand)
{

}

set<string> Clothing:: keywords() const{
  set<string> keywords = parseStringToWords(convToLower(name_));
  set<string> keywordsBrand = parseStringToWords(convToLower(brand_));
  keywords.insert(keywordsBrand.begin(), keywordsBrand.end());
  return keywords; 
}

string Clothing::displayString() const{
  stringstream ss;
  ss<< name_<< "\n"<< "Size: "<<size_<<" Brand: "<< brand_<<"\n"<<price_<<" "<<qty_<<" left.";
  return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}



