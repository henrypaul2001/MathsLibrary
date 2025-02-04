#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <math.h>
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

	Matrix3x3 GetRotationMatrix() {
		float x2 = x * x;
		float y2 = y * y;
		float z2 = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		return Matrix3x3(1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy),
						 2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx),
						 2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2));
	}

	void SetRotationMatrix(const Matrix3x3& m) {
		float m00 = m(0, 0);
		float m11 = m(1, 1);
		float m22 = m(2, 2);
		float sum = m00 + m11 + m22;

		if (sum > 0.0F)
		{
			w = sqrt(sum + 1.0F) * 0.5F;
			float f = 0.25F / w;

			x = (m(2, 1) - m(1, 2)) * f;
			y = (m(0, 2) - m(2, 0)) * f;
			z = (m(1, 0) - m(0, 1)) * f;
		}
		else if ((m00 > m11) && (m00 > m22))
		{
			x = sqrt(m00 - m11 - m22 + 1.0F) * 0.5F;
			float f = 0.25F / x;

			y = (m(1, 0) + m(0, 1)) * f;
			z = (m(0, 2) + m(2, 0)) * f;
			w = (m(2, 1) - m(1, 2)) * f;
		}
		else if (m11 > m22)
		{
			y = sqrt(m11 - m00 - m22 + 1.0F) * 0.5F;
			float f = 0.25F / y;

			x = (m(1, 0) + m(0, 1)) * f;
			z = (m(2, 1) + m(1, 2)) * f;
			w = (m(0, 2) - m(2, 0)) * f;
		}
		else
		{
			z = sqrt(m22 - m00 - m11 + 1.0F) * 0.5F;
			float f = 0.25F / z;

			x = (m(0, 2) + m(2, 0)) * f;
			y = (m(2, 1) + m(1, 2)) * f;
			w = (m(1, 0) - m(0, 1)) * f;
		}
	}
};

Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(
		q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
		q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
		q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
		q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
}

Vector3 Transform(const Vector3& v, const Quaternion& q) {
	const Vector3& b = q.GetVectorPart();
	float b2 = b.x * b.x + b.y * b.y + b.z * b.z;

	return v * (q.w * q.w - b2) + b * (Dot(v, b) * 2.0f) + Cross(b, v) * (q.w * 2.0f);
}