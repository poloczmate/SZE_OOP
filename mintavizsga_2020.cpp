#include <iostream>
#include <string>
#include <vector>

/*
    A 2 származtatott osztály a ClonableString és a ClonableNumber, előbbi egy std::string-et tároljon, utóbbi egy double-t. Ezeket az adatokat a konstruktornak lehessen megadni, és a getString() ill. getNumber() metódusokkal lehessen lekérdezni.
    A clone() metódus dinamikusan hozzon létre egy másolatot az objektumból, és adja vissza a másolat címét. A visszatérési érték típusa minden osztályban az adott osztályra mutató pointer legyen!

    A feladat 2. része egy CloneContainer osztály elkészítése. Ez tetszőleges, előre nem ismert számú, Clonable interfészt megvalósító objektumot tudjon tárolni.
    Legyen egy push_back() metódusa, ami a paraméterként kapott Clonable objektumot leklónozza, és a clone() által visszaadott címet tárolja el. A tároláshoz használható STL tároló vagy saját implementáció is 
    A destruktor gondoskodjon a klónok destruktálásáról!
    Legyen egy [] operátora is, ami adjon vissza egy Clonable referenciát a megadott indexű klónra! És legyen egy size() metódusa is, ami visszaadja a tárolt objektumok darabszámát!
    Bár normál esetben egy ilyen tárolóhoz meg kellene írni a másoló konstruktort és az értékadás operátort is, ez most nem a feladat része, csak gyakorlásként megoldható szorgalmi részfeladat.
*/
class Clonable {
public:
    virtual ~Clonable() = default;
    virtual Clonable* clone() const = 0;
};

class ClonableString : public Clonable{
    std::string s;
public:
    ClonableString(std::string s) : s(s) {}
    std::string getString() const { return s;}
    virtual Clonable* clone() const{
        Clonable* c = new ClonableString(s);
        return c;
    }
};

class ClonableNumber : public Clonable{
    double d;
public:
    ClonableNumber(double d) : d(d) {}
    double getNumber() const { return d;}
    virtual Clonable* clone() const{
        Clonable* c = new ClonableNumber(d);
        return c;
    }
};

class CloneContainer{
    std::vector<Clonable*> cont;
public:
    void push_back(const ClonableNumber c) {
		Clonable* a = c.clone();
		cont.push_back(a);
	}
	void push_back(const ClonableString c) {
		Clonable* a = c.clone();
		cont.push_back(a);
	}
    ~CloneContainer(){
        for(auto c : cont){
            delete c;
        }
    }
    Clonable& operator[](int index){
        return *cont[index];
    }
    int size(){
        return cont.size();
    }
};

int main(){
    //first tasks main
    using namespace std;
    /*
    const ClonableString str1("text");
    string testStr = str1.getString();
    cout << "str1 = " << testStr << endl;
    ClonableString* str2 = str1.clone();
    cout << "str2 = " << str2->getString() << endl;

    const ClonableNumber num1(3.14);
    double testNum = num1.getNumber();
    cout << "num1 = " << testNum << endl;
    ClonableNumber* num2 = num1.clone();
    cout << "num2 = " << num2->getNumber() << endl;

    delete str2;
    delete num2;
*/
    //second tasks main
    

    const ClonableString str1("szo");
    const ClonableString str2("szoveg");
    const ClonableString str3("word");

    const ClonableNumber num1(4.2);
    const ClonableNumber num2(-6.66);

    CloneContainer clones;
    clones.push_back(str1);
    clones.push_back(num1);
    clones.push_back(str2);
    cout << clones.size() << " clones have been made\n";

    Clonable& i1 = clones[0];
    string testStr = dynamic_cast<ClonableString*>(&i1)->getString();
    cout << "Item 1: " << testStr << endl;

    ClonableNumber* i2 = dynamic_cast<ClonableNumber*>(&clones[1]);
    cout << "Item 2: " << i2->getNumber() << endl;

    ClonableString& i3 = dynamic_cast<ClonableString&>(clones[2]);
    cout << "Item 3: " << i3.getString() << endl;

    clones.push_back(str3);
    clones.push_back(num2);
    cout << clones.size() << " clones have been made\n";

    ClonableString* i4 = dynamic_cast<ClonableString*>(&clones[3]);
    cout << "Item 4: " << i4->getString() << endl;

    ClonableNumber& i5 = dynamic_cast<ClonableNumber&>(clones[4]);
    cout << "Item 5: " << i5.getNumber() << endl;
    
    return 0;
}