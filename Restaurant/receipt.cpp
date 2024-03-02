#include <windows.h>
#include "receipt.h";
double receipt::getPrice(std::vector<dish> const& chosenDishes, std::map<int, double> prices)
{
    double price = 0;
    for (int i = 0; i < chosenDishes.size(); i++)
    {
        price += prices[std::stoi(chosenDishes[i].id)];
    }
    return price;
}

double receipt::_getTip(double subtotal)
{
    int tipSelect;
    std::cout << "Select tip amount:\n";
    std::cout << "1. 5%\n";
    std::cout << "2. 10%\n";
    std::cout << "3. 15%\n";
    std::cout << "4. Custom amount\n";
    std::cout << "5. Cancel\n";
    std::cin >> tipSelect;
    switch (tipSelect)
    {
    case 1:
    {
        subtotal *= 0.05;
        return subtotal;
    }
    case 2:
    {
        subtotal *= 0.1;
        return subtotal;
    }
    case 3:
    {
        subtotal *= 0.15;
        return subtotal;
    }
    case 4:
    {
        std::string tipCustomStr;
        double tipCustomDob;
        std::cout << "Enter custom tip: ";
        std::cin >> tipCustomStr;
        do
        try
        {
            tipCustomDob = abs(stod(tipCustomStr));
            return tipCustomDob;
        }
        catch(...)
        {
            std::cerr << "\nEnter a number.\n";
            std::cin >> tipCustomStr;
        }
        while (true);
    }
    default:
        std::cout << "Tip canceled.\n";
        return 0;
    }
}
std::tm receipt::_getTime() //Funkcja zwracaj¹ca aktualny czas; tm - struktura zawieraj¹ca aktualny czas
{
    auto current = std::chrono::system_clock::now();
    std::time_t now_timet = std::chrono::system_clock::to_time_t(current);

    std::tm now_tm;
    localtime_s(&now_tm, &now_timet);

    return now_tm;
}

void receipt::printReceipt(double subtotal, int tableNum, std::vector<dish> const& dishesOrdered, std::string tipChoice)
{
    double tip;
    if (tipChoice[0] == '1' || toupper(tipChoice[0]) == 'Y')
    {
        tip = _getTip(subtotal);
    }
    else
    {
        tip = 0;
    }
    std::ofstream file;
    LPCWSTR dirName = L"receipts";
    CreateDirectory(dirName, NULL);
    std::string fileName = "receipts/";
    fileName += "S_" + std::to_string(tableNum) + "_" + std::to_string(_getTime().tm_hour) + "_" + std::to_string(_getTime().tm_min) + ".txt";
    file.open(fileName);

    file << "Table number: " << tableNum << std::endl << std::endl;
    for (int i = 0; i < dishesOrdered.size(); i++)
    {
        file << std::left << std::setw(40) << dishesOrdered[i].name << dishesOrdered[i].price << "$;" << std::endl;
    }
    file << std::setfill('=') << std::setw(40 + std::to_string(subtotal).size()) << "=" << std::endl;
    file << std::setfill(' ') << std::left << std::setw(40) << "Subtotal:" << std::setprecision(2) << std::fixed << subtotal << "$;\n";
    file << std::left << std::setw(40) << "Tip:" << std::setprecision(2) << std::fixed << tip << "$;\n";
    file << std::left << std::setw(40) << "Total:" << std::setprecision(2) << std::fixed << subtotal + tip << "$;\n";
    file.close();
}
