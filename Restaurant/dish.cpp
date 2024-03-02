#include "dish.h"
void dish::dataBases()
{
    std::cout << "Databases: \n";
    for (auto& p : std::filesystem::directory_iterator(".")) {
        if (p.is_regular_file()) {
            if (p.path().extension().string() == ".txt") {
                std::cout << p << std::endl;
                _bases.push_back(p.path().string());
            }
        }
    }
}

void dish::help(std::string& str)
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = tolower(str[i]);
    }
    if (str == "help")
    {
        std::cout << "To proceed, type the name of one of the avaivable databases.\n";
        std::cout << "To show avaivable databases again, type 'databases'\n";
        return;
    }
    else if (str == "databases")
    {
        dataBases();
        return;
    }
    auto it = std::find_if(_bases.begin(), _bases.end(),
        [&str](const auto& base) { return base == str; });

    if (it == _bases.end())
    {
        std::cout << "Selected database doesn't exist.\n";
        std::cout << "For help, type 'help'.\n";
    }
}
