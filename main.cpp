#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>

#include "HLR3.h"
#include "strategy.h"
#include "template_method.h"

using namespace std;

class Kovrik
{
protected:
    string name;
    int width;
    int length;
    string color;
    ICleaningStrategy* cleaningStrategy = nullptr; // Стратегия чистки

public:
    Kovrik(const string& name, int width, int length, const string& color)
        : name(name), width(width), length(length), color(color) {}

    virtual ~Kovrik() = default;

    virtual void show_specs()
    {
        cout << "Name: " << name << "\tWidth: " << width << "\tLength: " << length;
    }

    virtual void square()
    {
        cout << "Square: " << static_cast<int>(length) * width << endl << endl;
    }

    void setCleaningStrategy(ICleaningStrategy* strategy)
    {
        cleaningStrategy = strategy;
    }

    void cleanKovrik() const
    {
        if (cleaningStrategy)
            cleaningStrategy->clean();
        else
            cout << "No cleaning strategy set!" << endl;
    }

    int GetWidth() const { return width; }
    int GetLength() const { return length; }
    string GetColor() const { return color; }
};

class Gembird : public Kovrik
{
public:
    Gembird(const string& name, int width, int length, const string& color)
        : Kovrik(name, width, length, color) {}

    void show_specs() override
    {
        Kovrik::show_specs();
        cout << "\tColor: " << color << endl;
    }
};

class Defender : public Kovrik
{
private:
    bool backlight;

public:
    Defender(const string& name, int width, int length, const string& color, bool backlight)
        : Kovrik(name, width, length, color), backlight(backlight) {}

    void show_specs() override
    {
        Kovrik::show_specs();
        cout << "\tBacklight: " << (backlight ? "Yes" : "No") << endl;
    }
};

class Logitech : public Kovrik
{
private:
    bool wireless_charging;

public:
    Logitech(const string& name, int width, int length, const string& color, bool wireless_charging)
        : Kovrik(name, width, length, color), wireless_charging(wireless_charging) {}

    void show_specs() override
    {
        Kovrik::show_specs();
        cout << "\tWireless charging: " << (wireless_charging ? "Enabled" : "Disabled") << endl;
    }
};

Kovrik* create_kovrik(int choice)
{
    switch (choice)
    {
    case 0:
        return new Gembird("MP-ROBO", 180, 220, "colorful");
    case 1:
        return new Defender("Black XXL HUB Light", 300, 780, "green", true);
    case 2:
        return new Logitech("Powerplay Wireless Charging", 321, 344, "blue", true);
    default:
        return nullptr;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    VectorContainer<Kovrik*> vec_container;
    ListContainer<Kovrik*> lst_container;

    for (int i = 0; i < 3; i++)
    {
        int choice = rand() % 3;
        vec_container.add_item(create_kovrik(choice));

        choice = rand() % 3;
        lst_container.add_item(create_kovrik(choice));
    }

    cout << "=== Vector Container ===" << endl;
    for (auto it = vec_container.begin(); !it.is_done(); it.go_next())
    {
        it.current_item()->show_specs();
        cout << endl;
    }

    cout << "\n=== List Container ===" << endl;
    for (auto it = lst_container.begin(); !it.is_done(); it.go_next())
    {
        it.current_item()->show_specs();
        cout << endl;
    }

    // ==== Демонстрация Стратегии ====
    cout << "\n=== Cleaning Strategy Demo ===" << endl;
    VacuumCleaning vacuum;
    HandWashing handWash;
    ChemicalCleaning chemical;

    Kovrik* myKovrik = new Logitech("Wireless Charging Mat", 300, 400, "black", true);
    myKovrik->setCleaningStrategy(&vacuum);
    myKovrik->cleanKovrik();

    myKovrik->setCleaningStrategy(&handWash);
    myKovrik->cleanKovrik();

    myKovrik->setCleaningStrategy(&chemical);
    myKovrik->cleanKovrik();

    // ==== Демонстрация Шаблонного метода ====
    cout << "\n=== Sale Process Demo ===" << endl;
    GembirdSale gembirdSale;
    DefenderSale defenderSale;
    LogitechSale logitechSale;

    gembirdSale.sale();
    defenderSale.sale();
    logitechSale.sale();

    delete myKovrik;

    return 0;
}
