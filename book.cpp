#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const string isbn, const string author) 
: Product(category, name, price, qty), isbn_(isbn), author_(author)
{

}

set<string> Book:: keywords() const{
  set<string> keywords = parseStringToWords(convToLower(name_));
  set<string> keywordsAuthor = parseStringToWords(convToLower(author_));
  keywords.insert(keywordsAuthor.begin(), keywordsAuthor.end());
  keywords.insert(isbn_);
  return keywords; 
}

string Book::displayString() const{
  stringstream ss;
  ss<< name_<< "\n"<< "Author: "<<author_<<" ISBN: "<< isbn_<<"\n"<<price_<<" "<<qty_<<" left.";
  return ss.str();
}


void Book::dump(std::ostream& os) const
{
    os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}



