#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "character.h"
using namespace std;

class Undead {
public:
    virtual string name() const = 0;
    virtual int power() const = 0;
    virtual int agility() const = 0;
    virtual int endurance() const = 0;
    virtual ~Undead() {}
};

class Zombie : public Undead {
public:
    string name() const override { return "Zombie"; }
    int power() const override { return 15; }
    int agility() const override { return 5; }
    int endurance() const override { return 20; }
};

class Skeleton : public Undead {
public:
    string name() const override { return "Skeleton"; }
    int power() const override { return 10; }
    int agility() const override { return 15; }
    int endurance() const override { return 10; }
};

class Lich : public Undead {
public:
    string name() const override { return "Lich"; }
    int power() const override { return 25; }
    int agility() const override { return 12; }
    int endurance() const override { return 18; }
};

// Adapter: Undead → Character
class UndeadAdapter : public Character {
    shared_ptr<Undead> undead;
public:
    UndeadAdapter(shared_ptr<Undead> u) : undead(u) { 
        // Undead 이름으로 설명과 타입 설정
        description = undead->name();
        string n = description;
        if (n == "Zombie")      type = CharacterType::Zombie;
        else if (n == "Skeleton") type = CharacterType::Skeleton;
        else if (n == "Lich")     type = CharacterType::Lich;
        else                      type = CharacterType::Unknown;
    }
    int getAttack() const override { return undead->power(); }      // 공격력
    int getSpeed() const override { return undead->agility(); }     // 속도
    int getDefense() const override { return undead->endurance(); } // 방어력
};
