#include <vector>
#include <glad/glad.h>
#include "depth_visualizer.h"

bool DepthVisualizer::RENDER_DEPTH = false;

void DepthVisualizer::render(float zNear, float zFar)
{
	if (!RENDER_DEPTH) return;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_TEXTURE_2D);

	static int vp[4] = { 0,0,0,0 };
	glGetIntegerv(GL_VIEWPORT, &vp[0]);
	int w = vp[2], h = vp[3];

	std::vector<float> depth(w * h, 0);
	glReadPixels(0, 0, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, &depth[0]);

	// Normalize the depth values from (zNear ~ zFar) to (0 ~ 1)
	for (size_t i = 0; i < depth.size(); ++i)
	{
		depth[i] = (2.0f * zNear) / (zFar + zNear - depth[i] * (zFar - zNear));
	}

	static unsigned int tex = 0;
	if (tex == 0)
	{
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w, h, 0, GL_LUMINANCE, GL_FLOAT, &depth[0]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, tex);
		// replace data instead of creating new texture for optimization
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_LUMINANCE, GL_FLOAT, &depth[0]);
	}

	// Revert matrix to default to make -1 ~ 1 in XY
	// to be from bottom left corner to upper right corner
	// Before reverting, save the current matrix so
	// we can return to it.
	static float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(-1, -1);
	glTexCoord2i(1, 0); glVertex2i(1, -1);
	glTexCoord2i(1, 1); glVertex2i(1, 1);
	glTexCoord2i(0, 1); glVertex2i(-1, 1);
	glEnd();
	glLoadMatrixf(m);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopAttrib();
}