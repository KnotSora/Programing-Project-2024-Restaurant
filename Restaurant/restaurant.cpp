#include "restaurant.h"
#include "category.h"
#include "receipt.h"
restaurant::restaurant(std::string path)
{
	_filePath = path;  
}

void restaurant::fill()    //Wype³nianie wektora z bazy danych
{
    dish helper;
    std::fstream file(_filePath);
    std::string enterEater;
    if (file.is_open())
    {
        while (getline(file, helper.id, ';'))
        {
            getline(file, helper.name, ';');
            getline(file, helper.price, ';');
            getline(file, helper.category, ';');
            getline(file, helper.desc, ';');
            getline(file, enterEater, '\n');
            _dishes.push_back(helper);
        }
        file.close();
    }
}

void restaurant::_printMenu(std::map <int, std::string> categories)    //Funkcja wypisuj¹ce opcje
{
    std::cout << "\n";
    std::cout << "=====Menu=====" << std::endl;
    for (int i = 1; i < categories.size(); i++)
    {
        std::cout << i << ". " << categories[i] << std::endl;
    }
    std::cout << "S. Show Order" << std::endl;
    std::cout << "P. Remove Last Position" << std::endl;
    std::cout << "C. Clear Order" << std::endl;
    std::cout << "0. Finish" << std::endl;
}
void restaurant::order(int tableNum)
{
    bool done = false;
    int categorySel = -1;
    double subtotal;
    std::string selection, choice, tipChoice;
    std::vector<dish> dishesOrdered;
    receipt rec;
    _fillCategories(_categories);
    std::map<int, double> prices = _fillPrices(_categories);
    while (done == false)
    { 
        _printMenu(_categories);
        std::cin >> choice;
        try
        {
            categorySel = stoi(choice);
            choice = "1";
        }
        catch (...) //wy³apanie wszelkich b³êdów
        {
            choice = choice[0];
        }
        if (categorySel == 0)
        {
            choice = "F";
        }
        switch (toupper(choice[0]))
        {
        case'1':
        {
            do
            {
                category cat;
                cat.printCategory(categorySel, _categories, _dishes);
                std::cin >> selection;
                try//Sprawdzenie czy wprowadzona wartoœæ jest typu int
                {
                    int dishChoice = stoi(selection);
                    dishesOrdered = cat.picker(dishChoice, dishesOrdered, _dishes, _categories, categorySel);
                }
                catch(...) 
                {
                    std::cout << "\nPlease select an option.\n";
                    selection = "1";
                }
            } while (stoi(selection) != 0);
            break;
        }
        case 'F':
        {
            //case koñcz¹cy dzia³anie programu; pytanie o napiwek
            std::cout << "Are you sure you want to finish ordering?\n";
            std::cout << "1. Yes\n";
            std::cout << "2. No\n";
            std::string leave;
            std::cin >> leave;
            if (leave[0] == '1' or toupper(leave[0]) == 'Y')
            {
                done = true;
                std::cout << "Would you like to leave a tip?\n";
                std::cout << "1. Yes\n";
                std::cout << "2. No\n";
                std::cin >> tipChoice;
                subtotal = rec.getPrice(dishesOrdered, prices);
                rec.printReceipt(subtotal, tableNum, dishesOrdered, tipChoice);
                std::cout << "Thank you for dining with us, here is your receipt.";
                break;
            }
            else
            {
                categorySel = 1;
                break;
            }
            
        }
        case 'S':
        {
            //case pokazuj¹cy aktualny stan zamównienia
            subtotal = rec.getPrice(dishesOrdered, prices);
            std::cout << "Your current order is: \n";
            for (auto el : dishesOrdered)
            {
                std::cout << std::left << std::setw(40) << el.name <<  " " << el.price << "$; " << std::endl;
            }
            std::cout << std::setfill('=') << std::setw(40 + std::to_string(subtotal).size()) << "=" << std::endl;
            std::cout << std::setfill(' ') << std::left << std::setw(42) << "\nTotal:" << subtotal << "$;\n";
            break;
        }
        case 'P':
        {
            if (dishesOrdered.size() > 0)
            {
                dishesOrdered.pop_back();
                std::cout << "Removed last item added.";
            }
            else
            {
                std::cout << "Please add an item before removing one\n";
            }
            break;
        }
        case 'C':
        {
            //wymazanie zamówienia
            dishesOrdered.clear();
            std::cout << "Cleared the order.";
            break;
        }
        default:
        {
            std::cout << "Please select a menu position.";
            break;
        }
        }
    }
}

std::vector<dish> restaurant::getDishes()
{
    return _dishes;
}

void restaurant::_fillCategories(std::map<int, std::string>& categories)
{
    for (const auto& dish : _dishes)
    {
        //sprawdzenie czy kategoria istnieje w mapie
        auto it = std::find_if(categories.begin(), categories.end(),
            [&dish](const auto& pair) { return pair.second == dish.category; });

        if (it == categories.end())
        {
            int newIndex = categories.size() + 1;
            categories.insert(std::pair<int, std::string>(newIndex, dish.category));
        }
    }
}


std::map<int, double> restaurant::_fillPrices(std::map<int, std::string> categories)
{
    std::map<int, double> prices;
    for (int i = 0; i < _dishes.size(); i++)
    {
        //Mapa gdzie kluczem jest id potrawy a wartoœci¹ cena
        prices.insert(std::pair<int, double>(std::stoi(_dishes[i].id), std::stof(_dishes[i].price)));
    }
    return prices;
}

