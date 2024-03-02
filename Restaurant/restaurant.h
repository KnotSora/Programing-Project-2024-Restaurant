#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iomanip>
#include <iterator>
#include "dish.h"
#include"category.h"
class restaurant
{
private:
	std::vector<dish> _dishes;
	std::string _filePath;
	std::map<int, std::string> _categories;
	void _printMenu(std::map <int, std::string> categories);
	void _fillCategories(std::map<int, std::string>& categories);
	std::map<int, double> _fillPrices(std::map<int, std::string> categories);
public:
	restaurant(std::string path);
	void fill();
	void order(int tableNum);
	std::vector<dish> getDishes();
};
