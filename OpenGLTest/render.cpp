#include <GL\freeglut.h>
#include "main.h"
#include "basic_camera.h"

void OnDraw() {
	
	//glViewport(0, 0, windowWidth, windowHeight);
	camera.see();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//float whRatio = float(windowWidth) / windowHeight;
	//gluPerspective(45, whRatio, 0.1, 100);

	//gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glTranslated(0, 0, -2);
	glRotated(90, 1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	GLfloat white[] = { 1, 1, 1, 1 }; // 定义颜色
	GLfloat light_pos[] = { 5, 5, 5, 1 };  //定义光源位置

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//if (isPlaying) {
	//	gluLookAt(playerPosition[0], playerPosition[1], 0, playerPosition[0] + cos(rotate), playerPosition[1] + sin(rotate), 0, 0, 0, 1);
	//}
	//else {
	//	gluLookAt(eye[0], eye[1], eye[2], obj[0], obj[1], obj[2], 0, 1, 0);
	//}


	//glPushMatrix();
	//for (int i = 0; i < 5; i++)
	//	for (int j = 0; j < 5; j++)
	//		if (maze[i][j]) {
	//			glPushMatrix();
	//			glTranslatef(i, j, 0);
	//			glutSolidCube(1);
	//			glPopMatrix();
	//		}
	//if (isPlaying) {

	//}
	//else {
	//	glPushMatrix();
	//	glTranslatef(playerPosition[0], playerPosition[1], 0);
	//	glutSolidSphere(0.5, 20, 20);
	//	glPopMatrix();
	//}


	//glPopMatrix();

	glutSwapBuffers();
}

void OnReshape(int w, int h) {
	camera.setShape(w, h);
	camera.see();
}