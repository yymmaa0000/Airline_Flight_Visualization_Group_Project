#include "sorting_and_flight.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include"DrawingUtilNG.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
using namespace std;
#define PI 3.1415926

const char *p[18] = { "ORD", "ATL", "LAX", "DEN", "SFO", "LAS",
"SEA", "CLT", "EWR", "JFK", "MCO", "PHX",
"MIA", "IAH", "BOS", "DTW", "MSP", "DFW" };//Airport name
const double coord[18][2] = { { 690, 200 },{ 755, 380 },{ 150, 360 },{ 400, 255 },{ 110, 290 },{ 190, 290 },
{ 70, 90 },{ 810, 345 },{ 920, 230 },{ 930, 220 },{ 800, 490 },{ 280, 380 },
{ 815, 530 },{ 560, 460 },{ 970, 195 },{ 765, 205 },{ 600, 140 },{ 525, 395 } };//Airport coordinates


int convert_to_minutes(int hour, int minute)
{
	return hour * 60 + minute;
}

void Flight::air_addre(int x, int y, int mapw, int maph)//calculate and display the location of the plane for the current airport, based on the data struct of the flight information
{

	printf("%02d:%02d\r\r\r\r", h, m);
	// ===============================================

	string timeNow = to_string(h) + ":" + to_string(m);
	glRasterPos2i(980, 500);  // sets position
	glColor3ub(0, 0, 255);
	YsGlDrawFontBitmap8x12(timeNow.c_str());

	glRasterPos2i(850, 500);  // sets position
	glColor3ub(0, 0, 255);
	YsGlDrawFontBitmap8x12("Current Time: ");

	//=====================================================

	if (show == false) return;
	int cur_time = convert_to_minutes(h, m) - start_time;//calculate the difference between the current time and the departure time
	if (convert_to_minutes(h, m) < start_time || convert_to_minutes(h, m) > stop_time)return;//if negative, then the plane doesn't takeoff, end function
	flight_line(x, y, mapw, maph);//draw trajectory
	int times = stop_time - start_time;//calculate the difference between landing and landing time 
	double a = fight_info.a1 - fight_info.a0;//calculate the difference between the two angles
	double cur_a;
	//Calculate the current angle of aircraft according to the time ratio, calculate separately based on the direction of landing and landing
	if (fight_info.s_x < fight_info.a_x)
		cur_a = ((double)cur_time / times * a + fight_info.a0);
	else
		cur_a = (-(double)cur_time / times * a + fight_info.a1);
	//Calculate the position of the aircraft and draw based on the angle of the aircraft
	double x1 = fight_info.c_x + (fight_info.c_r + 2.5)*sin(cur_a*PI / 180);
	double y1 = fight_info.c_y - (fight_info.c_r + 2.5)*cos(cur_a*PI / 180);

	cur_locx = x1;
	cur_locy = y1;

	draw_flight();

	char *flight_number2;
	flight_number2 = new char[flight_number.size() + 1];
	strcpy(flight_number2, flight_number.c_str());


	glRasterPos2i(int(x1 + 10), int(y1));  // sets position
	glColor3ub(0, 0, 255);
	YsGlDrawFontBitmap8x12(flight_number2);


	DrawingUtilNG::writeTimesRoman(flight_number, int(x1 + 10), int(y1), 8);
}
void Flight::flight_line(int x, int y, int mapwidth, int mapheight)//determine the trajectory and draw it based on the location of the departure and landing airport
{
	// Determine the coordinates of the airport according to the name of the landing airport (coord[i][0] - 50) *(width)/1000 + x, (coord[i][1] - 50) * (height)/521 + y,
	for (int i = 0; i < 18; i++)
	{
		if (start_place == *(p + i))
		{
			fight_info.s_x = (coord[i][0] - 50) *(mapwidth) / 1000 + x;
			fight_info.s_y = (coord[i][1] - 50) * (mapheight) / 521 + y;
		}
		if (arrive_place == *(p + i))
		{
			fight_info.a_x = (coord[i][0] - 50) *(mapwidth) / 1000 + x;
			fight_info.a_y = (coord[i][1] - 50) * (mapheight) / 521 + y;
		}
	}


	double x1 = fight_info.s_x, y1 = fight_info.s_y, x2 = fight_info.a_x, y2 = fight_info.a_y;//assign the landing airport coordinates to x1, y1, x2, y1 for calculation

																							  //direct distances
	double distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	double d = distance / 6;
	//circle radius
	double r = 10 * distance / 12;
	fight_info.c_r = r;
	double sina0 = (y1 - y2) / distance;
	double cosa0 = (x1 - x2) / distance;
	//center coordinates（xx，yy）
	double t = cosa0 < 0 ? 1 : -1;
	double xx = (x1 + x2) / 2 + (r - d)*sina0*t;
	fight_info.c_x = xx;
	double yy = (y1 + y2) / 2 + abs((r - d)*cosa0);//for the two sets of coordinates in calculation, the increment of yy is positive taking the center of the circle below
	fight_info.c_y = yy;
	//Calculate the angle of deflection of the landing and landing airport to its center
	double sina = (x1 - xx) / r;
	double cosa = -(y1 - yy) / r;
	double angle0 = acos(cosa) * 180 / PI;
	if (sina < 0)
		angle0 = -angle0;
	double sinb = (x2 - xx) / r;
	double cosb = -(y2 - yy) / r;
	double angle1 = acos(cosb) * 180 / PI;
	if (sinb < 0)
		angle1 = -angle1;
	//find the size between the two angles
	double anglemin = (angle0 < angle1) ? angle0 : angle1;
	double anglemax = (angle0 > angle1) ? angle0 : angle1;
	fight_info.a0 = anglemin;
	fight_info.a1 = anglemax;
	glColor3ub(100, 100, 200);
	glBegin(GL_QUADS);
	double bit = 500 / r;
	//draw the trajectory according to two angles
	for (double iangle = anglemin; iangle + bit <= anglemax; iangle += 2 * bit)
	{
		glVertex2d(xx + (r + 1.5)*sin(iangle*PI / 180), yy - (r + 1.5)*cos(iangle*PI / 180));
		glVertex2d(xx + (r + 1.5)*sin((iangle + bit)*PI / 180), yy - (r + 1.5)*cos((iangle + bit)*PI / 180));
		glVertex2d(xx + (r - 1.5)*sin((iangle + bit)*PI / 180), yy - (r - 1.5)*cos((iangle + bit)*PI / 180));
		glVertex2d(xx + (r - 1.5)*sin(iangle*PI / 180), yy - (r - 1.5)*cos(iangle*PI / 180));
	}
	glEnd();
}

void Flight::draw_flight() {
	int t; //decide the direction of plane 
	if (fight_info.s_x < fight_info.a_x)
		t = 1;
	else
		t = -1;
	int scale = 2;
	t = t * scale;
	glColor3ub(0, 25, 255);
	glBegin(GL_POLYGON);
	glVertex2d(cur_locx, cur_locy);
	glVertex2d(cur_locx - 2 * t, cur_locy + 2 * scale);
	glVertex2d(cur_locx, cur_locy + 2 * scale);
	glVertex2d(cur_locx + 2 * t, cur_locy);
	glVertex2d(cur_locx + 8 * t, cur_locy);
	glVertex2d(cur_locx + 4 * t, cur_locy - 2 * scale);
	glVertex2d(cur_locx - 4 * t, cur_locy - 2 * scale);
	glVertex2d(cur_locx - 4 * t, cur_locy);
	glEnd();

	glColor3ub(0, 25, 255);
	glBegin(GL_POLYGON);
	glVertex2d(cur_locx + 2 * t, cur_locy - 2 * scale);
	glVertex2d(cur_locx, cur_locy - 4 * scale);
	glVertex2d(cur_locx - 2 * t, cur_locy - 4 * scale);
	glVertex2d(cur_locx, cur_locy - 2 * scale);
	glEnd();

	glColor3ub(0, 25, 255);
	glBegin(GL_POLYGON);
	glVertex2d(cur_locx - 4 * t, cur_locy - 2 * scale);
	glVertex2d(cur_locx - 6 * t, cur_locy - 4 * scale);
	glVertex2d(cur_locx - 6 * t, cur_locy - 2 * scale);
	glVertex2d(cur_locx - 4 * t, cur_locy);
	glEnd();
}



void GUI::load_data(string filename)
{
	string input;
	string delimiter = ",";
	int counter = 0, hour, minute;
	char clone[100];
	char * temp, *target;

	// open the file
	ifstream infile;
	infile.open(filename.c_str());

	// check if it opened
	if (!infile.is_open()) {
		cout << "File is not opened correctly!" << endl;
		return;
	}

	// read it but read past end
	while (counter < number_of_flight && !infile.eof()) {
		getline(infile, input);

		// copy the input string
		strcpy_s(clone, input.c_str());

		// break the string into pieces when there is a space
		// convert each piece from char to int
		target = strtok_s(clone, ",", &temp);
		flight[counter].start_place = target;
		target = strtok_s(temp, ",", &temp);
		flight[counter].arrive_place = target;
		//starting time
		target = strtok_s(temp, ",", &temp);
		hour = atoi(target);
		target = strtok_s(temp, ",", &temp);
		minute = atoi(target);
		flight[counter].start_time = convert_to_minutes(hour, minute);
		//ending time
		target = strtok_s(temp, ",", &temp);
		hour = atoi(target);
		target = strtok_s(temp, ",", &temp);
		minute = atoi(target);
		flight[counter].stop_time = convert_to_minutes(hour, minute);

		target = strtok_s(temp, ",", &temp);
		flight[counter].airline = target;
		target = strtok_s(temp, ",", &temp);
		flight[counter].flight_number = target;

		counter++;
	}

	// close it
	infile.close();

}

void GUI::time(int *count, int start_time, int *timeChange)
{
	if (*timeChange == 1)
	{
		for (int i = 0; i < number_of_flight; i++) {
			flight[i].h = start_time;
		}
		*timeChange = 0;
	}



	for (int i = 0; i < number_of_flight; i++) {

		if (flight[i].m >= 56)
		{
			flight[i].h++;
			flight[i].m = 0;
			if (flight[i].h > 23)
				flight[i].h = 0;
		}

		flight[i].m += 4;
		*count = flight[i].h * 60 + flight[i].m;
	}
}

void GUI::draw(int x, int y, int mapw, int maph)
{
	for (int i = 0; i < number_of_flight; i++) {
		if (flight[i].show == true)
			flight[i].air_addre(x, y, mapw, maph);
	}
}

void GUI::getinfo()
{
	for (int i = 0; i < number_of_flight; i++) {
		flight[i].start_place;
	}
}


void GUI::search_flight(string start_place, string arrive_place, int start_time, int stop_time, string airline)
{
	for (int i = 0; i < number_of_flight; i++) {
		if (start_place == "ALL" || flight[i].start_place == start_place) {
			if (arrive_place == "ALL" || flight[i].arrive_place == arrive_place) {
				if (flight[i].start_time >= start_time && flight[i].stop_time <= stop_time) {
					if (airline == "ALL" || flight[i].airline == airline) {
						flight[i].show = true;
						continue;
					}
				}
			}
		}
		flight[i].show = false;
	}
}

void GUI::search_flight(string start_and_arrive_place, int start_time, int stop_time, string airline)
{
	for (int i = 0; i < number_of_flight; i++) {
		if (start_and_arrive_place == "ALL" || flight[i].start_place == start_and_arrive_place
			|| flight[i].arrive_place == start_and_arrive_place) {
			if (flight[i].start_time >= start_time && flight[i].stop_time <= stop_time) {
				if (airline == "ALL" || flight[i].airline == airline) {
					flight[i].show = true;
					continue;
				}
			}
		}
		flight[i].show = false;
	}
}

void GUI::search_flight(string start_place, string arrive_place, int time, string airline)
{
	for (int i = 0; i < number_of_flight; i++) {
		if (start_place == "ALL" || flight[i].start_place == start_place) {
			if (arrive_place == "ALL" || flight[i].arrive_place == arrive_place) {
				if (flight[i].start_time <= time && flight[i].stop_time >= time) {
					if (airline == "ALL" || flight[i].airline == airline) {
						flight[i].show = true;
						continue;
					}
				}
			}
		}
		flight[i].show = false;
	}
}

void GUI::search_flight(string start_and_arrive_place, int time, string airline)
{
	for (int i = 0; i < number_of_flight; i++) {
		if (start_and_arrive_place == "ALL" || flight[i].start_place == start_and_arrive_place
			|| flight[i].arrive_place == start_and_arrive_place) {
			if (flight[i].start_time <= time && flight[i].stop_time >= time) {
				if (airline == "ALL" || flight[i].airline == airline) {
					flight[i].show = true;
					continue;
				}
			}
		}
		flight[i].show = false;
	}
}

void GUI::search_flight(string start_place, string arrive_place, int start_time, int stop_time)
{
	search_flight(start_place, arrive_place, start_time, stop_time, "ALL");
}

void GUI::search_flight(string start_place, string arrive_place, int time)
{
	search_flight(start_place, arrive_place, time, "ALL");
}

void GUI::search_flight(string start_place, string arrive_place)
{
	search_flight(start_place, arrive_place, 0, 24 * 60, "ALL");
}

void GUI::search_flight(string start_place, string arrive_place, string airline)
{
	search_flight(start_place, arrive_place, 0, 24 * 60, airline);
}

void GUI::search_flight(string start_and_arrive_place, int start_time, int stop_time)
{
	search_flight(start_and_arrive_place, start_time, stop_time, "ALL");
}

void GUI::search_flight(string start_and_arrive_place, int time)
{
	search_flight(start_and_arrive_place, time, "ALL");
}

void GUI::search_flight(string start_and_arrive_place)
{
	search_flight(start_and_arrive_place, 0, 24 * 60, "ALL");
}

void GUI::search_flight(int start_time, int stop_time)
{
	search_flight("ALL", start_time, stop_time, "ALL");
}

void GUI::search_flight(int time)
{
	search_flight("ALL", time, "ALL");
}
