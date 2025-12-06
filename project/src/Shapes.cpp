#include "Shapes.h" 
#include <glad/glad.h> 
#include "angle_util/vector.h"
#include <vector>
#include "framework/texture/texture_utils.h"
#include <corecrt_math_defines.h>
#include "Cylindroid.h"
#include "angle_util/matrix.h"

void Shapes::CreateTriangle(const Vector3& diValues, const colorValues& colValues, bool flipTriangle)
{
	float x = diValues.x;
	float y = diValues.y;
	float z = diValues.z;

	float r = colValues.r;
	float g = colValues.g;
	float b = colValues.b;
	float a = colValues.a;

	if (x < 0 || y < 0 || z < 0) return;

	glBegin(GL_TRIANGLES);

		glColor4f(r, g, b, a);

		if (!flipTriangle)
		{
			glVertex3f(0, 0, z);
			glVertex3f(x, 0, z);
			glVertex3f(x, y, z);
		}
		else
		{
			glVertex3f(x, y, z);
			glVertex3f(0, y, z);
			glVertex3f(0, 0, z);
		}
	glEnd();
}

void Shapes::CreateSquare(const Vector3& diValues, const colorValues& colValues, Texture2D* texture)
{
	float x = diValues.x;
	float y = diValues.y;
	float z = diValues.z;

	float r = colValues.r;
	float g = colValues.g;
	float b = colValues.b;
	float a = colValues.a;

    if (x < 0 || y < 0 || z < 0) return;

    std::vector<Vector3> position = {
        Vector3(0.0f,  0.0f, z),
        Vector3(x,  0.0f, z),
        Vector3(x,  y, z),
        Vector3(0.0f, y, z)
    };

    std::vector<Vector4> colour = {
        Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a)
    };

    std::vector<Vector2> texCoord = {
        Vector2(0.0f, 0.0f),
        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(0.0f, 1.0f),
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, // Left top triangle
        2, 3, 0, // Left bottom triangle
    };


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, position.data());
    glColorPointer(4, GL_FLOAT, 0, colour.data());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoord.data());

    if (texture != NULL)
    {
        glBindTexture(GL_TEXTURE_2D, texture->getNativeHandle());
    }

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

    glDisable(GL_ALPHA_TEST);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shapes::CreateDisk(const circleValues& cirValues, const colorValues& colValues, Texture2D* texture, bool flipDisk)
{
	float outRad = cirValues.outerRadius;
	float inRad = cirValues.innerRadius;
	int slices = cirValues.slices;
	float height = cirValues.height;
	float squash = cirValues.squash;

	float r = colValues.r;
	float g = colValues.g;
	float b = colValues.b;
	float a = colValues.a;

	if (outRad <= 0 || inRad < 0 || slices < 8) return;
	if (inRad >= outRad) return;

	float anglePerSlice = 2 * M_PI / slices;

	if (texture != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getNativeHandle());
	}

	// Does not require index buffer because the current draw structure GL_TRIANGLE_STRIP already reuses vertices quite efficiently
	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(r, g, b, a);

	for (int i = 0; i <= slices; i++)
	{
		float theta = anglePerSlice * i;
		float xOuter = cos(theta) * outRad;
		float zOuter = (sin(theta) * outRad) * squash;

		float uOuter = (xOuter / (2 * outRad)) + 0.5f;
		float vOuter = (zOuter / (2 * outRad)) + 0.5f;

		if (flipDisk) 
		{
			glTexCoord2f(uOuter, vOuter);
			glVertex3f(xOuter, height, zOuter);
		}

		if (inRad != 0)
		{
			float xInner = cos(theta) * inRad;
			float zInner = (sin(theta) * inRad) * squash;

			float uInner = (xInner / (2 * outRad)) + 0.5f;
			float vInner = (zInner / (2 * outRad)) + 0.5f;

			glTexCoord2f(uInner, vInner);
			glVertex3f(xInner, height, zInner);
		}
		else
		{
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0, height, 0);
		}

		if (!flipDisk)
		{
			glTexCoord2f(uOuter, vOuter);
			glVertex3f(xOuter, height, zOuter);
		}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Shapes::CreateCube(const Vector3& diValues, const colorValues& colValues)
{
	float x = diValues.x;
	float y = diValues.y;
	float z = diValues.z;

	float r = colValues.r;
	float g = colValues.g;
	float b = colValues.b;
	float a = colValues.a;

	if (x <= 0 || y <= 0 || z <= 0) return;

	std::vector<Vector3> position = {

		// bottom square position
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(x, 0.0f, 0.0f),
		Vector3(x, 0.0f, -z),
		Vector3(0.0f, 0.0f, -z),

		// top square position
		Vector3(0.0f, y, 0.0f),
		Vector3(x, y, 0.0f),
		Vector3(x, y, -z),
		Vector3(0.0f, y, -z)
	};

	std::vector<Vector4> colour = {
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),

		Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a)
	};

	std::vector<unsigned int> indices = {
		// bottom square
		3, 2, 1, 
		1, 0, 3, 

		// front square
		0, 1, 5,
		5, 4, 0,

		// back square
		2, 3, 7,
		7, 6, 2,

		// left square
		3, 0, 4,
		4, 7, 3,

		// right square
		1, 2, 6,
		6, 5, 1,

		// top square
		4, 5, 6,
		6, 7, 4

	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, position.data());
	glColorPointer(4, GL_FLOAT, 0, colour.data());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisable(GL_BLEND);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void Shapes::CreateCylinder(const cylinderValues& cyValues, const colorValues& colValues, bool enableTopDisk, bool enableBottomDisk)
{
	float topRadius = cyValues.topRadius;
	float bottomRadius = cyValues.bottomRadius;
	int slices = cyValues.slices;
	float height = cyValues.height;
	float squash = cyValues.squash;

	float r = colValues.r;
	float g = colValues.g;
	float b = colValues.b;
	float a = colValues.a;

	if (slices < 8 || height <= 0) return;
	if (topRadius == 0 && bottomRadius == 0) return;

	float anglePerSlice = 2 * M_PI / slices;

	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(r, g, b, a);

	for (int i = 0; i <= slices; i++)
	{
		float theta = anglePerSlice * i;

		float xBot = cos(theta) * bottomRadius;
		float zBot = (sin(theta) * bottomRadius) * squash;
		glVertex3f(xBot, 0, zBot);

		float xTop = cos(theta) * topRadius;
		float zTop = (sin(theta) * topRadius) * squash;
		glVertex3f(xTop, height, zTop);
	}
	glEnd();

	// Bottom disk
	if (bottomRadius != 0 && enableBottomDisk)
	{
		CreateDisk(circleValues(slices, bottomRadius, 0, 0.0f, squash), colValues, NULL);
	}

	// Top disk
	if (topRadius != 0 && enableTopDisk)
	{
		CreateDisk(circleValues(slices, topRadius, 0, height, squash), colValues, NULL, true);
	}
}

void Shapes::CreatePyramid(const Vector3& diValues, const colorValues& colValues)
{
	float x = diValues.x;
	float y = diValues.y;
	float z = diValues.z;

	float r = colValues.r;
	float g = colValues.g;
	float b = colValues.b;
	float a = colValues.a;

	if (x <= 0 || y <= 0 || z <= 0) return;

	std::vector<Vector3> position = {

		// bottom square position
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(x, 0.0f, 0.0f),
		Vector3(x, 0.0f, -z),
		Vector3(0.0f, 0.0f, -z),

		// top tip
		Vector3(x * 0.5f, y, -z * 0.5f)
	};

	std::vector<Vector4> colour = {
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),
		Vector4(r, g, b, a),

		Vector4(r, g, b, a)
	};

	std::vector<unsigned int> indices = {
		// bottom square
		3, 2, 1,
		1, 0, 3,

		// front face
		0, 1, 4,

		// back face
		2, 3, 4,

		// left face
		3, 0, 4,

		// right face
		1, 2, 4
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, position.data());
	glColorPointer(4, GL_FLOAT, 0, colour.data());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisable(GL_BLEND);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void Shapes::CreateSphere(const float& radius, const colorValues& colValues, const Matrix4& viewProjectionMatrix)
{
	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(0.0f, 0.0f));
	loops.push_back(cylindroidLoopValues(radius * 0.5f, 2.0f));
	loops.push_back(cylindroidLoopValues(radius, 3.5f));
	loops.push_back(cylindroidLoopValues(radius * 0.5f, 5.0f));
	loops.push_back(cylindroidLoopValues(0.0f, 5.3f));

	Cylindroid* sphere = new Cylindroid(8.0f, loops, viewProjectionMatrix, colValues);
	sphere->draw();
}