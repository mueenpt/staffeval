#include "BitcoinExchange.hpp"

void BitcoinExchange::loadDatabase(const std::string& file)
{
    std::ifstream f(file.c_str());
    std::string line;

    if (!f)
    {
        throw std::runtime_error("Error: could not open database.");
    }

    getline(f, line);

    while (getline(f, line))
    {
        std::stringstream ss(line);
        std::string date, rate;

        getline(ss, date, ',');
        getline(ss, rate);

        _db[date] = std::atof(rate.c_str());
    }
}

static std::string trim(const std::string& s)
{
    size_t start = s.find_first_not_of(" \t\r");
    size_t end = s.find_last_not_of(" \t\r");

    if (start == std::string::npos)
        return "";

    return s.substr(start, end - start + 1);
}

float BitcoinExchange::getRate(const std::string& date)
{
    std::map<std::string, float>::iterator it = _db.lower_bound(date);

    if (it != _db.end() && it->first == date)
        return it->second;

    if (it == _db.begin())
        throw std::runtime_error("Error: no exchange rate found.");

    --it;
    return it->second;
}

bool BitcoinExchange::validDate(const std::string& date)
{
    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;

    int maxDay = 31;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDay = 30;
    else if (month == 2)
    {
        maxDay = 28;

        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            maxDay = 29;
    }

    if (day < 1 || day > maxDay)
        return false;

    return true;
}

void BitcoinExchange::processInput(const std::string& file)
{
    std::ifstream f(file.c_str());
    std::string line;

    if (!f)
    {
        throw std::runtime_error("Error: could not open file.");
    }

    getline(f, line);

    while (getline(f, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string date, valueStr;

        if (!getline(ss, date, '|') || !getline(ss, valueStr))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = trim(date);
        valueStr = trim(valueStr);

        if (!validDate(date))
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }

        std::stringstream valueStream(valueStr);
        float value;

        valueStream >> value;

        if (valueStream.fail() || !valueStream.eof())
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (value < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        try
        {
            float rate = getRate(date);
            std::cout << date << " => "
                      << value << " = "
                      << value * rate << std::endl;
        }
        catch (const std::exception&)
        {
            std::cout << "Error: bad input => " << date << std::endl;
        }
    }
}
