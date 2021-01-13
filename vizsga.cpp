#include <iostream>
// ********************************************

#include <array>
#include <vector>

class Lamp
{
    std::string name;
    bool on;

public:
    Lamp(std::string name) : name(name), on(false){};
    virtual ~Lamp() {}
    std::string getName() const
    {
        return name;
    }
    void tf()
    {
        on = false;
    }
    void tn()
    {
        on = true;
    }
    bool isOn()
    {
        return on;
    }
    virtual void turnOn()
    {
        if (on == true)
        {
        }
        else
        {
            on = true;
            std::cout << name << " turned ON" << std::endl;
        }
    }
    virtual void turnOff()
    {
        if (on == false)
        {
        }
        else
        {
            on = false;
            std::cout << name << " turned OFF" << std::endl;
        }
    }
};

class RGBLamp : public Lamp
{
    int red;
    int green;
    int blue;

public:
    RGBLamp(std::string name) : Lamp(name), red(255), green(255), blue(255) {}
    int getRed()
    {
        if (isOn() == false)
        {
            return 0;
        }
        else
        {
            return red;
        }
    }
    int getGreen()
    {
        if (isOn() != false)
        {
            return green;
        }
        else
        {
            return 0;
        }
    }
    int getBlue()
    {
        if (isOn() == false)
        {
            return 0;
        }
        else
        {
            return blue;
        }
    }
    void setColor(int r, int g, int b)
    {
        red = r;
        green = g;
        blue = b;
    }
    void turnOn()
    {
        if (isOn() == true)
        {
        }
        else
        {
            tn();
            std::cout << getName() << " in color rgb(" << red << "," << green << "," << blue << ") turned ON" << std::endl;
        }
    }
    void turnOff()
    {
        if (isOn() == false)
        {
        }
        else
        {
            tf();
            std::cout << getName() << " in color rgb(" << red << "," << green << "," << blue << ") turned OFF" << std::endl;
        }
    }
};

class Room
{
    std::vector<Lamp *> lampak;

public:
    void add(Lamp *l)
    {
        lampak.push_back(l);
    }
    ~Room()
    {
        for (auto a : lampak)
        {
            delete a;
        }
    }
    void clear()
    {
        lampak.clear();
        Room::~Room();
    }
    int lampCount()
    {
        return lampak.size();
    }
    Lamp &operator[](int index)
    {
        return *lampak[index];
    }
    void setAllLamps(bool on)
    {
        for (auto a : lampak)
        {
            if (on == false) // kikapcsolni
            {
                if (a->isOn() != on)
                {
                    a->turnOff();
                }
            }
            else
            {
                if (a->isOn() != on)
                {
                    a->turnOn();
                }
            }
        }
    }
};

// ********************************************
int
main()
{
    using namespace std;
    Room r;
    if (r.lampCount() != 0)
        cout << "Hiba: ures szobaban nem lehet lampa\n";
    r.add(new Lamp("Desk lamp"));
    if (r.lampCount() != 1)
        cout << "Hiba: nem 1 lampa van a szobaban\n";
    r[0].turnOn();
    if (!r[0].isOn())
        cout << "Hiba: nincs felkapcsolva a lampa\n";
    r.setAllLamps(false);
    r.add(new RGBLamp("Ceiling lamp"));
    if (r.lampCount() != 2)
        cout << "Hiba: nem 2 lampa van a szobaban\n";
    r[1].turnOn();
    if (!r[1].isOn())
        cout << "Hiba: nincs felkapcsolva a 2. lampa\n";
    r.add(new RGBLamp("Kitchen lamp"));
    if (r.lampCount() != 3)
        cout << "Hiba: nem 3 lampa van a szobaban\n";
    r.setAllLamps(true);
    r.add(new Lamp("Reading lamp"));
    if (r.lampCount() != 4)
        cout << "Hiba: nem 4 lampa van a szobaban\n";
    r.setAllLamps(false);
    r.setAllLamps(true);
    r.clear();
    if (r.lampCount() != 0)
        cout << "Hiba: kiuritett szobaban nem lehet lampa\n";
    RGBLamp *rl = new RGBLamp("Bedside lamp");
    rl->setColor(64, 12, 36);
    r.add(rl);
    if (rl->getRed() != 0 || rl->getGreen() != 0 || rl->getBlue() != 0)
        cout << "Hiba: a kikapcsolt lampa szine nem fekete.\n";
    r.setAllLamps(true);
    if (rl->getRed() != 64 || rl->getGreen() != 12 || rl->getBlue() != 36)
        cout << "Hiba: az RGB lampa nem a kert szinu.\n";
    r.add(new Lamp("Floor lamp"));
    if (r.lampCount() != 2)
        cout << "Hiba: nem 2 lampa van a szobaban\n";
    r.setAllLamps(true);
    r.setAllLamps(false);
    return 0;
}