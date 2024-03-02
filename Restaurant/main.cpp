#include "restaurant.h"

int main()
{
	std::string selection = "x";
	std::string dataBase;
	std::vector<dish> dataBaseChecker;
	dish dish;
	dish.dataBases();
	do
	{
		std::cout << "Please select a database:\n";
		std::cin >> dataBase;
		restaurant laConsola = restaurant(dataBase);
		laConsola.fill();
		dataBaseChecker = laConsola.getDishes();
		if (dataBaseChecker.size() != 0)
		{
			std::cout << "Welcome!\n";
			std::cout << "Please provide a table number.\n";
			do
			{
				std::cin >> selection;
				try
				{
					int tableNumber = stoi(selection);
					laConsola.order(abs(tableNumber));
				}
				catch (...)
				{
					std::cout << "Please provide a number.\n";
					selection = "x";
				}
			} while (selection == "x");
		}
		else
		{
			dish.help(dataBase);
		}

	} while (dataBaseChecker.size() == 0);
}