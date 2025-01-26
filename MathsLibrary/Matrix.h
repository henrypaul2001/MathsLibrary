#pragma once
#include "Vector.h"

class Matrix3x3 {
public:
	Matrix3x3() = default;
	Matrix3x3(const float n00, const float n01, const float n02,
			  const float n10, const float n11, const float n12,
			  const float n20, const float n21, const float n22)
	{
		n[0][0] = n00; n[0][1] = n01; n[0][2] = n02;
		n[1][0] = n10; n[1][1] = n11; n[1][2] = n12;
		n[2][0] = n20; n[2][1] = n21; n[2][2] = n22;
	}

	Matrix3x3(const Vector3& a, const Vector3& b, const Vector3& c) {
		n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
		n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
		n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
	}

	float& operator()(int i, int j) {
		return n[j][i];
	}
	const float& operator()(int i, int j) const {
		return n[j][i];
	}

	Vector3& operator [](int j) {
		return *reinterpret_cast<Vector3*>(n[j]);
	}
	const Vector3& operator [](int j) const {
		return *reinterpret_cast<const Vector3*>(n[j]);
	}

private:
	float n[3][3];
};

inline Matrix3x3 operator *(const Matrix3x3& a, const Matrix3x3& b) {
	return Matrix3x3(a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
					 a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
					 a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2), 
		
					 a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
					 a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
					 a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),

					 a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
					 a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
					 a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2));
}

inline Vector3 operator *(const Matrix3x3& m, const Vector3& v) {
	return Vector3(m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
				   m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
				   m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z);
}

inline float Determinant(const Matrix3x3& m) {
	return (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1))
		  + m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2))
		  + m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));
}

using Mat3 = Matrix3x3;