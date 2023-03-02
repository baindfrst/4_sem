#include <iostream>

class apple
{
    int weight;
    char bad;
    public:
    int getWeight()
    {
        return weight;
    }
    int getbad()
    {
        return bad;
    }
    void gen_weight_apple(void)
    {
        weight = rand() % 5;
        bad = 1 + rand() % 10;
        if (bad == 10)
        {
            bad = 1;
        }
        else
        {
            bad = 0;
        }
    }
};

class rat 
{
    int weight;
    int speed;
    int health;
    int poision;
    public:
    void gen_rat(void)
    {
        int weight = rand() % 6;
        int speed = 1 + rand() & 5;
        health = 1 + rand() % 2;
        poision = 0;
    }
    void eat_apple(apple ap)
    {
        if (ap.getbad())
        {
            health--;
            if (!health)
            {
                speed = 0;
                poision = 1;
            }
            weight += ap.getWeight();
        }
        else
        {
            weight += ap.getWeight();   
        }
    }
    int get_poision()
    {
        return poision;
    }
    int get_weight()
    {
        return weight;
    }
    int get_speed()
    {
        return speed;
    }
};

class pit
{
    int len;
    int empty;
    int enemy_damage;
    int enemy_weight;
    public:
    void gen_pit()
    {
        len = 1 + rand() % 10;
        empty = rand() % 2;
        enemy_damage = 0;
        enemy_weight = 0;
        if (!empty)
        {
            if(rand()%2)
            {
                enemy_1 enemy;
                enemy.spawn_enemy();
                enemy_damage = enemy.get_damage();
                enemy_weight = enemy.get_weight();
            }
            else
            {
                enemy_2 enemy;
                enemy.spawn_enemy();
                enemy_damage = enemy.get_damage();
                enemy_weight = enemy.get_weight();
            }
        }
    }
    int get_len()
    {
        return len;
    }
    int get_enemy_weight()
    {
        return enemy_weight;
    }
    int get_enemy_damage()
    {
        return enemy_damage;
    }
};

class enemy_1
{
    int damage;
    int weight;
    public:
    void spawn_enemy()
    {
        damage = 1;
        weight = 1 + rand() % 3;
    }
    int get_damage()
    {
        return damage;
    }
    int get_weight()
    {
        return weight;
    }
};

class enemy_2
{
    int damage;
    int weight;
    public:
    void spawn_enemy()
    {
        damage = 2;
        weight = 2 + rand() % 4;
    }
        int get_damage()
    {
        return damage;
    }
    int get_weight()
    {
        return weight;
    }
};

class berd
{
    int weight;
    int h;
    int health;
    public:
    void spawn_snake()
    {
        weight = 1 + rand() % 2;
        h = 5 + rand() % 5;
        health = 1;
    }
    void attack_rat(rat obj)
    {
        if(obj.get_speed() == 0)
        {
            weight += obj.get_weight();
            if(obj.get_poision() == 1)
            {
                health--;
                h = 0;
            }
        }
    }
    void eat_apple(apple obj)
    {
        weight += obj.getWeight();
        if(obj.getbad() > 0)
        {
            health--;
            h = 0;
        }
    }
    int get_weight()
    {
        return weight;
    }
    int get_h()
    {
        return h;
    }
};

class snake
{
    int len;
    int speed;
    int spawn_snake;
    int health;
    public:
    void spawn_snake(void)
    {
        len = 1;
        speed = 10;
        health = 1 + rand() % 3;
    }
    void eat_apple(apple food)
    {
        if(food.getbad())
        {
            health--;
        }
        len += food.getWeight();
        speed--;
    }
    void eat_rat(rat food)
    {
        if (food.get_speed() < speed)
        {
            if (food.get_poision())
            {
                health--;
            }
            len += food.get_weight();
            speed--;
        }
    }
    void try_run_pit(pit pt)
    {
        if (pt.get_len() > len)
        {
            health -= pt.get_enemy_damage();
            len += pt.get_enemy_weight();
            speed--;
        }
    }
    void berd_at(berd obj)
    {
        if (obj.get_h() <= len)
        {
            len += obj.get_weight();
        }
        else
        {
            health--;
        }
    }
};
