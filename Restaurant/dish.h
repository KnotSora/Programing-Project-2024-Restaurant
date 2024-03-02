#pragma once
#include <filesystem>
#include <iostream>
class dish{
private: 
    std::vector<std::string> _bases;
public:
    std::string id, name, category, price, desc;
    void dataBases();
    void help(std::string& str);
};