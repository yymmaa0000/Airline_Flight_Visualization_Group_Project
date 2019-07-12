#pragma once
#include <string>

using namespace std;

int convert_to_minutes(int hour, int minute); // convert hour:minute to minutes

struct flight_port {
	double s_x, s_y, a_x, a_y;//coordinates of the start point and end point
	double c_x, c_y, c_r;//trajectory related properties of flight path
	double a0, a1;//start value and end value of the radius of flight path
};

class Time {

public:
	int h;
	int m;
	Time()
	{
		h = 0;
		m = 0;
	};
};

class Flight :public Time {
private:
	double cur_locx, cur_locy;

public:
	string start_place, arrive_place, flight_number, airline; //DFW, ORD
	flight_port fight_info;
	int start_time, stop_time;
	bool show = true;
	void air_addre(int x, int y, int mapwidth, int mapheight);//calculate and display the location of airplane for the current airport, based on the struct data of the flight information
	void flight_line(int x, int y, int mapwidth, int mapheight);//determine the trajectory based on the?location of the departure and landing airport
	void draw_flight(); // draw the plane
};

class GUI : Flight {
public:
	static const int number_of_flight = 60;
	Flight flight[number_of_flight];
	void load_data(string filename); // load data from a file
	void draw(int *count, int x, int y, int mapw, int maph, int start_time, bool *timeChange[]);
	void getinfo();

	// search all flights that travels from "start_place" to "arrive_place" within time period
	// from "start_time" to "stop_time" (written in minutes) in a specific "airline"
	// Note, you can put "ALL" in start_place, arrive_place and airline to search
	// for all places or all airline
	void search_flight(string start_place, string arrive_place, int start_time, int stop_time, string airline);

	// search all flights that leave from or arrive at "start_and_arrive_place"
	// within time period from "start_time" to "stop_time" (written in minutes) in a specific "airline"
	// Note, you can put "ALL" in start_place, arrive_place and airline to search
	// for all places or all airline
	void search_flight(string start_and_arrive_place, int start_time, int stop_time, string airline);

	// search all flights that travels from "start_place" to "arrive_place" and is still in the sky
	// during the "time" (written in minutes) in a specific "airline"
	// Note, you can put "ALL" in start_place, arrive_place and airline to search
	// for all places or all airline
	void search_flight(string start_place, string arrive_place, int time, string airline);

	// search all flights that leave from or arrive at "start_and_arrive_place"
	// and is still in the sky during the "time" (written in minutes) in a specific "airline"
	// Note, you can put "ALL" in start_place, arrive_place and airline to search
	// for all places or all airline
	void search_flight(string start_and_arrive_place, int time, string airline);

	// search all flights that travels from "start_place" to "arrive_place" within time period
	// from "start_time" to "stop_time" (written in minutes) in all airline
	// Note, you can put "ALL" in start_place, arrive_place to search for all places
	void search_flight(string start_place, string arrive_place, int start_time, int stop_time);

	// search all flights that travels from "start_place" to "arrive_place"  
	// and is still in the sky during the "time" (written in minutes) in all airline
	// Note, you can put "ALL" in start_place, arrive_place to search for all places
	void search_flight(string start_place, string arrive_place, int time);

	// search all flights that travels from "start_place" to "arrive_place"  
	// in all time and airline
	// Note, you can put "ALL" in start_place, arrive_place to search for all places
	void search_flight(string start_place, string arrive_place);

	// search all flights that travels from "start_place" to "arrive_place" in a specific "airline"
	// Note, you can put "ALL" in start_place, arrive_place and airline to search for all places or all airline
	void search_flight(string start_place, string arrive_place, string airline);

	// search all flights that leave from or arrive at "start_and_arrive_place" within time period
	// from "start_time" to "stop_time" (written in minutes) in all airline
	// Note, you can put "ALL" in start_place, arrive_place to search for all places
	void search_flight(string start_and_arrive_place, int start_time, int stop_time);

	// search all flights that leave from or arrive at "start_and_arrive_place"?	// and is still in the sky during the "time" (written in minutes) in all airline
	void search_flight(string start_and_arrive_place, int time);

	// search all flights that leave from or arrive at "start_and_arrive_place"?	// in all time and airline
	void search_flight(string start_and_arrive_place);

	// search all flights that are within time period from "start_time" to "stop_time"?	// (written in minutes) in all airline
	void search_flight(int start_time, int stop_time);

	// search all flights that are still in the sky during the "time"?	// (written in minutes) in all airline
	void search_flight(int time);
};