#include <iostream>
#include <string>
#include <vector>

class Part
{
    std::string name;
    int age = 0;
    const int lifetime;

public:
    Part(std::string name, int lifetime) : name(name), lifetime(lifetime) {}
    std::string getName() const
    {
        return name;
    }
    int getAge(){
        return age;
    }
    void repair()
    {
        age = 0;
    }
    void amortize()
    {
        age++;
    }
    bool isHealthy()
    {
        if (age <= lifetime)
        {
            return true;
        }
        else
            return false;
    }
    void print()
    {
        std::cout << getName() << std::endl;
    }
};

class Vehicle
{
protected:
    std::string name;
    std::vector<Part *> parts;

public:
    Vehicle(const std::string &name) : name(name) {}
    std::string getName() const
    {
        return name;
    }
    void addPart(Part *p)
    {
        parts.push_back(p);
    }
    virtual void print() = 0;
    void amortizeParts()
    {
        for (auto p : parts)
        {
            p->amortize();
        }
    }
    void repairParts()
    {
        for (auto p : parts)
        {
            if (!p->isHealthy())
            {
                p->repair();
            }
        }
    }
};

class Car : public Vehicle
{
public:
    Car(const std::string &name) : Vehicle(name)
    {
        addPart(new Part("front-left-wheel", 5));
        addPart(new Part("rear-left-wheel", 5));
        addPart(new Part("front-right-wheel", 5));
        addPart(new Part("rear-right-wheel", 5));
    }
    virtual void print() override{
        std::cout << "Car named " << getName() << " with " << parts.size() << " parts:\n";
        for (auto p : parts) {
            std::cout << "\t" << p->getName() << " (" << p->getAge() << " years old)";
            if (!p->isHealthy()) std::cout << " - Needs repair!";
            std::cout << std::endl;
        }
	}
};

class MotorBike : public Vehicle
{
public:
    MotorBike(std::string name) : Vehicle(name)
    {
        addPart(new Part("front-wheel", 5));
        addPart(new Part("rear-wheel", 5));
    }
    virtual void print() override
    {
        std::cout << "Car named " << getName() << " with " << parts.size() << " parts:\n";
        for (auto p : parts) {
            std::cout << "\t" << p->getName() << " (" << p->getAge() << " years old)";
            if (!p->isHealthy()) std::cout << " - Needs repair!";
            std::cout << std::endl;
        }
    }
};

class VehiclePark
{
    std::vector<Vehicle *> vehicles;

public:
    void addVehicle(Vehicle *v)
    {
        vehicles.push_back(v);
    }
    void printVehicles()
    {
        for (auto v : vehicles)
        {
            v->print();
        }
    }
    void amortize()
    {
        for (auto v : vehicles)
        {
            v->amortizeParts();
        }
    }
    void repairCars()
    {
        for (auto c : vehicles)
        {
            Car *test = dynamic_cast<Car *>(c);
            if (test != nullptr)
            {
                c->repairParts();
            }
        }
    }
    void repairBikes()
    {
        for (auto b : vehicles)
        {
            MotorBike *test = dynamic_cast<MotorBike *>(b);
            if (test != nullptr)
            {
                b->repairParts();
            }
        }
    }
};

int main()
{
    Vehicle* c1 = new Car("Oliver's Ferrari");
    Vehicle* c2 = new Car("Erno's Porsche");
    Vehicle* c3 = new Car("Adam's Mercedes");
    Vehicle* mb1 = new MotorBike("Mate's Harley");

	c1->addPart(new Part("Air conditioner", 2));
    c2->addPart(new Part("Engine", 6));
    c3->addPart(new Part("Piston", 7));
    c3->addPart(new Part("Spark plug", 3));

	VehiclePark vehiclepark;
	vehiclepark.addVehicle(c1);
	vehiclepark.addVehicle(c2);

    vehiclepark.amortize();
    std::cout << "After 1 year:\n";
    vehiclepark.printVehicles();

	vehiclepark.addVehicle(c3);
	vehiclepark.addVehicle(mb1);

    for (int y = 2; y < 10; ++y) {
        vehiclepark.amortize();
        std::cout << "After " << y << " years:\n";
        vehiclepark.printVehicles();
        if (y == 6) vehiclepark.repairCars();
        else if (y == 7) vehiclepark.repairBikes();
    }
    std::cout << "\nPress Enter to exit...\n";
    std::cin.get();

    return 0;

}