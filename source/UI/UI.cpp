#include "UI.hpp"
#include "Button.hpp"
#include "InputBox.hpp"

void InputBox::Construct(float x, float y, float width, float height, Font _font, Vector2 _coordText, int _szText, float _spacing, int _MAX_SIZE) {
	inputShape = { x, y, width, height };
	font = _font;
	coordText = _coordText;
	szText = _szText;
	spacing = _spacing;
	MAX_SIZE = _MAX_SIZE;
	lengthText = inputShape.width;
}

void InputBox::SetColorBox(Color colorDefault, Color colorTouched, Color colorTyping) {
	colorBoxDefault = colorDefault;
	colorBoxTouched = colorTouched;
	colorBoxTyping = colorTyping;
}

void InputBox::SetColorText(Color colorDefault, Color colorTouched, Color colorTyping) {
	colorTextDefault = colorDefault;
	colorTextTouched = colorTouched;
	colorTextTyping = colorTyping;
}

void InputBox::Draw() {
	manipulate();

	if (getState() == DEFAULT) {
		//DrawRectangleRec(inputShape, colorBoxDefault);
		DrawRectangleRounded(inputShape, roundness, segments, colorBoxDefault);
		DrawTextEx(font, currentInput.substr(posL, posR - posL + 1).c_str(), {coordText.x, coordText.y}, szText, spacing, colorTextDefault);
		if (drawCorner) {
			//DrawRectangleLinesEx(inputShape, 2, colorCornerDefault);
			DrawRectangleRoundedLines(inputShape, roundness, segments, 2, colorCornerDefault);
		}
	} else if (getState() == TOUCHED) {
		//DrawRectangleRec(inputShape, colorBoxTouched);
		DrawRectangleRounded(inputShape, roundness, segments, colorBoxTouched);
		DrawTextEx(font, currentInput.substr(posL, posR - posL + 1).c_str(), {coordText.x, coordText.y}, szText, spacing, colorTextTouched);
		if (drawCorner) {
			//DrawRectangleLinesEx(inputShape, 2, colorCornerDefault);
			DrawRectangleRoundedLines(inputShape, roundness, segments, 2, colorCornerDefault);
		}
	} else if (getState() == TYPING) {
		//DrawRectangleRec(inputShape, colorBoxTyping);
		DrawRectangleRounded(inputShape, roundness, segments, colorBoxTyping);
		DrawTextEx(font, currentInput.substr(posL, posR - posL + 1).c_str(), {coordText.x, coordText.y}, szText, spacing, colorTextTyping);
		if (drawCorner) {
			//DrawRectangleLinesEx(inputShape, 2, colorCornerDefault);
			DrawRectangleRoundedLines(inputShape, roundness, segments, 2, colorCornerDefault);
		}
	}
}

bool InputBox::isClicked() {
	if (CheckCollisionPointRec(GetMousePosition(), inputShape)) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			return true;
		}
	}
	return false;
}

void InputBox::reset() {
	currentInput = "";
	isTyping = false;
}

int InputBox::getState() {
	if (CheckCollisionPointRec(GetMousePosition(), inputShape)) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			return TYPING;
		}
		else {
			return TOUCHED;
		}
	}
	return DEFAULT;
}

bool InputBox::checkCollisionText(int l, int r) {
	if (l > r || l < 0 || r >= currentInput.size()) return false;
	return coordText.x + MeasureTextEx(font, currentInput.substr(l, r - l + 1).c_str(), szText, spacing).x <= inputShape.x + lengthText;
}

void InputBox::manipulate() {
	if (add) {
		currentInput.erase(posCursor, 1);
	}

	timeline += 60;
	if (timeline > 5000) timeline = 0;

	add = false;

	// check if the input box is clicked
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (CheckCollisionPointRec(GetMousePosition(), inputShape)) {
			isTyping = true;
			add = true;
			timeline = 0;
		}
		else {
			isTyping = false;
		}
	}

	if (isTyping) {
		// for ctrl + v
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
			if (IsKeyPressed(KEY_V)) {
				string clipboard = GetClipboardText();
				for(int i = 0; i < clipboard.size(); ++i) {
					if (clipboard[i] < 32 || clipboard[i] > 126) {
						clipboard.erase(i, 1);
						--i;
					}
				}
				if (clipboard.length() + currentInput.length() <= MAX_SIZE) {
					currentInput.insert(posCursor, clipboard);
					posCursor += clipboard.length();
					posR += clipboard.length();
					while (posL < posR && !checkCollisionText(posL, posR)) {
						--posR;
					}
					add = true;
					timeline = 0;
				}
			}
		}
		// for typing
		int key = GetCharPressed();
		if (key >= 32 && key <= 126 && currentInput.length() < MAX_SIZE) {
			currentInput.insert(posCursor++, 1, key);
			++posR;
			while (posL < posR && !checkCollisionText(posL, posR)) {
				--posR;
			}
			add = true;
			timeline = 0;
		}
		int key2 = GetKeyPressed();
		if (!IsKeyDown(lastKey)) countConsecutiveKey = 0;
		// for arrow keys
		key2 = (IsKeyDown(KEY_LEFT) && (timeline == 540 || (timeline % 60 == 0 && countConsecutiveKey >= 4)) ? KEY_LEFT : key2);
		if (key2 == KEY_LEFT && posCursor > 0) {
			if (lastKey != key2) {
				lastKey = key2;
				countConsecutiveKey = 0;
			}
			++countConsecutiveKey;
			posCursor--;
			add = true;
			timeline = 0;
		}
		key2 = (IsKeyDown(KEY_RIGHT) && (timeline % 540 == 0 || (timeline % 60 == 0 && countConsecutiveKey >= 4)) ? KEY_RIGHT : key2);
		if (key2 == KEY_RIGHT && posCursor < currentInput.length()) {
			if (lastKey != key2) {
				lastKey = key2;
				countConsecutiveKey = 0;
			}
			++countConsecutiveKey;
			posCursor++;
			add = true;
			timeline = 0;
		}
		// for backspace
		key2 = (IsKeyDown(KEY_BACKSPACE) && (timeline % 540 == 0 || (timeline % 60 == 0 && countConsecutiveKey >= 4)) ? KEY_BACKSPACE : key2);
		if (key2 == KEY_BACKSPACE && currentInput.length() > 0 && posCursor) {
			if (lastKey != key2) {
				lastKey = key2;
				countConsecutiveKey = 0;
			}
			++countConsecutiveKey;
			currentInput.erase(--posCursor, 1);
			if (posCursor < 0) posCursor = 0;
			add = true;
			timeline = 0;
		}
		// for delete
		key2 = (IsKeyDown(KEY_DELETE) && (timeline % 540 == 0 || (timeline % 60 == 0 && countConsecutiveKey >= 4)) ? KEY_DELETE : key2);
		if (key2 == KEY_DELETE && currentInput.length() > 0 && posCursor < currentInput.length()) {
			if (lastKey != key2) {
				lastKey = key2;
				countConsecutiveKey = 0;
			}
			++countConsecutiveKey;
			currentInput.erase(posCursor, 1);
			add = true;
			timeline = 0;
		}
	}
	// for cursor
	if (isTyping && (add || timeline <= 2500)) {
		currentInput.insert(posCursor, "|");
		add = true;
	}
	// for text drawing
	if (posL > posCursor) {
		posL = posCursor;
		while (posL < posR && !checkCollisionText(posL, posR)) {
			--posR;
		}
	} else if (posR < posCursor) {
		posR = posCursor;
		while (posL < posR && !checkCollisionText(posL, posR)) {
			++posL;
		}
	}
	posR = min(posR, (int)currentInput.size() - 1);
	while (checkCollisionText(posL - 1, posR)) {
		--posL;
	}
	while (checkCollisionText(posL, posR + 1)) {
		++posR;
	}
}

string InputBox::getInput() {
	string ans;
	for (char &i : currentInput) {
		if (i != '|') ans.push_back(i);
	}
	return ans;
}

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