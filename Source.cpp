#include<iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "View.h"
#include <sstream>
#include <SFML/Audio.hpp>
#include <vector>
#include <list>
#include "Menu.h"


using namespace sf;


class Entity {
public:
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove , onGround ;
	Texture texture;
	
	Sprite sprite;
	String name;
	enum { left, right, up, down, jump, stay }state;
	Entity(sf:: Image&image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w/2,h/2);
	}
		FloatRect getRect() {
			return FloatRect(x, y, w, h);
		
	}
		virtual void update(float time) = 0;
};
class Player {

public:
Player(sf::Vector2f size){
	
}

	FloatRect rect;
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, onGround;
	enum { left, right, up, down, jump, stay }state;
	String File;
	Image im;
	Texture t;
	Sprite s;

	Player(String F, float X, float Y, float W, float H) {

		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false; onGround = false;
		File = F;
		w = W; h = H;
		im.loadFromFile("C:\\ekzz\\11.png");
		t.loadFromImage(im);
		s.setTexture(t);
		x = X; y = Y;
		s.setTextureRect(IntRect(0, 0, w, h));
		s.setOrigin(w / 2, h / 2);
		
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	
	


	void control() {
		
		if (life == true) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				
				state = right;
				speed = 0.15;
			}

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left;
				speed = 0.15;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
				state = jump;  onGround = false; 
			}
		}
	}
	void update(float time)
	{
		
	
		control();
		switch (state)
		{
		case right: dx = speed; break;
		case left: dx = -speed; break;
		case jump: break;

		}


		x += dx * time;
		checkCollisionWithMap(dx, 0);
		y += dy * time;
		checkCollisionWithMap(0, dy);
		if (!isMove) speed = 0;

		s.setPosition(x + w / 2, y + h / 1.62);

		if (health <= 0) {
			life = false; 
if (!life) s.setTextureRect(IntRect(0, 224, 120, 100));
		}
		
		dy = dy + 0.0015*time;
	}

	float getplayercoordinateX() {
		return x;
	}
	float getplayercoordinateY() {
		return y;
		
	}
	


	void checkCollisionWithMap(float Dx, float Dy)
	{
		

		for (int i = y / 50; i < (y + h) / 50; i++)
			for (int j = x / 50; j < (x + w) / 50; j++)
			{
				if (TileMap[i][j] == 't')
				{
					if (Dy > 0) { y = i * 50 - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = i * 50 + 50;  dy = 0; }
					if (Dx > 0) { x = j * 50 - w; }
					if (Dx < 0) { x = j * 50 + 50; }
				}
				if (TileMap[i][j] == 'q')
				{
					if (Dy > 0) { y = i * 50 - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = i * 50 + 50;  dy = 0; }
					if (Dx > 0) { x = j * 50 - w; }
					if (Dx < 0) { x = j * 50 + 50; }
				}
				if (TileMap[i][j] == 'a') {
					playerScore++;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'd') {
					health -= 40;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'l') {
					health += 40;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'y') {
					playerScore++;
					TileMap[i][j] = 'o';
				}
				if (TileMap[i][j] == 'p') {
					health -= 40;
				}
				if (TileMap[i][j] == '1') {
					x = 1200; y = 10;
					TileMap[i][j] = '1';
				}
				if (TileMap[i][j] == '2') {
					
						TileMap[i][j] = ' ';
					}

				}
			
	}
};
class Enemy :public Entity {
public:
	int dir;
	Enemy(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		dir = 0;
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, 80, 60));
			dx = 0.1;
			FloatRect rect;
			

		}
	}
	void set(int x, int y)
	{
		float currentFrame = 0;
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 50; i < (y + h) / 50; i++)
			for (int j = x / 50; j < (x + w) / 50; j++)
			{
				if (TileMap[i][j] == 't')
				{
					if (Dy > 0) { y = i * 50 - h;  dy = 0; }
					if (Dy < 0) { y = i * 50 + 50; }
					if (Dx > 0) { x = j * 50 - w; dx = -0.1; sprite.scale(-1, 1); }
					if (Dx < 0) { x = j * 50 + 50; dx = 0.1; sprite.scale(-1, 1); }
				}

			}
	};
	void update(float time)
	{
		if (name == "EasyEnemy") {
			if (onGround = "t") { onGround = false; }
			moveTimer += time;
			if (moveTimer > 9000000000000000) { dx *= -1; moveTimer = 0; }
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
			x += dx * time;
			checkCollisionWithMap(dx, 0);
			y += dy * time;
			checkCollisionWithMap(0, dy);
			if (!isMove) speed = 0;
			dy = dy + 0.0015*time;

			float currentFrame = 0;
			currentFrame += time * 0.005;
			if (currentFrame > 3) currentFrame -= 3;

			sprite.setTextureRect(IntRect(80 * int(currentFrame), 0, 80, 60));
			if (!life) sprite.setTextureRect(IntRect(0, 0, 0, 0));
		}
	}
};




class Enemy1 :public Entity {
public:

	Enemy1(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "EasyEnemy1") {
			sprite.setTextureRect(IntRect(0, 0, 33, 48));
			dx = 0.25;
			FloatRect rect;


		}
	}
	void set(int x, int y)
	{
		float currentFrame = 0;
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 50; i < (y + h) / 50; i++)
			for (int j = x / 50; j < (x + w) / 50; j++)
			{
				if (TileMap[i][j] == 't')
				{
					if (Dy > 0) { y = i * 50 - h;  dy = 0; }
					if (Dy < 0) { y = i * 50 + 50; }
					if (Dx > 0) { x = j * 50 - w; dx = -0.25; sprite.scale(-1, 1); }
					if (Dx < 0) { x = j * 50 + 50; dx = 0.25; sprite.scale(-1, 1); }
				}
				if (TileMap[i][j] == 'q')
				{
					if (Dy > 0) { y = i * 50 - h;  dy = 0; }
					if (Dy < 0) { y = i * 50 + 50; }
					if (Dx > 0) { x = j * 50 - w; dx = -0.25; sprite.scale(-1, 1); }
					if (Dx < 0) { x = j * 50 + 50; dx = 0.25; sprite.scale(-1, 1); }
				}

			}
	};
	void update(float time)
	{
		if (name == "EasyEnemy1") {
			if (onGround = "t") { onGround = false; }
			moveTimer += time;
			if (moveTimer > 9000000000000000) { dx *= -1; moveTimer = 0; }
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
			x += dx * time;
			checkCollisionWithMap(dx, 0);
			y += dy * time;
			checkCollisionWithMap(0, dy);
			if (!isMove) speed = 0;
			dy = dy + 0.0015*time;

			float currentFrame = 0;
			currentFrame += time * 0.005;
			if (currentFrame > 3) currentFrame -= 3;

			sprite.setTextureRect(IntRect(33 * int(currentFrame), 0, 33, 48));
			if (!life) sprite.setTextureRect(IntRect(0, 0, 0, 0));
		}
	}
};


int main()
{
	RenderWindow window(sf::VideoMode(1204, 768),"GAME1");
	menu(window);

	
	Image map_image;
	map_image.loadFromFile("C:\\ekzz\\tileset.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite play_map;
	play_map.setTexture(map);

	int count = 0;
	int count1 = 10;

	Player p("C:\\ekzz\\11.png", 0, 0, 49, 100);

	sf::SoundBuffer q;
	q.loadFromFile("C:\\ekzz\\55.ogg");
	sf::Sound sound2; sound2.setBuffer(q);

	sf::SoundBuffer t;
	t.loadFromFile("C:\\ekzz\\3.ogg");
	sf::Sound sound1; sound1.setBuffer(t);

	sf::SoundBuffer r;
	r.loadFromFile("C:\\ekzz\\11.ogg");
	sf::Sound sound3; sound3.setBuffer(r);
	
	Sprite tile(play_map);
	{
		RenderWindow window(sf::VideoMode(1204, 768), "1");
		view.reset(sf::FloatRect(0, 0, 550, 400));



		Font font;
		font.loadFromFile("C:\\ekzz\\CyrilicOld.ttf");
		Text text("", font, 20);
		text.setFillColor(Color::Red);
		text.setStyle(Text::Bold);

		Image map_image;
		map_image.loadFromFile("C:\\ekzz\\tileset.png");
		Texture map;
		map.loadFromImage(map_image);
		Sprite play_map;
		play_map.setTexture(map);

		Image easyEnemyImage;
		easyEnemyImage.loadFromFile("C:\\ekzz\\enemy0.png");

		Image easyEnemyImage1;
		easyEnemyImage1.loadFromFile("C:\\ekzz\\enemy14.png");

		
		Enemy easyEnemy(easyEnemyImage, 50, 50, 80, 60, "EasyEnemy");
		Enemy1 easyEnemy1(easyEnemyImage1, 200,100,33, 48, "EasyEnemy1");
		
		std::list<Entity*>  entities;
		std::list<Entity*>::iterator it;
		
		Music music;
		music.openFromFile("C:\\ekzz\\4.ogg");
		music.play();
		music.setLoop(true);

		float CurrentFrame = 0;
		Clock clock;
		Clock gameTimeClock;
		int gameTime = 0;
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
			clock.restart();
			time = time / 800;


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return true; }

			float coordinatePlayerX, coordinatePlayerY = 0;
			coordinatePlayerX = p.getplayercoordinateX();
			coordinatePlayerY = p.getplayercoordinateY();

			if (easyEnemy.life == true) {
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					easyEnemy.dir = 0; easyEnemy.speed = 0.1;
					float currentFrame = 0;
					currentFrame += time * 0.005;
					if (currentFrame > 3) currentFrame -= 3;
					easyEnemy.sprite.setTextureRect(IntRect(80 * int(currentFrame), 0, 80, 60));
				}
			}
			
			if (p.life == true) {
				
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					p.dir = 0; p.speed = 0.1;
					CurrentFrame += 0.008*time;
					if (CurrentFrame > 8) CurrentFrame -= 8;
					p.s.setTextureRect(IntRect(49 * int(CurrentFrame), 0, 49, 112));

				}

				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					p.dir = 1; p.speed = 0.1;
					CurrentFrame += 0.008*time;
					if (CurrentFrame > 8) CurrentFrame -= 8;
					p.s.setTextureRect(IntRect(49 * int(CurrentFrame), 112, 49, 112));
				}

				if (Keyboard::isKeyPressed(Keyboard::Up))	if (p.onGround) {
					
					p.dy = -0.7; p.onGround = false; sound1.play();
				}
				if (p.life == false); sound2.play();
			
			}

			
			setPlayerCoordinateForView(coordinatePlayerX, coordinatePlayerY);

			p.update(time);
		
			if ((easyEnemy.getRect().intersects(p.getRect())))
			{
				if (easyEnemy.life) {
					
					{
						if ((p.dy > 0) && (p.onGround == false)) {
							easyEnemy.dx = 0; p.dy = -0.7; sound3.play(); sound1.play(); easyEnemy.life = false;
						}
						else {

							p.health -= 5;
						}
					}
				}
			}
			if ((easyEnemy1.getRect().intersects(p.getRect())))
			{
				if (easyEnemy1.life) {
					bool deleted = false;
					if ((p.dy > 0) && (p.onGround == false)) {
						easyEnemy1.dx = 0; p.dy = -0.7; easyEnemy1.health = 0; sound3.play(); sound1.play(); deleted = true; easyEnemy1.life = false; 
					}
					else {

						p.health -=1;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::R)) { return true; }
			easyEnemy.update(time);
			easyEnemy1.update(time);
			for (it = entities.begin(); it != entities.end(); it++) { (*it)->update(time); }
			window.setView(view);
			window.clear();


			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
				{
					if (TileMap[i][j] == ' ') play_map.setTextureRect(IntRect(50 * 0, 0, 50, 50));
					if (TileMap[i][j] == 't') play_map.setTextureRect(IntRect(50 * 1, 0, 50, 50));
					if (TileMap[i][j] == 'o') play_map.setTextureRect(IntRect(50 * 4, 0, 50, 50));
					if (TileMap[i][j] == 's') play_map.setTextureRect(IntRect(50 * 3, 0, 50, 50));
					if (TileMap[i][j] == 'a') play_map.setTextureRect(IntRect(50 * 6, 0, 50, 50));
					if (TileMap[i][j] == 'd') play_map.setTextureRect(IntRect(50 * 7, 0, 50, 50));
					if (TileMap[i][j] == 'l') play_map.setTextureRect(IntRect(50 * 8, 0, 50, 50));
					if (TileMap[i][j] == 'q') play_map.setTextureRect(IntRect(50 * 5, 0, 50, 50));
					if (TileMap[i][j] == 'y') play_map.setTextureRect(IntRect(50 * 9, 0, 50, 50));
					if (TileMap[i][j] == 'p') play_map.setTextureRect(IntRect(50 * 10, 0, 50, 50));
					if (TileMap[i][j] == '0') play_map.setTextureRect(IntRect(50 * 11, 0, 50, 50));
					if (TileMap[i][j] == '1') play_map.setTextureRect(IntRect(50 * 12, 0, 50, 50));
					if (TileMap[i][j] == '2') play_map.setTextureRect(IntRect(50 * 2, 0, 50, 50));
					


					play_map.setPosition(j * 50, i * 50);


					window.draw(play_map);
				}
			std::ostringstream playerHealthString, gameTimeString, playerScoreString;
			playerHealthString << p.health; gameTimeString << gameTime;
			playerScoreString << p.playerScore;
			text.setString("Здоровье:" + playerHealthString.str() + "\nВремя игры:" + gameTimeString.str() + "   Собрано шестерёнок:" + playerScoreString.str());
			text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);
			window.draw(text);
			window.draw(easyEnemy.sprite);
			window.draw(easyEnemy1.sprite);
			window.draw(p.s);
			window.display();
		

		}
		return 0;

	}
}

