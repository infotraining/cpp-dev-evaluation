#pragma once
#include <vector>

struct Product {
    int id;
    double price;
    bool inStock;
};

double totalInStockGrossValue(const std::vector<Product>& products, double vatRate);
const Product* findProductById(std::vector<Product>& products, int targetId);
