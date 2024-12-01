#include "Settlement.h"
#include <iostream>

using std::cout;
using std::endl;

// Constructor
Settlement::Settlement(const string &name, SettlementType type)
    : name(name), type(type)
{
    // Constructor body (if needed)
}

// Getter for the name
const string &Settlement::getName() const
{
    return name;
}

// Getter for the type
SettlementType Settlement::getType() const
{
    return type;
}

// Convert the Settlement to a string representation
const string Settlement::toString() const
{
    string typeStr;
    switch (type)
    {
    case SettlementType::VILLAGE:
        typeStr = "Village";
        break;
    case SettlementType::CITY:
        typeStr = "City";
        break;
    case SettlementType::METROPOLIS:
        typeStr = "Metropolis";
        break;
    }
    return "Settlement Name: " + name + ", Type: " + typeStr;
}
int Settlement::getConstructionLimit() const
{
    switch (type)
    {
    case SettlementType::VILLAGE:
        return 1;
    case SettlementType::CITY:
        return 2;
    case SettlementType::METROPOLIS:
        return 3;
    }
    return 0; // Default case (should never occur)
}
