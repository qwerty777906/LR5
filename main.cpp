#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "HLR3.h"
#include <ctime>

using namespace std;

class Kovrik
{
protected:
    string name;
    int width;
    int length;
    string color;

public:
    Kovrik(const string& name, int width, int length, const string& color)
        : name(name), width(width), length(length) , color(color) {}

    virtual void show_specs()
    {
        cout << "Name: " << name << "\tWidth: " << width << "\tLength: " << length;
    }

    virtual void square()
    {
        cout << "Square: " << static_cast<int>(length) * width << endl << endl;
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

    void update_name()
    {
        name = "MP-BRICKS";
        cout << "New name: " << name << endl;
    }
};

class Defender : public Kovrik
{
private:
    bool backlight;

public:
    Defender(const string& name, int width, int length, const string& color, bool backlight)
        : Kovrik(name, width, length, color), backlight(backlight) {}

    void input_specs()
    {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter width: ";
        cin >> width;
        cout << "Enter length: ";
        cin >> length;
    }

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

    void display()
    {
        cout << "Kovrik " << name << " has " << width << " width and " << length << " length!" << endl;
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

template<typename Container>
void output(Container& container)
{
    for (auto it = container.begin(); !it.is_done(); it.go_next())
    {
        it.current_item()->show_specs();
        it.current_item()->square();
    }
}

class KovrikWidthDecorator : public IteratorDecorator<Kovrik*>
{
private:
    int TargetWidth;

public:
    KovrikWidthDecorator(Iterator<Kovrik*> *it, int width)
    : IteratorDecorator<Kovrik*>(it), TargetWidth(width) {}

    void go_first()
    {
        It->go_first();
        while(!It->is_done() && It->current_item()->GetWidth() < TargetWidth)
        {
            It->go_next();
        }
    }

    void go_next()
    {
        do
        {
            It->go_next();

        } while(!It->is_done() && It->current_item()->GetWidth() < TargetWidth);
    }
};

class KovrikLengthDecorator : public IteratorDecorator<Kovrik*>
{
private:
    int TargetLength;

public:
    KovrikLengthDecorator(Iterator<Kovrik*> *it, int length)
    : IteratorDecorator<Kovrik*>(it), TargetLength(length) {}

    void go_first()
    {
        It->go_first();
        while(!It->is_done() && It->current_item()->GetLength() < TargetLength)
        {
            It->go_next();
        }
    }

    void go_next()
    {
        do
        {
            It->go_next();

        } while(!It->is_done() && It->current_item()->GetLength() < TargetLength);
    }
};

class KovrikColorDecorator : public IteratorDecorator<class Kovrik*>
{
private:
    string TargetColor;

public:
    KovrikColorDecorator(Iterator<Kovrik*> *it, string color)
    : IteratorDecorator<Kovrik*>(it), TargetColor(color) {}

    void go_first()
    {
        It->go_first();
        while(!It->is_done() && It->current_item()->GetColor() != TargetColor)
        {
            It->go_next();
        }
    }

    void go_next()
    {
        do
        {
            It->go_next();

        } while(!It->is_done() && It->current_item()->GetColor() != TargetColor);
    }
};

enum class KovrikType : int
{
    Gembird = 1,
    Defender = 2,
    Logitech = 3,

    Undefined = 0
};

void CalcArea(Iterator<Kovrik*> *it)
{
    for(it->go_first(); !it->is_done(); it->go_next())
    {
        Kovrik *currentKovrik = it->current_item();
        currentKovrik->show_specs();
    }
}

int main()
{
    VectorContainer<Kovrik*> vec_container;
    ListContainer<Kovrik*> lst_container;

    srand(time(0));
    for (int i = 0; i < 3; i++)
    {
        int choice = rand() % 3;
        vec_container.add_item(create_kovrik(choice));

        choice = rand() % 3;
        lst_container.add_item(create_kovrik(choice));
    }

    cout << "Vector Container" << endl;
    output(vec_container);
    Iterator<Kovrik*> *goodIt = new KovrikColorDecorator(lst_container.GetIterator(), "blue");
    CalcArea(goodIt);

    cout << endl << "List container" << endl;
    output(lst_container);

    size_t N = 30;

    list<Kovrik*> KovrikList;
    for(size_t i=0; i<N; i++)
    {
        int kovrik_num = rand() % 3;
        Kovrik *newKovrik = create_kovrik(kovrik_num);
        KovrikList.push_back(newKovrik);
    }

     cout << "Size list kovrik: " << KovrikList.size() << endl;

     cout << endl << "we find those rugs that are blue and have a length of 344:" << endl;
     Iterator<Kovrik*> *adaptedIt = new ConstIteratorAdapter<std::list<Kovrik*>, Kovrik*>(&KovrikList);
     Iterator<Kovrik*> *adaptedBlueIt = new KovrikLengthDecorator(new KovrikColorDecorator(adaptedIt, "blue"), 344);
     CalcArea(adaptedBlueIt);
     delete adaptedBlueIt;
}

