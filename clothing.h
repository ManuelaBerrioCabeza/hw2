#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product {
public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    std::string size_;
    std::string brand_;

};
#endif
