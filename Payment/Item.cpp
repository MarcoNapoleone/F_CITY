#include "Item.h"

const string &Item::getName() const {
    return name;
}

void Item::setName(const string &name) {
    this->name = name;
}

float Item::getPrice() const {
    return price;
}

void Item::setPrice(float price) {
    this->price = price;
}
