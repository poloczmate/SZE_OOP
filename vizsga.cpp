#include <iostream>
#include <string>
using namespace std;

class Lamp
{
private:
    bool on = false;
    string name;

public:
    Lamp(string name) : name(name) {}
    bool isOn()
    {
        return on;
    }
    void setOn()
    {
        on = true;
    }
    void setOff()
    {
        on = false;
    }
    string getName()
    {
        return name;
    }
    virtual void flip()
    {
        if (isOn())
        {
            on = false;
            cout << getName() << "turned OFF" << std::endl;
        }
        else
        {
            on = true;
            cout << getName() << "turned ON" << std::endl;
        }
    }
    virtual ~Lamp() {}
};

class DimmableLamp : public Lamp
{
    int fenyero;

public:
    DimmableLamp(string name) : Lamp(name), fenyero(100) {}
    void setBrightness(int uj)
    {
        /*fenyero += a;
        if(fenyero > 100) fenyero = 100;
        if(fenyero < 1) fenyero = 1;*/
        if (fenyero + uj > 100)
        {
            fenyero = 100;
            //cout << getName() << " turned ON at " << brightness << "% brightness"<<endl;
        }
        if (fenyero + uj < 1)
        {
            fenyero = 1;
            //cout << getName() << " turned ON at " << brightness << "% brightness"<<endl;
        }
        fenyero += uj;
        //cout << getName() << " turned ON at " << brightness << "% brightness" << endl;
    }
    int getBrightness()
    {
        if (!isOn())
        {
            return 0;
        }
        return fenyero;
    }
    void flip()
    {
        if (!isOn())
        {
            setOn();
            cout << getName() << " turned ON at " << getBrightness() << " brightness" << std::endl;
        }
        else
        {
            setOff();
            cout << getName() << " turned OFF" << std::endl;
        }
    }
};
//innentol main **************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
int main()
{
    using namespace std;

    Lamp *l1 = new Lamp("Desk lamp");
    cout << "Test 1: " << l1->isOn() << endl;
    l1->flip();
    cout << "Test 2: " << l1->isOn() << endl;
    l1->flip();
    cout << "Test 3: " << l1->isOn() << endl;

    cout << "DimmableLamp tests" << endl;
    DimmableLamp *dl = new DimmableLamp("Ceiling lamp");
    Lamp *l2 = dl;
    cout << "Test 4: " << l2->isOn() << endl;
    cout << "Test 5: " << dl->getBrightness() << endl;
    l2->flip();
    cout << "Test 6: " << l2->isOn() << endl;
    cout << "Test 7: " << dl->getBrightness() << endl;
    dl->setBrightness(50);
    cout << "Test 8: " << dl->getBrightness() << endl;
    l2->flip();
    cout << "Test 9: " << l2->isOn() << endl;
    l2->flip();
    dl->setBrightness(0);
    cout << "Test 10: " << dl->getBrightness() << endl;
    dl->setBrightness(101);
    cout << "Test 11: " << dl->getBrightness() << endl;

    delete l1;
    delete l2;

    return 0;
}