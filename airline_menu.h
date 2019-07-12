#pragma once
#include "fssimplewindow.h"
#include "yspng.h"
#include <string>
#include <iostream>

using namespace std;

class Mouse_event_regoin { 
	// regoin on the window where the mouse click event is meaningful
public:
	int x1, y1, x2, y2;
	// coordinate of the upperleft and bottomright points of region
	Mouse_event_regoin();
	Mouse_event_regoin(int x3, int x4, int y3, int y4);
	void init(int x3, int x4, int y3, int y4);
	bool is_inside_region(int x, int y); // determine if the mouse at location x,y is inside this region
};

class Logo {
	string filename;
	YsRawPngDecoder png;
	//GLuint texId; // this will be use as texture identifiers for the two PNGs

	void read_png(); // load png file
public:
	bool mouse_on_it; // to indicate if the mouse is on top of this logo

	Logo() {};
	Logo(string filename1); // initialize a logo by giving it the logo png file name
	void init(string filename1); // initialize a logo by giving it the logo png file name

								 // draw the logo in a box with width and height and its upperleft corner at window coordinate x and y
	void draw(int x, int y, int width, int height);

	// draw the logo frame in a box with width and height and its upperleft corner at window coordinate x and y
	// draw it with the color r,g,b
	void draw_frame(int x, int y, int width, int height, int r, int g, int b);
};

class Drop_down_buttom {
	int x, y, width, height; // width and height and its upperleft corner at window coordinate x and y
public:
	bool mouse_on_it; // to indicate if the mouse is on top of this button

	Drop_down_buttom() {};
	void init(int x1, int y1, int width1, int height1);
	void draw();
};

class Airline_Menu {
	int x, y, width, height; // width and height and its upperleft corner at window coordinate x and y
	int number_of_logo;
	Drop_down_buttom buttom;
	Logo logo[6]; // contains 5 airline logos and 1 logo for all airline
	int current_logo; // the index of the logo that will be displayed in the main menu
	Mouse_event_regoin mouse_event_regoin[7]; // keep track of the reguion of screen where the mouse click is meaningful
	bool show_drop_down_menu; // indicate if the drop down menu is showing

	string logo_to_airline(int logo); // converts the current logo index to airline name
	void change_current_airline(int logo); // change the currently selected airline
public:
	// the name of the current airline selected
	// can be the following option:
	// ALL, AA, UA, Delta, Alaska, Southwest
	// this variable can be used by other objects to get the information about the selected airline
	string current_airline;

	// create a airline menu with its upper left corner at coordinate x1 and y1
	// also with width = width1 and height = height1
	Airline_Menu(int x1, int y1, int width1, int height1);
	void draw(); // draw the entire menu

				 // handel mouse event, need to pass in the mouse location and mouse clicking status
	void handle_mouse_event(int mouseEvent, int locX, int locY);
};
