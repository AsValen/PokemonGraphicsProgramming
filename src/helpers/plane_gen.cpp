#include "plane_gen.h"
#include <glad/glad.h>

// How to use
//
// Create instance of plane using Plane::create
// // Makes a 20x20 size plane, with UV repeating 5 times horizontal&vertical
// // and subdivided to 10x10 tiles
// Plane* p = Plane::create(Vector2(20,20), Vector2(5,5), 10);
//
// // Drawing the plane
// p->draw();

void Plane::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, positions.data());
	glColorPointer(3, GL_FLOAT, 0, colours.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());
	glNormalPointer(GL_FLOAT, 0, normals.data());

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

// Create a Plane given the parameters.
// static member function of a _class_ CAN access private member function of a _class instance_
Plane* Plane::create(Vector2 size, Vector2 tiling, int partitions)
{
	Plane* p = new Plane();

	// Create plane using tiling approach
	// Starting from bottom left (relative to default orientation)
	// Starting position is half of the size of the plane (so that the plane's centroid is 0,0,0)
	Vector2 start = Vector2(-size.x * 0.5f, size.y * 0.5f);

	Vector2 pos_part = Vector2(size.x / partitions, size.y / partitions);
	Vector2 uv_part = Vector2(tiling.x / partitions, tiling.y / partitions);

	for (int r = 0; r < partitions; r++) // row
	{
		for (int c = 0; c < partitions; c++) // column
		{
			Vector2 thisPart(c * pos_part.x, r * pos_part.y);
			Vector2 nextPart((c + 1) * pos_part.x, (r + 1) * pos_part.y);

			Vector2 thisUv(c * uv_part.x, r * uv_part.y);
			Vector2 nextUv((c + 1) * uv_part.x, (r + 1) * uv_part.y);

			p->positions.insert(p->positions.end(), {
					Vector3(start.x + thisPart.x, 0, start.y - thisPart.y), // Tri 1
					Vector3(start.x + nextPart.x, 0, start.y - thisPart.y), // Tri 1
					Vector3(start.x + nextPart.x, 0, start.y - nextPart.y), // Tri 1

					Vector3(start.x + nextPart.x, 0, start.y - nextPart.y), // Tri 2
					Vector3(start.x + thisPart.x, 0, start.y - nextPart.y), // Tri 2
					Vector3(start.x + thisPart.x, 0, start.y - thisPart.y)  // Tri 2
				});

			p->colours.insert(p->colours.end(), {
					1.0f,1.0f,1.0f, // Tri 1
					1.0f,1.0f,1.0f, // Tri 1
					1.0f,1.0f,1.0f, // Tri 1

					1.0f,1.0f,1.0f, // Tri 2
					1.0f,1.0f,1.0f, // Tri 2
					1.0f,1.0f,1.0f	// Tri 2
				});

			p->texCoords.insert(p->texCoords.end(), {
				thisUv.x, thisUv.y, // Tri 1
				nextUv.x, thisUv.y, // Tri 1
				nextUv.x, nextUv.y, // Tri 1

				nextUv.x, nextUv.y, // Tri 2
				thisUv.x, nextUv.y, // Tri 2
				thisUv.x, thisUv.y  // Tri 2
				});

			p->normals.insert(p->normals.end(), {
				0,1,0, // Tri 1
				0,1,0, // Tri 1
				0,1,0, // Tri 1

				0,1,0, // Tri 2
				0,1,0, // Tri 2
				0,1,0  // Tri 2
				});
		}
	}

	// because positions are stored as Vector3 packs, the amount of vertices is the array count.
	// if positions are stored as individual floats, the amount of vertices is the array count divided by 3
	p->vertexCount = p->positions.size();

	return p;
}