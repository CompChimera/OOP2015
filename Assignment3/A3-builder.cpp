//The whole idea behind builder is that a separate method
//creates or builds all the things



#include <iostream>
#include <string>

/* Car parts */
class Burger
{
public:
	std::string type;
};

class Drink
{
public:
	std::string name;
};

class Toy
{
public:
	std::string name;
};

/* Final product -- a car */
class Meal
{
public:
	Burger* burger;
	Drink* drink;
	Toy* toy;

	void specifications()
	{
		std::cout << "burger:" << burger->type << std::endl;
		std::cout << "drink:" << drink->name << std::endl;
		std::cout << "toy:" << toy->name << "'" << std::endl;
	}
};

//Builder assembles the parts together
class Builder
{
public:
	virtual Burger* getBurger() = 0;
	virtual Drink* getDrink() = 0;
	virtual Toy* getToy() = 0;
};

//Directs the creation
class Director
{
	Builder* builder;

public:
	void setBuilder(Builder* newBuilder)
	{
		builder = newBuilder;
	}

	Meal* getMeal()
	{
		Meal* meal = new Meal();

		meal->burger = builder->getBurger();

		meal->drink = builder->getDrink();

		meal->toy = builder->getToy();

		return meal;
	}
};

//Builder for Hamburger
class HamburgerBuilder : public Builder
{
public:
	Burger* getBurger()
	{
		Burger* burger = new Burger();
		burger->type = "Hamburger";
		return burger;
	}

	Drink* getDrink()
	{
		Drink* drink = new Drink();
		drink->name = "Sprite";
		return drink;
	}

	Toy* getToy()
	{
		Toy* toy = new Toy();
		toy->name = "Transformer";
	}
};

//builder for cheeseburger meal
class CheeseBurgerBuilder : public Builder
{
public:
	Burger* getBurger()
	{
		Burger* burger = new Burger();
		burger->type = "CheeseBurger";
		return burger;
	}

	Drink* getDrink()
	{
		Drink* drink = new Drink();
		drink->name = "Root Beer";
		return drink;
	}

	Toy* getToy()
	{
		Toy* toy = new Toy();
		toy->name = "Barbie";
	}
};


int main()
{
	Meal* meal; // Final product

	//controlls the process
	Director cashier;

	//creates the details of the components
	HamburgerBuilder hamburgerBuilder;
	CheeseBurgerBuilder cheeseburgerBuilder;

	//Build a Hamburger Meal
	std::cout << "Hamburger" << std::endl;
	cashier.setBuilder(&hamburgerBuilder); // using HamburgerBuilder instance
	meal = cashier.getMeal();
	meal->specifications();

	std::cout << std::endl;

	/* Build a Nissan */
	std::cout << "Cheeseburger" << std::endl;
	cashier.setBuilder(&cheeseburgerBuilder); // using NissanBuilder instance
	meal = cashier.getMeal();
	meal->specifications();

	return 0;
}
