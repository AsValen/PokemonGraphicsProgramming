#include "Shapes.h" 
#include <glad/glad.h> 
#include "angle_util/vector.h"
#include <vector>
#include "framework/texture/texture_utils.h"
#include <corecrt_math_defines.h>
#include "Cylindroid.h"
#include "angle_util/matrix.h"

Texture2D* texture;

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

    if (x < 0.0f || y < 0.0f || z < 0.0f) return;

    std::vector<Vector3> position = {
		{0.0f,  0.0f, z},
		{x,  0.0f, z},
		{x,  y, z},
		{0.0f, y, z}
    };

	std::vector<Vector4> colour;

	for (int i = 0; i < position.size(); i++)
	{
		colour.push_back(Vector4(r, g, b, a));
	}

    std::vector<Vector2> texCoord = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
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
		glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->getNativeHandle());
    }


    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

    glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
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

	if (outRad <= 0.0f || inRad < 0.0f || slices < 8) return;
	if (inRad >= outRad) return;

	float anglePerSlice = 2 * M_PI / slices;

	if (texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
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
	glDisable(GL_TEXTURE_2D);

}

void Shapes::CreateCube(const Vector3& diValues, const colorValues& colValues, Texture2D* texture, const cubeFacesValues& cubeFaces )
{
	float x = diValues.x;
	float y = diValues.y;
	float z = diValues.z;

	float r = colValues.r;
	float g = colValues.g;
	float b = colValues.b;
	float a = colValues.a;

	if (x <= 0.0f || y <= 0.0f || z <= 0.0f) return;

	std::vector<Vector3> position = {

		// FRONT
	   {0, 0, 0}, {x, 0, 0}, {x, y, 0}, {0, y, 0},

	   // BACK
	   {x, 0, -z}, {0, 0, -z}, {0, y, -z}, {x, y, -z},

	   // LEFT
	   {0, 0, -z}, {0, 0, 0}, {0, y, 0}, {0, y, -z},

	   // RIGHT
	   {x, 0, 0}, {x, 0, -z}, {x, y, -z}, {x, y, 0},

	   // TOP
	   {0, y, 0}, {x, y, 0}, {x, y, -z}, {0, y, -z},

	   // BOTTOM
	   {0, 0, -z}, {x, 0, -z}, {x, 0, 0}, {0, 0, 0}
	};

	std::vector<Vector4> colour;

	for (int i = 0; i < position.size(); i++)
	{
		colour.push_back(Vector4(r, g, b, a));
	}

	std::vector<Vector2> texCoord = {
		// FRONT 
		{0,0}, {1,0}, {1,1}, {0,1}, 
		// BACK 
		{0,0}, {1,0}, {1,1}, {0,1}, 
		// LEFT 
		{0,0}, {1,0}, {1,1}, {0,1}, 
		// RIGHT 
		{0,0}, {1,0}, {1,1}, {0,1}, 
		// TOP 
		{0,0}, {1,0}, {1,1}, {0,1}, 
		// BOTTOM 
		{0,0}, {1,0}, {1,1}, {0,1},
	};

	std::vector<unsigned int> indices;

	if (cubeFaces.front)
	{
		indices.insert(indices.end(), {
			0,1,2,  2,3,0,
		});
	}

	if (cubeFaces.back)
	{
		indices.insert(indices.end(), {
			4,5,6,  6,7,4,
		});
	}

	if (cubeFaces.left)
	{
		indices.insert(indices.end(), {
			8,9,10, 10,11,8,
		});
	}

	if (cubeFaces.right)
	{
		indices.insert(indices.end(), {
			12,13,14, 14,15,12,
		});
	}

	if (cubeFaces.top)
	{
		indices.insert(indices.end(), {
			16,17,18, 18,19,16,
		});
	}

	if (cubeFaces.bottom)
	{
		indices.insert(indices.end(), {
			 20,21,22, 22,23,20
		});
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, position.data());
	glColorPointer(4, GL_FLOAT, 0, colour.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord.data());

	if (texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->getNativeHandle());
	}

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shapes::CreateCylinder(const cylinderValues& cyValues, const colorValues& colValues, bool enableTopDisk, bool enableBottomDisk, Texture2D* cylinderTexture, Texture2D* diskTexture)
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

	if (cylinderTexture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cylinderTexture->getNativeHandle());
	}

	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(r, g, b, a);

	for (int i = 0; i <= slices; i++)
	{
		float theta = anglePerSlice * i;

		float xBot = (cos(theta) * bottomRadius);
		float zBot = (sin(theta) * bottomRadius) * squash;

		float u = (float)i / slices;
		float vBot = 0.0f; 
		float vTop = 1.0f; 

		glTexCoord2f(u, vBot);
		glVertex3f(xBot, 0, zBot);

		float xTop = (cos(theta) * topRadius);
		float zTop = (sin(theta) * topRadius) * squash;
		glTexCoord2f(u, vTop);
		glVertex3f(xTop, height, zTop);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	if(diskTexture == NULL)
	{
		diskTexture = cylinderTexture;
	}

	// Bottom disk
	if (bottomRadius != 0 && enableBottomDisk)
	{
		CreateDisk(circleValues(slices, bottomRadius, 0, 0.0f, squash), colValues, diskTexture);
	}

	// Top disk
	if (topRadius != 0 && enableTopDisk)
	{
		CreateDisk(circleValues(slices, topRadius, 0, height, squash), colValues, diskTexture, true);
	}
}

void Shapes::CreatePyramid(const Vector3& diValues, const colorValues& colValues, Texture2D* texture, bool bottomFace)
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

		// Side 1 (front)
		{0.0f, 0.0f, 0.0f},
		{x, 0.0f, 0.0f},
		{x * 0.5f, y, -z * 0.5f},

		// Side 2 (right)
		{x, 0.0f, 0.0f},
		{x, 0.0f, -z},
		{x * 0.5f, y, -z * 0.5f},

		// Side 3 (back)
		{x, 0.0f, -z},
		{0.0f, 0.0f, -z},
		{x * 0.5f, y, -z * 0.5f},

		// Side 4 (left)
		{0.0f, 0.0f, -z},
		{0.0f, 0.0f, 0.0f},
		{x * 0.5f, y, -z * 0.5f},

		// Bottom face (optional)
		{0.0f, 0.0f, 0.0f},
		{x, 0.0f, 0.0f},
		{x, 0.0f, -z},
		{0.0f, 0.0f, -z}
	};

	std::vector<Vector4> colour;

	for (int i = 0; i < position.size(); i++)
	{
		colour.push_back(Vector4(r, g, b, a));
	}

	std::vector<Vector2> texCoord = {
		// front
		{0,0}, {1,0}, {0.5f,1},
		// right
		{0,0}, {1,0}, {0.5f,1},
		// back
		{0,0}, {1,0}, {0.5f,1},
		// left
		{0,0}, {1,0}, {0.5f,1},
		// bottom
		{0,0}, {1,0}, {1,1}, {0,1}
	};

	std::vector<unsigned int> indices = {
		// sides
		0,1,2,     // front
		3,4,5,     // right
		6,7,8,     // back
		9,10,11,   // left
	};

	// bottom face (optional)
	if (bottomFace)
	{
		indices.insert(indices.end(), {
			15,14,13,  
			13,12,15    
		});
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, position.data());
	glColorPointer(4, GL_FLOAT, 0, colour.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord.data());

	if (texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->getNativeHandle());
	}

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shapes::CreateSphere(const int& numLoops, const float& radius, const colorValues& colValues, const Matrix4& viewProjectionMatrix, Texture2D* texture)
{
	std::vector<cylindroidLoopValues> loops;

	float R = radius;

	for (int i = 0; i <= numLoops; ++i)
	{
		float t = float(i) / numLoops;        // 0 to 1
		float y = t * 2.0f * R;               // 0 to 2*R (bottom to top)
		float r = sqrt(R * R - (y - R) * (y - R)); // radius at this height

		loops.push_back(cylindroidLoopValues(r, y));
	}

	Cylindroid* sphere = new Cylindroid(8.0f, loops, viewProjectionMatrix, colValues, texture);
	sphere->draw();
}