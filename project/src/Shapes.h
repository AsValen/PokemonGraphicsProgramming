#pragma once
#include "MeshValues.h"
#include "angle_util/vector.h"
#include <vector>
#include "framework/texture/texture_utils.h"
#include "angle_util/matrix.h"

class Shapes
{

public :

	void CreateTriangle(const Vector3& diValues, const colorValues& colValues, bool flipTriangle = false);

	void CreateSquare(const Vector3& diValues, const colorValues& colValues, Texture2D* texture = NULL);

	void CreateDisk(const circleValues& cirValues, const colorValues& colValues, Texture2D* texture = NULL, bool flipDisk = false);

	void CreateCube(const Vector3& diValues, const colorValues& colValues, Texture2D* texture = NULL, const cubeFacesValues& cubeFaces = new cubeFacesValues);

	void CreateCylinder(const cylinderValues& cyValues, const colorValues& colValues, bool enableTopDisk = true, bool enableBottomDisk = true, Texture2D* cylinderTexture = NULL, Texture2D* diskTexture = NULL);

	void CreatePyramid(const Vector3& diValues, const colorValues& colValues, Texture2D* texture = NULL, bool bottomFace = true);

	void CreateSphere(const int& numLoops, const float& radius, const colorValues& colValues, const Matrix4& viewProjectionMatrix, Texture2D* texture = NULL);
};