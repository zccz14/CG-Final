#pragma once
#include <GL\freeglut.h>
#include "tiny_obj_loader.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

//obj parser
vector<tinyobj::shape_t> tree_shapes, stone_shapes;
vector<tinyobj::material_t> tree_materials, stone_materials;
GLfloat tree_loc[4][2] = { { 25, 15 },{ 15, 25 },{ 35, 24 },{ 45, 35 } };
GLfloat stone_loc[4][2] = { { 5, 15 },{ 25, 5 },{ 35, 6 },{ 15, 35 } };
string err;
//lookat
int fx = -10, fy = -10, fz = 20;
int tox = 50, toy = 50, toz = 0;
static int r = 0;
void drawObj ();
void lightinit ();
void timer (int e) {
	glutPostRedisplay ();
	glutTimerFunc (100, timer, 1);
}
void display () {

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sky.ShowSky ();
	drawObj ();
	glColor3f (0.1, 0.3, 0.2);
	glBegin (GL_POLYGON);
	glVertex3d (0, 0, 0);
	glVertex3d (0, 50, 0);
	glVertex3d (50, 50, 0);
	glVertex3d (50, 0, 0);
	glVertex3d (0, 0, 0);
	glEnd ();

	//water
	glEnable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture[1]);
	glPushMatrix ();
	glColor3f (0.0, 0.0, 1.0);
	glTranslated (15, 15, 0);
	glScalef (1, 1, 0.1);
	glutSolidCube (10);
	glPopMatrix ();
	glDisable (GL_TEXTURE_2D);
	//wall
	glPushMatrix ();
	glColor3f (1.0, 1.0, 1.0);
	glTranslatef (25, 25, 25);
	glutWireCube (50);
	glPopMatrix ();
	glutSwapBuffers ();
}
void init (int w, int h) {
	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (75, 1024.0 / 960.0, 1, 2000);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (fx, fy, fz, tox, toy, toz, 0.0, 0.0, 1.0);
	TextureInit ();
	lightinit ();
	glEnable (GL_DEPTH_TEST);
}

void SpecialKeys (int key, int x, int y) {

}


void fileload (const string &inputfile, vector<tinyobj::shape_t> &shapes, vector<tinyobj::material_t> &materials) {
	bool ret = tinyobj::LoadObj (shapes, materials, err, inputfile.c_str ());
	if (!err.empty ()) {
		std::cerr << err << std::endl;
	}
	if (!ret) {
		exit (1);
	}
}


void drawObj () {
	glColor3f (0.0, 0.9, 0.2);
	GLfloat bigsca;
	glBegin (GL_TRIANGLES);
	for (size_t k = 0; k < 4; ++k) {
		bigsca = 1.0*k / 2 + 1;
		for (size_t i = 0; i < tree_shapes.size (); i++) {
			for (size_t f = 0; f < tree_shapes[i].mesh.indices.size () / 3; f++) {
				int v0 = tree_shapes[i].mesh.indices[3 * f + 0];
				int v1 = tree_shapes[i].mesh.indices[3 * f + 1];
				int v2 = tree_shapes[i].mesh.indices[3 * f + 2];
				glNormal3f (tree_shapes[i].mesh.normals[3 * v0 + 0] * bigsca + tree_loc[k][0],
					tree_shapes[i].mesh.normals[3 * v0 + 1] * bigsca + tree_loc[k][1],
					tree_shapes[i].mesh.normals[3 * v0 + 2] * bigsca);
				glVertex3f (tree_shapes[i].mesh.positions[3 * v0 + 0] * bigsca + tree_loc[k][0],
					tree_shapes[i].mesh.positions[3 * v0 + 1] * bigsca + tree_loc[k][1],
					tree_shapes[i].mesh.positions[3 * v0 + 2] * bigsca);

				glVertex3f (tree_shapes[i].mesh.normals[3 * v1 + 0] * bigsca + tree_loc[k][0],
					tree_shapes[i].mesh.normals[3 * v1 + 1] * bigsca + tree_loc[k][1],
					tree_shapes[i].mesh.normals[3 * v1 + 2] * bigsca);
				glVertex3f (tree_shapes[i].mesh.positions[3 * v1 + 0] * bigsca + tree_loc[k][0],
					tree_shapes[i].mesh.positions[3 * v1 + 1] * bigsca + tree_loc[k][1],
					tree_shapes[i].mesh.positions[3 * v1 + 2] * bigsca);
				glVertex3f (tree_shapes[i].mesh.normals[3 * v2 + 0] * bigsca + tree_loc[k][0],
					tree_shapes[i].mesh.normals[3 * v2 + 1] * bigsca + tree_loc[k][1],
					tree_shapes[i].mesh.normals[3 * v2 + 2] * bigsca);
				glVertex3f (tree_shapes[i].mesh.positions[3 * v2 + 0] * bigsca + tree_loc[k][0],
					tree_shapes[i].mesh.positions[3 * v2 + 1] * bigsca + tree_loc[k][1],
					tree_shapes[i].mesh.positions[3 * v2 + 2] * bigsca);
			}
		}

	}
	glEnd ();
	//stone
	glColor3f (0.3, 0.3, 0.3);
	glBegin (GL_TRIANGLES);
	for (size_t k = 0; k < 4; ++k) {
		for (size_t i = 0; i < stone_shapes.size (); i++) {
			for (size_t f = 0; f < stone_shapes[i].mesh.indices.size () / 3; f++) {
				int v0 = stone_shapes[i].mesh.indices[3 * f + 0];
				int v1 = stone_shapes[i].mesh.indices[3 * f + 1];
				int v2 = stone_shapes[i].mesh.indices[3 * f + 2];
				glNormal3f (stone_shapes[i].mesh.normals[3 * v0 + 0] + stone_loc[k][0],
					stone_shapes[i].mesh.normals[3 * v0 + 1] + stone_loc[k][1],
					stone_shapes[i].mesh.normals[3 * v0 + 2]);
				glVertex3f (stone_shapes[i].mesh.positions[3 * v0 + 0] + stone_loc[k][0],
					stone_shapes[i].mesh.positions[3 * v0 + 1] + stone_loc[k][1],
					stone_shapes[i].mesh.positions[3 * v0 + 2]);

				glVertex3f (stone_shapes[i].mesh.normals[3 * v1 + 0] + stone_loc[k][0],
					stone_shapes[i].mesh.normals[3 * v1 + 1] + stone_loc[k][1],
					stone_shapes[i].mesh.normals[3 * v1 + 2]);
				glVertex3f (stone_shapes[i].mesh.positions[3 * v1 + 0] + stone_loc[k][0],
					stone_shapes[i].mesh.positions[3 * v1 + 1] + stone_loc[k][1],
					stone_shapes[i].mesh.positions[3 * v1 + 2]);

				glVertex3f (stone_shapes[i].mesh.normals[3 * v2 + 0] + stone_loc[k][0],
					stone_shapes[i].mesh.normals[3 * v2 + 1] + stone_loc[k][1],
					stone_shapes[i].mesh.normals[3 * v2 + 2]);
				glVertex3f (stone_shapes[i].mesh.positions[3 * v2 + 0] + stone_loc[k][0],
					stone_shapes[i].mesh.positions[3 * v2 + 1] + stone_loc[k][1],
					stone_shapes[i].mesh.positions[3 * v2 + 2]);
			}
		}
	}
	glEnd ();
}


void lightinit () {
	glEnable (GL_LIGHTING);
	GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 0.5f };
	GLfloat dif[] = { 0.3f, 0.3f, 0.3f, 0.5f };
	GLfloat spe[] = { 0.3f, 0.3f, 0.3f, 0.5f };
	GLfloat pos[] = { 25.0f, 25.0f,  100, 1.0f };
	glLightfv (GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv (GL_LIGHT0, GL_SPECULAR, spe);
	glLightfv (GL_LIGHT0, GL_POSITION, pos);
	glEnable (GL_LIGHT0);
	glEnable (GL_COLOR_MATERIAL);
}