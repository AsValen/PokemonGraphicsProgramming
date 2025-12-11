#pragma once
#include <vector>
#include <glad/glad.h>
#include "framework/texture/texture_utils.h"
#include "angle_util/vector.h"
#include <stdexcept>
#include "Transform.h"
#include "MeshValues.h"

#include <iostream>
using namespace std;


struct cylindroidLoopValues
{
	float radius;
	float height;
	Vector3 offset;
	Vector3 rotation;
	float squish;

	cylindroidLoopValues(float radius, float height, Vector3 offset = Vector3(0.0f, 0.0f, 0.0f), Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f), float squish = 1.0f) : radius(radius), height(height), offset(offset), rotation(rotation), squish(squish)
	{
	}
};

class Cylindroid
{
public:

	Vector3 getEndPosition() const { return endPosition; }

	Cylindroid(int segments, std::vector<cylindroidLoopValues> loops, Matrix4 viewProjectionMatrix, colorValues colour, Texture2D* texture = NULL)
	{
		if (segments < 3) throw std::invalid_argument("segments < 3");
		if (loops.size() < 1) throw std::invalid_argument("loop size < 1");
		meshColour = colour;
		meshTexture = texture;
		setup(segments, loops, viewProjectionMatrix);
	}

	void draw()
	{
		glColor4f(meshColour.r, meshColour.g, meshColour.b, meshColour.a);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glPointSize(8.0f);
		glVertexPointer(3, GL_FLOAT, 0, positions.data());
		glColorPointer(4, GL_FLOAT, 0, colours.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());

		if (meshTexture != NULL)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, meshTexture->getNativeHandle());
		}

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

private:

	colorValues meshColour;
	Texture2D* meshTexture;
	std::vector<Vector3> positions;
	std::vector<colorValues> colours;
	std::vector<Vector2> texCoords;
	std::vector<unsigned int> indices;
	Vector3 endPosition;

	void setup( int segments, std::vector<cylindroidLoopValues> loops, Matrix4 viewProjectionMatrix)
	{

		// from tutorial 2, but this time also following buffer approach
		float anglePerSlice = 6.283184 / segments;
		for (int i = 0; i < loops.size(); i++)
		{
			cylindroidLoopValues sliceData = loops[i];

			Transform loop;
			loop.setRotation(sliceData.rotation.x, sliceData.rotation.y, sliceData.rotation.z);
			loop.getMatrix();

			for (int j = 0; j < segments; j++)
			{
				float theta = anglePerSlice * j;

				Vector3 pLocal(
					(cos(theta) * sliceData.radius),
					sliceData.height,
					((sin(theta) * sliceData.radius) * sliceData.squish)
				);

				Vector3 pWorld = loop.transformPoint(pLocal);

				pWorld.x += sliceData.offset.x;
				pWorld.y += sliceData.offset.y;
				pWorld.z += sliceData.offset.z;

				positions.push_back(Vector3(pWorld));	

				//if (j == 0)
				//{
				//	colours.push_back(colorValues(1.0f, 1.0f, 1.0f, 1.0f));
				//}
				//else {
				//	colours.push_back(colorValues(0.5f, 0.5f, 0.5f, 1.0f));
				//}
				colours.push_back(colorValues(meshColour.r, meshColour.g, meshColour.b, meshColour.a));


				if(meshTexture != NULL)
				{
					float u = (float)j / (segments - 1);
					//std::cout << "u: " << u << std::endl;
					float v = (float)i / (loops.size() - 1);
					//std::cout << "v: " << v << std::endl;
					texCoords.push_back(Vector2(u, v));
				}
			}

			// This is just for getting the avg position of the last loop
			if (i == loops.size() - 1)
			{
				// the last loop (the one at the hand)

				// compute "center" of the slice
				// average of all 8 points
				Vector3 avg(0, 0, 0);
				for (int j = 0; j < segments; j++)
				{
					avg += positions[i * segments + j];
				}
				avg /= segments;

				endPosition = avg;
			}
		}

		// bridge the loops
		// right now we have 2 loops, so need to do 1 time hence no outer loop yet

		int loopCount = loops.size() - 1;

		for (int i = 0; i < loopCount; i++)
		{
			int offset = i * segments;

			for (int j = 0; j < segments; j++)
			{

				// edge case: connecting from 2nd last to first
				int idx = offset + j;
				int idxNext = offset + (j + 1) % segments;

				// tri 1
				indices.push_back(idx);
				indices.push_back(idx + segments);
				indices.push_back(idxNext);

				// tri2	
				indices.push_back(idx + segments);
				indices.push_back(idxNext + segments);
				indices.push_back(idxNext);
			}
		}

	}
};
