# Airline_Flight_Visualization_Group_Project
This is a group project creating a GUI to display airline flight information between major cities in U.S.   
This project was written in C++ and OpenGL library

The project was completed on 12/10/2018, and was just uploaded to my Github account recently

This project was written without any GUI library. The basic function includes:
1. Map with some major cities on it
2. GUI: time bar (let user choose which time the flight information they want)
3. GUI: Information searching/sorting (let user search airline companies)
4. Airlines and flights corresponding with current time
5. Zoom in/out Feature
6. Animation to show all the flight in 24 hours

The GUI that allows the user to choose to view flights from specific airlines, time slots and destinations. The program visualizes the flight information as lines between two cities with a little airplane on the line to show the amount of distance it has traveled. The user is able to search for airline name, arrival and departure time and current flight status to find specific flights. The user is also able to select a major city and find all the connecting flights to this city. Finally, the user is able to pan and zoom the map using mouse.

In addition to the searching and visualization functionality, this program can also display the airline traffic in a 24-hour time period. With this, the user is able to see the the amount of airline flights in all cities during an a day in a animation and get a better understanding of the airline traffic in US at different time and location in a day.

This product will enables the user to check the available airlines at a specific time during the 24 hours of a designated date. Throughout the squeezed display animation of the trajectories of the entire flights, the user will get an overview regarding to the speed and the timescale of each flight. The trajectory of each flight can be picked by the user to show its detailed information.

#### Compile instruction:  ####
.h Files: 
* airline_menu.h  
* arrivalbutton.h  
* departurebutton.h  
* sorting_and_flight.h  
* Zoom_Pan.h  

.cpp Files:  
* main.cpp  
* aieline_menu.cpp  
* arrivalbutton.cpp  
* departurebutton.cpp  
* sorting_and_flight.cpp  
* Zoom_Pan.cpp  
    
Source Files:  
* fssimplewindow.cpp  
* fssimplewindow.h  
* yspng.cpp  
* yspng.h  
* ysglfontdata.c  
* ysglfont.h  
* DrawingUtilNG.cpp  
* DrawingUtilNG.h  
* Data.csv (containing recorded airline information)  
* map4.png (back ground map)  

To run the program, load it in Visual Studio and run main.cpp.


#### User instruction about the GUI we designed: ####
![alt text](https://github.com/yymmaa0000/Airline_Flight_Visualization_Group_Project/blob/master/user%20guide/user%20instruction.png)

