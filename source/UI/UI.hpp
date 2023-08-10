#include <iostream>
#include <Dict.hpp>
#include "raylib.h"
#include "Button.hpp"
#include "InputBox.hpp"
#include "Other.hpp"

class UI {
public:
    Texture background;
    Texture noti;
    Texture ribbon;
    Texture buttondown;
    Color title_color;
    Font title_font;
    Font word_font;
    Button Home;
    Button Reset;
    Button Favourite;
    Button History;
    Button Game;
    Button Datasets;
    Rectangle frame;
    int mouseCursor;
    int favourite_button;
    int history_button;

    bool datasets = false;
	bool reset = false;
	bool home = false;
    bool favourite = false;
    bool history = false;
    bool game = false;
    std::vector <bool*> status;
    Button clear_yes;
    Button clear_no;
	Button reset_yes;
	Button reset_no;
    Button clearhis_yes;
    Button clearhis_no;
	Button engeng;
    Button engviet;
	Button vieteng;
    Button clearFavList;
    Button clearHisList;
    Button removeFav[100];
    Button removeHis[100];
    bool removeFavourite[100];
    bool removeHistory[100];
    Button removeYes;
    Button removeNo;
    Button removehisYes;
    Button removehisNo;
    InputBox search;
    Button enterdef;
    Button enterkey;
    Rectangle messagebar;
    int homestate;
    Button down;
    Button down1;
    Button def;
    Button key;

    std::vector <std::string> favlist;
	Rectangle fav[100];
    float wheel = 0;
    std::vector <std::string> hislist;
    Rectangle his[100];

    const int screenWidth = 1280;
    const int screenHeight = 832;

    Dict* dict;

    void DefaultWindow();
    void Menu();
    void DrawFavouriteScreen();
    void DrawHistoryScreen();
    void DrawHomeScreen();
    void DrawDailyWords();
    void run();
};