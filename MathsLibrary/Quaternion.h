#pragma once
#include "Vector.h"
#include "Matrix.h"

class Quaternion {
public:
	float x, y, z, w;
	
	Quaternion() = default;
	Quaternion(float a, float b, float c, float s) {
		x = a; y = b; z = c;
		w = s;
	}
	Quaternion(const Vector3& v, float s) {
		x = v.x; y = v.y; z = v.z;
		w = s;
	}

	const Vector3& GetVectorPart() const { return reinterpret_cast<const Vector3&>(x); }
};

Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(
		q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
		q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
		q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
		q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
}