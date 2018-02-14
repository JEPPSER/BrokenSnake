#include "BrokenEngine2D.hpp"

class BrokenSnake : public BrokenEngine2D
{
public:
	BrokenSnake()
	{
	}
protected:
	virtual bool onCreate()
	{
		return true;
	}

	virtual bool onUpdate(Input t_input, float t_elapsedTime)
	{

		return true;
	}

	virtual bool onRender(Graphics t_graphics)
	{
		t_graphics.Clear();
		t_graphics.Draw(10, 10);
		return true;
	}
};

int main()
{
	BrokenSnake game;
	game.createWindow(160, 100, 8, 8);
	game.start();

	return 0;
}

