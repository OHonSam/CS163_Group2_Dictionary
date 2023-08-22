#include "UI.hpp"
#include "Button.hpp"
#include "InputBox.hpp"
#include "Other.hpp"
#include <sstream>
#include <algorithm>

Vector2 GetCenterPos(Font font, string text, float fontSize, float spacing, float x, float y, float width, float height) {
	Vector2 centerPos;
	centerPos.x = x + (width - MeasureTextEx(font, text.c_str(), fontSize, spacing).x) / 2;
	centerPos.y = y + (height - MeasureTextEx(font, text.c_str(), fontSize, spacing).y) / 2;
	return centerPos;
}

Vector2 GetCenterPos(Font font, string text, float fontSize, float spacing, Rectangle rect) {
	return GetCenterPos(font, text, fontSize, spacing, rect.x, rect.y, rect.width, rect.height);
}

Vector2 DrawTextOnBox(Rectangle boxShape, Font font, string text, Vector2 coord, float fontSize, float spacing, float lineGap, Color colorText) {
	float x = coord.x, y = coord.y;
	float limitX = boxShape.x + boxShape.width;
	float limitY = boxShape.y + boxShape.height;
	stringstream ss(text);
	string line = "", word;
	Vector2 size;
	while (ss >> word) {
		size = MeasureTextEx(font, line.c_str(), fontSize, spacing);
		Vector2 wordSize = MeasureTextEx(font, word.c_str(), fontSize, spacing);
		if (x + size.x + wordSize.x > limitX) {
			DrawTextEx(font, line.c_str(), { x, y }, fontSize, spacing, colorText);
			x = boxShape.x;
			y += lineGap;
			line = word + " ";
		}
		else {
			line += word + " ";
		}
		if (y + size.y > limitY) {
			return { x, y };
		}
	}
	DrawTextEx(font, line.c_str(), { x, y }, fontSize, spacing, colorText);
	
	return { x + MeasureTextEx(font, line.c_str(), fontSize, spacing).x, y };
}

float DrawTextOnBoxEx(Rectangle boxShape, Font font, vector<string> &text, Vector2 coord, float fontSize, float spacing, float lineGap, float paraGap, Color colorText) {
	 float y = coord.y;
	 for (int i = 1; i < text.size(); i++) {
		 Vector2 pos = DrawTextOnBox(boxShape, font, to_string(i) + ". " + text[i], {coord.x, y}, fontSize, spacing, lineGap, colorText);
		 y = pos.y + paraGap;
	 }
	 return y;
}

int RandInt(int min, int max) {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

string PartialText(Font font, string text, float fontSize, float spacing, float width) {
	if (MeasureTextEx(font, text.c_str(), fontSize, spacing).x <= width) {
		return text;
	}
	string line = "";
	for (char& c : text) {
		if (MeasureTextEx(font, (line + c + "...").c_str(), fontSize, spacing).x > width) {
			return line + "...";
		}
		line += c;
	}
	return line + "...";
}

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
	cur = DataSet::EE;
	posTextY = 430;
	posTextX = 236;
	homestate = 0;
	keyword = "";
	definition = "";
	hislist = dict -> getHistory();
	favlist = dict -> getFav();
	dailyword = dict -> getDailyWord();
	beingmodified = false;
	neww = false;
	isdeleted = false;
	for (int i = 0; i < favlist.size(); i++) removeFavourite[i] = false;
	for (int i = 0; i < hislist.size(); i++) removeHistory[i] = false;
    background = LoadTexture("background.png");
	noti = LoadTexture("notifications.png");
	deleteword = LoadTexture("delete.png");
	modify = LoadTexture("modify.png");
	newword = LoadTexture("new.png");
	next = LoadTexture("rightarrow.png");
    title_color = {131, 13, 5, 255};
	ribbon = LoadTexture("ribbontitle.png");
	like = LoadTexture("like.png");
	dislike = LoadTexture("dislike.png");
	buttondown = LoadTexture("question.png");
    title_font = LoadFontEx("IrishGrover-Regular.ttf", 120, 0, 0);
	word_font = LoadFontEx("Margarine-Regular.ttf", 120, 0, 0);
	home = true;
	favourite_button = 0;
	history_button = 0;
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
		if (cur == DataSet::EE) Datasets.SetText(title_font, "ENG-ENG", {1133, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		else if (cur == DataSet::EV) Datasets.SetText(title_font, "ENG-VIET", GetCenterPos(title_font, "ENG-VIET", 36, 1, Datasets.buttonShape), 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		else if (cur == DataSet::VE) Datasets.SetText(title_font, "VIET-ENG", GetCenterPos(title_font, "VIET-ENG", 36, 1, Datasets.buttonShape), 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		else if (cur == DataSet::Emoji) Datasets.SetText(title_font, "EMOJI", GetCenterPos(title_font, "EMOJI", 36, 1, Datasets.buttonShape), 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
		else if (cur == DataSet::Slang) Datasets.SetText(title_font, "SLANG", GetCenterPos(title_font, "SLANG", 36, 1, Datasets.buttonShape), 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
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
		if (!reset) {
			status.push_back(&reset);
			wheel = 0;
		}
		reset = true;
		// dict -> reset();
	}
	if (Datasets.state == 3) {
		if (!datasets) {
			status.push_back(&datasets);
			wheel = 0;
		}
		datasets = true;
	}
	if (Favourite.state == 3) {
		if (!favourite) {
			wheel = 0;
			status.push_back(&favourite);
		}
		favlist = dict -> getFav();
		favourite = true;
	}
	if (History.state == 3) {
		if (!history) {
			status.push_back(&history);
			wheel = 0;
			// std::cout << hislist.size();
			// for (int i = 0; i < hislist.size(); i++) removeHistory[i] = false;
		}
		hislist = dict -> getHistory();
		history = true;
	}
	if (Game.state == 3) {
		if (!game) {
			status.push_back(&game);
			guessthemeaning = true;
			// guessthemeaning = true;
			// v.clear();
			// v = dict->getMultiChoices(4);
			// for (int i = 0; i < 4; i++) {
			// 	randef.clear();
			// 	randef.push_back(v[i]->getRandDef());
			// }
			// wheel = 0;
		}
		
		a = b = c = d = false;
		v.clear();
		v = dict->getMultiChoices(4);
		randef.clear();
		for (int i = 0; i < 4; i++) {
			
			randef.push_back(v[i]->getRandDef());
		}
		res = 0;
		textx = 365;
		texty = 340;
		game = true;
		wheel = 0;
	}
	if (Home.state == 3) {
		if (!home) {
			status.push_back(&home);
			wheel = 0;
		}
		dailyword = dict -> getDailyWord();
		home = true;
		homestate = 0;
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
			dailyword = dict -> getDailyWord();
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
		emoji.drawCorner = true;
		emoji.colorCornerClicked = {255, 255, 255, 255};
		emoji.colorCornerDefault = {255, 255, 255, 255};
		emoji.colorCornerTouched = {255, 255, 255, 255};
		emoji.SetBox(460, 450, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		emoji.SetText(title_font, "EMOJI", GetCenterPos(title_font, "EMOJI", 36, 1, emoji.buttonShape), 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		emoji.DrawText(mouseCursor);
		slang.drawCorner = true;
		slang.colorCornerClicked = {255, 255, 255, 255};
		slang.colorCornerDefault = {255, 255, 255, 255};
		slang.colorCornerTouched = {255, 255, 255, 255};
		slang.SetBox(660, 450, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		slang.SetText(title_font, "SLANG", GetCenterPos(title_font, "SLANG", 36, 1, slang.buttonShape), 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		slang.DrawText(mouseCursor);
		DrawTextureEx(noti, {787, 200}, 0, 0.3, WHITE);
		if (vieteng.state == 3) {
			dict -> switchDataSet(DataSet::VE);
			dailyword = dict -> getDailyWord();
			homestate = 0;
			cur = DataSet::VE;
			datasets = false;
			status.pop_back();
		}
		else if (engeng.state == 3) {
			dict -> switchDataSet(DataSet::EE);
			dailyword = dict -> getDailyWord();
			homestate = 0;
			cur = DataSet::EE;
			datasets = false;
			status.pop_back();
		}
		else if (engviet.state == 3) {
			dict -> switchDataSet(DataSet::EV);
			dailyword = dict -> getDailyWord();
			homestate = 0;
			cur = DataSet::EV;
			datasets = false;
			status.pop_back();
		}
		else if (emoji.state == 3) {
			dict -> switchDataSet(DataSet::Emoji);
			dailyword = dict -> getDailyWord();
			homestate = 0;
			cur = DataSet::Emoji;
			datasets = false;
			status.pop_back();
		}
		else if (slang.state == 3) {
			dict -> switchDataSet(DataSet::Slang);
			dailyword = dict -> getDailyWord();
			homestate = 0;
			cur = DataSet::Slang;
			datasets = false;
			status.pop_back();
		}
		// if (game || favourite || reset || history || home) datasets = false;
	
	}

	if (home) {
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		DrawHomeScreen();
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
		DrawHistoryScreen();
		// if (game || datasets || reset || favourite || home) history = false;
	}

	if (game) {
		DrawRectangleRoundedLines(Home.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
		DrawRectangleRoundedLines(Game.buttonShape, 0.1, 10, 4, {255, 255, 255, 255});
		textx = 365;
		texty = 340;
		DrawGame();
		// if (history || datasets || reset || favourite || home) game = false;
	}
	return;
}

void UI::DrawFavouriteScreen() {
	int scrollSpeed = 60;      
	wheel += (GetMouseWheelMove()*scrollSpeed);
	if (wheel < - (370 + ((int) (favlist.size() - 1) / 3) * (80 + 45) + 80) + 738) {
		wheel = - (370 + ((int) (favlist.size() - 1) / 3) * (80 + 45) + 80) + 738;
	}
	if (wheel > 0) {
			wheel = 0;
			// fav[i].y = 370 + ((int) i / 3) * (80 + 45) + (int) wheel;
			// fav[i].x = 245 + 225 * (i % 3) + 50 * (i % 3); 
			// fav[i].width = 225;
			// fav[i].height = 80;
	}
	for (int i = 0; i < favlist.size(); i++) {
		fav[i].y = 370 + ((int) i / 3) * (80 + 45) + (int) wheel;
		fav[i].x = 245 + 225 * (i % 3) + 50 * (i % 3); 
		fav[i].width = 225;
		fav[i].height = 80;
		// if (i == favlist.size() - 1 && fav[favlist.size() - 1].y + fav[favlist.size() - 1].height > 750) {
		// 	wheel = 750 - fav[favlist.size() - 1].y - fav[favlist.size() - 1].height ;
		// 	fav[i].y = 370 + ((int) i / 3) * (80 + 45) + (int) wheel;
		// 	fav[i].x = 245 + 225 * (i % 3) + 50 * (i % 3); 
		// 	fav[i].width = 225;
		// 	fav[i].height = 80;
		// }
		if (fav[i].y + fav[i].height < 370 || fav[i].y > 738) {} else {
			// for (int i = 0; i < favlist.size(); i++) {
			// 	fav[i].y = 370 + ((int) i / 3) * (80 + 45) + (int) wheel;
			// 	fav[i].x = 245 + 225 * (i % 3) + 50 * (i % 3); 
			// 	fav[i].width = 225;
			// 	fav[i].height = 80;
			// }
			DrawRectangleRounded(fav[i], 0.1, 10, {248, 199, 199, 255});
			DrawRectangleRoundedLines(fav[i], 0.1, 10, 4, {253, 84, 145, 255});
			DrawTextEx(word_font, favlist[i].c_str(), GetCenterPos(word_font, favlist[i], 50, 1, fav[i]), 50, 1, title_color);
			removeFav[i].drawCorner = true;
			removeFav[i].colorCornerClicked = {255, 255, 255, 255};
			removeFav[i].colorCornerDefault = {255, 255, 255, 255};
			removeFav[i].colorCornerTouched = {255, 255, 255, 255};
			removeFav[i].roundness = 1;
			removeFav[i].SetBox(fav[i].x + 203, fav[i].y + 2, 22, 22, {251, 69, 69, 69}, {173, 170, 171, 255}, {93, 93, 93, 255});
			removeFav[i].SetText(word_font, "X", GetCenterPos(word_font, "X", 20, 1, removeFav[i].buttonShape), 20, 1, {251, 69, 69, 255}, {251, 69, 69, 255}, {251, 69, 69, 255});
			removeFav[i].DrawText(mouseCursor);
		}
	}
	for (int i = 0; i < favlist.size(); i++) {
		if (removeFav[i].state == 3) removeFavourite[i] = true;
	}
	// draw words;
	Rectangle cover;
	cover.x = 110;
	cover.y = 234;
	cover.width = 1058;
	cover.height = 133;
	Rectangle cover2;
	cover2.y = 750;
	cover2.x = 110;
	cover2.width = 1058;
	cover2.height = 64; 
	DrawRectangleRounded(cover2, 1, 10, {248, 224, 224, 255});
	DrawRectangleRounded(cover, 0.5, 10, {248, 224, 224, 255});
	DrawTextureEx(ribbon, {100, 150}, 0, 0.4, WHITE);
	DrawTextEx(title_font, "Favourite Words", {183, 252}, 36, 1, {227, 89, 97, 255});
	for (int i = 0; i < favlist.size(); i++) {
		if (removeFavourite[i]) {
			Rectangle remove;
			remove.x = 365;
			remove.y = 298;
			remove.width = 550;
			remove.height = 210;
			DrawRectangleRounded(remove, 0.1, 10, {248, 199, 199, 255});
			DrawRectangleRoundedLines(remove, 0.1, 10, 4, {253, 84, 145, 255});
			DrawTextEx(title_font, "Message!", {580, 310}, 36, 1, {227, 89, 97, 255});
			DrawTextEx(title_font, "Are you sure?", {540, 343}, 36, 1, {94, 32, 36, 255});
			removeYes.drawCorner = true;
			removeYes.colorCornerClicked = {255, 255, 255, 255};
			removeYes.colorCornerDefault = {255, 255, 255, 255};
			removeYes.colorCornerTouched = {255, 255, 255, 255};
			removeYes.SetBox(450, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
			removeYes.SetText(title_font, "YES", {499, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
			removeYes.DrawText(mouseCursor);
			removeNo.drawCorner = true;
			removeNo.colorCornerClicked = {255, 255, 255, 255};
			removeNo.colorCornerDefault = {255, 255, 255, 255};
			removeNo.colorCornerTouched = {255, 255, 255, 255};
			removeNo.SetBox(680, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
			removeNo.SetText(title_font, "NO", {740, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
			removeNo.DrawText(mouseCursor);
			DrawTextureEx(noti, {787, 200}, 0, 0.3, WHITE);
			if (removeYes.state == 3) {
				dict -> removeFav(favlist[i]);
				favlist = dict -> getFav();
				for (int i = 0; i < favlist.size(); i++) removeFavourite[i] = false;
			}
			else if (removeNo.state == 3) {
				removeFavourite[i] = false;
			}
			break;
		}
	}
	clearFavList.drawCorner = true;
	clearFavList.colorCornerClicked = {255, 255, 255, 255};
	clearFavList.colorCornerDefault = {255, 255, 255, 255};
	clearFavList.colorCornerTouched = {255, 255, 255, 255};
	clearFavList.roundness = 1;
	clearFavList.SetBox(1002, 763, 160, 44, {251, 69, 69, 69}, {173, 170, 171, 255}, {93, 93, 93, 255});
	clearFavList.SetText(title_font, "clear all", {1023, 765}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
	clearFavList.DrawText(mouseCursor);
	// add slang, emoji
	if (clearFavList.state == 3) favourite_button = 1;
	if (favourite_button) {
		Rectangle clearall;
		clearall.x = 365;
		clearall.y = 298;
		clearall.width = 550;
		clearall.height = 210;
		DrawRectangleRounded(clearall, 0.1, 10, {248, 199, 199, 255});
		DrawRectangleRoundedLines(clearall, 0.1, 10, 4, {253, 84, 145, 255});
		DrawTextEx(title_font, "Message!", {580, 310}, 36, 1, {227, 89, 97, 255});
		DrawTextEx(title_font, "Are you sure?", {540, 343}, 36, 1, {94, 32, 36, 255});
		clear_yes.drawCorner = true;
		clear_yes.colorCornerClicked = {255, 255, 255, 255};
		clear_yes.colorCornerDefault = {255, 255, 255, 255};
		clear_yes.colorCornerTouched = {255, 255, 255, 255};
		clear_yes.SetBox(450, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		clear_yes.SetText(title_font, "YES", {499, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		clear_yes.DrawText(mouseCursor);
		clear_no.drawCorner = true;
		clear_no.colorCornerClicked = {255, 255, 255, 255};
		clear_no.colorCornerDefault = {255, 255, 255, 255};
		clear_no.colorCornerTouched = {255, 255, 255, 255};
		clear_no.SetBox(680, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		clear_no.SetText(title_font, "NO", {740, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		clear_no.DrawText(mouseCursor);
		DrawTextureEx(noti, {787, 200}, 0, 0.3, WHITE);
		if (clear_yes.state == 3) {
			dict -> clearFavList();
			favlist = dict -> getFav();
			favourite_button = 0;
		}
		else if (clear_no.state == 3) {
			favourite_button = 0;
		}
	}
}

void UI::DrawHistoryScreen() {
	hislist = dict -> getHistory();
	// for (int i = 0; i < hislist.size(); i++) removeHistory[i] = false;
	int scrollSpeed = 60;      
	// std::cout << hislist.size() << '\n';
	wheel += (GetMouseWheelMove()*scrollSpeed);
	if (wheel < - (370 + ((int) (hislist.size() - 1) / 3) * (80 + 45) + 80) + 738) {
		wheel = - (370 + ((int) (hislist.size() - 1) / 3) * (80 + 45) + 80) + 738;
	}
	if (wheel > 0) {
			wheel = 0;
	}
	for (int i = 0; i < hislist.size(); i++) {
		his[i].y = 370 + ((int) i / 3) * (80 + 45) + (int) wheel;
		his[i].x = 245 + 225 * (i % 3) + 50 * (i % 3); 
		his[i].width = 225;
		his[i].height = 80;
		if (his[i].y + his[i].height < 370 || his[i].y > 738) {} else {
			DrawRectangleRounded(his[i], 0.1, 10, {248, 199, 199, 255});
			DrawRectangleRoundedLines(his[i], 0.1, 10, 4, {253, 84, 145, 255});
			DrawTextEx(word_font, hislist[i].c_str(), GetCenterPos(word_font, hislist[i], 50, 1, his[i]), 50, 1, title_color);
			removeHis[i].drawCorner = true;
			removeHis[i].colorCornerClicked = {255, 255, 255, 255};
			removeHis[i].colorCornerDefault = {255, 255, 255, 255};
			removeHis[i].colorCornerTouched = {255, 255, 255, 255};
			removeHis[i].roundness = 1;
			removeHis[i].SetBox(his[i].x + 203, his[i].y + 2, 22, 22, {251, 69, 69, 69}, {173, 170, 171, 255}, {93, 93, 93, 255});
			removeHis[i].SetText(word_font, "X", GetCenterPos(word_font, "X", 20, 1, removeHis[i].buttonShape), 20, 1, {251, 69, 69, 255}, {251, 69, 69, 255}, {251, 69, 69, 255});
			removeHis[i].DrawText(mouseCursor);
		}
	}
	for (int i = 0; i < hislist.size(); i++) {
		if (removeHis[i].state == 3) {
			// std::cout << i << 'x';
			removeHistory[i] = true;
		}
		// break;
	}
	// draw words;
	Rectangle cover;
	cover.x = 110;
	cover.y = 234;
	cover.width = 1058;
	cover.height = 133;
	Rectangle cover2;
	cover2.y = 750;
	cover2.x = 110;
	cover2.width = 1058;
	cover2.height = 64; 
	DrawRectangleRounded(cover2, 1, 10, {248, 224, 224, 255});
	DrawRectangleRounded(cover, 0.5, 10, {248, 224, 224, 255});
	DrawTextureEx(ribbon, {100, 150}, 0, 0.4, WHITE);
	DrawTextEx(title_font, "History Words", {183, 252}, 36, 1, {227, 89, 97, 255});
	for (int i = 0; i < hislist.size(); i++) {
		if (removeHistory[i]) {
			// cout << hislist[i] << i << '\n';
			Rectangle remove;
			remove.x = 365;
			remove.y = 298;
			remove.width = 550;
			remove.height = 210;
			DrawRectangleRounded(remove, 0.1, 10, {248, 199, 199, 255});
			DrawRectangleRoundedLines(remove, 0.1, 10, 4, {253, 84, 145, 255});
			DrawTextEx(title_font, "Message!", {580, 310}, 36, 1, {227, 89, 97, 255});
			DrawTextEx(title_font, "Are you sure?", {540, 343}, 36, 1, {94, 32, 36, 255});
			removehisYes.drawCorner = true;
			removehisYes.colorCornerClicked = {255, 255, 255, 255};
			removehisYes.colorCornerDefault = {255, 255, 255, 255};
			removehisYes.colorCornerTouched = {255, 255, 255, 255};
			removehisYes.SetBox(450, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
			removehisYes.SetText(title_font, "YES", {499, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
			removehisYes.DrawText(mouseCursor);
			removehisNo.drawCorner = true;
			removehisNo.colorCornerClicked = {255, 255, 255, 255};
			removehisNo.colorCornerDefault = {255, 255, 255, 255};
			removehisNo.colorCornerTouched = {255, 255, 255, 255};
			removehisNo.SetBox(680, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
			removehisNo.SetText(title_font, "NO", {740, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
			removehisNo.DrawText(mouseCursor);
			DrawTextureEx(noti, {787, 200}, 0, 0.3, WHITE);
			if (removehisYes.state == 3) {
				dict -> removeHistory(hislist[i]);
				hislist = dict -> getHistory();
				for (int i = 0; i < hislist.size(); i++) removeHistory[i] = false;
			}
			else if (removehisNo.state == 3) {
				removeHistory[i] = false;
			}
			// break;
		}
	}
	clearHisList.drawCorner = true;
	clearHisList.colorCornerClicked = {255, 255, 255, 255};
	clearHisList.colorCornerDefault = {255, 255, 255, 255};
	clearHisList.colorCornerTouched = {255, 255, 255, 255};
	clearHisList.roundness = 1;
	clearHisList.SetBox(1002, 763, 160, 44, {251, 69, 69, 69}, {173, 170, 171, 255}, {93, 93, 93, 255});
	clearHisList.SetText(title_font, "clear all", {1023, 765}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
	clearHisList.DrawText(mouseCursor);
	// add slang, emoji
	if (clearHisList.state == 3) history_button = 1;
	if (history_button) {
		Rectangle clearall;
		clearall.x = 365;
		clearall.y = 298;
		clearall.width = 550;
		clearall.height = 210;
		DrawRectangleRounded(clearall, 0.1, 10, {248, 199, 199, 255});
		DrawRectangleRoundedLines(clearall, 0.1, 10, 4, {253, 84, 145, 255});
		DrawTextEx(title_font, "Message!", {580, 310}, 36, 1, {227, 89, 97, 255});
		DrawTextEx(title_font, "Are you sure?", {540, 343}, 36, 1, {94, 32, 36, 255});
		clearhis_yes.drawCorner = true;
		clearhis_yes.colorCornerClicked = {255, 255, 255, 255};
		clearhis_yes.colorCornerDefault = {255, 255, 255, 255};
		clearhis_yes.colorCornerTouched = {255, 255, 255, 255};
		clearhis_yes.SetBox(450, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		clearhis_yes.SetText(title_font, "YES", {499, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		clearhis_yes.DrawText(mouseCursor);
		clearhis_no.drawCorner = true;
		clearhis_no.colorCornerClicked = {255, 255, 255, 255};
		clearhis_no.colorCornerDefault = {255, 255, 255, 255};
		clearhis_no.colorCornerTouched = {255, 255, 255, 255};
		clearhis_no.SetBox(680, 390, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		clearhis_no.SetText(title_font, "NO", {740, 395}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		clearhis_no.DrawText(mouseCursor);
		DrawTextureEx(noti, {787, 200}, 0, 0.3, WHITE);
		if (clearhis_yes.state == 3) {
			dict -> clearAllHistory();
			hislist = dict -> getHistory();
			history_button = 0;
		}
		else if (clearhis_no.state == 3) {
			history_button = 0;
		}
	}
}

void UI::DrawHomeScreen() {
	// Button reset
	// when a new word is done search, the right previous word added to the history?
	// babion
	switch (homestate)
	{
	case 0:
		DrawDailyWords();
		break;
	case 1:
		DrawDailyWords();
		messagebar.y = 297;
		messagebar.x = 135;
		messagebar.width = 856;
		messagebar.height = 48;
		DrawRectangleRec(messagebar, {255, 249, 249, 255});
		DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
		DrawTextEx(title_font, "Click here to search for a definition!", GetCenterPos(title_font, "Click here to search for a definition!", 35, 1, messagebar), 35, 1, {0, 0, 0, 140});
		break;
	case 2:
		DrawDailyWords();
		messagebar.y = 297;
		messagebar.x = 135;
		messagebar.width = 856;
		messagebar.height = 48;
		DrawRectangleRec(messagebar, {255, 249, 249, 255});
		DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
		DrawTextEx(title_font, "Click here to search for a keyword!", GetCenterPos(title_font, "Click here to search for a keyword!", 35, 1, messagebar), 35, 1, {0, 0, 0, 140});
		break;
	case 3:
		likebutt = dict -> isInFavList(search.getInput());
		wheel = 0;
		hislist = dict -> getHistory();
		// dict -> searchForDef(search.getInput());
		if (draw = (dict -> searchForDef(search.getInput()))) {
			dict -> addHistory(search.getInput());
			hislist = dict -> getHistory();
			for (int i = 0; i < hislist.size(); i++) removeHistory[i] = false;
		}
		keyword = search.getInput();
		homestate = 9;
		break;
	case 4:
		// likebutt = dict -> isInFavList(search.getInput());
		wheel = 0;
		foundwords = dict -> searchForWord(search.getInput());
		definition = search.getInput();
		homestate = 10;
		break;
	case 5:
		DrawDailyWords();
		messagebar.y = 297;
		messagebar.x = 135;
		messagebar.width = 856;
		messagebar.height = 48;
		DrawRectangleRec(messagebar, {255, 249, 249, 255});
		DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
		DrawTextEx(title_font, "Click here if you want suggestions for a definition you could type!", GetCenterPos(title_font, "Click here if you want suggestions for a definition you could type!", 27, 1, messagebar), 27, 1, {0, 0, 0, 140});
		break;
	case 6:
		DrawDailyWords();
		// break;
		// Rectangle message;
		// message.x = 365;
		// message.y = 338;
		// message.width = 550;
		// message.height = 210;
		// DrawRectangleRounded(message, 0.1, 10, {248, 199, 199, 255});
		// DrawRectangleRoundedLines(message, 0.1, 10, 4, {253, 84, 145, 255});
		// DrawTextEx(title_font, "Choose your mode!", {500, 350}, 36, 1, {227, 89, 97, 255});
		// def.drawCorner = true;
		// def.colorCornerClicked = {255, 255, 255, 255};
		// def.colorCornerDefault = {255, 255, 255, 255};
		// def.colorCornerTouched = {255, 255, 255, 255};
		// def.SetBox(450, 410, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		// def.SetText(title_font, "DEF", {499, 415}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		// def.DrawText(mouseCursor);
		// key.drawCorner = true;
		// key.colorCornerClicked = {255, 255, 255, 255};
		// key.colorCornerDefault = {255, 255, 255, 255};
		// key.colorCornerTouched = {255, 255, 255, 255};
		// key.SetBox(680, 410, 160, 44, {233, 220, 221, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
		// key.SetText(title_font, "KEY", {740, 415}, 36, 1, {94, 32, 36, 255}, {94, 32, 36, 255}, {94, 32, 36, 255});
		// key.DrawText(mouseCursor);
		messagebar.y = 297;
		messagebar.x = 135;
		messagebar.width = 856;
		messagebar.height = 48;
		if (dict -> CorrectDef(search.getInput()) == "No further corrections could be made!")
		{
			DrawRectangleRec(messagebar, {255, 249, 249, 255});
			DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
			DrawTextEx(title_font, "No further corrections could be made!", GetCenterPos(title_font, "No further corrections could be made!", 35, 1, messagebar), 35, 1, {0, 0, 0, 140});
			break;
		}
		DrawRectangleRec(messagebar, {255, 249, 249, 255});
		DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
		DrawTextEx(title_font, dict -> CorrectDef(search.getInput()).c_str(), GetCenterPos(title_font, dict -> CorrectDef(search.getInput()), 50, 1, messagebar), 50, 1, {0, 0, 0, 140});
		break;
	case 7:
		DrawDailyWords();
		messagebar.y = 297;
		messagebar.x = 135;
		messagebar.width = 856;
		messagebar.height = 48;
		DrawRectangleRec(messagebar, {255, 249, 249, 255});
		DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
		DrawTextEx(title_font, "Click here if you want suggestions for a keyword you could type!", GetCenterPos(title_font, "Click here if you want suggestions for a keyword you could type!", 27, 1, messagebar), 27, 1, {0, 0, 0, 140});
		break;
	case 8:
		DrawDailyWords();
		if (dict -> searchPrefix(search.getInput()).size()) {
			messagebar.y = 297;
			messagebar.x = 135;
			messagebar.width = 856;
			messagebar.height = 200 + min(0, (int) dict -> searchPrefix(search.getInput()).size() - 5) * 35;
			int scrollSpeed = 60;      
			wheel += (GetMouseWheelMove()*scrollSpeed);
			if (wheel < 465 - 305 - 35 * min(15, (int) dict -> searchPrefix(search.getInput()).size())) wheel = 465 - 305 - 35 * min(15, (int) dict -> searchPrefix(search.getInput()).size());
			if (wheel > 0) wheel = 0;
			DrawRectangleRec(messagebar, {255, 249, 249, 255});
			DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
			// std::vector < std::string> display;
			for (int i = 0; i < min(15, (int) dict -> searchPrefix(search.getInput()).size()); i++) {
				// std::cout << dict -> searchPrefix(search.getInput())[i] << '\n';
				if (305 + i * 35 + wheel >= 305 && 305 + i * 35 + wheel <= 465) DrawTextEx(title_font, dict -> searchPrefix(search.getInput())[i].c_str(), {GetCenterPos(title_font, dict -> searchPrefix(search.getInput())[i].c_str(), 40, 1, messagebar).x, (float) 305 + (float) i * 35 + (float) wheel}, 40, 1, {0, 0, 0, 140});
			}
		}
		else {
			messagebar.y = 297;
			messagebar.x = 135;
			messagebar.width = 856;
			messagebar.height = 48;
			DrawRectangleRec(messagebar, {255, 249, 249, 255});
			DrawRectangleLinesEx(messagebar, 2, {113, 201, 206, 255});
			DrawTextEx(title_font, "No further suggestions could be made!", GetCenterPos(title_font, "No further suggestions could be made!", 35, 1, messagebar), 35, 1, {0, 0, 0, 140});
		}
		break;
	case 9:
		if (keyword.size()) {
			DrawSearchforDef(draw);
		}	
		else homestate = 0;
		break;
	case 10:
		if (definition.size()) {
			DrawSearchforWord(definition, foundwords);
		}
		else homestate = 0;
		break;
	default:
		break;
	}
	// draw button down here
	search.SetColorText(title_color, title_color, title_color);
	search.SetColorBox({248, 199, 199, 255}, {248, 199, 199, 255}, {248, 199, 199, 255});
	search.colorCornerDefault = {230, 72, 72, 255};
	search.Construct(138, 244, 850, 48, word_font, {139, 245}, 44, 1, 1000);
	search.Draw();
	enterdef.drawCorner = true;
	enterdef.colorCornerClicked = {253, 84, 145, 255};
	enterdef.colorCornerDefault = {253, 84, 145, 255};
	enterdef.colorCornerTouched = {253, 84, 145, 255};
	enterdef.SetBox(1000, 244, 70, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
	enterdef.SetText(title_font, "ENTER", GetCenterPos(title_font, "ENTER", 27, 1, enterdef.buttonShape), 27, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	enterdef.DrawText(mouseCursor);
	enterkey.drawCorner = true;
	enterkey.colorCornerClicked = {253, 84, 145, 255};
	enterkey.colorCornerDefault = {253, 84, 145, 255};
	enterkey.colorCornerTouched = {253, 84, 145, 255};
	enterkey.SetBox(1085, 244, 70, 44, {255, 249, 249, 255}, {173, 170, 171, 255}, {93, 93, 93, 255}); 
	enterkey.SetText(title_font, "ENTER", GetCenterPos(title_font, "ENTER", 27, 1, enterkey.buttonShape), 27, 1, {253, 84, 145, 255}, {253, 84, 145, 255}, {253, 84, 145, 255});
	enterkey.DrawText(mouseCursor);

	// down.drawCorner = true;
	// down.colorCornerClicked = {255, 255, 145, 255};
	// down.colorCornerDefault = {255, 255, 145, 255};
	// down.colorCornerTouched = {255, 255, 145, 255};
	down.roundness = 4;
	down.SetBox(932, 244, 50, 46, {205, 205, 255, 255}, {220, 205, 255, 255}, {234, 205, 255, 255});
	down.SetText(title_font, "", GetCenterPos(title_font, "", 27, 1, down.buttonShape), 27, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	down.DrawText(mouseCursor);

	down1.roundness = 4;
	down1.SetBox(875, 244, 50, 46, {205, 175, 255, 255}, {220, 175, 255, 255}, {234, 175, 255, 255});
	down1.SetText(title_font, "", GetCenterPos(title_font, "", 27, 1, down.buttonShape), 27, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	down1.DrawText(mouseCursor);
	DrawTextureEx(buttondown, {875, 243}, 0, 0.017, WHITE);

	// if (down.state == 1) homestate = 5;
	// if (down.state == 3) homestate = 6;

	// if (enterkey.state == 0) homestate = 0;
	
	// if (homestate == 3 && enterdef.state == 3) homestate = 0;
	// if (homestate == 4 && enterkey.state == 3) homestate = 0;
	if (homestate != 3 && homestate != 4 && homestate != 6 && homestate != 8 && homestate != 9 && homestate != 10) {
		if (enterdef.state == 1) homestate = 1;

		else if (down1.state == 1) homestate = 7;
		// if (enterdef.state == 0) homestate = 0; 
		else if (enterkey.state == 1) homestate = 2;
		
		else if (down.state == 1) homestate = 5;
		else homestate = 0;
	}
	
	if (down.state == 3) {
		// if (homestate == 6) homestate = 0;
		homestate = 6;
	}
	
	
	if (enterdef.state == 3) {
		// if (homestate == 3) homestate = 0;
		// else 
		homestate = 3;
	}
	
	if (enterkey.state == 3) {
		// if (homestate == 4) homestate = 0;
		// else 
		homestate = 4;
	}

	if (down1.state == 3) homestate = 8;
	DrawTextureEx(buttondown, {932, 243}, 0, 0.017, WHITE);
}

void UI::DrawDailyWords() {
	static bool li = dict -> isInFavList(dailyword -> word);
	DrawWord(dailyword, li, nullptr);
}

void UI::DrawWord(Word* word, bool &x, SmallTrie* highlight) {
	
	// std::cout << dict -> isInFavList(word -> word) << '\n'; 
	// favlist = dict -> getFav();
	// std::cout << favlist.size();
	if (!word) {
		// DrawTextEx(word_font, "-", {153, 310}, 73, 1, {220, 71, 89, 255});
		// DrawTextEx(word_font, word -> word.c_str(), {193, 310}, 73, 1, {220, 71, 89, 255});
		DrawTextEx(title_font, "No results found!", {193, 380}, 50, 1, {220, 205, 255, 255});
		return;
	}
	x = dict -> isInFavList(word -> word);
	int scrollspeed = 50;
	if (!neww && !beingmodified) wheel += GetMouseWheelMove() * scrollspeed;
	int lim;
		posTextX = 236;
		posTextY = 330;
		for (int i = 0; i < 9; i++) {
			if (word -> def[i].size()) {
				posTextY += 50;
				// DrawTextEx(title_font, (POS::TypeString[i]).c_str(), {193, (float) posTextY}, 50, 1, {220, 205, 255, 255});
				for (int j = 0; j < word -> def[i].size(); j++) {
					posTextX = 236;
					posTextY += 50;
					// int scrollspeed = 30;
					// wheel += GetMouseWheelMove() * scrollspeed;
					std::vector <std::string> words = dict -> stringCut(word -> def[i][j]);
					// if (posTextY + MeasureTextEx(word_font, "*", 45, 1).y + wheel <= 770 && posTextY + wheel >= 430) DrawTextEx(word_font, "*", {(float) posTextX, (float) posTextY + (float) wheel}, 45, 1, {220, 71, 89, 255});
					posTextX += MeasureTextEx(word_font, " ", 45, 1).x;
					posTextX += MeasureTextEx(word_font, "*", 45, 1).x;
					for (int i = 0; i < words.size(); i++) {
						if (posTextX + MeasureTextEx(word_font, words[i].c_str(), 45, 1).x > 1123) {
							posTextX = 236;
							posTextY += 50;
						}
						if (posTextY + MeasureTextEx(word_font, words[i].c_str(), 45, 1).y + wheel <= 770 && posTextY + wheel >= 430) {
							// DrawTextEx(word_font, words[i].c_str(), {(float) posTextX, (float) posTextY + (float) wheel}, 45, 1, {220, 71, 89, 255});
						}
						posTextX += MeasureTextEx(word_font, words[i].c_str(), 45, 1).x;
						posTextX += MeasureTextEx(word_font, " ", 73, 1).x;
						lim = posTextY + MeasureTextEx(word_font, words[i].c_str(), 45, 1).y;
					}
				}
			}
		}
	if (lim + wheel < 770) wheel = 770 - lim;
	if (wheel > 0) wheel = 0; 
	
	display.x = 138;
	display.y = 307;
	display.width = 1017;
	display.height = 493;
	DrawRectangleRoundedLines(display, 0.03, 10, 4, {253, 84, 145, 255});
	// string s = word -> word;
	// if (s[0] > 90) s[0] -= 32;
	// cout << s[0];
	DrawTextureEx(newword, {1090, 316}, 0, 0.032, WHITE);
	DrawTextureEx(modify, {950, 314}, 0, 0.13, WHITE);
	DrawTextureEx(deleteword, {1022, 310}, 0, 0.3, WHITE);
	DrawTextEx(word_font, "-", {153, 310}, 73, 1, {220, 71, 89, 255});
	DrawTextEx(word_font, word -> word.c_str(), {193, 310}, 73, 1, {220, 71, 89, 255});
	if (x) DrawTextureEx(like, {860, 304}, 0, 0.07, WHITE);
	else DrawTextureEx(dislike, {860, 304}, 0, 0.07, WHITE);
	Like.drawCorner = true;
	Like.colorCornerClicked = {253, 84, 145, 0};
	Like.colorCornerDefault = {253, 84, 145, 0};
	Like.colorCornerTouched = {253, 84, 145, 0};
	Like.SetBox(870, 310, 53, 53, {253, 84, 145, 0}, {173, 170, 171, 0}, {93, 93, 93, 0});
	Like.SetText(title_font, "", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	Like.DrawText(mouseCursor);
	Modify.SetBox(950, 315, 63, 63, {253, 84, 145, 0}, {173, 170, 171, 0}, {93, 93, 93, 0});
	Modify.SetText(title_font, "", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	Modify.DrawText(mouseCursor);
	Deleteword.SetBox(1030, 315, 53, 53, {253, 84, 145, 0}, {173, 170, 171, 0}, {93, 93, 93, 0});
	Deleteword.SetText(title_font, "", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	Deleteword.DrawText(mouseCursor);
	Neww.SetBox(1093, 318, 60, 60, {253, 84, 145, 0}, {173, 170, 171, 0}, {93, 93, 93, 0});
	Neww.SetText(title_font, "", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	Neww.DrawText(mouseCursor);
	if (Deleteword.state == 3) {
		isdeleted = true;
	}
	if (Neww.state == 3) {
		new_word = new Word();
		for (int i = 0; i < 9; i++) new_word -> def[i].push_back("");
		inputindex = 1;
		for (int i = 0; i < 9; i++) {
			if (new_word -> def[i].size()) {
				for (int j = 0; j < new_word -> def[i].size(); j++)
				{
					typenew[inputindex].currentInput = new_word -> def[i][j];
					typenew[inputindex].posCursor = 0;
					inputindex++;
				}
			}
		}
		posTextX = 236;
		posTextY = 330;
		inputindex = 0;
		wheel = 0;
		neww ^= 1;
		
	}
	if (Modify.state == 3) {
		inputindex = 1;
		for (int i = 0; i < 9; i++) {
			if (word -> def[i].size()) {
				for (int j = 0; j < word -> def[i].size(); j++)
				{
					typenew[inputindex].currentInput = word -> def[i][j];
					typenew[inputindex].posCursor = 0;
					inputindex++;
				}
			}
			else {
				word -> def[i].push_back("");
				word -> type += (1 << i);
				i--;
			}
		}
		posTextX = 236;
		posTextY = 330;
		inputindex = 0;
		wheel = 0;
		beingmodified ^= 1;
	}
	if (Like.state == 3) {
		x ^= 1;
		if (!x) {
			dict -> removeFav(word -> word);
			favlist = dict -> getFav();
			for (int index = 0; index < favlist.size(); index++) removeFavourite[index] = false;
		}
		else {
			dict -> addFav(word -> word);
			favlist = dict -> getFav();
			for (int index = 0; index < favlist.size(); index++) removeFavourite[index] = false;
		}
		// x = dict -> isInFavList(word -> word);
	}
	posTextX = 236;
	posTextY = 330;
	for (int i = 0; i < 9; i++) {
		if (word -> def[i].size()) {
			posTextY += 50;
			if ((float) posTextY + wheel >= 380 && (float) posTextY + wheel + MeasureTextEx(title_font, (POS::TypeString[i]).c_str(), 50, 1).y <= 770) DrawTextEx(title_font, (POS::TypeString[i]).c_str(), {193, (float) posTextY + wheel}, 50, 1, {220, 205, 255, 255});
			for (int j = 0; j < word -> def[i].size(); j++) {
				DrawLongText(word -> def[i][j], highlight);
			}
		}
	}
	if (beingmodified) {
		inputindex = 0;
		posTextX = 236;
		posTextY = 330;
		DrawModifyBox(word);
	}
	if (isdeleted) {
		Rectangle clearall;
		clearall.x = 365;
		clearall.y = 298;
		clearall.width = 550;
		clearall.height = 210;
		DrawRectangleRounded(clearall, 0.1, 10, {248, 199, 199, 255});
		DrawRectangleRoundedLines(clearall, 0.1, 10, 4, {253, 84, 145, 255});
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
		if (reset_yes.state == 3) {
			dict -> removeWord(word -> word);
			// remove in history, favlist, all?
			homestate = 0;
			if (word == dailyword) dailyword = dict -> getDailyWord();
			isdeleted = false;
		}
		else if (reset_no.state == 3) isdeleted = false;
	}
	if (neww) {
		inputindex = 0;
		posTextX = 236;
		posTextY = 330;
		DrawModifyBox(new_word);
	}
	// DrawTextEx(title_font, "Noun.", {193, 380}, 50, 1, {0, 0, 0, 255});
	// DrawTextEx(word_font, "- em iu anh", {236, 430}, 45, 1, {0, 0, 0, 255});
	
	// DrawLongText("It was year ago ago ago ago year it was a good story I was excited I was hooked on these things I'm so thankful!");
	return;
}

// reset posTextX posTextY
void UI::DrawLongText(std::string s, SmallTrie* highlight) {
	// reset wheel = 0 where?
	posTextX = 236;
	posTextY += 50;
	std::vector <std::string> words = dict -> stringCut(s);
	if (posTextY + MeasureTextEx(word_font, "*", 45, 1).y + wheel <= 770 && posTextY + wheel >= 380) DrawTextEx(word_font, "*", {(float) posTextX, (float) posTextY + (float) wheel}, 45, 1, {220, 71, 89, 255});
	posTextX += MeasureTextEx(word_font, " ", 45, 1).x;
	posTextX += MeasureTextEx(word_font, "*", 45, 1).x;
	for (int i = 0; i < words.size(); i++) {
		if (posTextX + MeasureTextEx(word_font, words[i].c_str(), 45, 1).x > 1123) {
			posTextX = 236;
			posTextY += 50;
		}
		if (posTextY + MeasureTextEx(word_font, words[i].c_str(), 45, 1).y + wheel <= 770 && posTextY + wheel >= 380) {
			if (highlight && highlight -> search(dict -> Purify(words[i]))) {
				DrawTextEx(word_font, words[i].c_str(), {(float) posTextX, (float) posTextY + (float) wheel}, 45, 1, {150, 0, 0, 255});
			}
			else DrawTextEx(word_font, words[i].c_str(), {(float) posTextX, (float) posTextY + (float) wheel}, 45, 1, {220, 71, 89, 255});
		}
		posTextX += MeasureTextEx(word_font, words[i].c_str(), 45, 1).x;
		posTextX += MeasureTextEx(word_font, " ", 73, 1).x;
	}
	return;
	// centerPos.x = x + (width - MeasureTextEx(font, text.c_str(), fontSize, spacing).x) / 2;
	// centerPos.y = y + (height - MeasureTextEx(font, text.c_str(), fontSize, spacing).y) / 2;
}

// bool showText(int x, int y) {}

void UI::DrawSearchforDef(Word* word) {
	DrawWord(draw, likebutt, nullptr);
	return;
}
void UI::DrawSearchforWord(const std::string def, std::vector <std::string> foundwords) {
	static int index = 0;
	if (!foundwords.size()) {
		DrawTextEx(title_font, "No results found!", {193, 380}, 50, 1, {220, 205, 255, 255});
		return;
	}
	std::vector <std::string> cut = dict -> stringCut(def);
	SmallTrie* highlight = new SmallTrie();
	for (int i = 0; i < cut.size(); i++) {
		highlight -> insert(cut[i]);
	}
	right.SetBox(1105, 760, 40, 40, {253, 84, 145, 0}, {173, 170, 171, 0}, {93, 93, 93, 0});
	right.SetText(title_font, "", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	right.DrawText(mouseCursor);
	left.SetBox(1055, 760, 40, 40, {253, 84, 145, 0}, {173, 170, 171, 0}, {93, 93, 93, 0});
	left.SetText(title_font, "", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	left.DrawText(mouseCursor);
	if (right.state == 3) {
		wheel = 0;
		index++;
	}
	if (left.state == 3) {
		wheel = 0;
		index--;
	}
	DrawTextureEx(next, {1105, 755}, 0, 0.1, WHITE);
	DrawTextureEx(next, {1103, 807}, 180, 0.1, WHITE);
	if (index < 0) index = 0;
	if (index >= foundwords.size()) index = foundwords.size() - 1;
	static bool lik = dict -> isInFavList(foundwords[index]);
	DrawWord(dict -> searchForDef(foundwords[index]), lik, highlight);
 	return;
}

void UI::run() {
	dict = new Dict();
    DefaultWindow();
	dict->~Dict();
}

void UI::DrawModifyBox(Word* &word) {
	
	if (!word) {
		std::cout << "Error" << '\n';
		return;
	}
	static float wheelModify = 0;
	int scrollspeed = 50;
	display.x = 138;
	display.y = 307;
	display.width = 1017;
	display.height = 493;
	DrawRectangleRoundedLines(display, 0.03, 10, 4, {253, 84, 145, 255});
	// if (neww) {
		DrawRectangleRounded(display, 0.1, 10, {248, 224, 224, 255});
	// }
	done.drawCorner = true;
	done.colorCornerClicked = {253, 84, 145, 255};
	done.colorCornerDefault = {253, 84, 145, 255};
	done.colorCornerTouched = {253, 84, 145, 255};
	done.SetBox(1010, 180, 128, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
	done.SetText(title_font, "Done", GetCenterPos(title_font, "Done", 36, 1, done.buttonShape), 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	done.DrawText(mouseCursor);
	
	if (done.state == 3) {
		if (beingmodified) {
			dict -> removeDefTrie(word);
			// std::cout << word -> word << 'y';
			// for (int i = 0; i < 9; i++) {
			// 	if (word -> def[i].size()) {
			// 		for (int j = 0; j < word -> def[i].size(); j++) {word -> def[i][j] = "hsg";
			// 		std::cout << word -> def[i][j] << '\n';}
			// 	}
			// }
			int cnt = 1;
			for (int i = 0; i < 9; i++) {
				if (word -> def[i].size()) {
					// std::cout << word -> def[i].size();
					for (int j = 0; j < word -> def[i].size(); j++) {
						// std::cout << word -> def[i].size() << ' ' << i << ' ' << j << '\n';
						// std::cout << typenew[cnt].getInput() << '\n';
						if (typenew[cnt].getInput().size()) {
							// dict -> updateDef(word -> word, 1 << i, word -> def[i][j], typenew[cnt].getInput());
							// std::cout << word -> def[i].size() << ' ' << i << ' ' << j << '\n';
							// std::cout << word -> def[0][0] << '\n';
							// std::cout << typenew[cnt].getInput() << '\n';
							word -> def[i][j] = typenew[cnt].getInput();
							// std::cout << word -> def[0][0] << '\n';
							// std::cout << "done";
							// break;
						}
						else {
							word -> def[i].erase(word -> def[i].begin() + j);
							j--;
						}
						cnt++;
						// verb always?
					}
					if (!word -> def[i].size()) word -> type -= (1 << i);
				}
			}
			dict -> addDefTrie(word);
		}
		else if (neww) {
			int cnt = 0;
			if (typenew[0].getInput().size()) {
				word -> word = typenew[cnt].getInput();
				cnt++;
				for (int i = 0; i < 9; i++) {
					if (word -> def[i].size()) {
						// std::cout << word -> def[i].size();
						for (int j = 0; j < word -> def[i].size(); j++) {
							// std::cout << word -> def[i].size() << ' ' << i << ' ' << j << '\n';
							// std::cout << typenew[cnt].getInput() << '\n';
							if (typenew[cnt].getInput().size()) {
								// dict -> updateDef(word -> word, 1 << i, word -> def[i][j], typenew[cnt].getInput());
								// std::cout << word -> def[i].size() << ' ' << i << ' ' << j << '\n';
								// std::cout << word -> def[0][0] << '\n';
								// std::cout << typenew[cnt].getInput() << '\n';
								word -> def[i][j] = typenew[cnt].getInput();
								// std::cout << word -> def[0][0] << '\n';
								// std::cout << "done";
								// break;
							}
							else {
								word -> def[i].erase(word -> def[i].begin() + j);
								j--;
							}
							cnt++;
							// verb always?
						}
					}
					if (word -> def[i].size()) word -> type += (1 << i);
				}
			}
			else {
				delete word;
				word = nullptr;
			}
		}
		
		homestate = 0;
		
		if (word && word -> word.size()) {
			if (!dict -> isInDict(word -> word)) dict -> addWord(word, true);
			homestate = 9;
			keyword = word -> word;
			draw = dict -> searchForDef(word -> word);
		}
		// std::cout << draw -> word << " " << word -> word << '\n';
		if (neww) neww ^= 1;
		else if (beingmodified) beingmodified ^= 1;
		wheelModify = 0;
		return;
		// std::cout << draw -> def[0][0] << '\n';
	}
	// posTextX = 236;
	// posTextY = 330;
	// for (int i = 0; i < 9; i++) {
	// 	if (word -> def[i].size()) {
	// 		posTextY += 50;
	// 		if ((float) posTextY + wheelModify >= 380 && (float) posTextY + wheelModify + MeasureTextEx(title_font, (POS::TypeString[i]).c_str(), 50, 1).y <= 770) DrawTextEx(title_font, (POS::TypeString[i]).c_str(), {193, (float) posTextY + wheelModify}, 50, 1, {220, 205, 255, 255});
	// 		for (int j = 0; j < word -> def[i].size(); j++) {
	// 			DrawLongText(word -> def[i][j], highlight);
	// 		}
	// 	}
	// }
	DrawTextEx(word_font, "-", {153, 310}, 73, 1, {220, 71, 89, 255});
	// DrawTextEx(word_font, word -> word.c_str(), {193, 310}, 73, 1, {220, 71, 89, 255});
	if (beingmodified) {
		DrawTextEx(title_font, "Modifying", {138, 190}, 50, 1, {227, 89, 97, 255});
		DrawTextEx(word_font, word -> word.c_str(), {193, 310}, 73, 1, {220, 71, 89, 255});
	}
	else {
		DrawTextEx(title_font, "Adding", {138, 190}, 50, 1, {227, 89, 97, 255});
		typenew[inputindex].SetColorText(title_color, title_color, title_color);
		typenew[inputindex].SetColorBox({248, 199, 199, 255}, {248, 199, 199, 255}, {248, 199, 199, 255});
		typenew[inputindex].colorCornerDefault = {230, 72, 72, 255};
		typenew[inputindex].Construct(193, 315, 750, 48, word_font, {193, 315}, 44, 1, 1000);
		typenew[inputindex].Draw();
	}
	inputindex++;
	
	for (int i = 0; i < 9; i++) {
		if (word -> def[i].size()) {
			posTextY += 50;
			if ((float) posTextY + wheelModify >= 380 && (float) posTextY + wheelModify + MeasureTextEx(title_font, (POS::TypeString[i]).c_str(), 50, 1).y <= 770) {
				DrawTextEx(title_font, (POS::TypeString[i]).c_str(), {193, (float) posTextY + wheelModify}, 50, 1, {220, 205, 255, 255});
				DrawTextureEx(newword, {193 + MeasureTextEx(title_font, (POS::TypeString[i]).c_str(), 50, 1).x + 20, (float) posTextY + wheelModify + 10}, 0, 0.017, WHITE);
				addpos[i].SetBox(193 + MeasureTextEx(title_font, (POS::TypeString[i]).c_str(), 50, 1).x + 20, (float) posTextY + wheelModify + 10, 35, 35, {253, 84, 145, 0}, {173, 170, 171, 0}, {93, 93, 93, 0});
				addpos[i].SetText(title_font, "", {25, 7}, 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
				addpos[i].DrawText(mouseCursor);
			}
			for (int j = 0; j < word -> def[i].size(); j++) {
				
				posTextY += 50;
				typenew[inputindex].SetColorText(title_color, title_color, title_color);
				typenew[inputindex].SetColorBox({248, 199, 199, 255}, {248, 199, 199, 255}, {248, 199, 199, 255});
				typenew[inputindex].colorCornerDefault = {230, 72, 72, 255};
				typenew[inputindex].Construct(posTextX, posTextY + wheelModify, 750, 48, word_font, {(float) posTextX, (float) posTextY + wheelModify}, 44, 1, 1000);
				typenew[inputindex].MAX_SIZE = 10000;
				// std::cout << inputindex << '\n';
				if ((float) posTextY + wheelModify >= 380 && (float) posTextY + wheelModify + 48 <= 770) typenew[inputindex].Draw();
				inputindex++;
				// std::cout << new_word -> word << "x" << '\n';
				// DrawLongText(word -> def[i][j], highlight);
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		if (addpos[i].state == 3) word -> def[i].push_back("");
	}
	wheelModify += GetMouseWheelMove() * scrollspeed;
	if (wheelModify + posTextY + 50 < 770) wheelModify = 770 - posTextY - 50;
	if (wheelModify > 0) wheelModify = 0;
	// call remove and add.

	return;
}

void UI::DrawGame() {
	static int wheel1 = 0;
	static int wheel2 = 0;
	static int wheel3 = 0;
	static int wheel4 = 0;
	int scrollspeed = 50;
	wheel += GetMouseWheelMove() * scrollspeed;
	if (guess.state == 3) {
		guessthemeaning ^= 1;
		v.clear();
		v = dict->getMultiChoices(4);
		randef.clear();
		for (int i = 0; i < 4; i++) {
			randef.push_back(v[i]->getRandDef());
		}
		wheel = 0;
		a = false;
		b = false;
		c = false;
		d = false;
		res = 0;
	}
	Rectangle givenword;
	givenword.x = 350;
	givenword.y = 258;
	givenword.width = 550;
	givenword.height = 210;
	DrawRectangleRounded(givenword, 0.1, 10, {248, 199, 199, 255});
	DrawRectangleRoundedLines(givenword, 0.1, 10, 4, {253, 84, 145, 255});
	DrawTextureEx(noti, {772, 160}, 0, 0.3, WHITE);
	if (guessthemeaning) {
		DrawTextEx(title_font, v[0] -> word.c_str(), GetCenterPos(title_font, v[0] -> word.c_str(), 60, 1, givenword), 60, 1, {227, 89, 97, 255});
	}
	else {
		// DrawTextEx();
		BeginScissorMode(350, 340, 550, 108);
		std::vector <std::string> print = dict -> stringCut(randef[0]);
		for (int i = 0; i < print.size(); i++) {
			if (wheel > 0) wheel = 0;
			if (textx + MeasureTextEx(title_font, print[i].c_str(), 36, 1).x > 890) {
				textx = 365;
				texty += 50;
			}
			DrawTextEx(title_font, print[i].c_str(), {(float) textx, (float) texty + wheel}, 36, 1, {227, 89, 97, 255});
			textx += MeasureTextEx(title_font, print[i].c_str(), 36, 1).x + MeasureTextEx(title_font, " ", 36, 1).x;
		}
		EndScissorMode();
	}
	if (A.state == 3) {
		a = true;
		b = false;
		c = false;
		d = false;
		res = 1;
	}
	else if (B.state == 3) {
		b = true;
		a = false;
		c = false;
		d = false;
		res = 1;
	}
	else if (C.state == 3) {
		c = true;
		b = false;
		a = false;
		d = false;
		res = 1;
	}
	else if (D.state == 3) {
		d = true;
		b = false;
		c = false;
		a = false;
		res = 1;
	}
	if (a) {
		DrawRectangleRounded(A.buttonShape, 0.1, 10, {0, 0, 0, 80});
	} 
	else if (b) DrawRectangleRounded(B.buttonShape, 0.1, 10, {0, 0, 0, 80});
	else if (c) DrawRectangleRounded(C.buttonShape, 0.1, 10, {0, 0, 0, 80});
	else if (d) DrawRectangleRounded(D.buttonShape, 0.1, 10, {0, 0, 0, 80});
	if (res == 1) DrawRectangleRounded(A.buttonShape, 0.1, 10, {0, 228, 48, 200});
	else if (res == 2) DrawRectangleRounded(B.buttonShape, 0.1, 10, {0, 228, 48, 200});
	else if (res == 3) DrawRectangleRounded(C.buttonShape, 0.1, 10, {0, 228, 48, 200});
	else if (res == 4) DrawRectangleRounded(D.buttonShape, 0.1, 10, {0, 228, 48, 200});
	A.SetBox(120, 500, 500, 130, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 30});
	A.SetText(word_font, "", {120, 530}, 36, 1, {255, 255, 255, 255}, {0, 0, 0, 255}, {0, 0, 0, 255});
	DrawRectangleRoundedLines(A.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
	A.DrawText(mouseCursor);
	C.SetBox(120, 650, 500, 130, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 30});
	C.SetText(word_font, "", {120, 530}, 36, 1, {255, 255, 255, 255}, {0, 0, 0, 255}, {0, 0, 0, 255});
	DrawRectangleRoundedLines(C.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
	C.DrawText(mouseCursor);
	D.SetBox(658, 650, 500, 130, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 30});
	D.SetText(word_font, "", {120, 530}, 36, 1, {255, 255, 255, 255}, {0, 0, 0, 255}, {0, 0, 0, 255});
	DrawRectangleRoundedLines(D.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
	D.DrawText(mouseCursor);
	B.SetBox(658, 500, 500, 130, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 30});
	B.SetText(word_font, "", {120, 530}, 36, 1, {255, 255, 255, 255}, {0, 0, 0, 255}, {0, 0, 0, 255});
	DrawRectangleRoundedLines(B.buttonShape, 0.1, 10, 4, {253, 84, 145, 255});
	B.DrawText(mouseCursor);
	if (guessthemeaning) {
		if (A.state == 1) {
			wheel1 += GetMouseWheelMove() * scrollspeed;
		}
		else {
			wheel1 = 0;
		}
		if (D.state == 1) {
			wheel2 += GetMouseWheelMove() * scrollspeed;
		}
		else {
			wheel2 = 0;
		}
		if (C.state == 1) {
			wheel3 += GetMouseWheelMove() * scrollspeed;
		}
		else {
			wheel3 = 0;
		}
		if (B.state == 1) {
			wheel4 += GetMouseWheelMove() * scrollspeed;
		}
		else {
			wheel4 = 0;
		}
		textx = 130;
		texty = 510;
		BeginScissorMode(120, 500, 500, 130);
		std::vector <std::string> print = dict -> stringCut(randef[0]);
		for (int i = 0; i < print.size(); i++) {
			if (wheel1 > 0) wheel1 = 0;
			if (textx + MeasureTextEx(word_font, print[i].c_str(), 36, 1).x > 610) {
				textx = 130;
				texty += 50;
			}
			if (A.state == 1) {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty + wheel1}, 36, 1, {227, 89, 97, 255});
			}
			else {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty}, 36, 1, {227, 89, 97, 255});
			}
			textx += MeasureTextEx(word_font, print[i].c_str(), 36, 1).x + MeasureTextEx(word_font, " ", 36, 1).x;
		}
		EndScissorMode();
		textx = 668;
		texty = 660;
		BeginScissorMode(658, 650, 500, 130);
		print = dict -> stringCut(randef[3]);
		for (int i = 0; i < print.size(); i++) {
			if (wheel2 > 0) wheel2 = 0;
			if (textx + MeasureTextEx(word_font, print[i].c_str(), 36, 1).x > 1148) {
				textx = 668;
				texty += 50;
			}
			if (D.state == 1) {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty + wheel2}, 36, 1, {227, 89, 97, 255});
			}
			else {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty}, 36, 1, {227, 89, 97, 255});
			}
			textx += MeasureTextEx(word_font, print[i].c_str(), 36, 1).x + MeasureTextEx(word_font, " ", 36, 1).x;
		}
		EndScissorMode();
		textx = 130;
		texty = 660;
		BeginScissorMode(130, 650, 500, 130);
		print = dict -> stringCut(randef[2]);
		for (int i = 0; i < print.size(); i++) {
			if (wheel3 > 0) wheel3 = 0;
			if (textx + MeasureTextEx(word_font, print[i].c_str(), 36, 1).x > 620) {
				textx = 130;
				texty += 50;
			}
			if (C.state == 1) {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty + wheel3}, 36, 1, {227, 89, 97, 255});
			}
			else {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty}, 36, 1, {227, 89, 97, 255});
			}
			textx += MeasureTextEx(word_font, print[i].c_str(), 36, 1).x + MeasureTextEx(word_font, " ", 36, 1).x;
		}
		EndScissorMode();
		textx = 668;
		texty = 510;
		BeginScissorMode(658, 500, 500, 130);
		print = dict -> stringCut(randef[1]);
		for (int i = 0; i < print.size(); i++) {
			if (wheel4 > 0) wheel4 = 0;
			if (textx + MeasureTextEx(word_font, print[i].c_str(), 36, 1).x > 1148) {
				textx = 668;
				texty += 50;
			}
			if (B.state == 1) {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty + wheel4}, 36, 1, {227, 89, 97, 255});
			}
			else {
				DrawTextEx(word_font, print[i].c_str(), {(float) textx, (float) texty}, 36, 1, {227, 89, 97, 255});
			}
			textx += MeasureTextEx(word_font, print[i].c_str(), 36, 1).x + MeasureTextEx(word_font, " ", 36, 1).x;
		}
		EndScissorMode();
	}
	else {
		DrawTextEx(word_font, v[0] -> word.c_str(), GetCenterPos(word_font, v[0] -> word.c_str(), 36, 1, A.buttonShape), 36, 1, {227, 89, 97, 255});
		DrawTextEx(word_font, v[1] -> word.c_str(), GetCenterPos(word_font, v[1] -> word.c_str(), 36, 1, B.buttonShape), 36, 1, {227, 89, 97, 255});
		DrawTextEx(word_font, v[2] -> word.c_str(), GetCenterPos(word_font, v[2] -> word.c_str(), 36, 1, C.buttonShape), 36, 1, {227, 89, 97, 255});
		DrawTextEx(word_font, v[3] -> word.c_str(), GetCenterPos(word_font, v[3] -> word.c_str(), 36, 1, D.buttonShape), 36, 1, {227, 89, 97, 255});
	}
	guess.drawCorner = true;
	guess.colorCornerClicked = {253, 84, 145, 255};
	guess.colorCornerDefault = {253, 84, 145, 255};
	guess.colorCornerTouched = {253, 84, 145, 255};
	if (guessthemeaning) guess.SetText(title_font, "GUESS THE MEANING", GetCenterPos(title_font, "GUESS THE MEANING", 36, 1, guess.buttonShape), 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	else guess.SetText(title_font, "GUESS THE WORD", GetCenterPos(title_font, "GUESS THE WORD", 36, 1, guess.buttonShape), 36, 1, {255, 249, 249, 255}, {255, 249, 249, 255}, {255, 249, 249, 255});
	guess.SetBox(365, 273, 330, 44, {253, 84, 145, 255}, {173, 170, 171, 255}, {93, 93, 93, 255});
	guess.DrawText(mouseCursor);
	return;
}
// add renew button to view random words, homestate = 0, get daily word again;
// add modify button 
// add remove button 