//
//  arrivalbutton.cpp
//  GUI_Departuretime

#include "arrivalbutton.h"



AButton::AButton(int x1,int y1,int height1, int width1){
    x= x1;y=y1;height=height1; width = width1;
}



void AButton::drawFrame ( ) {
    glColor3ub(0,0,0);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x+width,y);
    glVertex2d(x+width, y-height);   // xcode-
    glVertex2d(x,y-height);  // xcode-
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2d(x, y-3.*height/4.);// xcode-
    glVertex2d(x+width, y-3.*height/4.);// xcode-
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2d(x+width/4., y);
    glVertex2d(x+width/4., y-3.*height/4.); //xcode-
    glEnd();
    
    for (int i = 1; i < 4; i++){
        glBegin(GL_LINES);
        glVertex2d(x+width/4, y - 3./16.*i*height); //xcode-
        glVertex2d(x+width, y - 3./16.*i*height); //xcode-
        glEnd();
    }
    
    glBegin(GL_QUADS);   // bar in black
    glVertex2d(x+width/12., y);
    glVertex2d(x+2*width/12., y);
    glVertex2d(x+2*width/12., y-3.*height/4.); //xcode-
    glVertex2d(x+width/12., y-3.*height/4.); //xcode-
    glEnd();
    
    glRasterPos2d(x+5,y-3.*height/4.-10); // xcode-
    YsGlDrawFontBitmap6x10("Arrival Time");
}

void AButton::drawBox (double ybox) {
    glColor3ub(220, 220, 220); // light grey, height of box: height/8, half of it : height/16
    glBegin(GL_QUADS);
    if (ybox > y-height/16.) { // xcode change: ybox < y+ height/16
        glVertex2d(x, y);
        glVertex2d(x+width/4., y);
        glVertex2d(x+width/4., y-height/8.); //xcode-
        glVertex2d(x, y-height/8.); //xcode-
    }
    else if (ybox < y - 3.*height/4+height/16){  // xcode change: ybox > y + 3*height/4 - height/16
        glVertex2d(x, y-3.*height/4); //xcode-
        glVertex2d(x+width/4., y-3.*height/4.); //xcode-
        glVertex2d(x+width/4., y-5.*height/8. ); //xcode-
        glVertex2d(x, y-5.*height/8.); //xcode-
    }
    else {
        glVertex2d(x,ybox-height/16.);
        glVertex2d(x+width/4., ybox-height/16.);
        glVertex2d(x+width/4., ybox+height/16.);
        glVertex2d(x, ybox+height/16.);
    }
    glEnd();
}

int AButton::drawText (double ybox){
    glColor3ub(0, 0, 255);
    int baseT;
    if (y-ybox < height/8) {
        glRasterPos2i(x+width/4.+5,y-5);  // xcode-   // sets position
        YsGlDrawFontBitmap8x12("23 : 59");  glRasterPos2d(x+width/4+5,y-3.*height/16.-5);  // xcode-
        YsGlDrawFontBitmap8x12("22 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/8.-5);  // xcode-
        YsGlDrawFontBitmap8x12("21 : 00");  glRasterPos2d(x+width/4+5,y-9.*height/16.-5); // xcode-
        YsGlDrawFontBitmap8x12("20 : 00");  baseT=20;   }
    else if (y-ybox < height/4) {
        glRasterPos2i(x+width/4.+5,y-5);  // xcode-  // sets position
        YsGlDrawFontBitmap8x12("19 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/16.-5);  // xcode-
        YsGlDrawFontBitmap8x12("18 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/8.-5);  // xcode-
        YsGlDrawFontBitmap8x12("17 : 00");  glRasterPos2d(x+width/4+5,y-9.*height/16.-5); // xcode-
        YsGlDrawFontBitmap8x12("16 : 00");  baseT=16; }
    else if (y-ybox < 3*height/8){
        glRasterPos2i(x+width/4.+5,y-5);  // xcode-  // sets position
        YsGlDrawFontBitmap8x12("15 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/16.-5);  // xcode-
        YsGlDrawFontBitmap8x12("14 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/8.-5);  // xcode-
        YsGlDrawFontBitmap8x12("13 : 00");  glRasterPos2d(x+width/4+5,y-9.*height/16.-5); // xcode-
        YsGlDrawFontBitmap8x12("12 : 00");  baseT=12; }
    else if (y-ybox < height/2){
        glRasterPos2i(x+width/4.+5,y-5);   // xcode- // sets position
        YsGlDrawFontBitmap8x12("11 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/16.-5);  // xcode-
        YsGlDrawFontBitmap8x12("10 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/8.-5);  // xcode-
        YsGlDrawFontBitmap8x12("09 : 00");  glRasterPos2d(x+width/4+5,y-9.*height/16.-5); // xcode-
        YsGlDrawFontBitmap8x12("08 : 00");  baseT=8; }
    else if (y-ybox < 5.*height/8.){
        glRasterPos2i(x+width/4.+5,y-5);   // xcode- // sets position
        YsGlDrawFontBitmap8x12("07 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/16.-5);  // xcode-
        YsGlDrawFontBitmap8x12("06 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/8.-5);  // xcode-
        YsGlDrawFontBitmap8x12("05 : 00");  glRasterPos2d(x+width/4+5,y-9.*height/16.-5); // xcode-
        YsGlDrawFontBitmap8x12("04 : 00");  baseT=4;  }
    else {
        glRasterPos2i(x+width/4.+5,y-5);  // xcode-  // sets position
        YsGlDrawFontBitmap8x12("03 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/16.-5);  // xcode-
        YsGlDrawFontBitmap8x12("02 : 00");  glRasterPos2d(x+width/4+5,y-3.*height/8.-5);  // xcode-
        YsGlDrawFontBitmap8x12("01 : 00");  glRasterPos2d(x+width/4+5,y-9.*height/16.-5); // xcode-
        YsGlDrawFontBitmap8x12("00 : 00");  baseT=0;  }
    return baseT;
}


int AButton::returntime(int baseT, int addT){
    double ybox;
    int Atime;
    
    Atime= baseT + addT;
    
    return Atime;
}
