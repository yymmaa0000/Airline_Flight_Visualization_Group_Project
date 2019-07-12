
#pragma once

void Zoom(bool mode, int &x, int &y, int &mapwidth, int &mapheight, int mouseX, int mouseY, double &scale);
void Pan(int &x, int &y, int locX, int locY, int prevLocX, int prevLocY, double scale);