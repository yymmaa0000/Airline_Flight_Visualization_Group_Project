// 24780 Final Project
// 12/7/2018
// Mandarin Orange
// Weijia Gao, Xingyu Wang, Xinyue Shi, Yintong Lu, Yibo Cao, Ruixin Liu


#include <stdio.h>
#include "sorting_and_flight.h"
#include<iostream>
#include "yspng.h"
#include<string.h>
#include<time.h>
#include"DrawingUtilNG.h"
#include "fssimplewindow.h"
#include "Zoom_Pan.h"
#include "departurebutton.h"
#include "arrivalbutton.h"

using namespace std;

// =================================================================
// Airport names and coordinates initialization.
const char *stop[18] = { "ORD", "ATL", "LAX", "DEN", "SFO", "LAS",
"SEA", "CLT", "EWR", "JFK", "MCO", "PHX",
"MIA", "IAH", "BOS", "DTW", "MSP", "DFW" };//name of airport
const double coord[18][2] = { { 690, 200 },{ 755, 380 },{ 150, 360 },{ 400, 255 },{ 110, 290 },{ 190, 290 },
{ 70, 90 },{ 810, 345 },{ 920, 230 },{ 930, 220 },{ 800, 490 },{ 280, 380 },
{ 815, 530 },{ 560, 460 },{ 970, 195 },{ 765, 205 },{ 600, 140 },{ 525, 395 } };//coordinates of airport


class Map {
	char *p;//image address
	Logo image;

public:
	Map() {//class constructor: set the image address and execute the load function
		p = "map4.png";
		image.init(p);
	};

	void show(int x, int y, int width, int height) {//Show map information
													// set up parameters for the current texture
		image.draw(x, y, width, height);
		for (int i = 0; i < 18; i++)//Show the location of the airport on the map
		{
			flight_stop((coord[i][0] - 50) *(width) / 1000 + x, (coord[i][1] - 50) * (height) / 521 + y, *(stop + i));

		}
	};

	void flight_stop(double x, double y, string stop)//Draw the airport
	{
		glColor3ub(255, 25, 0);
		glBegin(GL_QUADS);
		glVertex2d(x - 5, y - 5);
		glVertex2d(x + 5, y - 5);
		glVertex2d(x + 5, y + 5);
		glVertex2d(x - 5, y + 5);
		glEnd();

		char *stop2;
		stop2 = new char[stop.size() + 1];
		strcpy(stop2, stop.c_str());
	

		glRasterPos2i(int(x + 10), int(y));  // sets position
		glColor3ub(0, 0, 255);
		YsGlDrawFontBitmap8x12(stop2);

		DrawingUtilNG::writeTimesRoman(stop, int(x + 10), int(y), 24);
	}
	void drawFrame() {  //draws the frame of map monitor
		glLineWidth(5);
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2d(50, 50);
		glVertex2d(1050, 50);
		glVertex2d(1050, 571);
		glVertex2d(50, 571);
		glEnd();
	}
	void background() {  //Set background color of panel, also cover part of the map that is shown
		glColor3ub(255, 255, 200);
		glBegin(GL_QUADS);
		glVertex2d(0, 0);
		glVertex2d(1050, 0);
		glVertex2d(1050, 50);
		glVertex2d(0, 50);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2d(0, 50);
		glVertex2d(0, 571);
		glVertex2d(50, 571);
		glVertex2d(50, 50);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2d(0, 571);
		glVertex2d(0, 1000);
		glVertex2d(1500, 1000);
		glVertex2d(1500, 571);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2d(1050, 571);
		glVertex2d(1500, 571);
		glVertex2d(1500, 0);
		glVertex2d(1050, 0);
		glEnd();
	}

	void drawMapBottom() {    // set color of map monitor background color
		glColor3ub(192, 192, 192);
		glBegin(GL_QUADS);
		glVertex2d(53, 53);
		glVertex2d(1047, 53);
		glVertex2d(1047, 568);
		glVertex2d(53, 568);
		glEnd();
	}
};

int main()
{

	// =======================================================================
	// Inititalization for map and flight parameters.
	int x = 50, y = 50;
	int prevLocX = 50, prevLocY = 50;
	int width = 1000, height = 521;
	bool mode;
	double scale = 1;
	int time;
	bool if_paused = false;
	int leftButton, middleButton, rightButton, locX, locY;
	int mouseEvent;
	Airline_Menu menu(1050, 50, 250, 50);
	GUI gui;
	gui.load_data("Data.csv");
	Map C_map;

	// =========================================================================
	// Inititalization for GUI time scroll bar.
	int x1 = 1050; int y1 = 570; int height1 = 120; int width1 = 100;
	int x2 = 1150; int y2 = 570; int height2 = 120; int width2 = 100;
	int posX, posY;
	int departT = 1;
	int arriveT = 23;
	int departT_m = 1;
	int arriveT_m = 1439;
	int baseTD, addTD, baseTA, addTA;   addTA = 0; addTD = 0;
	double yboxD = y1 - height1 / 2. - 0.1; //xcode-   // initialize boxD:
	double yboxA = y1 - height1 / 4. - 0.1; // xcode-   //initialize boxA:
	DButton DepartB(x1, y1, height1, width1);
	AButton ArrivalB(x2, y2, height2, width2);
	int timeChanged = 0;

	FsOpenWindow(100, 16, 1300, 900, 1);
	int key = FSKEY_NULL;
	while (FSKEY_ESC != key)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		FsPollDevice();
		key = FsInkey();
		// =============================================================
		// Pause & zoon in/out feature keys setup.
		switch (key)
		{
		case FSKEY_SPACE:
			if_paused = (!if_paused);
			break;
		case FSKEY_WHEELUP:
			mode = true;
			if (scale < 4 && locX > 50 && locX < 1050 && locY > 50 && locY < 571)   //Zoom in limit
				Zoom(mode, x, y, width, height, locX, locY, scale);                
			break;
		case FSKEY_WHEELDOWN:
			mode = false;
			if (scale > 1 && locX > 50 && locX < 1050 && locY > 50 && locY < 571)  //Zoom out limit
				Zoom(mode, x, y, width, height, locX, locY, scale);
			break;
		default:
			break;
		}
		// ===========================================================
		// Draw map, flgiht and airline menu.
		C_map.drawMapBottom();
		C_map.show(x, y, width, height);//display map
		if (!if_paused)
		{
			gui.time(&time, departT, &timeChanged);
		}
		gui.draw(x, y, width, height);
		C_map.drawFrame();
		C_map.background();
		mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);
		menu.handle_mouse_event(mouseEvent, locX, locY);
		menu.draw();


		// =============================================================
		// Time scroll bar keys, decision loop and draw.
		DepartB.drawFrame();
		DepartB.drawBox(yboxD);
		ArrivalB.drawFrame();
		ArrivalB.drawBox(yboxA);
		baseTD = DepartB.drawText(yboxD);
		baseTA = ArrivalB.drawText(yboxA);

		if (leftButton == 1) {
			posX = locX; posY = locY;
			if (posX >= x1 && posX <= x1 + width1 / 4. && posY<y1 && posY>y1 - height1) {//xcode-: posY>y1 && posY<y1-height1
				yboxD = posY;
				DepartB.drawBox(yboxD);
				baseTD = DepartB.drawText(yboxD);
			}
		}
		if (leftButton == 1) {
			posX = locX; posY = locY;
			if (posX >= x1 + width1 / 4 && posX <= x1 + width1 && posY<y1 && posY>y1 - height1) {//xcode-: posY>y1 && posY<y1-height1
				if (y1 - posY <= 3. / 16 * height1) { addTD = 3; }
				else if (y1 - posY <= 3. / 8 * height1) { addTD = 2; }
				else if (y1 - posY <= 9. / 16 * height1) { addTD = 1; }
				else { addTD = 0; }
				timeChanged = 1;
			}
		}
		if (leftButton == 1) {
			posX = locX; posY = locY;
			if (posX >= x2 && posX <= x2 + width2 / 4. && posY<y2 && posY>y2 - height2) {//xcode-: posY>y2 && posY<y2-height2
				yboxA = posY;
				ArrivalB.drawBox(yboxA);
				baseTA = ArrivalB.drawText(yboxA);
			}
		}
		if (leftButton == 1) {
			posX = locX; posY = locY;
			if (posX >= x2 + width2 / 4 && posX <= x2 + width2 && posY<y2 && posY>y2 - height2) {//xcode-: posY>y2 && posY<y2-height2
				if (y2 - posY <= 3. / 16 * height2) { addTA = 3; }
				else if (y2 - posY <= 3. / 8 * height2) { addTA = 2; }
				else if (y2 - posY <= 9. / 16 * height2) { addTA = 1; }
				else { addTA = 0; }
			}
		}

		departT = DepartB.returntime(baseTD, addTD); // hour
		arriveT = ArrivalB.returntime(baseTA, addTA); // hour
		departT_m = departT * 60; // min
		arriveT_m = arriveT * 60; // min
		//====================================================================================
		// Filtering flights.

		gui.search_flight("ALL", "ALL", departT_m, arriveT_m, menu.current_airline);

		if (leftButton && locX != prevLocX && locY != prevLocY && locX > 50 && locX < 1050 && locY > 50 && locY < 571) { //Pan condition and limit
			Pan(x, y, locX, locY, prevLocX, prevLocY, scale);
		}
		prevLocX = locX;
		prevLocY = locY;

		//==================================================================
		
		FsSwapBuffers();
		FsSleep(50);
	}
	return 0;
}
