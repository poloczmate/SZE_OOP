#include <iostream>
#include <string>
#include <vector>

// Készítsen programot mobiltelefonok és laptopok leltári nyilvántartására
// az alábbiak szerint:
//
// A Laptop és Mobil objektumok egyfajta Termekek
// A Laptop példányosításakor meg kell adni a laptop nevét és árát
// A Mobil példányosításakor meg kell adni a mobil nevét, árát és IMEI számát
//
// A Keszlet osztály úgynevezett singleton osztály:
// a) konstruktorát kívülről nem lehet meghívni
// b) copy konstruktor és assignment le van tiltva
// c) kizárólag a GetInstance() nevű statikus metóduson keresztül kérhető le egy példánya
//
// A Keszlet osztály addTermek() metódusa egy Termekre mutató pointert és egy darabszámot vár
// -- ami a készleten fellelhető darabok számát jelenti
// A Keszlet osztály getQuantity() metódusa egy Termekre mutató pointert vár, és visszaadja, hogy
// az adott Termekből hány darab lelhető fel a készletben

// 3-as jegyért:
// A Keszlet osztály rendel() metódusa egy Termekre mutató pointert vár, illetve egy darabszámot,
// és a készleten fellelhető darabok számát a megadott számmal csökkenti (mintha annyit rendeltek volna)

// 4-es jegyért:
// Készítsen a Keszlet osztályhoz egy checkedRendel() metódust, ami ugyanúgy egy Termekre mutató
// pointert és egy darabszámot vár, viszont kivételt dob, ha nincs a készleten elegendő darab a termékből

// 5-ös jegyzért:
// Készítsen a Keszlet osztályhoz egy addTermekChecked() metódust, ami egy Termekre mutató pointert vár
// amennyiben az adott termékkel azonos termék már szerepel a nyilvántartásban, annak darabszámát növelje új
// Termek felvétele helyett

class Termek{

};

class Mobil : public Termek{
    std::string name;
    int price;
    std::string IMEI;
public:
    Mobil(std::string name, int price, std::string IMEI) : name(name), price(price), IMEI(IMEI) {}
};

class Laptop : public Termek{
    std::string name;
    int price;
public:
    Laptop(std::string name, int price) : name(name), price(price) {}
};

class Keszlet{
    Keszlet() {}
    Keszlet(const Keszlet&) = delete; // copy assignement, copy konstruktor letiltva
	Keszlet& operator=(const Keszlet&) = delete;
	std::vector<std::pair<Termek*, int>> keszlet_vec;
public:
    static Keszlet* GetInstance(){
        static Keszlet* k = new Keszlet();
        return k;
    }
};

int main(){
    // van ketfele termek: Laptop es Mobil
	// Termek absztrakt ososztaly, uh nem peldanyosithato:
	// Termek t("Gyarto", 2);
	Termek* laptop = new Laptop("Asus", 1000);
	Termek* mobil1 = new Mobil("Samsung", 80, "15-372612-847221-1");
	Termek* mobil2 = new Mobil("Samsung", 800, "62-882612-847221-1");
	Termek* mobil3 = new Mobil("Apple", 3000, "75-262612-847221-1");

	//Keszlet keszlet; // nem mukodik mert Keszlet singleton
	Keszlet* keszlet = Keszlet::GetInstance(); // GetInstance statikus valtozot hoz letre es ad vissza
	// Keszlet keszlet2 = *keszlet; // nem mukodik mert copy es assignment le van tiltva
	// Keszlet keszlet2(*keszlet); // nem mukodik, mert copy le van tiltva
	Keszlet* keszlet2 = Keszlet::GetInstance(); // mivel statikus valtozot ad vissza, csak 1x hozza letre
	if (keszlet == keszlet2) {
		std::cout << "Eljen eljen: ugyanaz a cim!!" << std::endl;
	}
	keszlet->addTermek(laptop, 15);
	keszlet->addTermek(mobil1, 9);
	keszlet->addTermek(mobil2, 23);

	std::cout << laptop->getName() << " " << keszlet->getQuantity(laptop) << " mennyisegben all rendelkezesre" << std::endl; // 15
	std::cout << mobil3->getName() << " " << keszlet->getQuantity(mobil3) << " mennyisegben all rendelkezesre" << std::endl; // 0

    delete laptop;
	delete mobil1;
	delete mobil2;
	delete mobil3;

    return 0;
}