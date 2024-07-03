#include "TradeStrategy.cpp"
// #include "DataModel.cpp"
// #include <vector>
// #include <iostream>


int main() {
    // const std::string symb = "NVDA";
    // const int longw = 200;
    // const int shortw = 50;
    std::vector<StockData> data = fetchStockData("NVDA", 50, 200);

    TradeStrategy strat(50, 200);
    strat.execute(data);
}