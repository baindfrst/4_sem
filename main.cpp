#include <iostream>
#include <iostream>
#include <vector>
#include <string>
class Player;
class Citizen;
class Item;
class Builds;
class Ore;
class Enem;
class Cave;
class Pickax;
class Swords;
class Farm;
class Wiz;

using namespace std;

class Base
{
public:
    friend Citizen;
    std::vector <Builds*> *buildsBase;
    std::vector <Citizen*> *citizensBase;
    std::vector <Item*> *itemsBase;
    Cave *caveBase;
    int size;
    int food;
    friend ostream& operator<<(ostream& out, Base *base);
    ~Base();
    Base();
    Base* operator-(Builds* build);
    Base(std::vector <Builds*> *buildsBase, std::vector <Citizen*> *citizensBase, std::vector <Item*> *itemsBase, int size, int food, Cave *caveBase);
    void goToCave(Player *player);
    void eventAtackBase();
    void newBuild(Player *player);
    //void newSitizen(Player *player);
    //checkBaseChest(Player *player);
    void goToBuld(Player *player);
    void newDay();
};

ostream& operator<< (ostream& out, Base *base)
{
    out << "food: " << base->food << std::endl;
    out << "size: " << base->size << std::endl;
    return out;
}

class Builds{
    friend Base;
public:
    std::string name;
    int size;
    Citizen *citizen;
    Builds(std::string name, int size, Citizen *citizen);
    void tellCitizen(Player *player);
    virtual void newCitizen(Citizen *citizen);
};

Base* Base::operator-(Builds* build)
{
    this->size -= build->size;
    return this;
}


class Item
{
public:
    std::string name;
    std::string rar;
    int mainCost;
    int addedCost;
    std::string description;
    Item(std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    friend bool operator==(const Item a, const  Pickax b);
    friend bool operator==(const Item a, const  Swords b);
    friend bool operator==(const Item a, const  Wiz b);
};

class HandItem: public Item{
public:
    int damage;
    int damageType;
    int upgrades = 0;
    HandItem(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    virtual void Abilite(Enem *enem, Player *player);
    virtual void Atack(Enem *enem);
    virtual void Atack(Ore *ore, Player *player);
    friend ostream& operator<<(ostream& out, HandItem *item);
    void upgrade(Player *player);
};


ostream& operator<<(ostream& out, HandItem *item)
{
    out<<item->name<< " description: " << item->description << std::endl;
    out << "damage: " << item->damage << " cost: " << item->mainCost << std::endl;
    return out;
}

class Ore: public Item
{
public:
    int density;
    Ore(int density, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    virtual void tryGet(Player *player);
};

class Swords: public HandItem {
public:
    Swords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
};

class Wiz: public HandItem {
public:
    Wiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
};

class Pickax: public HandItem {
public:
    Pickax();
    virtual ~Pickax();
    Pickax(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    virtual void Atack(Enem *enem);
    virtual void Atack(Ore *ore, Player *player);
    void Abilite(Enem *enem, Player *player);
};


class Enem {
public:
    float hp;
    float damage;
    std::string name;
    std::vector <Item*> *loot;
    int *resists;
    Enem();
    ostream& operator<<(ostream& out);
    Enem(std::string name, float hp, int damage, int *resists, std::vector<Item*> *loot);
    ~Enem();
    virtual void frstAbil(Player *player);
    virtual void scndAbil(Player *player);
    virtual void thrdAbil(Player *player);
};

ostream& Enem::operator<<(ostream& out)
{
    out << name << " HP: " << hp << " Damage: " << damage << std::endl;
    return out;
}

class CaveSect {
public:
    std::vector<Ore*> *loot;
    std::vector<Enem*> *enem;
    CaveSect(std::vector<Ore*> *loot, std::vector<Enem*> *enem);
    ~CaveSect();
    Enem* findEnem();
    Ore* findLoot();
    void search(Player *player);
};

class Cave {
public:
    std::vector<CaveSect*> *cavePrev;
    std::vector<CaveSect*> *caveNext;
    CaveSect *caveCur;
    Cave();
    ~Cave();
    void operator++(int i);
    void operator++();
    void exitCave();
};

class World {
public:
    int day;
    std::string name;
    Base *playerBase;
    ~World();
    World();
    void eventAtack();
    void eventRand();
    void newDay();
};

class Slime: public Enem {
public:
    Slime(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot);
    void frstAbil(Player *player);
    void scndAbil(Player *player);
    void thrdAbil(Player *player);
};

class Wizard: public Enem {
public:
    Wizard(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot);
    void frstAbil(Player *player);
    void scndAbil(Player *player);
    void thrdAbil(Player *player);
};

class Rober: public Enem {
public:
    Rober(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot);
    void frstAbil(Player *player);
    void scndAbil(Player *player);
    void thrdAbil(Player *player);
};

class Wolf: public Enem {
public:
    Wolf(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot);
    void frstAbil(Player *player);
    void scndAbil(Player *player);
    void thrdAbil(Player *player);
};

class Golem: public Enem {
public:
    Golem();
    Golem(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot);
    void frstAbil(Player *player);
    void scndAbil(Player *player);
    void thrdAbil(Player *player);
};

class Goblin: public Enem {
public:
    Goblin(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot);
    void frstAbil(Player *player);
    void scndAbil(Player *player);
    void thrdAbil(Player *player);
};

class WindOre: public Ore
{
public:
    WindOre();
    void tryGet(Player *player);
};

class HolyOre: public Ore
{
public:
    HolyOre();
    void tryGet(Player *player);
};

class DarkOre: public Ore
{
public:
    DarkOre();
    void tryGet(Player *player);
};

class IceOre: public Ore
{
public:
    IceOre();
    void tryGet(Player *player);
};

class Coal: public Ore
{
public:
    Coal();
    void tryGet(Player *player);
};

class Iron: public Ore
{
public:
    Iron();
    void tryGet(Player *player);
};

class ManaStone: public Ore
{
public:
    ManaStone();
    void tryGet(Player *player);
};

class FireOre: public Ore
{
public:
    FireOre();
    void tryGet(Player *player);
};

class SmallSword: public Swords {
public:
    SmallSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class Sword: public Swords {
public:
    Sword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class FireSword: public Swords {
public:
    FireSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Atack(Enem *enem);
    void Abilite(Enem *enem, Player *player);
};

class ManaSword: public Swords {
public:
    ManaSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class WindSword: public Swords {
public:
    WindSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class IceSwords: public Swords {
public:
    IceSwords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class HolySwords: public Swords {
public:
    HolySwords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class DarkSwords: public Swords {
public:
    DarkSwords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class FireWiz: public Wiz {
public:
    FireWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};
class WindWiz: public Wiz {
public:
    WindWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};
class HolyWiz: public Wiz {
public:
    HolyWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};
class DarkWiz: public Wiz {
public:
    DarkWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};
class IceWiz: public Wiz {
public:
    IceWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description);
    void Abilite(Enem *enem, Player *player);
    void Atack(Enem *enem);
};

class CommonPickax: public Pickax {
public:
    CommonPickax();
    void Atack(Enem *enem);
    void Atack(Ore *ore, Player *player);
};
class FirePickax: public Pickax {
public:
    FirePickax();
    void Atack(Enem *enem);
    void Atack(Ore *ore, Player *player);
};
class WindPickax: public Pickax {
public:
    WindPickax();
    void Atack(Enem *enem);
    void Atack(Ore *ore, Player *player);
};
class HolyPickax: public Pickax {
public:
    HolyPickax();
    void Atack(Enem *enem);
    void Atack(Ore *ore, Player *player);
};

class Seeds {
public:
    int needSoil;
    int food;
    Seeds(int needSoil, int food);
    int daylive();
};

class Player
{
public:
    friend Citizen;
    float hp;
    int money;
    std::vector <HandItem*> *inventUse;
    std::pair<int, Ore*>* inventBack[8];
    friend ostream& operator<<(ostream& out, Player* player);
    friend ostream& operator<<(ostream& out, std::vector <HandItem*> *inventUse);
    friend ostream& operator<<(ostream& out, std::pair<int, Ore*>* *inventBack);
    World *WorldPlayer;
    ~Player();
    Player(World* WorldPlayer);

    void fight(Enem *enem);

};

ostream& operator<<(ostream& out, Player *player)
{
    std::cout << "ur har" << std::endl;
    out << "hp - " << player->hp <<std::endl;
    out << "money - " << player->money << std::endl;
    return out;
}

ostream& operator<<(ostream& out, std::vector <HandItem*> *inventUse)
{
    std::cout << "ur invent" << std::endl;
    for(int i = 0; i != inventUse->size(); i++)
    {
        out << inventUse->at(i) << std::endl;
    }
    return out;
}
ostream& operator<<(ostream& out, std::pair<int, Ore*>* *inventBack)
{
    std::cout << "ur invent ore" << std::endl;
    for(int i = 0; i != 8; i++)
    {
        out << inventBack[i]->second->name << "--" << inventBack[i]->first << std::endl;
    }
    return out;
}

class Market: public Builds
{
public:
    Market(Citizen *citizen);
    void newCitizen(Citizen *citizen);
};

class Chest: public Builds
{
public:
    Chest(Citizen *citizen);
    void newCitizen(Citizen *citizen);
};

class MainHouse: public Builds
{
public:
    MainHouse(Citizen *citizen);
    void newCitizen(Citizen *citizen);
};

class Tower: public Builds
{
public:
    Tower(Citizen *citizen);
    void newCitizen(Citizen *citizen);
};

class Hospital: public Builds
{
public:
    Hospital(Citizen *citizen);
    void newCitizen(Citizen *citizen);
};

class Forge: public Builds
{
public:
    Forge(Citizen *citizen);
    void newCitizen(Citizen *citizen);
};

class Farm: public Builds
{
public:
    static int soilQuolity;
    Farm(Citizen *citizen);
    void newCitizen(Citizen *citizen);
    static void setQuolity(int quol);
};

int Farm::soilQuolity = 5;

class Citizen
{
public:
    friend Builds;
    int prof;
    int food;
    int hp;
    int dmg;
    Citizen(int prof, int food, int hp, int dmg);
    virtual void newDay(Base *base);
    virtual void talk(Player *player);
};

class CommonCitizen: public Citizen
{
public:
    void newDay(Base *base);
    void talk(Player *player);
    CommonCitizen();
};

class Healer: public Citizen
{
public:
    void newDay(Base *base);
    void talk(Player *player);
    Healer();
};

class MarketMan: public Citizen
{
public:
    //vector <vector <int, *Item>> assort; //не успел((
    void newDay(Base *base);
    void talk(Player *player);
    MarketMan();
};

class Forger: public Citizen
{
public:
    void newDay(Base *base);
    void talk(Player *player);
    Forger();
};

class Farmer: public Citizen {
public:
    Seeds *seed;
    void newDay(Base *base);
    void talk(Player *player);
    Farmer();
    ~Farmer();
};

Farmer::~Farmer()
{
    delete seed;
}

Base::Base(vector <Builds*> *buildsBase, vector <Citizen*> *citizensBase, vector <Item*> *itemsBase, int size, int food, Cave *caveBase) {
    this->buildsBase = buildsBase;
    this->citizensBase = citizensBase;
    this->itemsBase = itemsBase;
    this->size = size;
    this->food = food;
    this->caveBase = caveBase;
}

void Base::goToCave(Player *player) {
    bool inCave = true;
    while(inCave)
    {
        std::cout << "этаж: " << caveBase->cavePrev->size() << std::endl;
        std::cout << "предметы на этаже" <<std::endl;
        std::cout << "---" <<std::endl;
        for(int i = 0; i != caveBase->caveCur->loot->size(); i++)
        {
            std::cout << caveBase->caveCur->loot->at(i)->name << std::endl;
        }
        std::cout << "---" <<std::endl;
        std::cout << "враги на этаже" <<std::endl;
        std::cout << "---" <<std::endl;
        for(int i = 0; i != caveBase->caveCur->enem->size(); i++)
        {
            std::cout << caveBase->caveCur->enem->at(i)->name << std::endl;
        }
        std::cout << "---" <<std::endl;
        std::cout << "выбирите действие: " <<std::endl;
        std::cout << "1. поиски" <<std::endl;
        std::cout << "2. идти вниз" <<std::endl;
        std::cout << "3. подняться на этаж выше" <<std::endl;
        std::cout << "4. выйти" <<std::endl;
        int mode;
        std::cin >> mode;
        system("clear");
        switch (mode) {
            case 1:
                caveBase->caveCur->search(player);
                break;
            case 2:
                (*caveBase)++;
                break;
            case 3:
                ++(*caveBase);
                break;
            case 4:
                caveBase->exitCave();
                inCave = false;
                break;
            default:
                throw -1;
                break;

        }
    }
}

void Base::goToBuld(Player *player) {
    std::cout << "выбирите здание" << std::endl;
    for(int i = 0; i != buildsBase->size(); i++)
    {
        std::cout << i << " " << buildsBase->at(i)->name << std::endl;
    }
    int num;
    std::cin >> num;
    system("clear");
    if(num >= 0 && num <= buildsBase->size())
    {
        std::cout << "вы зачем то пришли к: " <<  buildsBase->at(num)->name << std::endl;
        std::cout << "хотите поговорить с житилем?(yes/no)" << std::endl;
        std::string answ;
        cin >> answ;
        system("clear");
        if(answ == "yes")
        {
            buildsBase->at(num)->tellCitizen(player);
        }
    } else
    {
        throw -1;
    }
}

void Base::eventAtackBase() {
    for(int i = 0; i != citizensBase->size(); i++)
    {
        citizensBase->at(i)->hp -= 1;
    }
}

void Base::newBuild(Player *player) {
    std::cout << "что вы хотите построить ?" << std::endl;
    std::cout << "1. сундук(особо и не нужен)" << std::endl;
    std::cout << "2. магазин" << std::endl;
    std::cout << "3. главное здание(особо и не надо)" << std::endl;
    std::cout << "4. вышка (а зачем?)" << std::endl;
    std::cout << "5. больница" << std::endl;
    std::cout << "6. кузня" << std::endl;
    std::cout << "7. ферма" << std::endl;
    int mode;
    std::cin >> mode;
    system("clear");
    Citizen *cit;
    switch (mode) {
        case 1:
            cit = new CommonCitizen();
            citizensBase->push_back(cit);
            buildsBase->push_back(new Chest(cit));
            break;
        case 2:
            cit = new MarketMan();
            citizensBase->push_back(cit);
            buildsBase->push_back(new Market(cit));
            break;
        case 3:
            cit = new CommonCitizen();
            citizensBase->push_back(cit);
            buildsBase->push_back(new MainHouse(cit));
            break;
        case 4:
            cit = new CommonCitizen();
            citizensBase->push_back(cit);
            buildsBase->push_back(new Tower(cit));
            break;
        case 5:
            cit = new Healer();
            citizensBase->push_back(cit);
            buildsBase->push_back(new Hospital(cit));
            break;
        case 6:
            cit = new Forger();
            citizensBase->push_back(cit);
            buildsBase->push_back(new Forge(cit));
            break;
        case 7:
            cit = new Farmer();
            citizensBase->push_back(cit);
            buildsBase->push_back(new Farm(cit));
            break;
        default:
            throw -1;
            break;
    }
}

Builds::Builds(std::string name, int size, Citizen *citizen)
{
    this->name = name;
    this->size = size;
    this->citizen = citizen;
}

void Builds::tellCitizen(Player *player)
{
    citizen->talk(player);
}
void Builds::newCitizen(Citizen *citizen)
{
    this->citizen = citizen;
}

Cave::Cave() {
    cavePrev = new std::vector<CaveSect*>;
    caveNext = new std::vector<CaveSect*>;
    caveCur = new CaveSect(new std::vector<Ore*>,new std::vector<Enem*>);
}
Cave::~Cave() {
    for(int i = 0; i != cavePrev->size(); i++)
    {
        delete cavePrev->at(i);
    }
    delete cavePrev;
    for(int i = 0; i != caveNext->size(); i++)
    {
        delete caveNext->at(i);
    }
    delete caveNext;
    delete caveCur;
}

void Cave::operator++(int i) {
    std::cout << "спуск ниже..." << std::endl;
    cavePrev->push_back(caveCur);
    if(caveNext->size() == 0)
    {
        std::vector<Ore*> *ores = new vector<Ore*>;
        std::vector<Enem*> *enems = new vector<Enem*>;
        caveCur = new CaveSect(ores, enems);
        for(int i = 0; i < rand()%cavePrev->size(); i++) {
            switch (rand() % (cavePrev->size()>8?4:8)) {
                case 0:
                    ores->push_back(new Coal());
                    break;
                case 1:
                    ores->push_back(new Iron());

                    break;
                case 2:
                    ores->push_back(new FireOre());

                    break;
                case 3:
                    ores->push_back(new IceOre());

                    break;
                case 4:
                    ores->push_back(new HolyOre());

                    break;
                case 5:
                    ores->push_back(new DarkOre());
                    break;
                case 6:
                    ores->push_back(new WindOre());
                    break;
                case 7:
                    ores->push_back(new ManaStone());
                    break;
                default:
                    break;

            }
        }
        for(int i = 0; i < rand()%cavePrev->size(); i++) {
            std::vector<Item*> *lootMob = new std::vector<Item*>;
            for (int i = 0; i < rand()%4; i++)
            {
                switch (rand() % (cavePrev->size()>8?4:8)) {
                    case 0:
                        lootMob->push_back(new Coal());
                        break;
                    case 1:
                        lootMob->push_back(new Iron());
                        break;
                    case 2:
                        lootMob->push_back(new FireOre());
                        break;
                    case 3:
                        lootMob->push_back(new IceOre());
                        break;
                    case 4:
                        lootMob->push_back(new HolyOre());
                        break;
                    case 5:
                        lootMob->push_back(new DarkOre());
                        break;
                    case 6:
                        lootMob->push_back(new WindOre());
                        break;
                    case 7:
                        lootMob->push_back(new ManaStone());
                        break;
                    default:
                        break;

                }
            }
            int *rez = new int[2];
            switch (rand() %(cavePrev->size()>4?6:3)) {
                case 0:
                    rez = new int[2];
                    rez[0] = 0;
                    rez[1] = 1;
                    enems->push_back(new Slime(string("Slime"), 2 + int(cavePrev->size()), int(cavePrev->size())/2, rez, lootMob));
                    break;
                case 1:
                    rez = new int[2];
                    rez[0] = 2;
                    rez[1] = 3;
                    enems->push_back(new Rober(string("Rober"), 1 + cavePrev->size(), cavePrev->size(), rez, lootMob));
                    break;
                case 2:
                    rez = new int[2];
                    rez[0] = 2;
                    rez[1] = 1;
                    enems->push_back(new Wolf(string("Wolf"), 3 + cavePrev->size(), cavePrev->size(), rez, lootMob));
                    break;
                case 3:
                    rez = new int[2];
                    rez[0] = 9;
                    rez[1] = 9;
                    enems->push_back(new Golem(string("Golem"), 20 + cavePrev->size(), cavePrev->size()/2, rez, lootMob));
                    break;
                case 4:
                    rez = new int[2];
                    rez[0] = 4;
                    rez[1] = 7;
                    enems->push_back(new Wizard(string("Wizard"), 1 + cavePrev->size() / 2, cavePrev->size()/4, rez, lootMob));
                    break;
                case 5:
                    rez = new int[2];
                    rez[0] = 5;
                    rez[1] = 5;
                    enems->push_back(new Goblin(string("Goblin"), 5 + cavePrev->size(), cavePrev->size() * 1.5, rez, lootMob));
                    break;
                    break;
                default:
                    break;

            }
        }
    }
    else
    {
        caveCur = caveNext->at(caveNext->size() - 1);
        caveNext->pop_back();
    }
}

void Cave::exitCave() {
}

CaveSect::CaveSect(std::vector<Ore*> *loot, std::vector<Enem*> *enem) {
    this->loot = loot;
    this->enem = enem;
}
CaveSect::~CaveSect() {
    for(int i = 0; i != loot->size(); i++)
    {
        delete loot->at(i);
    }
    delete loot;
    for(int i = 0; i != enem->size(); i++)
    {
        delete enem->at(i);
    }
    delete enem;
}

Enem* CaveSect::findEnem()
{
    if(enem->size() > 0)
    {
        Enem *ret = enem->at(enem->size() - 1);
        enem->pop_back();
        return ret;
    }
    else
    {
        return nullptr;
    }
}
Ore* CaveSect::findLoot()
{
    if(loot->size() > 0)
    {
        Ore *ret = loot->at(loot->size() - 1);
        loot->pop_back();
        return ret;
    }
    else
    {
        return nullptr;
    }
}

void CaveSect::search(Player *player) {
    if(rand()%2)
    {
        Enem* tofight = findEnem();
        if(tofight != nullptr)
        {
            std::cout << "вы нашли врага" << std::endl;
            player->fight(tofight);
            // for(int i = 0; i != tofight->loot->size(); i++)
            // {
            //     delete tofight->loot->at(i);
            // }
        }
        else
        {
            Ore* lootpl = findLoot();
            if(lootpl != nullptr)
            {
                std::cout << "вы нашли руду: " << lootpl->name << std::endl;
                lootpl->tryGet(player);
                delete lootpl;
            }
            else
            {
                throw -1;
            }
        }
    }
    else
    {
        Ore* lootpl = findLoot();
        if(lootpl != nullptr)
        {
            std::cout << "вы нашли руду: " << lootpl->name << std::endl;
            lootpl->tryGet(player);
            delete lootpl;
        }
        else
        {
            Enem* tofight = findEnem();
            if(tofight != nullptr)
            {
                std::cout << "вы нашли врага" << std::endl;
                player->fight(tofight);
                // for(int i = 0; i != tofight->loot->size(); i++)
                // {
                //     delete tofight->loot->at(i);
                // }
            }
            else
            {
                throw -1;
            }
        }
    }
}


void Cave::operator++() {
    std::cout << "идем вверх..." << std::endl;
    if(cavePrev->size() == 0){
        exitCave();
    }
    else
    {
        caveNext->push_back(caveCur);
        caveCur = cavePrev->at(cavePrev->size() - 1);
       cavePrev->pop_back();
    }
}

Chest::Chest(Citizen *citizen): Builds("", 2, citizen)
{
    string name;
    std::cout << "введите название здания: ";
    std::cin >> name;
    system("clear");
    this->name = name;
}
void Chest::newCitizen(Citizen *citizen)
{
    delete citizen;
    this->citizen = citizen;
}

Citizen::Citizen(int prof, int food, int hp, int dmg)
{
    this->prof = prof;
    this->food = food;
    this->hp = hp;
    this->dmg = dmg;
}

Coal::Coal(): Ore(1, "Coal", "common", 4, 1, "а хорошо горит") {
}

void Coal::tryGet(Player *player) {
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь")
        {
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        std::cout << "теперь вы чумазый" << std::endl;
        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}

CommonPickax::CommonPickax():Pickax(2, 0, "кирка", "common", 15, 8, "кирка, что еще тут сказать"){
}

void CommonPickax::Atack(Enem *enem) {
    if(enem->name == "Golem")
    {
        enem->hp = 0;
        std::cout << "вы нанесли критический удар" << std::endl;
    } else
    {
        enem->hp -= damage * (1 - 0.1 * enem->resists[1]);
        std::cout << "вы нанесли удар " << enem->name << " и нанесли ему " << damage * (1 - 0.1 * enem->resists[1]) << std::endl;
    }
}

void CommonPickax::Atack(Ore *ore, Player *player) {
        if(ore->name == "Coal") {
            player->inventBack[0]->first += 1;
            std::cout << "вы добыли 1 Coal" << std::endl;
        }
        if(ore->name == "Iron") {
            player->inventBack[1]->first += 1;
            std::cout << "вы добыли 1 Iron" << std::endl;
        }
        if(ore->name == "FireOre") {
            player->inventBack[2]->first += 1;
            std::cout << "вы добыли 1 FireOre" << std::endl;
        }
        if(ore->name == "DarkOre") {
            player->inventBack[3]->first += 1;
            std::cout << "вы добыли 1 DarkOre" << std::endl;
        }
        if(ore->name == "HolyOre") {
            player->inventBack[4]->first += 1;
            std::cout << "вы добыли 1 HolyOre" << std::endl;
        }
        if(ore->name == "IceOre") {
            player->inventBack[5]->first += 1;
            std::cout << "вы добыли 1 IceOre" << std::endl;
        }
        if(ore->name == "WindOre") {
            player->inventBack[6]->first += 1;
            std::cout << "вы добыли 1 WindOre" << std::endl;
        }
        if(ore->name == "ManaStone") {
            player->inventBack[7]->first += 1;
            std::cout << "вы добыли 1 ManaStone" << std::endl;
        }
}

DarkOre::DarkOre():Ore(4, "DarkOre", "rar rar", 18, 5, "Тьма сгущается рядом с этим камнем"){
}
void DarkOre::tryGet(Player *player) {
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь")
        {
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        if(numb > PickaxInPLayer.size() || numb < 0)
        {
            throw -1;
        }

        if(player->inventBack[0]->first != 0)
        {
            player->inventBack[0]->first -=1;
        }

        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}

DarkSwords::DarkSwords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Swords(damage, damageType, name, rar, mainCost, addedCost, description) {
}

void DarkSwords::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage - enem->resists[0] << " урона" << std::endl;
}

void DarkSwords::Abilite(Enem *enem, Player *player) {
    enem->hp -= (damage * (1 - (0.1 * enem->resists[1])) * 4);
    std::cout << "вы махнули мечем в сотору " << enem->name << "и в него полетело 4 темных пятна и нанесли ему " << (damage * (1 - (0.1 * enem->resists[1])) * 4) << "у рона" << std::endl;
}

DarkWiz::DarkWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Wiz(damage, damageType, name, rar, mainCost, addedCost, description) {
}

void DarkWiz::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы выпустили сферу из посоха в " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[1])) << " урона" << std::endl;
}

void DarkWiz::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage * 2;
    std::cout << "вы запустили большую темную сферу в " << enem->name << "и нанесли ему " << damage * 2 << "у рона" << std::endl;
}

Enem::Enem(std::string name, float hp, int damage, int *resists, std::vector<Item*> *loot) {
    this->name = name;
    this->hp = hp;
    this->damage = damage;
    this->resists = resists;
    this->loot = loot;

}
Enem::~Enem() {
    for(int i = 0; i != loot->size(); i++)
    {
        delete (*loot)[i];
    }
    delete loot;
}

Farm::Farm(Citizen *citizen): Builds("", 4, citizen)
{
    string name;
    std::cout << "введите название здания: ";
    std::cin >> name;
    system("clear");
    this->name = name;
}
void Farm::newCitizen(Citizen *citizen)
{
    this->citizen = citizen;
}


void Farm::setQuolity(int quol) {
    soilQuolity = quol;
}

Farmer::Farmer(): Citizen(3, 5, 5, 2)
{
    seed = new Seeds(0,0); 
}

void Farmer::newDay(Base *base)
{
    base->food += seed->daylive();
    if(base->food > food)
    {
        base->food -= food;
    }
    else
    {
        hp--;
    }
}

void Farmer::talk(Player *player)
{
    std::cout << "хотите посадить семена?(yes/no)" << std::endl;
    std::string name;
    std::cin >> name;
    system("clear");
    if(name == "yes")
    {
        seed = new Seeds(rand()%5, 10 + rand()%5);
    }

}

FireOre::FireOre(): Ore(2, "FireOre", "rar", 10, 2, "не сказать, что тепло, но и не холодно"){
}
void FireOre::tryGet(Player *player) {
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь"){
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        if(player->hp != 1)
        {
            player->hp--;
            std::cout << "наверное, все же стоило брать перчатки для этого..." << std::endl;
        }
        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}


FirePickax::FirePickax() :Pickax(2, 0, "огненная кирка", "rar", 50, 8, "кирка, котороая может плавить все, что угодно")
{}

void FirePickax::Atack(Enem *enem) {
    if(enem->name == "Golem")
    {
        enem->hp = 0;
        std::cout << "вы нанесли критический удар" << std::endl;
    } else
    {
        enem->hp -= damage * (1 - 0.1 * enem->resists[1]);
        std::cout << "вы нанесли удар " << enem->name << " и нанесли ему " <<  damage * (1 - 0.1 * enem->resists[1]) << std::endl;
    }
}

void FirePickax::Atack(Ore *ore, Player *player) {
   if(ore->name == "Coal") {
            player->inventBack[0]->first += 2;
            std::cout << "вы добыли 2 Coal" << std::endl;
        }
        if(ore->name == "Iron") {
            player->inventBack[1]->first += 2;
            std::cout << "вы добыли 2 Iron" << std::endl;
        }
        if(ore->name == "FireOre") {
            player->inventBack[2]->first += 2;
            std::cout << "вы добыли 2 FireOre" << std::endl;
        }
        if(ore->name == "DarkOre") {
            player->inventBack[3]->first += 2;
            std::cout << "вы добыли 2 DarkOre" << std::endl;
        }
        if(ore->name == "HolyOre") {
            player->inventBack[4]->first += 2;
            std::cout << "вы добыли 2 HolyOre" << std::endl;
        }
        if(ore->name == "IceOre") {
            player->inventBack[5]->first += 2;
            std::cout << "вы добыли 2 IceOre" << std::endl;
        }
        if(ore->name == "WindOre") {
            player->inventBack[6]->first += 2;
            std::cout << "вы добыли 2 WindOre" << std::endl;
        }
        if(ore->name == "ManaStone") {
            player->inventBack[7]->first += 2;
            std::cout << "вы добыли 2 ManaStone" << std::endl;
        }
}

FireSword::FireSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Swords(damage, damageType, name, rar, mainCost, addedCost, description)
{}

void FireSword::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage - enem->resists[0] << " урона" << std::endl;
}

void FireSword::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы махнули мечем в сотору противника и запистили в него огненную волну, после чего подбежали и ударили " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[0])) + damage * (1 - (0.1 * enem->resists[1])) << "у рона" << std::endl;
    player->hp -= 1;
    std::cout << "но вы обожглись и получили урон от огня: " << 1 << std::endl;
}

FireWiz::FireWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Wiz(damage, damageType, name, rar, mainCost, addedCost, description) {
}

void FireWiz::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы выпустили сферу из посоха в " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[1])) << " урона" << std::endl;
}

void FireWiz::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage * 3 * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы запустили большой шар в  " << enem->name << "и нанесли ему " << damage * 3 * (1 - (0.1 * enem->resists[1])) << "у рона" << std::endl;
    player->hp -= 1;
    std::cout << "но он обжог и вас и нанес вам урон: " << 1 << std::endl;
}

Forge::Forge(Citizen *citizen) : Builds("", 4, citizen)
{
    string name;
    std::cout << "введите название здания: ";
    std::cin >> name;
    system("clear");
    this->name = name;
}
void Forge::newCitizen(Citizen *citizen)
{
    this->citizen = citizen;
}

Forger::Forger(): Citizen(1, 5, 5, 3){
}

void Forger::newDay(Base *base)
{
    if(base->food > food)
    {
        base->food -= food;
    }
    else
    {
        hp--;
    }
}

void Forger::talk(Player *player)
{
    std::cout<<"выберите то, что вы хотети изготовить:" <<std::endl;
    std::cout<<"1. мечи"<<std::endl;
    std::cout<<"2. посохи"<<std::endl;
    std::cout<<"3. кирка"<<std::endl;
    std::cout<<"4. улучшить предмет"<<std::endl;
    int mode;
    std::cin>>mode;
    system("clear");
    switch (mode) {
        case 1:
            std::cout << "1.железный кинжал: 4 железной руды и 6 угля" << std::endl;
            std::cout << "2.железный меч: 10 железной руды и 10 угля" << std::endl;
            std::cout << "3.огненный меч: 10 огненной руды и 20 угля" << std::endl;
            std::cout << "4.меч темноты: 6 темной руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "5.святой меч: 6 святой руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "6.меч морозов: 10 ледяной руды и 8 угля" << std::endl;
            std::cout << "7.меч бурь: 10 руды ветра и 12 угля" << std::endl;
            std::cout << "8.мана-меч: 10 кристалов маны, 4 железной руды и 8 угля" << std::endl;
            std::cin >> mode;
            system("clear");
            switch (mode) {
                case 1:
                    if (player->inventBack[1]->first > 4 && player->inventBack[0]->first > 6) {
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 6;
                        player->inventUse->push_back(new SmallSword(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 2:
                    if (player->inventBack[1]->first > 10 && player->inventBack[0]->first > 10) {
                        player->inventBack[1]->first -= 10;
                        player->inventBack[0]->first -= 10;
                        player->inventUse->push_back(new Sword(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 3:
                    if (player->inventBack[2]->first > 10 && player->inventBack[0]->first > 20) {
                        player->inventBack[2]->first -= 10;
                        player->inventBack[0]->first -= 20;
                        player->inventUse->push_back(new FireSword(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 4:
                    if (player->inventBack[3]->first > 6 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[3]->first -= 6;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new DarkSwords(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 5:
                    if (player->inventBack[4]->first > 6 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventBack[4]->first -= 6;
                        player->inventUse->push_back(new HolySwords(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 6:
                    if (player->inventBack[5]->first > 10 && player->inventBack[0]->first > 8) {
                        player->inventBack[5]->first -= 10;
                        player->inventBack[0]->first -= 6;
                        player->inventUse->push_back(new IceSwords(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 7:
                    if (player->inventBack[6]->first > 10 && player->inventBack[0]->first > 12) {
                        player->inventBack[6]->first -= 10;
                        player->inventBack[0]->first -= 12;
                        player->inventUse->push_back(new WindSword(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 8:
                    if (player->inventBack[7]->first > 10 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 6) {
                        player->inventBack[1]->first -= 4;
                        player->inventBack[7]->first -= 10;
                        player->inventBack[0]->first -= 6;
                        player->inventUse->push_back(new ManaSword(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;


                default:
                    throw -1;
                    break;
            }
        case 2:
            std::cout << "1.огненный посох: 18 огненной руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "2.посох темноты: 12 темной руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "3.святой посох: 12 святой руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "4.посох морозов: 18 ледяной руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "5.посох бурь: 12 руды ветра, 4 железной руды и 14 угля" << std::endl;
            std::cin >> mode;
            system("clear");
            switch (mode) {
                case 1:
                    if (player->inventBack[2]->first > 18 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[2]->first -= 18;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new FireWiz(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 2:
                    if (player->inventBack[3]->first > 12 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[3]->first -= 12;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new DarkWiz(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 3:
                    if (player->inventBack[4]->first > 12 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[4]->first -= 12;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new HolyWiz(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;
                case 4:
                    if (player->inventBack[5]->first > 18 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[5]->first -= 18;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new IceWiz(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                case 5:
                    if (player->inventBack[6]->first > 12 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[6]->first -= 12;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new WindWiz(1, 1, "c", "r", 1, 1, "d"));
                    }
                    else
                    {
                        throw -1;
                    }
                    break;

                default:
                    throw -1;
                    break;
            }
        case 3:
            std::cout << "1.простая кирка:  6 железной руды и 8 угля" << std::endl;
            std::cout << "2.огненная кирка: 10 огненной руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "3.святая кирка: 8 святой руды, 4 железной руды и 14 угля" << std::endl;
            std::cout << "4.кирка бурь: 10 руды ветра, 4 железной руды и 14 угля" << std::endl;
            std::cin >> mode;
            system("clear");
            switch (mode) {
                case 1:
                    if (player->inventBack[1]->first > 6 && player->inventBack[0]->first > 8) {
                        player->inventBack[1]->first -= 6;
                        player->inventBack[0]->first -= 8;
                        player->inventUse->push_back(new CommonPickax());
                    } else {
                        throw -1;
                    }
                    break;
                case 2:
                    if (player->inventBack[2]->first > 10 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[2]->first -= 10;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new FirePickax());
                    } else {
                        throw -1;
                    }
                    break;
                case 3:
                    if (player->inventBack[4]->first > 8 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[4]->first -= 8;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new HolyPickax());
                    } else {
                        throw -1;
                    }
                    break;
                case 4:
                    if (player->inventBack[6]->first > 10 && player->inventBack[1]->first > 4 && player->inventBack[0]->first > 14) {
                        player->inventBack[6]->first -= 10;
                        player->inventBack[1]->first -= 4;
                        player->inventBack[0]->first -= 14;
                        player->inventUse->push_back(new WindPickax());
                    } else {
                        throw -1;
                    }
                    break;
                default:
                    throw -1;
                    break;
            }

        case 4:
        {
            std::cout << "какой предмент улучшить?" << std::endl;
            for(int i = 0; i != player->inventUse->size(); i++)
            {
                std::cout << i << " " << player->inventUse->at(i) << std::endl;
            }
            int num;
            std::cin >> num;
            player->inventUse->at(num)->upgrade(player);
            break;
        }
        default:
        {
            throw -1;
            break;
        }

    }
    std::cout << "хотите продолжить разговор?(yes/no)" << std::endl;
    std::string cont;
    std::cin >> cont;
    system("clear");
    if(cont == "yes")
    {
        Forger::talk(player);
    }
}

Goblin::Goblin(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot): Enem(name, hp, damage, resists, loot){
}

void Goblin::frstAbil(Player *player) {
    std::cout << name << " нанес вам удар, вы получили урон: " << damage << std::endl;
    player->hp -= damage;
}
void Goblin::scndAbil(Player *player) {
    if(player->money > 0)
    {
        player->money -= 1;
        std::cout << name << " украл у вас монету" << std::endl;
    }
}
void Goblin::thrdAbil(Player *player) {
    if(player->money > 0)
    {
        player->money -= 2;
        std::cout << name << " украл у вас 2 монеты" << std::endl;
    }
}

Golem::Golem(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot): Enem(name, hp, damage, resists, loot){
}
void Golem::frstAbil(Player *player) {
    std::cout << name << " нанес вам удар, вы получили урон: " << damage << std::endl;
    player->hp -= damage;
}
void Golem::scndAbil(Player *player) {
    std::cout << name << " нанес вам удар, вы получили урон: " << damage * 1.5 << std::endl;
    player->hp -= damage * 1.5;
}
void Golem::thrdAbil(Player *player) {
    std::cout << name << "промазал" << std::endl;
}

HandItem::HandItem(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Item(name, rar, mainCost, addedCost, description)
{
    this->damage = damage;
    this->damageType = damageType;
}

void HandItem::upgrade(Player *player)
{
    std::cout << "для улучшения нужно: " << (upgrades + 1) * 2 << " manastone" << std::endl;
    std::cout << "улучшать?(yes/no)" << std::endl;
    std::string answ;
    std::cin >> answ;
    if(answ == "yes")
    {
        if(player->inventBack[7]->first >= (upgrades + 1) * 2)
        {
            player->inventBack[7]->first -= (upgrades + 1) * 2;
            damage += 4;
        }
        else
        {
            throw -1;
        }
    } 
}

Healer::Healer():Citizen(2, 5, 5, 2)
{
}

void Healer::newDay(Base *base)
{
    if(base->food > food)
    {
        base->food -= food;
    }
    else
    {
        hp--;
    }
}

void Healer::talk(Player *player)
{
    std::cout << "хотите подлечится: стоит 2 монеты?(yes/no)" << std::endl;
    std::string answ;
    std::cin >> answ;
    system("clear");
    if(answ == "yes")
    {
        if(player->money > 1)
        {
            player->money -= 2;
            player->hp += 5;
        } else
        {
            throw -1;
        }
    }
}

CommonCitizen::CommonCitizen():Citizen(2, 5, 5, 2)
{
}

void CommonCitizen::newDay(Base *base)
{
    if(base->food > food)
    {
        base->food -= food;
    }
    else
    {
        hp--;
    }
}

void CommonCitizen::talk(Player *player)
{
    std::cout << "мне не хочется говорить" << std::endl;
}



HolyOre::HolyOre() :Ore(4, "HolyOre", "rar rar", 18, 5, "вы чуствуете, что кто-то следит за вами")
{}
void HolyOre::tryGet(Player *player) {
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь")
        {
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        if(numb > PickaxInPLayer.size() || numb < 0)
        {
            throw -1;
        }
        player->hp += 1;
        std::cout << "Камень затянул ваши раны" << std::endl;
        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}
HolyPickax::HolyPickax():Pickax(2, 0, "кирка", "common", 15, 8, "кирка, что еще тут сказать")
{}

void HolyPickax::Atack(Enem *enem) {
    if(enem->name == "Golem")
    {
        enem->hp = 0;
        std::cout << "вы нанесли критический удар" << std::endl;
    } else
    {
        enem->hp -= damage * (1 - 0.1 * enem->resists[1]);
        std::cout << "вы нанесли удар " << enem->name << " и нанесли ему " << damage * (1 - 0.1 * enem->resists[1]) << std::endl;
    }
}

void HolyPickax::Atack(Ore *ore, Player *player) {
    player->hp+=1;
    cout<< "вы исцелились на 1 хп";
    if(ore->name == "Coal") {
            player->inventBack[0]->first += 1;
            std::cout << "вы добыли 1 Coal" << std::endl;
        }
        if(ore->name == "Iron") {
            player->inventBack[1]->first += 1;
            std::cout << "вы добыли 1 Iron" << std::endl;
        }
        if(ore->name == "FireOre") {
            player->inventBack[2]->first += 1;
            std::cout << "вы добыли 1 FireOre" << std::endl;
        }
        if(ore->name == "DarkOre") {
            player->inventBack[3]->first += 1;
            std::cout << "вы добыли 1 DarkOre" << std::endl;
        }
        if(ore->name == "HolyOre") {
            player->inventBack[4]->first += 1;
            std::cout << "вы добыли 1 HolyOre" << std::endl;
        }
        if(ore->name == "IceOre") {
            player->inventBack[5]->first += 1;
            std::cout << "вы добыли 1 IceOre" << std::endl;
        }
        if(ore->name == "WindOre") {
            player->inventBack[6]->first += 1;
            std::cout << "вы добыли 1 WindOre" << std::endl;
        }
        if(ore->name == "ManaStone") {
            player->inventBack[7]->first += 1;
            std::cout << "вы добыли 1 ManaStone" << std::endl;
        }
}

HolySwords::HolySwords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):Swords(damage, damageType, name, rar, mainCost, addedCost, description)
{}

void HolySwords::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[1])) << " урона" << std::endl;
}

void HolySwords::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage / 2 * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[1])) << " урона" << std::endl;
    player->hp += damage / 2 * (1 - (0.1 * enem->resists[1]));
    std::cout << "так же вы исцелились на : " << damage / 2 * (1 - (0.1 * enem->resists[1])) << std::endl;
}

HolyWiz::HolyWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Wiz(damage, damageType, name, rar, mainCost, addedCost, description)
{}

void HolyWiz::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы выпустили сферу из посоха в " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[1])) << " урона" << std::endl;
}

void HolyWiz::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage;
    player->hp += damage;
    std::cout << "вs стукнули посохом в землю возле " << enem->name << "и нанесли ему " << damage << "у рона" << std::endl;
    std::cout << "так же вы исцелились на: " << damage << std::endl;
}

Hospital::Hospital(Citizen *citizen): Builds(name, 4, citizen)
{
    string name;
    std::cout << "введите название здания: ";
    std::cin >> name;
    system("clear");
    this->name = name;
}
void Hospital::newCitizen(Citizen *citizen)
{
    this->citizen = citizen;
}

IceOre::IceOre(): Ore(2, "IceOre", "rar", 10, 2, "почти как кусок льда, но только больше")
{}
void IceOre::tryGet(Player *player) {
    std::cout << "ent" << std::endl;
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь")
        {
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    std::cout << "gened" << std::endl;
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        if(player->inventBack[2]->first != 0)
        {
            player->inventBack[2]->first -=1;
            std::cout << "кажется, какой то кусочек огненной руды превратился в камень" << std::endl;
        }
        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}

IceSwords::IceSwords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Swords(damage, damageType, name, rar, mainCost, addedCost, description)
{}

void IceSwords::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage - enem->resists[0] << " урона" << std::endl;
}

void IceSwords::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы махнули мечем в сотору противника и запистили в него ледяные осколки, после чего подбежали и ударили " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[0])) + damage * (1 - (0.1 * enem->resists[1])) << "у рона" << std::endl;
    player->hp -= 1;
    std::cout << "но вы подскальзнулись бежа к противнику и получили урон: " << 1 << std::endl;
}

IceWiz::IceWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): Wiz(damage, damageType, name, rar, mainCost, addedCost, description)
{}

void IceWiz::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы выпустили сферу из посоха в " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[1])) << " урона" << std::endl;
}

void IceWiz::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage/2 * 3 * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы запустили кучу сосулик в " << enem->name << "и нанесли ему " << damage/2 * 3 * (1 - (0.1 * enem->resists[1])) << "у рона" << std::endl;
    player->hp -= 1;
    std::cout << "но одна отлетела в вас и нанесла вам: " << 1 << std::endl;
}

Iron::Iron():Ore(1, "Iron", "common", 6, 1, "куй, пока горячо"){
}

void Iron::tryGet(Player *player) {
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь")
        {
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}

Item::Item(std::string name, std::string rar, int mainCost, int addedCost, std::string description) {
    this->name = name;
    this->rar = rar;
    this->mainCost = mainCost;
    this->addedCost = addedCost;
    this->description = description;
}

bool operator==(const Item a, const  Pickax b) {
    return typeid(a) == typeid(b);
}
bool operator==(const Item a, const  Swords b) {
    return typeid(a) == typeid(b);
}
bool operator==(const Item a, const  Wiz b) {
    return typeid(a) == typeid(b);
}

MainHouse::MainHouse(Citizen *citizen): Builds(name, 4, citizen)
{
    string name;
    std::cout << "введите название здания: ";
    std::cin >> name;
    system("clear");
    this->name = name;
}
void MainHouse::newCitizen(Citizen *citizen)
{
    this->citizen = citizen;
}

ManaStone::ManaStone():Ore(2, "ManaStone", "rar", 12, 4, "неужели магия...")
{}
void ManaStone::tryGet(Player *player) {
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь")
        {
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        if(player->inventBack[0]->first != 0)
        {
            player->inventBack[0]->first--;
            player->inventBack[rand()%8]->first += 1;
            std::cout << "произошла магия у вас в рюкзаке" << std::endl;
        }
        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}

ManaSword::ManaSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):Swords(damage, damageType, name, rar, mainCost, addedCost, description){
}

void ManaSword::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage - enem->resists[0] << " урона" << std::endl;
}

void ManaSword::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы махнули мечем в сотору противника и запистили в него магические осколки, после чего подбежали и ударили " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[0])) + damage * (1 - (0.1 * enem->resists[1])) << "у рона" << std::endl;
    player->hp -= 1;
    std::cout << "но вы использовали слишком много маны и получили урон: " << 1 << std::endl;
}

Market::Market(Citizen *citizen): Builds("", 4, citizen)
{
    string name;
    std::cout << "введите название здания: ";
    std::cin >> name;
    system("clear");
    this->name = name;
}
void Market::newCitizen(Citizen *citizen)
{
    this->citizen = citizen;
}

MarketMan::MarketMan():Citizen(3, 5, 5, 2){
}

void MarketMan::newDay(Base *base)
{
    if(base->food > food)
    {
        base->food -= food;
    }
    else
    {
        hp--;
    }
}

void MarketMan::talk(Player *player)
{
    std::cout << "хотите что то продать?(yes/no)" << std::endl;
    std::string answ;
    std::cin >> answ;
    system("clear");
    if(answ == "yes")
    {
        std::cout << "что именно?" << std::endl;
        std::cout << "1. руды" << std::endl;
        std::cout << "2. перметы" << std::endl;
        int num;
        std::cin >> num;
        system("clear");
        if(num == 1) {
            for (int i = 0; i != 8; i++) {
                std::cout << i << " " << player->inventBack[i]->second->name << " - " << player->inventBack[i]->first << " ("
                          << player->inventBack[i]->second->mainCost << " +- " << player->inventBack[i]->second->addedCost << ") "
                          << std::endl;
            }
            std::cin >> num;
            system("clear");
            if (player->inventBack[num]->first != 0) {
                player->inventBack[num]->first -= 1;
                int ran = rand() % 3;
                switch (ran) {
                    case 0:
                        player->money += player->inventBack[num]->second->mainCost;
                        break;
                    case 1:
                        player->money += player->inventBack[num]->second->mainCost - player->inventBack[num]->second->addedCost;
                        break;
                    case 2:
                        player->money += player->inventBack[num]->second->mainCost + player->inventBack[num]->second->addedCost;
                        break;
                    default:
                        player->money += player->inventBack[num]->second->mainCost;
                        break;

                }
            } else
            {
                throw -1;
            }
        } else{
            if(num == 2)
            {
                for (int i = 0; i != player->inventUse->size(); i++)
                {
                    std::cout << i << " " << player->inventUse->at(i)->name << " ("
                              << player->inventUse->at(i)->mainCost << " +- " << player->inventUse->at(i)->addedCost << ") "
                              << std::endl;
                }
                std::cin >> num;
                system("clear");
                if(num >= 0 && num < player->inventUse->size() - 1)
                {
                    int ran = rand() % 3;
                    switch (ran) {
                        case 0:
                            player->money += player->inventUse->at(num)->mainCost;
                            break;
                        case 1:
                            player->money += player->inventUse->at(num)->mainCost - player->inventUse->at(num)->addedCost;
                            break;
                        case 2:
                            player->money += player->inventUse->at(num)->mainCost + player->inventUse->at(num)->addedCost;
                            break;
                        default:
                            player->money += player->inventUse[num][1]->mainCost;
                            break;
                    }
                    player->inventUse->erase(player->inventUse->begin() + num);
                } else{
                    throw -1;
                }
            } else{
                throw -1;
            }
        }
    }
}

Ore::Ore(int density, std::string name, std::string rar, int mainCost, int addedCost, std::string description):Item(name, rar, mainCost, addedCost, description){
    this->density = density;
}

Pickax::Pickax():HandItem(-1, -1, "", "", -1, -1, ""){
}


Pickax::Pickax(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):HandItem(damage, damageType, name, rar, mainCost, addedCost, description){
}

Player::Player(World* WorldPlayer) {
    this->WorldPlayer = WorldPlayer;
    hp = 100;
    money = 5;
    inventUse = new std::vector<HandItem*>(2);
    (*inventUse)[0] = new SmallSword(6, 0, "кинжал", "common", 1, 0, "начальное оружие");
    (*inventUse)[1] = new CommonPickax();
    std::pair<int, Ore*> *coal = new std::pair<int, Ore*>;
    std::pair<int, Ore*> *iron = new std::pair<int, Ore*>;
    std::pair<int, Ore*> *fire = new std::pair<int, Ore*>;
    std::pair<int, Ore*> *dark = new std::pair<int, Ore*>;
    std::pair<int, Ore*> *holy = new std::pair<int, Ore*>;
    std::pair<int, Ore*> *ice = new std::pair<int, Ore*>;
    std::pair<int, Ore*> *wind = new std::pair<int, Ore*>;
    std::pair<int, Ore*> *mana = new std::pair<int, Ore*>;
    coal->first = 0;
    coal->second = new Coal();
    iron->first = 0;
    iron->second = new Iron();
    fire->first = 0;
    fire->second = new FireOre();
    dark->first = 0;
    dark->second = new DarkOre();
    holy->first = 0;
    holy->second = new HolyOre();
    ice->first = 0;
    ice->second = new IceOre();
    wind->first = 0;
    wind->second = new WindOre();
    mana->first = 0;
    mana->second = new ManaStone();
    inventBack[0] = coal;
    inventBack[1] = iron;
    inventBack[2] = fire;
    inventBack[3] = dark;
    inventBack[4] = holy;
    inventBack[5] = ice;
    inventBack[6] = wind;
    inventBack[7] = mana;

}

void Pickax::Abilite(Enem *enem, Player *player)
{
    Atack(enem);
}

void Player::fight(Enem *enem) {
    std::cout << "вы сражаетесь с " << enem->name << std::endl;
    while(enem->hp > 0)
    {
        (*enem) << std::cout << '\n' << this << std::endl;
        std::cout << "какое оружие использовать:" << std::endl;
        for(int i = 0; i != inventUse->size(); i++)
        {
            std::cout << i << " " << (*inventUse)[i]->name << std::endl;
        }
        int num;
        std::cin >> num;
        system("clear");
        if(num < 0 || num > inventUse->size())
        {
            throw -1;
        }
        std::cout << "что использовать?" << std::endl;
        std::cout << "1. Atack" << std::endl;
        std::cout << "2. Ability" << std::endl;
        int mode;
        std::cin >> mode;
        system("clear");
        switch (mode) {
            case 1:
                (*inventUse)[num]->Atack(enem);
                break;
            case 2:
                (*inventUse)[num]->Abilite(enem, this);
                break;
            default:
                throw -1;
        }
        if(enem->hp < 1)
        {
            break;
        }
        switch (rand()%3) {
            case 0:
                enem->frstAbil(this);
                break;
            case 1:
                enem->scndAbil(this);
                break;
            case 2:
                enem->thrdAbil(this);
                break;
            default:
                enem->frstAbil(this);
                break;
        }
        if(hp < 0)
        {
            exit(0);
        }
    }
    std::cout << "c " << enem->name << "выпало: " << std::endl;
    for(int i = 0; i != enem->loot->size(); i++)
    {
        std::cout<<enem->loot->at(i)->name << std::endl;
        if(enem->loot->at(i)->name == "Coal")
        {
            inventBack[0]->first += 1;
        }
        if(enem->loot->at(i)->name == "Iron")
        {
            inventBack[1]->first += 1;
        }
        if(enem->loot->at(i)->name == "FireOre")
        {
            inventBack[2]->first += 1;
        }
        if(enem->loot->at(i)->name == "DarkOre")
        {
            inventBack[3]->first += 1;
        }
        if(enem->loot->at(i)->name == "HolyOre")
        {
            inventBack[4]->first += 1;
        }
        if(enem->loot->at(i)->name == "IceOre")
        {
            inventBack[5]->first += 1;
        }
        if(enem->loot->at(i)->name == "WindOre")
        {
            inventBack[6]->first += 1;
        }
        if(enem->loot->at(i)->name == "ManaStone")
        {
            inventBack[7]->first += 1;
        }
    }
}

Rober::Rober(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot):Enem(name, hp, damage, resists, loot){
}
void Rober::frstAbil(Player *player) {
    std::cout << name << " нанес вам удар, вы получили урон: " << damage << std::endl;
    player->hp -= damage;
}
void Rober::scndAbil(Player *player) {
    if(player->money > 0)
    {
        player->money -= 1;
        std::cout << name << "украл у вас монету" << std::endl;
    }
}
void Rober::thrdAbil(Player *player) {
    std::cout << name << "промазал" << std::endl;
}

Seeds::Seeds(int needSoil, int food) {
    this->needSoil = needSoil;
    this->food = food;
}

int Seeds::daylive() {
    return food;
}



Slime::Slime(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot):Enem(name, hp, damage, resists, loot){
}
void Slime::frstAbil(Player *player) {
    std::cout << name << "нанес вам удар, вы получили урон: " << damage << std::endl;
    player->hp -= damage;
}
void Slime::scndAbil(Player *player) {
    std::cout << name << "нанес вам удар, вы получили урон: " << damage * 2 << std::endl;
    player->hp -= damage * 2;
}
void Slime::thrdAbil(Player *player) {
    std::cout << name << "промазал" << std::endl;
}

SmallSword::SmallSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):Swords(damage, damageType, name, rar, mainCost, addedCost, description){
}

void SmallSword::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[0])) << " урона" << std::endl;
}

void SmallSword::Abilite(Enem *enem, Player *player) {
    enem->hp -= ((damage/2) * (1 - (0.1 * enem->resists[0]))) * 4;
    std::cout << "вы нанесли град атак " << enem->name << "и нанесли ему " << ((damage/2) * (1 - (0.1 * enem->resists[0]))) * 4 << "у рона" << std::endl;
    player->hp -= damage/4;
    std::cout << "из вас получился бы плохой шуллер, вы поранились и получили " << (damage/4) << " урона" << std::endl;
}

Sword::Sword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):Swords(damage, damageType, name, rar, mainCost, addedCost, description){
}

void Sword::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[0]));
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[0])) << " урона" << std::endl;
}

void Sword::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage * 3;
    std::cout << "вы раскрутились с мечом и били " << enem->name << "и нанесли ему " << damage * 3 << "у рона" << std::endl;
    player->hp -= enem->damage;
    std::cout << "в конце вы споткнулись и враг вас ударил, нанеся вам: " << enem->damage << std::endl;
}

Swords::Swords(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):HandItem(damage, damageType, name, rar, mainCost, addedCost, description){
}

Tower::Tower(Citizen *citizen): Builds("", 4, citizen)
{
    string name;
    std::cout << "введите название здания: ";
    std::cin >> name;
    system("clear");
    this->name = name;
}
void Tower::newCitizen(Citizen *citizen)
{
    this->citizen = citizen;
}

WindOre::WindOre():Ore(3, "WindOre", "rar", 10, 2, "руда, которая может летать?"){
}
void WindOre::tryGet(Player *player) {
    std::vector <HandItem*> PickaxInPLayer;
    for(int i = 0; i != player->inventUse->size(); i++)
    {
        if(player->inventUse->at(i)->name == "кирка" || player->inventUse->at(i)->name == "огненная кирка" || player->inventUse->at(i)->name == "кирка бурь")
        {
            PickaxInPLayer.push_back(player->inventUse->at(i));
        }
    }
    if(PickaxInPLayer.size() != 0) {
        std::cout << "какую кирку использовать ?" << std::endl;
        for(int i = 0; i != PickaxInPLayer.size(); i++)
        {
            std::cout << i << ' ';
            std::cout << PickaxInPLayer[i]->name << std::endl;
        }
        int numb = 0;
        std::cin >> numb;
        system("clear");
        if(numb > PickaxInPLayer.size() || numb < 0)
        {
            throw -1;
        }
        if(player->money > 1)
        {
            std::cout << "ветер каким-то образом украл у вас монету" << std::endl;
            player->money -= 1;
        }
        if(PickaxInPLayer[numb]->damage >= density)
        {
            PickaxInPLayer[numb]->Atack(this, player);
        }
        else
        {
            std::cout << "не получилось добыть руду" << std::endl;
        }
    }
}

WindPickax::WindPickax():Pickax(2, 0, "кирка бурь", "rar", 50, 8, "кирка, котороая добывет больше, чем есть"){
}

void WindPickax::Atack(Enem *enem) {
    if(enem->name == "Golem")
    {
        enem->hp = 0;
        std::cout << "вы нанесли критический удар" << std::endl;
    } else
    {
        enem->hp -= damage * (1 - 0.1 * enem->resists[1]);
        std::cout << "вы нанесли удар " << enem->name << " и нанесли ему " <<  damage * (1 - 0.1 * enem->resists[1]) << std::endl;
    }
}

void WindPickax::Atack(Ore *ore, Player *player) {
    player->inventBack[0]->first += 1;
    std::cout<< "вы добыли 1 Coal" << std::endl;
    if(ore->name == "Coal") {
            player->inventBack[0]->first += 1;
            std::cout << "вы добыли 1 Coal" << std::endl;
        }
        if(ore->name == "Iron") {
            player->inventBack[1]->first += 1;
            std::cout << "вы добыли 1 Iron" << std::endl;
        }
        if(ore->name == "FireOre") {
            player->inventBack[2]->first += 1;
            std::cout << "вы добыли 1 FireOre" << std::endl;
        }
        if(ore->name == "DarkOre") {
            player->inventBack[3]->first += 1;
            std::cout << "вы добыли 1 DarkOre" << std::endl;
        }
        if(ore->name == "HolyOre") {
            player->inventBack[4]->first += 1;
            std::cout << "вы добыли 1 HolyOre" << std::endl;
        }
        if(ore->name == "IceOre") {
            player->inventBack[5]->first += 1;
            std::cout << "вы добыли 1 IceOre" << std::endl;
        }
        if(ore->name == "WindOre") {
            player->inventBack[6]->first += 1;
            std::cout << "вы добыли 1 WindOre" << std::endl;
        }
        if(ore->name == "ManaStone") {
            player->inventBack[7]->first += 1;
            std::cout << "вы добыли 1 ManaStone" << std::endl;
        }
}

WindSword::WindSword(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):Swords(damage, damageType, name, rar, mainCost, addedCost, description){
}

void WindSword::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[0])) * 2;
    std::cout << "вы ударили " << enem->name << "и нанесли ему " << damage - enem->resists[0] << " урона" << std::endl;
}

void WindSword::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage / 4 * (1 - (0.1 * enem->resists[1])) * 6;
    enem->hp -= damage / 4 * (1 - (0.1 * enem->resists[0])) * 6;
    std::cout << "вы махнули мечем в сотору " << enem->name << "и буря нанесли ему " << damage / 4 * (1 - (0.1 * enem->resists[0])) * 6 + damage / 4 * (1 - (0.1 * enem->resists[1])) * 6 << "у рона" << std::endl;
}

WindWiz::WindWiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description):Wiz(damage, damageType, name, rar, mainCost, addedCost, description){
}

void WindWiz::Atack(Enem *enem) {
    enem->hp -= damage * (1 - (0.1 * enem->resists[1]));
    std::cout << "вы выпустили сферу из посоха в " << enem->name << "и нанесли ему " << damage * (1 - (0.1 * enem->resists[1])) << " урона" << std::endl;
}

void WindWiz::Abilite(Enem *enem, Player *player) {
    enem->hp -= damage * 2 * (1 - (0.1 * enem->resists[1])) + 3;
    std::cout << "вы запустили торнадо в " << enem->name << "и нанесли ему " << damage * 2 * (1 - (0.1 * enem->resists[1])) + 3 << "у рона" << std::endl;
}

Wiz::Wiz(int damage, int damageType, std::string name, std::string rar, int mainCost, int addedCost, std::string description): HandItem(damage, damageType, name, rar, mainCost, addedCost, description) {
}

Wizard::Wizard(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot):Enem(name, hp, damage, resists, loot){
}
void Wizard::frstAbil(Player *player) {
    std::cout << name << "нанес вам удар, вы получили урон: " << damage << std::endl;
    player->hp -= damage;
}
void Wizard::scndAbil(Player *player) {
    std::cout << name << "нанес вам удар, вы получили урон: " << damage/2 * 3 << std::endl;
    player->hp -= damage/2 * 3;
}
void Wizard::thrdAbil(Player *player) {
    std::cout << name << "промазал" << std::endl;
}

Wolf::Wolf(std::string name, float hp, float damage, int *resists, std::vector<Item*> *loot):Enem(name, hp, damage, resists, loot){
}
void Wolf::frstAbil(Player *player) {
    std::cout << name << " нанес вам удар, вы получили урон: " << damage << std::endl;
    player->hp -= damage;
}
void Wolf::scndAbil(Player *player) {
    std::cout << name << " нанес вам удар, вы получили урон: " << damage + 2 << std::endl;
    player->hp -= damage + 2;
}
void Wolf::thrdAbil(Player *player) {
    std::cout << name << "промазал" << std::endl;
}

World::World()
{
    playerBase = new Base(new vector<Builds*>, new vector<Citizen*> , new vector<Item*>, 100, 100, new Cave());
}

void World::eventAtack() {
    playerBase->eventAtackBase();
}

void World::eventRand() {
    Farm::setQuolity(rand()%10);
}

void HandItem::Abilite(Enem *enem, Player *player)
{}
void HandItem::Atack(Enem *enem)
{}
void HandItem::Atack(Ore *ore, Player *player)
{}
void Citizen::newDay(Base *base)
{}
void Citizen::talk(Player *player)
{}


void Ore::tryGet(Player *player){}


void Enem::frstAbil(Player* player){}
void Enem::scndAbil(Player* player){}
void Enem::thrdAbil(Player* player){}

Pickax::~Pickax(){}

void Pickax::Atack(Ore *ore, Player* player){}
void Pickax::Atack(Enem *enem){}

void World::newDay()
{
    day++;
    playerBase->newDay();
}

void Base::newDay()
{
    for(int i = 0; i != citizensBase->size(); i++)
    {
        citizensBase->at(i)->newDay(this);
    }
}

Base::~Base()
{
    for(int i = 0; i < buildsBase->size(); i++)
    {
        delete (*buildsBase)[i];
    }
    delete buildsBase;
    for(int i = 0; i != citizensBase->size(); i++)
    {
        delete citizensBase->at(i);
    }
    delete citizensBase;
    delete caveBase;
    delete itemsBase;
}

Player::~Player()
{
    for(int i = 0; i != inventUse->size(); i++)
    {
        delete inventUse->at(i);
    }
    delete inventUse;
    for(int i = 0; i != 8; i++)
    {
        delete inventBack[i]->second;
        delete inventBack[i];
    }
    delete WorldPlayer;
}

World::~World()
{
    delete playerBase;
}

using namespace std;
int main() {
    cout << "creating world..." << endl;
    World *newWorld = new World();
    cout << "load player..." << endl;
    Player *player = new Player(newWorld);
    while(true)
    {
        cout << newWorld->day << endl;
        cout << "чем вы хотите заняться?" << endl;
        cout << "1.посторить здание" << endl;
        cout << "2.пойти в здание" << endl;
        cout << "3.пойти в пещеру" << endl;
        cout << "4.проверить корманы" << endl;
        cout << "5.информация о базе" << endl;
        cout << "6.проверить характеристики" <<endl;
        cout<<"-1. exit"<<endl;
        int fun;
        cin >> fun;
        system("clear");
        switch (fun) {
            case 1:
                try {
                    newWorld->playerBase->newBuild(player);
                    newWorld->playerBase = *(newWorld->playerBase)-newWorld->playerBase->buildsBase->at(newWorld->playerBase->buildsBase->size()-1);
                }
                catch (int er) {
                    cout << "вы что то не так нажали(" << endl;
                }
                break;
            case 2:
                try {
                    newWorld->playerBase->goToBuld(player);
                }
                catch (int er) {
                    cout << "вы что то не так нажали(" << endl;
                }
                break;
            case 3:
                try {
                    newWorld->playerBase->goToCave(player);
                }
                catch (int er) {
                    cout << "вы что то не так нажали(" << endl;
                }
                break;
            case 4:
                std::cout << player->inventUse << std::endl;
                std::cout << player->inventBack << std::endl;
                break;
            case 5:
                std::cout << newWorld->playerBase << std::endl;
                break;
            case 6:
                std::cout << player << std::endl;
                break;
            case -1:
                goto ext;
            default:
                cout << "вы что то не так нажали(" << endl;
                break;
        }
        std::cout << "day ended" << std::endl;
        newWorld->newDay();
        newWorld->eventRand();
    }
    ext:
    delete player;
    return 0;
}
