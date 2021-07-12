#include <SFML/Graphics.hpp>

using namespace sf;


void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("C:\\ekzz\\111.png");
	menuTexture2.loadFromFile("C:\\ekzz\\222.png");
	
	aboutTexture.loadFromFile("C:\\ekzz\\555.png");
	menuBackground.loadFromFile("C:\\ekzz\\Игра.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(500, 300);
	menu2.setPosition(500, 350);

	menuBg.setPosition(-50, 0);

	Music music;
	music.openFromFile("C:\\ekzz\\8.ogg");
	music.play();
	music.setLoop(true);

	SoundBuffer buffer;
	buffer.loadFromFile("C:\\ekzz\\15.ogg");
	Sound sound(buffer);
	
	while (isMenu)
	{
		menu1.setColor(Color::Green);
		menu2.setColor(Color::Green);
	
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(500, 300, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(500, 350, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { window.close(); sound.play(); isMenu = false;
			}
			if (menuNum == 2) { window.draw(about); window.display(); sound.play(); while (!Mouse::isButtonPressed(Mouse::Right)); sound.play(); }
			
			

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		

		window.display();
	}

}