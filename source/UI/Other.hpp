#ifndef OTHER_H
#define OTHER_H

#include "raylib.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

// center text
Vector2 GetCenterPos(Font font, string text, float fontSize, float spacing, float x, float y, float width, float height);
Vector2 GetCenterPos(Font font, string text, float fontSize, float spacing, Rectangle rect);
// draw text on box, return the position of the last character
Vector2 DrawTextOnBox(Rectangle boxShape, Font font, string text, Vector2 coord, float fontSize, float spacing, float lineGap, Color colorText);
float DrawTextOnBoxEx(Rectangle boxShape, Font font, vector<string> &text, Vector2 coord, float fontSize, float spacing, float lineGap, float paraGap, Color colorText);
int RandInt(int min, int max);
string PartialText(Font font, string text, float fontSize, float spacing, float width);

#endif