#include <iostream>
#include <Dict.hpp>
#include "raylib.h"
#include "Button.hpp"
#include "InputBox.hpp"
#include "Other.hpp"
#include <Word.hpp>
#include <SmallTrie.hpp>

class UI {
public:
    Texture background;
    Texture noti;
    Texture ribbon;
    Texture buttondown;
    Texture dislike;
    Texture like;
    Texture next;
    Texture modify;
    Texture deleteword;
    Texture newword;
    Button Neww;
    bool neww;
    Color title_color;
    Font title_font;
    Font word_font;
    Button Like;
    Button Home;
    Button Reset;
    Button Favourite;
    Button History;
    Button Game;
    Button Datasets;
    Button Modify;
    Rectangle frame;
    Button Deleteword;
    bool isdeleted;
    bool likebutt;
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
    bool beingmodified;
    Button right;
    Button left;
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
    Button renew;
    DataSet::Type cur;
    std::string keyword;
    std::string definition;
    Rectangle display;

    Word* dailyword;
    Word* draw;
    std::vector <std::string> favlist;
	Rectangle fav[100];
    float wheel = 0;
    std::vector <std::string> hislist;
    std::vector <std::string> foundwords;
    Rectangle his[100];
    int posTextY;
    int posTextX;

    const int screenWidth = 1280;
    const int screenHeight = 832;

    Dict* dict;

    void DefaultWindow();
    void Menu();
    void DrawFavouriteScreen();
    void DrawHistoryScreen();
    void DrawHomeScreen();
    void DrawDailyWords();
    void DrawSearchforDef(Word* word);
    void DrawSearchforWord(const std::string def, std::vector <std::string> foundwords);
    void DrawWord(Word* word, bool &x, SmallTrie* highlight);
    void DrawLongText(std::string s, SmallTrie* highlight);
    void DrawModifyBox(Word* word);
    void run();
};