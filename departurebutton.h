//
//  departurebutton.h


#include <stdio.h>
#include "fssimplewindow.h"
#include <string>
#include <iostream>
#include "ysglfontdata.h"


using namespace std;


/*class Mouse_activity {
public:
    int x1,y1,x2,y2;
};  */


class DButton {   //DepartureButton
    int x;int y;int height;int width;//x,y: coordinates of lower left corner
public:
    DButton(int x1,int y1,int height1, int width1);
    void drawFrame ();  //x,y: coordinates of lower left corner
    void drawBox ( double ybox);// ybox: userclick_y
    int drawText (  double ybox);
    int returntime(int baseT, int addT );
};


