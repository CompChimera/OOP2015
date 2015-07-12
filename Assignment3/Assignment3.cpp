#include <iostream.h>

enum barType
{
	pureChocolate, withNuts, withWaffer, withNougat
};

class ChocolateBar
{
public:
	virtual void wrapper() = 0;
	static ChocolateBar *findAndClone(barType);
protected:
	virtual barType returnType() = 0;
	virtual ChocolateBar *clone() = 0;
	// As each subclass of Bar is declared, it registers its prototype
	static void addPrototype(ChocolateBar *bar)
	{
		_prototypes[_nextSlot++] = bar;
	}
private:
	// addPrototype() saves each registered prototype here
	static ChocolateBar *_prototypes[10];
	static int _nextSlot;
};

ChocolateBar *ChocolateBar::_prototypes[];
int ChocolateBar::_nextSlot;

// Client calls this public static member function when it needs an instance
// of an Bar subclass
ChocolateBar *ChocolateBar::findAndClone(barType type)
{
	for (int i = 0; i < _nextSlot; i++)
	if (_prototypes[i]->returnType() == type)
		return _prototypes[i]->clone();
}

class SolidChocolateBar : public ChocolateBar
{
public:
	barType returnType()
	{
		return pureChocolate;
	}
	void draw()
	{
		cout << "SolidChocolateBar::draw " << _id << endl;
	}
	// When clone() is called, call the one-argument ctor with a dummy arg
	ChocolateBar *clone()
	{
		return new SolidChocolateBar(1);
	}
protected:
	// This is only called from clone()
	SolidChocolateBar(int dummy)
	{
		_id = _count++;
	}
private:
	// Mechanism for initializing an Image subclass - this causes the
	// default ctor to be called, which registers the subclass's prototype
	static SolidChocolateBar _pureChocolate;
	// This is only called when the private static data member is inited
	SolidChocolateBar()
	{
		addPrototype(this);
	}
	// Nominal "state" per instance mechanism
	int _id;
	static int _count;
};

// Register the subclass's prototype
SolidChocolateBar SolidChocolateBar::_pureChocolate;
// Initialize the "state" per instance mechanism
int SolidChocolateBar::_count = 1;

class NutChocolateBar : public ChocolateBar
{
public:
	barType returnType()
	{
		return withNuts;
	}
	void draw()
	{
		cout << "NutChocolateBar::draw " << _id << endl;
	}
	ChocolateBar *clone()
	{
		return new NutChocolateBar(1);
	}
protected:
	NutChocolateBar(int dummy)
	{
		_id = _count++;
	}
private:
	NutChocolateBar()
	{
		addPrototype(this);
	}
	static NutChocolateBar _spotImage;
	int _id;
	static int _count;
};

NutChocolateBar NutChocolateBar::_withNuts;
int NutChocolateBar::_count = 1;

//Variables to be used in the main function
const int NUM_BARS = 4;
barType input[NUM_BARS] =
{
	pureChocolate, withNuts, withNuts, withNuts
};

int main()
{
	ChocolateBar *bars[NUM_BARS];

}

