#include "../include/helper.h"

bool checkCollision(SDL_Rect &rect1, SDL_Rect &rect2, int y_offset) {
	return (
		rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y + y_offset < rect2.y + rect2.h &&
		rect1.h + rect1.y + y_offset > rect2.y
		);
}

double* calcVector(double diff_x, double diff_y) {

	double static unitVectors[2];
	double magnitude = sqrt((pow(diff_x, 2) + pow(diff_y, 2)));
	// 0th index is x value
	// 1st index is y value
	double unitX = diff_x / magnitude;
	double unitY = diff_y / magnitude;

	unitVectors[0] = unitX;
	unitVectors[1] = unitY;

	return unitVectors;
}

double calcAngle(double diff_x, double diff_y) {
	double angle = atan2(diff_y, diff_x);
	// convert to degrees from radians
	angle *= 180 / PI;
	// adjust angle acc to SDL 
	angle += 90;
	return angle;
}

bool checkMouseClick(SDL_Rect& a, SDL_Event& e) {
	// get x and y pos of mouse hover / click
	int x = e.button.x;
	int y = e.button.y;

	return (
		x >= a.x && x <= (a.x + a.w)
		&& y >= a.y && y <= (a.y + a.h)
		);
}

bool checkMouseHover(SDL_Rect& a, int x, int y) {
	return (
		x >= a.x && x <= (a.x + a.w)
		&& y >= a.y && y <= (a.y + a.h)
		);
}
