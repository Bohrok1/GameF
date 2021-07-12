#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
	Bullet(sf::Vector2f size) {
		bullet.setSize(size);
	}

	void fire(int speed) {
		bullet.move(speed, 0);
	}

	int getRight() {
		return bullet.getPosition().x + bullet.getSize().x;
	}

	int getLeft() {
		return bullet.getPosition().x;
	}

	int getTop() {
		return bullet.getPosition().y;
	}

	int getBottom() {
		return bullet.getPosition().y + bullet.getSize().y;
	}

	void draw(sf::RenderWindow &window) {
		window.draw(bullet);
	}

private:
	sf::RectangleShape bullet;
};
