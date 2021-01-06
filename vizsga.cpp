#include <iostream>
#include <string>
#include <vector>
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
            cout << getName() << " turned OFF" << std::endl;
        }
        else
        {
            on = true;
            cout << getName() << " turned ON" << std::endl;
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
        fenyero = uj;
        if (fenyero > 100)
        {
            fenyero = 100;
            //cout << getName() << " turned ON at " << brightness << "% brightness"<<endl;
        }
        if (fenyero < 1)
        {
            fenyero = 1;
            //cout << getName() << " turned ON at " << brightness << "% brightness"<<endl;
        }
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
            cout << getName() << " turned ON at " << getBrightness() << "% brightness" << std::endl;
        }
        else
        {
            setOff();
            cout << getName() << " turned OFF" << std::endl;
        }
    }
};

class Room{
    std::vector<Lamp*> lampak;
public:
    ~Room(){
        for (auto l : lampak)
        {
            delete l;
        }
    }
    void add(Lamp *l)
    {
        lampak.push_back(l);
    }
    int lampCount(){
        return lampak.size();
    } 
    Lamp& operator[](int index)
    {
        return *lampak.at(index);
    }
    void setAllLamps(bool on){
        for(auto l: lampak){
            if(l->isOn() != on) l->flip();
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
    r.setAllLamps(false);
    r.setAllLamps(false);
    r.setAllLamps(true);
    r.setAllLamps(true);
    r.setAllLamps(false);

    r.add(new DimmableLamp("Ceiling lamp"));
    cout << "DimmableLamp is bought" << endl;
    cout << "Test 5: " << r.lampCount() << endl;
    cout << "Test 6: " << r[1].isOn() << endl;
    r[1].flip();
    cout << "Test 7: " << r[1].isOn() << endl;
    r.setAllLamps(false);
    r[0].flip();
    r.setAllLamps(true);
    r[1].flip();
    r.setAllLamps(true);
    r.setAllLamps(true);
    r.setAllLamps(false);
    r.setAllLamps(false);
}