#pragma once
#include "basic_camera.h"
#include "ball.h"

void OnDraw(void);
void OnReshape(int w, int h);
void OnKeyboard(unsigned char key, int x, int y);
void OnMouseMove(int x, int y);
void OnInit(int *argc, char **argv);

extern BasicCamera camera;
extern Ball b;