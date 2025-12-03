//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Edited 13/10/2021 @Faris
//  - reworked operator overloads.
//  - added +=, -=, *=, /=, -unary
//  - added instance-based normalized, length and lengthSquared
//  - added Vector4 ctor that takes Vector3 and w.
//
// Edited 21/09/2023 @Faris
//  - added operator overloads for Vector2

#ifndef SAMPLE_UTIL_VECTOR_H
#define SAMPLE_UTIL_VECTOR_H

struct Vector2
{
	union
	{
		struct
		{
			float x, y;
		};
		float data[2];
	};

	Vector2();
	Vector2(float x, float y);

	static float length(const Vector2& vec);
	static float lengthSquared(const Vector2& vec);

	static Vector2 normalize(const Vector2& vec);

	Vector2 operator*(const Vector2& other);
	Vector2 operator*(const float& other);
	Vector2 operator/(const Vector2& other);
	Vector2 operator/(const float& other);
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator-() const;
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(const Vector2& other);
	Vector2& operator*=(const float& other);
	Vector2& operator/=(const Vector2& other);
	Vector2& operator/=(const float& other);
};

struct Vector3
{
	union
	{
		struct
		{
			float x, y, z;
		};
		float data[3];
	};

	Vector3();
	Vector3(float x, float y, float z);

	void normalize();
	float length();
	float lengthSquared();

	static float length(const Vector3& vec);
	static float lengthSquared(const Vector3& vec);
	static Vector3 normalize(const Vector3& vec);
	static float dot(const Vector3& a, const Vector3& b);
	static Vector3 cross(const Vector3& a, const Vector3& b);

	Vector3 operator*(const Vector3& other);
	Vector3 operator*(const float& other);
	Vector3 operator/(const Vector3& other);
	Vector3 operator/(const float& other);
	Vector3 operator+(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	Vector3 operator-() const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const Vector3& other);
	Vector3& operator*=(const float& other);
	Vector3& operator/=(const Vector3& other);
	Vector3& operator/=(const float& other);
};

struct Vector4
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float data[4];
	};

	Vector4();
	Vector4(const Vector3& vec, float w);
	Vector4(float x, float y, float z, float w);

	static float length(const Vector4& vec);
	static float lengthSquared(const Vector4& vec);

	static Vector4 normalize(const Vector4& vec);

	static float dot(const Vector4& a, const Vector4& b);
};

#endif // SAMPLE_UTIL_VECTOR_H
