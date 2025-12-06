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


	inline void translateBy(float tx, float ty, float tz)
	{

		position.x += tx;
		position.y += ty;
		position.z += tz;

		isDirty = true;
	}

	inline void setPosition(float tx, float ty, float tz)
	{
		position.x = tx;
		position.y = ty;
		position.z = tz;

		isDirty = true;
	}

	inline void rotateXBy(float xDegree)
	{
		rotation.x += xDegree;

		isDirty = true;
	}

	inline void rotateYBy(float yDegree)
	{
		rotation.y += yDegree;

		isDirty = true;
	}

	inline void rotateZBy(float zDegree)
	{
		rotation.z += zDegree;

		isDirty = true;
	}

	inline void rotateBy(float xDegree, float yDegree, float zDegree)
	{
		rotation.x += xDegree;
		rotation.y += yDegree;
		rotation.z += zDegree;

		isDirty = true;
	}

	inline void setRotation(float xDegree, float yDegree, float zDegree)
	{
		rotation.x = xDegree;
		rotation.y = yDegree;
		rotation.z = zDegree;

		isDirty = true;
	}

	inline void setScale(float sx, float sy, float sz)
	{
		scale.x = sx;
		scale.y = sy;
		scale.z = sz;

		isDirty = true;
	}

	inline Vector3 transformPoint( const Vector3& p)
	{
		return Vector3(
			matrix.data[0] * p.x + matrix.data[4] * p.y + matrix.data[8] * p.z,
			matrix.data[1] * p.x + matrix. data[5] * p.y + matrix.data[9] * p.z,
			matrix.data[2] * p.x + matrix.data[6] * p.y + matrix.data[10] * p.z
		);
	}

	// inline helps avoid declaration error if this .h file is being used in multiple cpp file
	// first const means that the caller cannot modify the returned matrix through this reference
	// second const means that Function promises not to modify the object (except mutable members)
	inline const Matrix4& getMatrix() const
	{
		if (isDirty)
		{

			matrix = Matrix4::translate(position)
				* Matrix4::rotate(rotation.z, Vector3(0.0f, 0.0f, 1.0f))
				* Matrix4::rotate(rotation.y, Vector3(0.0f, 1.0f, 0.0f))
				* Matrix4::rotate(rotation.x, Vector3(1.0f, 0.0f, 0.0f))
				* Matrix4::scale(scale);

			isDirty = false;
		}

		return matrix;
	}
};