// #include <iostream>
// #include <vector>
// #include "json.hpp"
#include "DataModel.cpp"


class TradeStrategy{
    private:
        int shortw;
        int longw;
    public:
        TradeStrategy(int shortw, int longw): shortw{shortw}, longw{longw}{}

        double calculateMA(const std::vector<double>& prices, int wind){
            if(prices.size() < wind) return 0.0;
            double sum = 0.0;
            for (int i = prices.size() - wind; i < prices.size(); ++i){
                sum += prices[i];
            }
            return sum / wind;
        }

        void execute(const std::vector<StockData>& stockData){
            std::vector<double> closePs;
            for (const auto& data : stockData){
                closePs.push_back(data.close);
            }

            fprintf(stdout, "\nSize %zu\n", closePs.size());
            int j = 0;
            for (size_t i = longw; i < closePs.size(); ++i) {
                std::vector<double> shortPs(closePs.begin() + i, closePs.begin() + i + shortw);
                std::vector<double> longPs(closePs.begin() + i, closePs.begin() + i + longw);

                double shortMA = calculateMA(shortPs, shortw);
                double longMA = calculateMA(longPs, longw);

                if (shortMA > longMA) {
                    std::cout << "Buy signal at " << stockData[i].timestamp << " with price " << stockData[i].close << std::endl;
                } else if (shortMA < longMA) {
                    std::cout << "Sell signal at " << stockData[i].timestamp << " with price " << stockData[i].close << std::endl;
                }
                j+=1;
            }

            fprintf(stdout, "J: %i\n", j);
        };
};