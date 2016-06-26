#include <GL\freeglut.h>
#include "main.h"

int windowWidth = 800;
int windowHeight = 600;
BasicCamera camera(0, 0, 2, 0, 0, 0, 0, 1, 0);

void OnInit(int *argc, char **argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CGFinal: Pinball");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glutDisplayFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyboard);
	glutIdleFunc(OnDraw);
	//glutPassiveMotionFunc(OnMouseMove);
}