#include <iostream>
#include <vector>

/*
A feladat 1. része az alább ismertetett Lamp osztály, és a belőle öröklődő DimmableLamp osztály definiálása.
A Lamp egy egyszerű lámpát modellez, ami vagy be van kapcsolva, vagy nincs. Létrehozáskor legyen kikapcsolva! Létrehozáskor meg kell adni a lámpa nevét is, amit jegyezzen meg! Az állapotát lehessen lekérdezni az isOn() metódussal,
 és lehessen ki/bekapcsolni a flip() metódussal! Utóbbi írja ki, hogy "<lámpa neve> turned <ON/OFF>" a standard kimenetre!
A DimmableLamp egy állítható fényerejű lámpát modellez, ahol a fényerő 1-100% közti egész értékeket vehet fel, amíg a lámpa világít.
Ez alapértelmezetten 100%, de lehessen állítani a setBrightness(int value) metódussal, ami a paraméterben adott értékre állítja az aktuális fényerőt!
Ha 100% fölé növelnék, akkor is csak 100% legyen az érték, ha pedig 1% alá csökkenne, akkor legyen 1%! Az aktuális fényerőt lehessen lekérdezni a getBrightness() metódussal, ami adjon vissza 0-t, ha a lámpa ki van kapcsolva!
Bekapcsoláskor automatikusan álljon be az utoljára beállított fényerőre, és ezt írja is ki bekapcsoláskor: "<lámpa neve> turned ON at <1-100>% brightness"!
*/
class Lamp
{
    bool status;
    std::string name;

public:
    Lamp(std::string name) : name(name), status(false) {}
    bool isOn() { return status; }
    virtual ~Lamp() {}
    virtual void flip()
    {
        if (status == false)
        {
            status = true;
            std::cout << name << " turned ON" << std::endl;
        }
        else
        {
            status = false;
            std::cout << name << " turned OFF" << std::endl;
        }
    }
    std::string getName() const
    {
        return name;
    }
    bool getStatus() const
    {
        return status;
    }
    void setStatus(bool status)
    {
        this->status = status;
    }
};

class DimmableLamp : public Lamp
{
    int brightness;

public:
    DimmableLamp(std::string name) : Lamp(name), brightness(100) {}
    void setBrightness(int value)
    {
        if (value > 100)
        {
            brightness = 100;
        }
        else if (value <= 0)
        {
            brightness = 1;
        }
        else
        {
            brightness = value;
        }
    }
    int getBrightness()
    {
        if (getStatus() == false)
            return 0;
        return brightness;
    }
    virtual void flip()
    {
        if (getStatus() == false)
        {
            setStatus(true);
            std::cout << getName() << " turned ON at " << brightness << "% brightness" << std::endl;
        }
        else
        {
            setStatus(false);
            std::cout << getName() << " turned OFF" << std::endl;
        }
    }
};

class Room
{
    std::vector<Lamp *> lamps;

public:
    void add(Lamp *l)
    {
        lamps.push_back(l);
    }
    ~Room()
    {
        for (auto a : lamps)
        {
            delete a;
        }
    }
    int lampCount() { return lamps.size(); }
    Lamp &operator[](int index)
    {
        return *lamps.at(index);
    }
    void setAllLamps(bool on)
    {
        for (auto a : lamps)
        {
            if (a->getStatus() != on)
            {
                a->flip();
            }
        }
    }
    void adjustLights(int change)
    {
        for (auto a : lamps)
        {
            DimmableLamp *dl = dynamic_cast<DimmableLamp *>(a);
            if (dl != nullptr)
            {
                if (dl->getStatus() == true)
                {
                    if (dl->getBrightness() + change > 100)
                    {
                        dl->setBrightness(100);
                    }
                    else if (dl->getBrightness() + change < 1)
                    {
                        dl->setBrightness(1);
                    }
                    else
                    {
                        dl->setBrightness(dl->getBrightness() + change);
                    }
                }
            }
        }
    }
};

int main()
{
    using namespace std;

    Room r;
    cout << "Test 1: " << r.lampCount() << endl;
    r.add(new Lamp("Desk lamp"));
    cout << "Test 2: " << r.lampCount() << endl;
    cout << "Test 3: " << r[0].isOn() << endl;
    r[0].flip();
    cout << "Test 4: " << r[0].isOn() << endl;

    r.add(new DimmableLamp("Ceiling lamp"));
    cout << "DimmableLamp is bought" << endl;
    cout << "Test 5: " << r.lampCount() << endl;
    cout << "Test 6: " << r[1].isOn() << endl;
    r.adjustLights(-50);
    r[1].flip();
    cout << "Test 7: " << r[1].isOn() << endl;
    r.adjustLights(-10);
    r.setAllLamps(false);
    r[0].flip();
    r.setAllLamps(true);
    r[1].flip();
    r[0].flip();
    r.setAllLamps(true);
    r.setAllLamps(true);
    r.setAllLamps(false);
    r.setAllLamps(false);
    r.add(new DimmableLamp("Smart lamp"));
    r.setAllLamps(true);
    r.adjustLights(-50);
    r.setAllLamps(false);
    r.setAllLamps(true);
    r.adjustLights(70);
    r.setAllLamps(false);
    r.setAllLamps(true);
}