#include "solution.hpp"
#include <algorithm>
#include <numeric>

double totalInStockGrossValue(const std::vector<Product>& products, double vatRate) {
    return std::accumulate(products.begin(), products.end(), 0.0,
        [vatRate](double acc, const Product& p) {
            return p.inStock ? acc + p.price * (1.0 + vatRate) : acc;
        });
}

const Product* findProductById(std::vector<Product>& products, int targetId) {
    std::sort(products.begin(), products.end(),
        [](const Product& a, const Product& b) { return a.id < b.id; });

    auto it = std::lower_bound(products.begin(), products.end(), targetId,
        [](const Product& p, int id) { return p.id < id; });

    if (it != products.end() && it->id == targetId) {
        return &(*it);
    }
    return nullptr;
}
