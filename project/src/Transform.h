#pragma once
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

class Transform
{
private:
	Vector3 position;	// default ctor makes zero vector.
	Vector3 rotation;	// default ctor makes zero vector.
	Vector3 scale;		// default ctor makes zero vector.

	mutable Matrix4 matrix;		// default ctor makes identity matrix.
	mutable bool isDirty = false;
public:

	// Default ctor
	Transform() :position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), isDirty(true) {}

	// Other custom ctor, DIY
	//Transform(Vector3 t, Vector3 r, Vector3 s) {}

	inline const Vector3 getPosition()
	{
		return position;
	}

	inline const Vector3 getRotation()
	{
		return rotation;
	}

	inline const Vector3 getScale()
	{
		return scale;
	}

	// @COMPLETE THIS
	void translateBy(float tx, float ty, float tz)
	{
		// Add to position
		position.x += tx;
		position.y += ty;
		position.z += tz;
		// the rest...

		// Set isDirty to true
		isDirty = true;
	}

	// @COMPLETE THIS
	void setPosition(float tx, float ty, float tz)
	{
		position.x = tx;
		position.y = ty;
		position.z = tz;

		isDirty = true;
		// Set values to position
		// Set isDirty to true
	}

	// @COMPLETE THIS
	void rotateXBy(float xDegree)
	{
		rotation.x += xDegree;

		isDirty = true;

		// Add to x rotation
		// Set isDirty to true
	}

	// @COMPLETE THIS
	void rotateYBy(float yDegree)
	{
		rotation.y += yDegree;

		isDirty = true;
		// Add to y rotation
		// Set isDirty to true
	}

	// @COMPLETE THIS
	void rotateZBy(float zDegree)
	{
		rotation.z += zDegree;

		isDirty = true;
		// Add to z rotation
		// Set isDirty to true
	}

	// @COMPLETE THIS
	void rotateBy(float xDegree, float yDegree, float zDegree)
	{
		rotation.x += xDegree;
		rotation.y += yDegree;
		rotation.z += zDegree;

		isDirty = true;
		// Add to rotation
		// Set isDirty to true
	}

	// @COMPLETE THIS
	void setRotation(float xDegree, float yDegree, float zDegree)
	{
		rotation.x = xDegree;
		rotation.y = yDegree;
		rotation.z = zDegree;

		isDirty = true;
		// Set values to rotation
		// Set isDirty to true
	}

	// @COMPLETE THIS
	void setScale(float sx, float sy, float sz)
	{
		scale.x = sx;
		scale.y = sy;
		scale.z = sz;

		isDirty = true;
		// Set values to scale
		// Set isDirty to true
	}

	inline const Matrix4& getMatrix() const
	{
		// If isDirty, recalculate matrix and unset the bool

		if (isDirty)
		{
			// @COMPLETE THIS
			// Recalculate by:
			// 1. Scale first
			// 2. Rotate Z-angle by Z-axis
			// 3. Rotate Y-angle by Y-axis
			// 4. Rotate X-angle by X-axis
			// 5. Translate



			matrix = Matrix4::translate(position)
				* Matrix4::rotate(rotation.z, Vector3(0.0f, 0.0f, 1.0f))
				* Matrix4::rotate(rotation.y, Vector3(0.0f, 1.0f, 0.0f))
				* Matrix4::rotate(rotation.x, Vector3(1.0f, 0.0f, 0.0f))
				* Matrix4::scale(scale);

			isDirty = false;
		}

		return matrix;
	}

	// Overloaded versions, DIY if you want
	//void translate(Vector3 translate)
	//{
	//}

	// and the rest...
};