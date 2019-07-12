#include <stdio.h>
#include <algorithm>    // std::max
//#include "GL\glut.h"

#include "fssimplewindow.h"
#include "DrawingUtilNG.h"

#undef max
#undef min
void DrawingUtilNG::drawCircle(double centerX, double centerY, double rad, bool fill)
{
	double x, y, angle;
	int points = std::max(12, (int)(rad / 15.));

	if (fill)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);

	for (int i = 0; i < points; i++) {
		angle = (double)i * PI / points * 2;
		x = centerX + cos(angle) * rad;
		y = centerY + sin(angle) * rad;
		glVertex2d(x, y);
	}

	glEnd();
}

void DrawingUtilNG::drawRect(double x1, double y1, double x2, double y2, bool fill)
{
	if (fill)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);

	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}

bool DrawingUtilNG::hsv2rgb(double H, double S, double V, double & red, double & green, double & blue)
{
	// using formula from:
	// https://www.rapidtables.com/convert/color/hsv-to-rgb.html

	// adjust H to be 0 <= H <= 360
	H = fabs(fmod(H, 360.));  // note that H=360 is the same as H=0

	double C = V * S;
	double X = C * (1 - fabs(fmod(H / 60., 2) - 1));
	double m = V - C;
	double Rprime, Gprime, Bprime;

	if (H < 0.) {  // unlikely due to adjustment above
		return false;  //  <<< possible exit from function
	}
	else if (H < 60.) {
		Rprime = C;
		Gprime = X;
		Bprime = 0.;
	}
	else if (H < 120.) {
		Rprime = X;
		Gprime = C;
		Bprime = 0.;
	}
	else if (H < 180.) {
		Rprime = 0.;
		Gprime = C;
		Bprime = X;
	}
	else if (H < 240.) {
		Rprime = 0.;
		Gprime = X;
		Bprime = C;
	}
	else if (H < 300.) {
		Rprime = X;
		Gprime = 0.;
		Bprime = C;
	}
	else if (H < 360.) {
		Rprime = C;
		Gprime = 0.;
		Bprime = X;
	}
	else
		return false;  //  <<< possible exit from function

	red = Rprime + m;
	green = Gprime + m;
	blue = Bprime + m;

	return true;
}

void DrawingUtilNG::writeHelvetica(std::string outString, int locX, int locY, int size)
{
	//void *fontCode;
	//switch (size) {
	//case 10: fontCode = GLUT_BITMAP_HELVETICA_10;
	//	break;
	//case 12: fontCode = GLUT_BITMAP_HELVETICA_12;
	//	break;
	//case 18: fontCode = GLUT_BITMAP_HELVETICA_18;
	//	break;
	//default: fontCode = GLUT_BITMAP_HELVETICA_10;
	//	break;
	//}

	//glRasterPos2i(locX, locY);
	//for (int i = 0; i < outString.length(); i++) {
	//	//glutBitmapCharacter(fontCode,
	//	//	outString.substr(i, 1).c_str()[0]);
	//}
}
void DrawingUtilNG::writeTimesRoman(std::string outString, int locX, int locY, int size)
{
	//void *fontCode;
	//switch (size) {
	//case 10: fontCode = GLUT_BITMAP_TIMES_ROMAN_10;
	//	break;
	//case 24: fontCode = GLUT_BITMAP_TIMES_ROMAN_24;
	//	break;
	//default: fontCode = GLUT_BITMAP_TIMES_ROMAN_10;
	//	break;
	//}

	//glRasterPos2i(locX, locY);
	//for (int i = 0; i < outString.length(); i++) {
	//	glutBitmapCharacter(fontCode,
	//		outString.substr(i, 1).c_str()[0]);
	//}
}

void DrawingUtilNG::coverAndFade(int x1, int y1, int x2, int y2, int totalT, int currT,
	int r, int g, int b)
{
	if (currT > totalT)
		currT = totalT;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int temp = currT / totalT * 255;
	glColor4ub(r, g, b, currT / (double)totalT * 255);
	//glColor4ub(0, 0, 0, 180);
	drawRect(x1, y1, x2, y2, true);

	glDisable(GL_BLEND);

}
