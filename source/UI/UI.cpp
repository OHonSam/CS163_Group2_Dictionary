#include "UI.hpp"
#include "Button.hpp"

void Button::SetBox(float x, float y, float width, float height, Color colorDefault, Color colorTouched, Color colorClicked) {
	buttonShape.x = x;
	buttonShape.y = y;
	buttonShape.width = width;
	buttonShape.height = height;
	colorBoxDefault = colorDefault;
	colorBoxTouched = colorTouched;
	colorBoxClicked = colorClicked;
}

void Button::SetText(Font _font, string _Text, Vector2 _coordText, float _fontSize, float _spacing, Color colorDefault, Color colorTouched, Color colorClicked) {
	font = _font;
	Text = _Text;
	coordText = _coordText;
	fontSize = _fontSize;
	spacing = _spacing;
	colorTextDefault = colorDefault;
	colorTextTouched = colorTouched;
	colorTextClicked = colorClicked;
}

void Button::DrawText(int &mouseCursor) {
	int state = getState();
	if (state == DEFAULT) {
		//DrawRectangleRec(buttonShape, colorBoxDefault);
		DrawRectangleRounded(buttonShape, roundness, segments, colorBoxDefault);
		DrawTextEx(font, Text.c_str(), coordText, fontSize, spacing, colorTextDefault);
		if (drawCorner) {
			//DrawRectangleLinesEx(buttonShape, 4, colorCornerDefault);
			DrawRectangleRoundedLines(buttonShape, roundness, segments, 4, colorCornerClicked);
		}
	}
	else if (state == TOUCHED) {
		//DrawRectangleRec(buttonShape, colorBoxTouched);
		DrawRectangleRounded(buttonShape, roundness, segments, colorBoxTouched);
		DrawTextEx(font, Text.c_str(), coordText, fontSize, spacing, colorTextTouched);
		if (drawCorner) {
			//DrawRectangleLinesEx(buttonShape, 4, colorCornerTouched);
			DrawRectangleRoundedLines(buttonShape, roundness, segments, 4, colorCornerClicked);
		}
		if (setMouse) {
			mouseCursor = MOUSE_CURSOR_POINTING_HAND;
		}
	}
	else if (state == CLICKED || state == RELEASED) {
		//DrawRectangleRec(buttonShape, colorBoxClicked);
		DrawRectangleRounded(buttonShape, roundness, segments, colorBoxClicked);
		DrawTextEx(font, Text.c_str(), coordText, fontSize, spacing, colorTextClicked);
		if (drawCorner) {
			//DrawRectangleLinesEx(buttonShape, 4, colorCornerClicked);
			DrawRectangleRoundedLines(buttonShape, roundness, segments, 4, colorCornerClicked);
		}
		if (setMouse) {
			mouseCursor = MOUSE_CURSOR_POINTING_HAND;
		}
	} 
	
}

int Button::getState() {
	if (CheckCollisionPointRec(GetMousePosition(), buttonShape)) {
		if (state == CLICKED && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			return state = RELEASED;
		}
		else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			return state = CLICKED;
		}
		else {
			return state = TOUCHED;
		}
	}
	return state = DEFAULT;
}

void UI::DefaultWindow() {
    InitWindow(screenWidth, screenHeight, "Dictionary");
    SetTargetFPS(60);      
    background = LoadTexture("background.png");
	noti = LoadTexture("notifications.png");
    title_color = {131, 13, 5, 255};
	ribbon = LoadTexture("ribbontitle.png");
    title_font = LoadFontEx("IrishGrover-Regular.ttf", 120, 0, 0);
	home = true;
	status.push_back(&home);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground({227, 168, 168, 255});
        DrawTextureEx(background, {0, 0}, 0, 0.8533333, WHITE);
        DrawTextEx(title_font, "Dictionary", {390, 50}, 120, 1, title_color);
		Home.drawCorner = true;
		Home.colorCornerClicked = {253, 84, 145, 255};
		Home.colorCornerDefault = {253, 84, 145, 255};
		Home.colorCornerTouched = {253, 84, 145, 255};
		Home.SetBox(5, 5, 128, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		Home.SetText(title_font, "Home", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		Home.DrawText(mouseCursor);
		Reset.drawCorner = true;
		Reset.colorCornerClicked = {253, 84, 145, 255};
		Reset.colorCornerDefault = {253, 84, 145, 255};
		Reset.colorCornerTouched = {253, 84, 145, 255};
		Reset.SetBox(190, 5, 140, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		Reset.SetText(title_font, "Reset", {218, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		Reset.DrawText(mouseCursor);
		Favourite.drawCorner = true;
		Favourite.colorCornerClicked = {253, 84, 145, 255};
		Favourite.colorCornerDefault = {253, 84, 145, 255};
		Favourite.colorCornerTouched = {253, 84, 145, 255};
		Favourite.SetBox(410, 5, 175, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		Favourite.SetText(title_font, "Favourite", {429, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		Favourite.DrawText(mouseCursor);
		History.drawCorner = true;
		History.colorCornerClicked = {253, 84, 145, 255};
		History.colorCornerDefault = {253, 84, 145, 255};
		History.colorCornerTouched = {253, 84, 145, 255};
		History.SetBox(663, 5, 160, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		History.SetText(title_font, "History", {688, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		History.DrawText(mouseCursor);
		Game.drawCorner = true;
		Game.colorCornerClicked = {253, 84, 145, 255};
		Game.colorCornerDefault = {253, 84, 145, 255};
		Game.colorCornerTouched = {253, 84, 145, 255};
		Game.SetBox(925, 5, 128, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		Game.SetText(title_font, "Game", {948, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		Game.DrawText(mouseCursor);
		Datasets.drawCorner = true;
		Datasets.colorCornerClicked = {253, 84, 145, 255};
		Datasets.colorCornerDefault = {253, 84, 145, 255};
		Datasets.colorCornerTouched = {253, 84, 145, 255};
		Datasets.SetBox(1120, 5, 160, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		Datasets.SetText(title_font, "ENG-ENG", {1133, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		Datasets.DrawText(mouseCursor);
		frame.x = 110;
		frame.y = 234;
		frame.width = 1058;
		frame.height = 580;
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		DrawRectangleRounded(frame, 0.1, 10, {248, 224, 224, 255});
		DrawRectangleRoundedLines(frame, 0.1, 10, 4, {249, 135, 135, 255});
		Menu();
        EndDrawing();
    }
	return;
}

void UI::Menu() {

	if (Reset.state == 3) {
		if (!reset) status.push_back(&reset);
		reset = true;
		// dict -> reset();
	}
	if (Datasets.state == 3) {
		if (!datasets) status.push_back(&datasets);
		datasets = true;
	}
	if (Favourite.state == 3) {
		if (!favourite) status.push_back(&favourite);
		favourite = true;
	}
	if (History.state == 3) {
		if (!history) status.push_back(&history);
		history = true;
	}
	if (Game.state == 3) {
		if (!game) status.push_back(&game);
		game = true;
	}
	if (Home.state == 3) {
		if (!home) status.push_back(&home);
		home = true;
	}
	if (status.size() == 2) {
		std::vector <bool*> temp;
		temp.push_back(status[status.size() - 1]);
		for (int i = 0; i < status.size() - 1; i++) {
			*(status[i]) = false;
		}
		status.clear();
		status = temp;
	}
	Rectangle resetnoti;
	resetnoti.x = 365;
	resetnoti.y = 298;
	resetnoti.width = 550;
	resetnoti.height = 210;
	if (reset) {
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(Reset.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		DrawRectangleRounded(resetnoti, 0.1, 10, {248, 199, 199, 255});
		DrawRectangleRoundedLines(resetnoti, 0.1, 10, 4, {253, 84, 145, 255});
		DrawTextEx(title_font, "Message!", {580, 310}, 36, 1, {227, 89, 97, 255});
		DrawTextEx(title_font, "Are you sure?", {540, 343}, 36, 1, {94, 32, 36, 255});
		reset_yes.drawCorner = true;
		reset_yes.colorCornerClicked = {255, 255, 255, 255};
		reset_yes.colorCornerDefault = {255, 255, 255, 255};
		reset_yes.colorCornerTouched = {255, 255, 255, 255};
		reset_yes.SetBox(450, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		reset_yes.SetText(title_font, "YES", {499, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		reset_yes.DrawText(mouseCursor);
		reset_no.drawCorner = true;
		reset_no.colorCornerClicked = {255, 255, 255, 255};
		reset_no.colorCornerDefault = {255, 255, 255, 255};
		reset_no.colorCornerTouched = {255, 255, 255, 255};
		reset_no.SetBox(680, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		reset_no.SetText(title_font, "NO", {740, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		reset_no.DrawText(mouseCursor);
		DrawTextureEx(noti, {787, 200}, 0, 0.3, WHITE);
		if (reset_yes.state == 3) {
			dict -> reset();
			reset = false;
			status.pop_back();
		}
		else if (reset_no.state == 3) {
			reset = false;
			status.pop_back();
		}
		// if (game || datasets || favourite || history || home) reset = false;
	}

	Rectangle datasetsnoti;
	datasetsnoti.x = 365;
	datasetsnoti.y = 298;
	datasetsnoti.width = 550;
	datasetsnoti.height = 210;
	if (datasets) 
	{
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(Datasets.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		DrawRectangleRounded(datasetsnoti, 0.1, 10, {248, 199, 199, 255});
		DrawRectangleRoundedLines(datasetsnoti, 0.1, 10, 4, {253, 84, 145, 255});
		DrawTextEx(title_font, "Message!", {580, 310}, 36, 1, {227, 89, 97, 255});
		DrawTextEx(title_font, "Choose your dictionary: ", {460, 343}, 36, 1, {94, 32, 36, 255});
		
		engeng.drawCorner = true;
		engeng.colorCornerClicked = {255, 255, 255, 255};
		engeng.colorCornerDefault = {255, 255, 255, 255};
		engeng.colorCornerTouched = {255, 255, 255, 255};
		engeng.SetBox(369, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		engeng.SetText(title_font, "ENG-ENG", {382, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		engeng.DrawText(mouseCursor);
		engviet.drawCorner = true;
		engviet.colorCornerClicked = {255, 255, 255, 255};
		engviet.colorCornerDefault = {255, 255, 255, 255};
		engviet.colorCornerTouched = {255, 255, 255, 255};
		engviet.SetBox(563, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		engviet.SetText(title_font, "ENG-VIET", {576, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		engviet.DrawText(mouseCursor);
		vieteng.drawCorner = true;
		vieteng.colorCornerClicked = {255, 255, 255, 255};
		vieteng.colorCornerDefault = {255, 255, 255, 255};
		vieteng.colorCornerTouched = {255, 255, 255, 255};
		vieteng.SetBox(754, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		vieteng.SetText(title_font, "VIET-ENG", {767, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		vieteng.DrawText(mouseCursor);
		DrawTextureEx(noti, {787, 200}, 0, 0.3, WHITE);
		if (vieteng.state == 3) {
			dict -> switchDataSet(DataSet::VE);
			datasets = false;
			status.pop_back();
		}
		else if (engeng.state == 3) {
			dict -> switchDataSet(DataSet::EE);
			datasets = false;
			status.pop_back();
		}
		else if (engviet.state == 3) {
			dict -> switchDataSet(DataSet::EV);
			datasets = false;
			status.pop_back();
		}
		// if (game || favourite || reset || history || home) datasets = false;
	
	}

	if (home) {
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		// datasets = false;
		// reset = false;
		// favourite = false;
		// history = false;
		// game = false;
		// home = false;
	}
	
	if (favourite) {
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(Favourite.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		DrawFavouriteScreen();
		// if (game || datasets || reset || history || home) favourite = false;
	}
	
	if (history) {
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(History.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		// if (game || datasets || reset || favourite || home) history = false;
	}

	if (game) {
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(Game.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		// if (history || datasets || reset || favourite || home) game = false;
	}
	return;
}

void UI::DrawFavouriteScreen() {
	DrawTextureEx(ribbon, {100, 150}, 0, 0.4, WHITE);
	DrawTextEx(title_font, "Favourite Words", {183, 252}, 36, 1, {227, 89, 97, 255});
}

void UI::run() {
	dict = new Dict();
    DefaultWindow();
	dict->~Dict();
}