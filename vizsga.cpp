#include <iostream>
// ********************************************

#include <array>
#include <list>

class Lamp
{
    std::string name;
    bool on;

public:
    Lamp(std::string name) : name(name), on(false){};
    virtual ~Lamp() {}
    std::string getName() const{
        return name;
    }
    void tf(){
        on = false;
    }
    void tn(){
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
    RGBLamp(std::string name) : Lamp(name), red(255), green(255), blue(255){}
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

// ********************************************
int
main()
{
    using namespace std;
    Lamp *l1 = new Lamp("Desk lamp");
    if (l1->isOn())
        cout << "Hiba: kezdetben kikapcsoltnak kell lennie a lampanak.\n";
    l1->turnOff();
    if (l1->isOn())
        cout << "Hiba: redundans kikapcsolas utan vilagit a lampa.\n";
    cout << "Bekapcsolas: ";
    l1->turnOn();
    if (!l1->isOn())
        cout << "Hiba: bekapcsolas utan sem vilagit a lampa.\n";
    l1->turnOn();
    if (!l1->isOn())
        cout << "Hiba: redundans bekapcsolas utan nem vilagit a lampa.\n";
    cout << "Kikapcsolas: ";
    l1->turnOff();
    if (l1->isOn())
        cout << "Hiba: kikapcsolas utan is vilagit a lampa.\n";

    cout << "RGBLamp tesztek" << endl;
    RGBLamp *rl = new RGBLamp("Ceiling lamp");
    Lamp *l2 = rl;
    if (l2->isOn())
        cout << "Hiba: kezdetben kikapcsoltnak kell lennie az RGB lampanak.\n";
    if (rl->getRed() != 0 || rl->getGreen() != 0 || rl->getBlue() != 0)
        cout << "Hiba: a kikapcsolt lampa szine nem fekete.\n";
    rl->turnOff();
    if (l2->isOn())
        cout << "Hiba: redundans kikapcsolas utan vilagit az RGB lampa.\n";
    cout << "Bekapcsolas: ";
    l2->turnOn();
    if (rl->getRed() != 255 || rl->getGreen() != 255 || rl->getBlue() != 255)
        cout << "Hiba: az RGB lampa kezdetben nem feher.\n";
    rl->turnOn();
    if (!l2->isOn())
        cout << "Hiba: redundans bekapcsolas utan nem vilagit az RGB lampa.\n";
    if (rl->getRed() != 255 || rl->getGreen() != 255 || rl->getBlue() != 255)
        cout << "Hiba: az RGB lampa mar nem feher.\n";
    rl->setColor(100, 128, 200);
    if (rl->getRed() != 100 || rl->getGreen() != 128 || rl->getBlue() != 200)
        cout << "Hiba: az RGB lampa nem a kert szinu.\n";
    cout << "Kikapcsolas: ";
    rl->turnOff();
    if (rl->getRed() != 0 || rl->getGreen() != 0 || rl->getBlue() != 0)
        cout << "Hiba: a kikapcsolt lampa szine nem fekete.\n";
    rl->turnOn();
    if (rl->getRed() != 100 || rl->getGreen() != 128 || rl->getBlue() != 200)
        cout << "Hiba: az RGB lampa nem a kert szinu.\n";

    delete l1;
    delete l2;
    return 0;
}