#include <iostream>
#include <vector>

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
    FieldPlayer(const std::string &name, short speed, short stamina, short shooting, short passing, short tackling) : SoccerPlayer(name, speed, stamina), shooting(shooting), passing(passing), tackling(tackling) {}
    short getShooting() const { return shooting; }
    short getPassing() const { return passing; }
    short getTackling() const { return tackling; }
    short getOverall() const
    {
        return (getSpeed() + getStamina() + getShooting() + getPassing() + getTackling()) / 5;
    }
};

class Goalkeeper : public SoccerPlayer
{
    short reflexes;
    short agility;

public:
    Goalkeeper(const std::string &name, short speed, short stamina, short reflexes, short agility) : SoccerPlayer(name, speed, stamina), reflexes(reflexes), agility(agility) {}
    short getReflexes() const { return reflexes; }
    short getAgility() const { return agility; }
    short getOverall() const
    {
        return (getSpeed() + getStamina() + getReflexes() + getAgility()) / 4;
    }
};

std::ostream &operator<<(std::ostream &os, const SoccerPlayer &s)
{
    os << s.getName() << " (" << s.getOverall() << ")\n";
    return os;
}

class SoccerTeam{
    std::vector<const SoccerPlayer*> team;
public:
    int add(const SoccerPlayer* sp){
        for(auto a:team){
            if (a == sp)
            {
                return false;
            }
        }
        const Goalkeeper* gk = dynamic_cast<const Goalkeeper*>(sp);
        if (gk != nullptr)
        {
            for(auto a: team){
                const Goalkeeper* gk2 = dynamic_cast<const Goalkeeper*>(a);
                if (gk2 != nullptr)
                {
                    return false;
                }
            }
        }
        team.push_back(sp);
        return true;
    }
    int playerCount(){return team.size();}
    const SoccerPlayer* operator[](int index){
        return team[index];
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