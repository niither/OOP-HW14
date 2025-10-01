#include <iostream>
#include <string>
using namespace std;

class Continent {
protected:
    string name;
public:
    Continent(string name) {
        this->name = name;
    }
    virtual string getName() const {
        return name;
    }
};

class Africa : public Continent {
public:
    Africa() : Continent("Africa") {}
};

class Europe : public Continent {
public:
    Europe() : Continent("Europe") {}
};

class Animal {
protected:
    string name;
    Continent* continent;
public:
    Animal(string name, Continent* continent) {
        this->name = name;
        this->continent = continent;
    }
    virtual void info() const = 0;
};

class Herbivore : public Animal {
protected:
    int weight;
    bool isAlive;
public:
    Herbivore(string name, Continent* continent, int weight, bool isAlive) : Animal(name, continent), weight(weight), isAlive(isAlive) {}

    void EatGrass() {
        weight += 10;
    }
    bool getIsAlive() const {
        return isAlive;
    }
    int getWeight() const {
        return weight;
    }
    virtual void info() const {
        cout << "Herbivore: " << name
            << "\nContinent: " << continent->getName()
            << "\nWeight: " << weight
            << "\nAlive: " << (isAlive ? "Yes\n" : "No\n");
    }
};

class Zebra : public Herbivore {
public:
    Zebra(Continent* continent) : Herbivore("Zebra", continent, 100, true) {}
};

class Sheep : public Herbivore {
public:
    Sheep(Continent* continent) : Herbivore("Sheep", continent, 50, true) {}
};

class Carnivore : public Animal {
protected:
    int power;
public:
    Carnivore(string name, Continent* continent, int power) : Animal(name, continent), power(power) {}

    void Eat(Herbivore& herbivore) {
        if (power > herbivore.getWeight()) {
            cout << name << " eats herbivore (weight " << herbivore.getWeight() << ")" << "\n";
            power += 10;
        }
        else {
            cout << name << " failed to eat herbivore, Power decreases" << "\n";
            power -= 10;
        }
    }

    virtual void info() const {
        cout << "Carnivore: " << name
            << "\nContinent: " << continent->getName()
            << "\nPower: " << power << "\n";
    }
};

class Lion : public Carnivore {
public:
    Lion(Continent* continent) : Carnivore("Lion", continent, 60) {}
};

class Bear : public Carnivore {
public:
    Bear(Continent* continent) : Carnivore("Bear", continent, 110) {}
};

int main() {
	srand(time(0));
    Africa africa;
    Europe eu;

    Herbivore* herbivores[5] = {
        new Zebra(&africa),
        new Sheep(&eu),
        new Zebra(&africa),
        new Sheep(&eu),
        new Zebra(&africa)
    };

    Carnivore* carnivores[5] = {
        new Lion(&africa),
        new Bear(&eu),
        new Lion(&africa),
        new Bear(&eu),
        new Bear(&eu)
    };

	Animal* allAnimals[10] = {
		herbivores[0], herbivores[1], herbivores[2], herbivores[3], herbivores[4],
		carnivores[0], carnivores[1], carnivores[2], carnivores[3], carnivores[4]
	};

    cout << "Animals info\n";
    int randomAnimal = rand() % 10;
    allAnimals[randomAnimal]->info();
}