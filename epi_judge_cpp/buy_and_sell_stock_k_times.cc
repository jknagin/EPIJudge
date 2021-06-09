#include <vector>
#include <limits>
#include "test_framework/generic_test.h"
using std::vector;

double unlimitedPairsProfits(const std::vector<double>& prices)
{
	double profit = 0;
	for (int i = 0; i < prices.size() - 1; ++i)
	{
		profit += std::max(prices[i + 1] - prices[i], 0.0);
	}
	return profit;
}

double BuyAndSellStockKTimes(const vector<double>& prices, int k) {
	// profit[t][d] = max(profit[t][d-1], prices[d] + max_x(profit[t-1][x] - prices[x])), 0 <= x < d
	if (prices.size() == 0) return 0;
	
	if (k * 2 >= prices.size())
	{
		return unlimitedPairsProfits(prices);
	}
	// profit is a 2 x n array
	std::vector<std::vector<double> > profit(2, std::vector<double>(prices.size(), 0));
	for (int i = 1; i <= k; ++i)
	{
		double max_ = std::numeric_limits<double>::min();
		for (int x = 1; x < prices.size(); ++x)
		{
			max_ = std::max(max_, profit[0][x - 1] - prices[x - 1]);
			profit[1][x] = std::max(profit[1][x - 1], max_ + prices[x]);
		}

		// Copy row 1 into row 0
		profit[0] = profit[1];
	}

	return profit.back().back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices", "k"};
  return GenericTestMain(
      args, "buy_and_sell_stock_k_times.cc", "buy_and_sell_stock_k_times.tsv",
      &BuyAndSellStockKTimes, DefaultComparator{}, param_names);
}
