#ifndef STRATEGY_H_INCLUDED
#define STRATEGY_H_INCLUDED

#include <iostream>
using namespace std;

class ICleaningStrategy
{
public:
    virtual ~ICleaningStrategy() = default;
    virtual void clean() const = 0;
};

class VacuumCleaning : public ICleaningStrategy
{
public:
    void clean() const override
    {
        cout << "Cleaning the mat with a vacuum cleaner." << endl;
    }
};

class HandWashing : public ICleaningStrategy
{
public:
    void clean() const override
    {
        cout << "Manually washing the mat with soap and water." << endl;
    }
};

class ChemicalCleaning : public ICleaningStrategy
{
public:
    void clean() const override
    {
        cout << "Dry-cleaning the mat using chemicals." << endl;
    }
};

#endif // STRATEGY_H_INCLUDED
