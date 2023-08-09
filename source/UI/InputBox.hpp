#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "raylib.h"
#include <iostream>
#include <string.h>
using namespace std;

struct InputBox {
    string currentInput = "";// current input string
    Font font;
    Rectangle inputShape;
    Vector2 coordText;
    float szText, spacing;
    Color colorBoxDefault = RAYWHITE, colorBoxTouched = RAYWHITE, colorBoxTyping = RAYWHITE;
    Color colorTextDefault = BLACK, colorTextTouched = BLACK, colorTextTyping = BLACK;
    Color colorCornerDefault = { 113, 201, 206, 255 };
    int MAX_SIZE = 0;// max size of input
    float roundness = 0, segments = 0;// for drawing corner of input box
    bool isTyping = false;// check if the input box is ready to type
    bool drawCorner = true;// draw corner of input box
    bool add = false;// add | to the end of currentInput
    int timeline = 0;// for blinking cursor
    int posCursor = 0;// position of cursor
    int posL = 0;// first position in currentInput would be drawn
    int posR = 0;// last position in currentInput would be drawn
    int countConsecutiveKey = 0;// count consecutive key pressed
    int lastKey = 0;// last key pressed
    float lengthText = 0;// length of text limit
    enum State { DEFAULT, TOUCHED, TYPING };

    void Construct(float x, float y, float width, float height, Font _font, Vector2 _coordText, int _szText, float _spacing, int _MAX_SIZE);
    void SetColorBox(Color colorDefault, Color colorTouched, Color colorTyping);
    void SetColorText(Color colorDefault, Color colorTouched, Color colorTyping);
    void Draw();
    bool checkCollisionText(int l, int r);
    bool isClicked();
    int getState();
    void reset();
    void manipulate();
    string getInput();
};

#endif