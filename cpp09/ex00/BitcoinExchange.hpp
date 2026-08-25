#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

class BitcoinExchange
{
private:
    std::map<std::string, float> _db;

public:
    void loadDatabase(const std::string& file);
    void processInput(const std::string& file);

    float getRate(const std::string& date);

    bool validDate(const std::string& date);
};

#endif