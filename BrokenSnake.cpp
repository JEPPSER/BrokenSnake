#include "BrokenEngine2D.hpp"
#include <string>

class BrokenSnake : public BrokenEngine2D
{
public:
	BrokenSnake()
	{
	}

private:
	struct Snake
	{
		float x;
		float y;
		float speed;
		int direction;
	};
	Snake m_player;

protected:
	virtual bool onCreate()
	{
		m_player.x = 15;
		m_player.y = 15;
		m_player.speed = 5;
		m_player.direction = 0;
		return true;
	}

	virtual bool onUpdate(Input t_input, float t_elapsedTime)
	{
		// Player movement
		if (m_player.direction == 0) {
			m_player.x += t_elapsedTime * m_player.speed;
		}
		else if (m_player.direction == 1) {
			m_player.y += t_elapsedTime * m_player.speed;
		}
		else if (m_player.direction == 2) {
			m_player.x -= t_elapsedTime * m_player.speed;
		}
		else if (m_player.direction == 3) {
			m_player.y -= t_elapsedTime * m_player.speed;
		}

		// Player direction change
		if (t_input.getKey('W').m_pressed) {
			m_player.direction = 3;
		}
		else if (t_input.getKey('S').m_pressed) {
			m_player.direction = 1;
		}
		else if (t_input.getKey('A').m_pressed) {
			m_player.direction = 2;
		}
		else if (t_input.getKey('D').m_pressed) {
			m_player.direction = 0;
		}

		return true;
	}

	virtual bool onRender(Graphics t_graphics)
	{
		t_graphics.Clear();
		t_graphics.Draw(m_player.x, m_player.y);
		return true;
	}
};

int main()
{
	BrokenSnake game;
	game.createWindow(30, 30, 15, 15);
	game.start();
	return 0;
}

