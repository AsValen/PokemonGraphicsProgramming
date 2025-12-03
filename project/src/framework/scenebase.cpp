#include "scenebase.h"
#include <glad/glad.h>

void SceneBase::drawWorldOriginLines()
{
	glPushAttrib(GL_LINE_BIT);
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	glColor3f(1.0f, 0.3f, 0.3f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.3f, 1.0f, 0.3f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.3f, 0.3f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();

	glPopAttrib();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void SceneBase::drawHorizontalGridLines() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDepthFunc(GL_LESS);
	glLineWidth(1.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	for (int i = -5; i <= 5; i++) {
		glVertex3f(i, 0.0f, -5.0f);
		glVertex3f(i, 0.0f, 5.0f);
		glVertex3f(-5.0f, 0.0f, i);
		glVertex3f(5.0f, 0.0f, i);
	}
	glEnd();

	glDepthFunc(GL_LEQUAL);
	glPopAttrib();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void SceneBase::drawVerticalGridLines() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDepthFunc(GL_LESS);
	glLineWidth(1.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	for (int i = -5; i <= 5; i++) {
		glVertex3f(i, -5.0f, 0.0f);
		glVertex3f(i, 5.0f, 0.0f);
		glVertex3f(-5.0f, i, 0.0f);
		glVertex3f(5.0f, i, 0.0f);
	}
	glEnd();

	glPopAttrib();

	glColor3f(1.0f, 1.0f, 1.0f);
}