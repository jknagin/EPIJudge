#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
    if (prices.size() == 0) return 0;
    if (prices.size() == 1) return 0;
    double minPrice = prices[0];
    double maxProfit = prices[1] - prices[0];
    for (int i = 1; i < prices.size(); ++i)
    {
        maxProfit = std::max(maxProfit, prices[i] - minPrice);
        minPrice = std::min(minPrice, prices[i]);
    }
    return std::max(maxProfit, 0.0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
