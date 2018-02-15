#include "BrokenEngine2D.hpp"
#include <string>
#include <thread>
#include <chrono>

class BrokenSnake : public BrokenEngine2D
{
public:
	BrokenSnake()
	{
	}

private:
	struct Snake
	{
		int x;
		int y;
		float speed;
		int direction;
		std::vector<std::pair<int, int>> body;
	};
	Snake m_player;
	float m_counter;
	bool m_alive;
	int m_score;

	void dead(Input t_input) {
		if (t_input.getKey(VK_SPACE).m_pressed) {
			onCreate();
		}
	}

	void alive(Input t_input, float t_elapsedTime) {
		if (m_counter > 1) {
			// Player movement
			if (m_player.direction == 0) {
				m_player.x += 1;
			}
			else if (m_player.direction == 1) {
				m_player.y += 1;
			}
			else if (m_player.direction == 2) {
				m_player.x -= 1;
			}
			else if (m_player.direction == 3) {
				m_player.y -= 1;
			}

			for (int i = m_player.body.size() - 1; i > 0; i--) {
				m_player.body[i] = m_player.body[i - 1];
			}
			m_player.body[0] = { m_player.x, m_player.y };
			m_counter = 0;
		}

		m_counter += t_elapsedTime * m_player.speed;

		// Player direction change
		if (t_input.getKey('W').m_pressed && m_player.direction != 1) {
			m_player.direction = 3;
		}
		else if (t_input.getKey('S').m_pressed && m_player.direction != 3) {
			m_player.direction = 1;
		}
		else if (t_input.getKey('A').m_pressed && m_player.direction != 0) {
			m_player.direction = 2;
		}
		else if (t_input.getKey('D').m_pressed && m_player.direction != 2) {
			m_player.direction = 0;
		}
	}

protected:
	virtual bool onCreate()
	{
		m_score = 0;
		m_alive = true;
		m_counter = 0;
		m_player.x = 15;
		m_player.y = 15;
		m_player.speed = 5;
		m_player.direction = 0;
		m_player.body = { {m_player.x, m_player.y}, {m_player.x - 1, m_player.y}, {m_player.x - 2, m_player.y}, { m_player.x - 3, m_player.y }, { m_player.x - 4, m_player.y } };
		return true;
	}

	virtual bool onUpdate(Input t_input, float t_elapsedTime)
	{
		// Out of bounds collision
		if (m_player.x > 30 || m_player.x < 0 || m_player.y > 30 || m_player.y < 0) {
			if (m_alive) {
				m_alive = false;
			}
		}
		// Body collision
		else {
			for (int i = 1; i < m_player.body.size(); i++) {
				if (m_player.x == m_player.body[i].first && m_player.y == m_player.body[i].second) {
					if (m_alive) {
						m_alive = false;
					}
				}
			}
		}

		if (m_alive) {
			alive(t_input, t_elapsedTime);
		}
		else {
			dead(t_input);
		}

		return true;
	}

	virtual bool onRender(Graphics t_graphics)
	{
		t_graphics.Clear();
		if (m_alive) {
			for (int i = 0; i < m_player.body.size(); i++) {
				t_graphics.Draw(m_player.body[i].first, m_player.body[i].second);
			}
		}
		else {
			t_graphics.DrawString(10, 5, "You Died!");
			t_graphics.DrawString(10, 7, "Score: " + std::to_string(m_score));
			t_graphics.DrawString(3, 9, "Press Space To Try Again");
		}
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

