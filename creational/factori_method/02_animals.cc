#include <iostream>
#include <string>

struct Animal {
  std::string name_;
  int calories_;
  Animal(std::string name) : name_(name), calories_(0) {}
  void AddCalories(int dt) const {
    this->calories_ += dt;
  }
}

class Food {
 public:
  // virtual ~Food() {}
  virtual std::string Operation(Animal& pet) const = 0;
};

class Meat : public Food {
 public:
  std::string Operation(Animal& pet) const override {
    pet.AddCalories(150);
    return pet.name_ + " fed with meat\n";
  }
};
class Milk : public Food {
 public:
  std::string Operation(Animal& pet) const override {
    pet.AddCalories(50);
    return pet.name_ + " drunk with milk\n";
  }
};
class Water : public Food {
 public:
  std::string Operation(Animal& pet) const override {
    return pet.name_ + " drunk with water\n";
  }
};

class Feeder {
 public:
  // virtual ~Feeder(){};
  virtual Food* FactoryFood() const = 0;

  std::string Feed(Animal& pet) const {
    Food* product = this->FactoryFood();

    std::string result = "Feeder report: " + product->Operation(pet);

    delete product;
    return result;
  }
};

class MeatFeeder : public Feeder {
 public:
  Food* FactoryFood() const override {
    return new Meat();
  }
};

class MilkFeeder : public Feeder {
 public:
  Food* FactoryFood() const override {
    return new Milk();
  }
};

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
void ClientCode(const Feeder& creator) {
  // ...
  std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator.Feed(Animal& pet) << std::endl;
  // ...
}

/**
 * The Application picks a creator's type depending on the configuration or
 * environment.
 */

int main() {
  std::cout << "App: Launched with the MeatFeeder.\n";
  Feeder* creator = new MeatFeeder();
  ClientCode(*creator);
  std::cout << std::endl;
  std::cout << "App: Launched with the MilkFeeder.\n";
  Feeder* creator2 = new MilkFeeder();
  ClientCode(*creator2);

  delete creator;
  delete creator2;
  return 0;
}