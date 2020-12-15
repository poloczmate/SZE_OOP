#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

using namespace std;

class SoccerPlayer
{
    const std::string name;
    short speed;
    short stamina;

public:
    SoccerPlayer(const std::string &name, short speed, short stamina); //TODO
    virtual ~SoccerPlayer() = default;
    const std::string &getName() const { return name; }
    short getSpeed() const { return speed; }
    short getStamina() const { return stamina; }
    virtual short getOverall() const = 0;
};

SoccerPlayer::SoccerPlayer(const std::string &name, short speed, short stamina) : name(name), speed(speed), stamina(stamina) {}

class FieldPlayer : public SoccerPlayer
{
    short shooting;
    short passing;
    short tackling;

public:
    short getShooting() const
    {
        return shooting;
    }

    short getPassing() const
    {
        return passing;
    }

    short getTackling() const
    {
        return tackling;
    }
    short getOverall() const
    {
        short sum = getSpeed() + getStamina() + shooting + passing + tackling;
        return floor(sum / 5);
    }
    FieldPlayer(std::string name, short speed, short stamina, short shooting, short passing, short tackling) : SoccerPlayer(name, speed, stamina), shooting(shooting), passing(passing), tackling(tackling) {}
};

class Goalkeeper : public SoccerPlayer
{
    short reflexes;
    short agility;

public:
    short getOverall() const
    {
        short sum = getSpeed() + getStamina() + reflexes + agility;
        return floor(sum / 4);
    }
    short getReflexes() const
    {
        return reflexes;
    }
    short getAgility() const
    {
        return agility;
    }
    Goalkeeper(std::string name, short speed, short stamina, short reflexes, short agility) : SoccerPlayer(name, speed, stamina), reflexes(reflexes), agility(agility) {}
};

ostream &operator<<(ostream &os, const SoccerPlayer &sp)
{
    os << sp.getName() << " (" << sp.getOverall() << ")";
    return os;
}

class SoccerTeam
{
    vector<const SoccerPlayer *> c;

public:
    int add(const SoccerPlayer *s)
    {
        if (find(c.begin(), c.end(), s) != c.end()) // ha nem talalja akkor a keresett vektor vege lesz ellenorizzuk bent van e mar
        {
            return false;
        }
        //try
        
        int counter = 0;
        const Goalkeeper *gk = dynamic_cast<const Goalkeeper *>(s);
        if (gk != nullptr) // ha nem nullptr akkor s kapus!
        {
            for (auto a : c)
            {
                const Goalkeeper *test = dynamic_cast<const Goalkeeper *>(a);
                if (test != nullptr)    //ha nem nullptr akkor kapus ezert noveljuk a szamot
                {
                    counter++;
                }
            }
            if (counter != 0)
            {
                return false;
            }
        }
        c.push_back(s);
        return true;
    }
    int playerCount() const
    {
        int counter = 0;
        for (auto a : c)
        {
            counter++;
        }
        //return c.size();
        return counter;
    }
    const SoccerPlayer *operator[](int index)
    {
        return c[index];
    }
    ~SoccerTeam()
    {
        for (auto a : c)
        {
            delete a;
        }
    }
};

int main()
{
    using namespace std;

    SoccerTeam team;

    if (team.add(new FieldPlayer("C. Ronaldo", 90, 85, 95, 91, 76)))
        cout << "Player added: " << *team[team.playerCount() - 1] << endl;
    else
        cout << "Failed to add C. Ronaldo.\n";

    if (team.add(new FieldPlayer("L. Messi", 88, 93, 75, 88, 96)))
        cout << "Player added: " << *team[team.playerCount() - 1] << endl;
    else
        cout << "Failed to add L. Messi.\n";

    if (team.add(new Goalkeeper("M. Neuer", 89, 87, 94, 95)))
        cout << "Player added: " << *team[team.playerCount() - 1] << endl;
    else
        cout << "Failed to add M. Neuer.\n";

    if (team.add(team[0]))
        cout << "Player added: " << *team[team.playerCount() - 1] << endl;
    else
        cout << "Failed to add " << *team[0] << endl;

    if (team.add(team[1]))
        cout << "Player added: " << *team[team.playerCount() - 1] << endl;
    else
        cout << "Failed to add " << *team[1] << endl;

    if (team.add(team[2]))
        cout << "Player added: " << *team[team.playerCount() - 1] << endl;
    else
        cout << "Failed to add " << *team[2] << endl;

    Goalkeeper *gk2 = new Goalkeeper("H. Lloris", 85, 86, 92, 94);
    if (team.add(gk2))
        cout << "Player added: " << *team[team.playerCount() - 1] << endl;
    else
        cout << "Failed to add " << *gk2 << endl;
    delete gk2;

    for (size_t i = 0; i < (size_t)team.playerCount(); ++i)
    {
        cout << *team[i] << endl;
        cout << team[i]->getName() << endl;
        cout << team[i]->getSpeed() << endl;
        cout << team[i]->getStamina() << endl
             << endl;
    }
}