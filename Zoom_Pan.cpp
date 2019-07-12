
#include "Zoom_Pan.h"
#include <math.h>

void Zoom(bool mode, int &x, int &y, int &mapwidth, int &mapheight, int mouseX, int mouseY, double &scale) {
	double mapscale;
	if (mode) {          //detect zoom mode: zoom in, zoom out
		mapscale = 2;
	}
	else {
		mapscale = 0.5;
	}
	scale *= mapscale;    //return new scale
	mapwidth = mapwidth * mapscale;
	mapheight = mapheight * mapscale;
	x = (x - mouseX) * mapscale + mouseX;      //calculate new map position
	y = (y - mouseY) * mapscale + mouseY;
}

void Pan(int &x, int &y, int locX, int locY, int prevLocX, int prevLocY, double scale) {
	double limitXMax = 850;                             //calculate limit based on different zoom ratio, in case map is out of view
	double limitXMin = -800 - 1000 * (scale - 1) + 50;
	double limitYMax = 350;
	double limitYMin = -300 - 521 * (scale - 1) + 50;
	if (x > limitXMax) {
		x = limitXMax;
		y += locY - prevLocY;
	}
	if (x < limitXMin) {
		x = limitXMin;
		y += locY - prevLocY;
	}
	if (y > limitYMax) {
		x += locX - prevLocX;
		y = limitYMax;
	}
	if (y < limitYMin) {
		x += locX - prevLocX;
		y = limitYMin;
	}
	else {
		x += locX - prevLocX;
		y += locY - prevLocY;
	}
}
