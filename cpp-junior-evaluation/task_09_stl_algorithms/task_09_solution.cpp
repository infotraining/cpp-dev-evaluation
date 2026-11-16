#include "task_09_solution.hpp"

#include <algorithm>
#include <numeric>

namespace Solution
{

    double total_in_stock_gross_value(const std::vector<Product>& products, double vatRate)
    {
        return std::accumulate(products.begin(), products.end(), 0.0,
            [vatRate](double acc, const Product& p) {
                return p.inStock ? acc + p.price * (1.0 + vatRate) : acc;
            });
    }

    const Product* find_product_by_id(std::vector<Product>& products, int targetId)
    {
        std::sort(products.begin(), products.end(),
            [](const Product& a, const Product& b) { return a.id < b.id; });

        auto it = std::lower_bound(products.begin(), products.end(), targetId,
            [](const Product& p, int id) { return p.id < id; });

        if (it != products.end() && it->id == targetId)
        {
            return &(*it);
        }
        return nullptr;
    }

} // namespace Solution
