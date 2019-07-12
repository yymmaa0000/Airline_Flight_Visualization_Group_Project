#include "airline_menu.h"

void Logo::read_png()
{
	if (YSOK == png.Decode(filename.c_str())) {
		//printf("Read Width=%d Height=%d\n", png.wid, png.hei);
		png.Flip();
	}
	else {
		printf("Read Error!\n");
		return;
	}
	//glGenTextures(1, &texId);// Reserve one texture identifier
	//glBindTexture(GL_TEXTURE_2D, texId);?// Making the texture identifier current (or bring it to the deck)
}

Logo::Logo(string filename1)
{
	init(filename1);
}

void Logo::init(string filename1)
{
	filename = filename1;
	read_png();
	mouse_on_it = false;
}

void Logo::draw(int x, int y, int width, int height)
{
	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	// in order for textures to show, you must create a projection
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind a texture to OpenGL primitives
	//glBindTexture(GL_TEXTURE_2D, texId);

	glBegin(GL_QUADS);

	// For each vertex, assign texture coordinate before vertex coordinate.
	glTexCoord2d(0.0, 1.0);
	glVertex2i(x, y);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(x + width, y);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(x + width, y + height);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(x, y + height);

	glEnd();

	draw_frame(x, y, width, height, 0, 0, 0);
}

void Logo::draw_frame(int x, int y, int width, int height, int r, int g, int b)
{
	glColor3ub(r, g, b);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x, y);
	glVertex2i(x + width, y);
	glVertex2i(x + width, y + height);
	glVertex2i(x, y + height);
	glEnd();
}

string Airline_Menu::logo_to_airline(int logo)
{
	string result;
	switch (logo) {
	case 1:
		result = "AA";
		break;
	case 2:
		result = "UA";
		break;
	case 3:
		result = "Delta";
		break;
	case 4:
		result = "Alaska";
		break;
	case 5:
		result = "Southwest";
		break;
	default:
		result = "ALL";
		break;
	}
	return result;
}

void Airline_Menu::change_current_airline(int logo)
{
	if (logo < 0 || logo >= number_of_logo) return;
	current_logo = logo;
	current_airline = logo_to_airline(logo);
}

Airline_Menu::Airline_Menu(int x1, int y1, int width1, int height1)
{
	x = x1;
	y = y1;
	width = width1;
	height = height1;
	number_of_logo = 6;

	buttom.init(x + width - height, y, height, height);
	show_drop_down_menu = false;

	logo[0].init("logo/All.png");
	logo[1].init("logo/AA_Logo.png");
	logo[2].init("logo/UA-Logo.png");
	logo[3].init("logo/Delta_Logo.png");
	logo[4].init("logo/Alaska_Logo.png");
	logo[5].init("logo/SouthWest-Logo.png");

	change_current_airline(0);

	mouse_event_regoin[0].init(x + width - height, y, x + width, y + height);
	for (int i = 1; i <= number_of_logo; i++) {
		mouse_event_regoin[i].init(x, y + height * i, x + width, y + height * (i + 1));
	}
}

void Airline_Menu::draw()
{
	logo[current_logo].draw(x, y, width - height, height);
	buttom.draw();

	int selected_one = -1;

	if (show_drop_down_menu) {
		for (int i = 0; i < number_of_logo; i++) {
			logo[i].draw(x, y + height * (i + 1), width, height);
			if (logo[i].mouse_on_it) {
				selected_one = i;
				logo[i].mouse_on_it = false;
			}
		}
		if (selected_one >= 0) {
			logo[selected_one].draw_frame(x, y + height * (selected_one + 1), width, height, 255, 127, 0);
		}
	}
}

void Airline_Menu::handle_mouse_event(int mouseEvent, int locX, int locY)
{
	bool inside;

	inside = mouse_event_regoin[0].is_inside_region(locX, locY);

	if (inside == true) {
		buttom.mouse_on_it = true;
		if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
			show_drop_down_menu = !show_drop_down_menu;
		}
		return;
	}

	if (show_drop_down_menu) {
		for (int i = 0; i < number_of_logo; i++) {
			inside = mouse_event_regoin[i + 1].is_inside_region(locX, locY);
			if (inside == true) {
				logo[i].mouse_on_it = true;
				if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
					change_current_airline(i);
					show_drop_down_menu = !show_drop_down_menu;
					break;
				}
			}
		}
		if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
			show_drop_down_menu = false;
		}
	}
}

Mouse_event_regoin::Mouse_event_regoin()
{
	x1 = x2 = y1 = y2 = -1;
}

Mouse_event_regoin::Mouse_event_regoin(int x3, int y3, int x4, int y4)
{
	init(x3, y3, x4, y4);
}

void Mouse_event_regoin::init(int x3, int y3, int x4, int y4)
{
	x1 = x3;
	x2 = x4;
	y1 = y3;
	y2 = y4;
}

bool Mouse_event_regoin::is_inside_region(int x, int y)
{
	if (x >= x1 && x <= x2 && y >= y1 && y <= y2) return true;
	else return false;
}

void Drop_down_buttom::init(int x1, int y1, int width1, int height1)
{
	x = x1;
	y = y1;
	width = width1;
	height = height1;
	mouse_on_it = false;
}

void Drop_down_buttom::draw()
{
	if (mouse_on_it) glColor3ub(0, 255, 255);
	else glColor3ub(0, 255, 0);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + width, y);
	glVertex2i(x + width, y + height);
	glVertex2i(x, y + height);
	glEnd();

	glColor3ub(0, 0, 0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x, y);
	glVertex2i(x + width, y);
	glVertex2i(x + width, y + height);
	glVertex2i(x, y + height);
	glEnd();

	if (mouse_on_it) glColor3ub(255, 255, 0);
	else glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(x + width / 5, y + height / 5);
	glVertex2i(x + width * 4 / 5, y + height / 5);
	glVertex2i(x + width / 2, y + height * 4 / 5);
	glEnd();

	glColor3ub(0, 0, 0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x + width / 5, y + height / 5);
	glVertex2i(x + width * 4 / 5, y + height / 5);
	glVertex2i(x + width / 2, y + height * 4 / 5);
	glEnd();

	if (mouse_on_it) mouse_on_it = false;
}