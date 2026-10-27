#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

ofstream fout("fortress_log.txt"); 


class Shooter {
private:
    string ammoName;
    int ammoAmount = 0;

protected:
    void setAmmo(const string& name, int amount) {
        ammoName = name;
        ammoAmount = amount;

        string msg = "Боєприпаси: " + name + ", кількість: " + to_string(amount);
        cout << msg << '\n';
        fout << msg << '\n';
    }

    void shoot(const string& who = "Стрілець") {
        string msg;
        if (ammoAmount > 0) {
            ammoAmount--;
            msg = who + ": постріл (" + ammoName + "), залишилось: " + to_string(ammoAmount);
        }
        else {
            msg = who + ": постріл неможливий, боєприпаси (" + ammoName + ") закінчились!";
        }
        cout << msg << '\n';
        fout << msg << '\n';
    }
};


class Archer : virtual public Shooter {
public:
    void shoot() { Shooter::shoot("Лучник"); }
};


class Ranger : virtual public Shooter {
public:
    void shoot() { Shooter::shoot("Рейнджер"); }
};


class Catapult : public Shooter {
public:
    void shoot() { Shooter::shoot("Катапульта"); }
    using Shooter::setAmmo;
};


class ShooterTower : public Archer, public Ranger {
public:
    using Shooter::setAmmo;
};


class Fortress final : public ShooterTower, public Catapult {
private:
    int wallThickness;
    int gateHealthPercentage;

public:
    Fortress() : wallThickness(5), gateHealthPercentage(100) {
        ShooterTower::setAmmo("стріла", 4); 
        Catapult::setAmmo("камінь", 5);     

        string msg = "Фортеця створена: товщина стін " + to_string(wallThickness) +
            " м, стан воріт " + to_string(gateHealthPercentage) + "%";
        cout << msg << '\n';
        fout << msg << '\n';
    }
};

int main() {
   
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Fortress fortress; 

    
    fortress.Archer::shoot();
    fortress.Archer::shoot();
    fortress.Archer::shoot();

    fortress.Ranger::shoot(); 
    fortress.Ranger::shoot(); 

    fortress.Catapult::shoot(); 

    fout.close();
    return 0;
}