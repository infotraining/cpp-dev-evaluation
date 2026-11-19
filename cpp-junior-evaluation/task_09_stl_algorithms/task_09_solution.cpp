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

    std::optional<Product> find_product_by_id(std::vector<Product>& products, int target_id)
    {
        auto predicate = [target_id](const Product& p) {
            return p.id == target_id;
        };

        if (auto pos = std::find_if(products.begin(), products.end(), predicate); pos != products.end())
        {
            return *pos;
        }

        return std::nullopt;
    }

} // namespace Solution
