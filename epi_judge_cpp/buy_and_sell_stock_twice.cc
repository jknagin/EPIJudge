#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {

  // "Buy and sell stock once" forward pass
  // forwardProfits[i] is the max profit by completing one transaction on or before day i
  std::vector<double> forwardProfits(prices.size(), 0);
  double minPrice = prices[0];
  double maxProfit = 0;
  for (int i = 1; i < prices.size(); ++i)
  {
    maxProfit = std::max(maxProfit, prices[i] - minPrice);
    minPrice = std::min(minPrice, prices[i]);
    forwardProfits[i] = maxProfit;
  }

  // "Buy and sell stock once" backward pass
  // backwardProfits[i] is the max profit of completing one transaction on or after day i
  double maxPrice = prices[prices.size() - 1];
  maxProfit = 0;
  std::vector<double> backwardProfits(prices.size(), 0);
  for (int i = prices.size() - 2; i >= 0; --i)
  {
    maxProfit = std::max(maxProfit, maxPrice - prices[i]);
    maxPrice = std::max(maxPrice, prices[i]);
    backwardProfits[i] = maxProfit;
  }

  // Max profit overall is the maximum sum of forwardProfits[i] + backwardProfits[i+1] from i=0 to n-2
  double maxProfitOverall = forwardProfits[0] + backwardProfits[1];
  for (int i = 1; i < prices.size() - 1; ++i)
  {
    maxProfitOverall = std::max(maxProfitOverall, forwardProfits[i] + backwardProfits[i + 1]);
  }

  // Also consider the possibility of only doing one transaction
  maxProfitOverall = std::max(maxProfitOverall, forwardProfits[prices.size() - 1]);
  return maxProfitOverall;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
