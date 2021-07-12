#include <SFML/Graphics.hpp>

; using namespace sf;

View view;

View setPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;
	if (x < 275) tempX = 275;
	if (y < 200) tempY = 200;
	if (y > 554) tempY = 554;

	view.setCenter(tempX, tempY);
	return view;
}