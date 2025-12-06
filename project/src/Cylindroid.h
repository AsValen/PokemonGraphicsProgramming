#pragma once
#include <vector>
#include <glad/glad.h>
#include "framework/texture/texture_utils.h"
#include "angle_util/vector.h"
#include <stdexcept>
#include "Transform.h"
#include "MeshValues.h"


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

	Cylindroid(int segments, std::vector<cylindroidLoopValues> loops, Matrix4 viewProjectionMatrix, colorValues colour)
	{
		if (segments < 3) throw std::invalid_argument("segments < 3");
		if (loops.size() < 1) throw std::invalid_argument("loop size < 1");
		meshColour = colour;
		setup(segments, loops, viewProjectionMatrix);
	}

	void draw()
	{
		glColor4f(meshColour.r, meshColour.g, meshColour.b, meshColour.a);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPointSize(8.0f);
		glVertexPointer(3, GL_FLOAT, 0, positions.data());
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
		glDisableClientState(GL_VERTEX_ARRAY);
	}

private:

	colorValues meshColour;
	std::vector<Vector3> positions;
	std::vector<Vector2> texCoords;
	std::vector<unsigned int> indices;

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
