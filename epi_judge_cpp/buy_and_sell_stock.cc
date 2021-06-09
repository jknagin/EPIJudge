#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices)
{
  double minPrice = prices[0];
  double maxProfit = 0; // initialize max profit to 0 in case the price is monotonically decreasing
  for (int i = 1; i < prices.size(); ++i)
  {
    // max profit is the max of current max profit and the profit we can make by selling on day i
    maxProfit = std::max(maxProfit, prices[i] - minPrice);

    // update min price *after* computing the max profit for the day, because we can't use today's price as a selling price
    minPrice = std::min(minPrice, prices[i]);
  }
  return maxProfit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
