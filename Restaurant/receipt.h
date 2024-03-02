#pragma once
#include <ctime>
#include <chrono>
#include "restaurant.h"
class receipt
{
private:
	std::tm _getTime();
	double _getTip(double subtotal);
public:
	double getPrice(std::vector<dish> const& dishesOrdered, std::map<int, double> prices);
	void printReceipt(double subtotal, int tableNum, std::vector<dish> const& dishesOrdered, std::string tipChoice);
};