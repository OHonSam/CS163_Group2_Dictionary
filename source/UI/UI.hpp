#include <iostream>
#include <Dict.hpp>
#include "raylib.h"
#include "Button.hpp"

class UI {
public:
    Texture background;
    Texture noti;
    Color title_color;
    Font title_font;
    Button Home;
    Button Reset;
    Button Favourite;
    Button History;
    Button Game;
    Button Datasets;
    Rectangle frame;
    int mouseCursor;

    bool datasets = false;
	bool reset = false;
	bool home = false;
    bool favourite = false;
    bool history = false;
    bool game = false;
    std::vector <bool*> status;
	Button reset_yes;
	Button reset_no;
	Button engeng;
    Button engviet;
	Button vieteng;

    const int screenWidth = 1280;
    const int screenHeight = 832;

    Dict* dict;

    void DefaultWindow();
    void Menu();
    void run();
};