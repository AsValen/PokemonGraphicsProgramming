#pragma once
#include <vector>
#include "../angle_util/vector.h"

class Plane
{
private:

	// Constructor is private to disallow creating Plane using 'new' keyword
	// Why? A choice.
	// Also to show Factory pattern
	Plane() : vertexCount(0) {};

	std::vector<Vector3> positions;		// data can be stored as VectorX packs instead of individual floats
	std::vector<float> colours;			// for example purposes, I'm storing colours, UV and normals as individual floats
	std::vector<float> texCoords;		// while for position I'm using Vector3
	std::vector<float> normals;			// Note: This is possible because VectorX data structure is X floats in sequential order!
	unsigned int vertexCount;

public:

	// To draw a plane, call this member function
	void draw();

	// To create a Plane, use this factory function instead
	static Plane* create(Vector2 size, Vector2 tiling, int partitions);
};

// How to use
//
// // Makes a 20x20 size plane, with UV repeating 5 times horizontal&vertical
// // and subdivided to 10x10 tiles
// Plane* p = Plane::create(Vector2(20,20), Vector2(5,5), 10);
//
// // Drawing the plane
// p->draw();