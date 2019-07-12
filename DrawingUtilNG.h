#pragma once
#include <string>

namespace DrawingUtilNG {
	const double PI = 3.141592653589793;
	// draws common shapes, filled in or not
	void drawCircle(double centerX, double centerY, double rad, bool fill);
	void drawRect(double x1, double y1, double x2, double y2, bool fill);

	//converts a color model from HSV to RGB
	bool hsv2rgb(double H, double S, double V,
		double &red, double &green, double &blue);

	// quick writing with fancy fonts, but requires GLUT library
	void writeHelvetica(std::string outString, int locX, int locY, int size);
	void writeTimesRoman(std::string outString, int locX, int locY, int size);

	// draws a box (colored rgb) that increases opacity based on the ratio of currT/totalT
	void coverAndFade(int x1, int y1, int x2, int y2, int totalT, int currT,
		int r = 0, int g = 0, int b = 0);
};