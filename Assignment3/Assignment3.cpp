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

class solidChocolateBar : public ChocolateBar
{
public:
	barType returnType()
	{
		return pureChocolate;
	}
	void draw()
	{
		cout << "solidChocolateBar::draw " << _id << endl;
	}
	// When clone() is called, call the one-argument ctor with a dummy arg
	ChocolateBar *clone()
	{
		return new solidChocolateBar(1);
	}
protected:
	// This is only called from clone()
	solidChocolateBar(int dummy)
	{
		_id = _count++;
	}
private:
	// Mechanism for initializing an Image subclass - this causes the
	// default ctor to be called, which registers the subclass's prototype
	static solidChocolateBar _landSatImage;
	// This is only called when the private static data member is inited
	solidChocolateBar()
	{
		addPrototype(this);
	}
	// Nominal "state" per instance mechanism
	int _id;
	static int _count;
};

// Register the subclass's prototype
solidChocolateBar solidChocolateBar::_pureChocolate;
// Initialize the "state" per instance mechanism
int solidChocolateBar::_count = 1;

class SpotImage : public ChocolateBar
{
public:
	imageType returnType()
	{
		return SPOT;
	}
	void draw()
	{
		cout << "SpotImage::draw " << _id << endl;
	}
	ChocolateBar *clone()
	{
		return new SpotImage(1);
	}
protected:
	SpotImage(int dummy)
	{
		_id = _count++;
	}
private:
	SpotImage()
	{
		addPrototype(this);
	}
	static SpotImage _spotImage;
	int _id;
	static int _count;
};

SpotImage SpotImage::_spotImage;
int SpotImage::_count = 1;

// Simulated stream of creation requests
const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] =
{
	LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT
};

int main()
{
	ChocolateBar *images[NUM_IMAGES];

	// Given an image type, find the right prototype, and return a clone
	for (int i = 0; i < NUM_IMAGES; i++)
		images[i] = ChocolateBar::findAndClone(input[i]);

	// Demonstrate that correct image objects have been cloned
	for (i = 0; i < NUM_IMAGES; i++)
		images[i]->draw();

	// Free the dynamic memory
	for (i = 0; i < NUM_IMAGES; i++)
		delete images[i];
}

