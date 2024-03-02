#pragma once
#include "dish.h"
#include "restaurant.h"
class category
{
public:
	void printCategory(int choice, std::map<int, std::string> categories, std::vector<dish> const& dishes);
	std::vector <dish> picker(int choice, std::vector <dish>& chosenDish, std::vector <dish> const& dishes, std::map<int, std::string>  categories, int catChoice);
};