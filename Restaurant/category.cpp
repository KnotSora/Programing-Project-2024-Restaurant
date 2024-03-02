#include "category.h"
void category::printCategory(int choice, std::map<int, std::string> categories, std::vector<dish> const& dishes)
{
    std::cout << "\n";
    std::cout << "======" << categories[choice] << "======\n";
    for (int i = 0; i < dishes.size(); i++)
    {

        if (dishes[i].category == categories[choice])
        {

            std::string s;
            if (stoi(dishes[i].id) < 10)
            {

                s = "   ";
                std::cout << dishes[i].id << s << std::left << std::setw(40) << dishes[i].name << dishes[i].price << "$; " << dishes[i].desc << std::endl;
            }
            else if(stoi(dishes[i].id) < 100 and stoi(dishes[i].id) > 10)
            {

                s = "  ";
                std::cout << dishes[i].id << s << std::left << std::setw(40) << dishes[i].name << dishes[i].price << "$; " << dishes[i].desc << std::endl;
            }
            else if (stoi(dishes[i].id) < 1000 and stoi(dishes[i].id) > 100)
            {
                s = " ";
                std::cout << dishes[i].id << s << std::left << std::setw(40) << dishes[i].name << dishes[i].price << "$; " << dishes[i].desc << std::endl;
            }
        }
    }
    std::cout << "0  Return\n";
    std::cout << "Please select the dish you want via ID number\n";
    std::cout << "\n";
}

std::vector <dish> category::picker(int choice, std::vector <dish>& chosenDish, std::vector <dish> const& dishes, std::map<int, std::string> categories, int categoryChoice)
{
    for (int i = 0; i < dishes.size(); i++)
    {
        //sprawdzanie czy podane id odpowiada wybranej kategorii
        if (choice == std::stoi(dishes[i].id) && dishes[i].category != categories[categoryChoice])
        {
            std::cout << "\nWrong category.";
            return chosenDish;
        }
        else if (choice == std::stoi(dishes[i].id))
        {
            chosenDish.push_back(dishes[i]);
            std::cout << "Item added.\n";
            return chosenDish;
        }
        else if (choice > dishes.size())
        {
            std::cout << "\nWe don't serve that many dishes.";
            return chosenDish;
        }
        else if (choice == 0)
        {
            return chosenDish;
        }
    }
}