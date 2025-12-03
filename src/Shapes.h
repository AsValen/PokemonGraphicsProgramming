#pragma once
#include "MeshValues.h"
#include "angle_util/vector.h"
#include <vector>
#include "framework/texture/texture_utils.h"

class Shapes
{

public :

	void CreateTriangle(const Vector3& diValues, const colorValues& colValues, bool flipTriangle = false);

	void CreateSquare(const Vector3& diValues, const colorValues& colValues, Texture2D* texture);

	void CreateDisk(const circleValues& cirValues, const colorValues& colValues, Texture2D* texture, bool flipDisk = false);

	void CreateCube(const Vector3& diValues, const colorValues& colValues);

	void CreateCylinder(const cylinderValues& cyValues, const colorValues& colValues, bool enableTopDisk = true, bool enableBottomDisk = true);

	void CreatePyramid(const Vector3& diValues, const colorValues& colValues);
};