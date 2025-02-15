#pragma once
#include "Vector.h"
#include "Plane.h"
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

class Matrix4x4 {
public:
	Matrix4x4() = default;
	Matrix4x4(const float n00, const float n01, const float n02, const float n03,
			  const float n10, const float n11, const float n12, const float n13,
			  const float n20, const float n21, const float n22, const float n23,
			  const float n30, const float n31, const float n32, const float n33) {
		n[0][0] = n00; n[0][1] = n01; n[0][2] = n02; n[0][3] = n03;
		n[1][0] = n10; n[1][1] = n11; n[1][2] = n12; n[1][3] = n13;
		n[2][0] = n20; n[2][1] = n21; n[2][2] = n22; n[2][3] = n23;
		n[3][0] = n30; n[3][1] = n31; n[3][2] = n32; n[3][3] = n33;
	}

	Matrix4x4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d) {
		n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
		n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
		n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
		n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
	}

	float& operator ()(int i, int j) { return n[i][j]; }
	const float& operator ()(int i, int j) const { return n[i][j]; }

	Vector4& operator [](int j) { 
		return *reinterpret_cast<Vector4*>(n[j]);
	}
	const Vector4& operator [](int j) const {
		return *reinterpret_cast<const Vector4*>(n[j]);
	}

protected:
	float n[4][4];
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

Matrix3x3 Inverse(const Matrix3x3& m) {
	const Vector3& a = m[0];
	const Vector3& b = m[1];
	const Vector3& c = m[2];

	const Vector3 r0 = Cross(b, c);
	const Vector3 r1 = Cross(c, a);
	const Vector3 r2 = Cross(a, b);
	float invDet = 1.0f / Dot(r2, c);

	return Matrix3x3(r0.x * invDet, r0.y * invDet, r0.z * invDet,
					 r1.x * invDet, r1.y * invDet, r1.z * invDet,
					 r2.x * invDet, r2.y * invDet, r2.z * invDet);
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	const Vector3& a = reinterpret_cast<const Vector3&>(m[0]);
	const Vector3& b = reinterpret_cast<const Vector3&>(m[1]);
	const Vector3& c = reinterpret_cast<const Vector3&>(m[2]);
	const Vector3& d = reinterpret_cast<const Vector3&>(m[3]);

	const float& x = m(3, 0);
	const float& y = m(3, 1);
	const float& z = m(3, 2);
	const float& w = m(3, 3);

	Vector3 s = Cross(a, b);
	Vector3 t = Cross(c, d);
	Vector3 u = a * y - b * x;
	Vector3 v = c * w - d * z;

	float invDet = 1.0f / (Dot(s, v) + Dot(t, u));
	s *= invDet;
	t *= invDet;
	u *= invDet;
	v *= invDet;

	Vector3 r0 = Cross(b, v) + t * y;
	Vector3 r1 = Cross(v, a) - t * x;
	Vector3 r2 = Cross(d, u) + s * w;
	Vector3 r3 = Cross(u, c) - s * z;

	return Matrix4x4(r0.x, r0.y, r0.z, -Dot(b, t),
					 r1.x, r1.y, r1.z,  Dot(a, t),
					 r2.x, r2.y, r2.z, -Dot(d, s),
					 r3.x, r3.y, r3.z,  Dot(c, s));
}

Matrix3x3 MakeRotationX(const float t) {
	float c = cos(t);
	float s = sin(t);

	return Matrix3x3(1.0f, 0.0f, 0.0f,
					 0.0f,    c,   -s,
					 0.0f,    s,    c);
}

Matrix3x3 MakeRotationY(const float t) {
	float c = cos(t);
	float s = sin(t);

	return Matrix3x3(c,    0.0f,    s,
					 0.0f, 1.0f, 0.0f,
					 -s,   0.0f,    c);
}

Matrix3x3 MakeRotatonZ(const float t) {
	float c = cos(t);
	float s = sin(t);

	return Matrix3x3(c,      -s, 0.0f,
					 s,       c, 0.0f,
					 0.0f, 0.0f, 1.0f);
}

Matrix3x3 MakeRotation(const float t, const Vector3& a) {
	float c = cos(t);
	float s = sin(t);
	float d = 1.0f - c;

	float x = a.x * d;
	float y = a.y * d;
	float z = a.z * d;

	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return Matrix3x3(c + x * a.x, axay - s * a.z, axaz + s * a.y,
					 axay + s * a.z, c + y * a.y, ayaz - s * a.x,
					 axaz - s * a.y, ayaz + s * a.x, c + z * a.z);
}

Matrix3x3 MakeReflection(const Vector3& a) {
	float x = a.x * -2.0f;
	float y = a.y * -2.0f;
	float z = a.z * -2.0f;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return Matrix3x3(x * a.x + 1.0f, axay, axaz,
					 axay, y * a.y + 1.0f, ayaz,
					 axaz, ayaz, z * a.z + 1.0f);
}

Matrix3x3 MakeInvolution(const Vector3& a) {
	float x = a.x * 2.0f;
	float y = a.y * 2.0f;
	float z = a.z * 2.0f;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return Matrix3x3(x * a.x - 1.0f, axay, axaz,
					 axay, y * a.y - 1.0f, ayaz,
					 axaz, ayaz, z * a.z - 1.0f);
}

Matrix3x3 MakeScale(float sx, float sy, float sz) {
	return Matrix3x3(sx, 0.0f, 0.0f,
					 0.0f, sy, 0.0f,
					 0.0f, 0.0f, sz);
}

Matrix3x3 MakeScale(float s, const Vector3& a) {
	s -= 1.0f;
	float x = a.x * s;
	float y = a.y * s;
	float z = a.z * s;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;
	
	return Matrix3x3(x * a.x + 1.0f, axay, axaz,
					 axay, y * a.y + 1.0f, ayaz,
					 axaz, ayaz, z * a.z + 1.0f);
}

Matrix3x3 MakeSkew(float t, const Vector3& a, const Vector3& b) {
	t = tan(t);
	float x = a.x * t;
	float y = a.y * t;
	float z = a.z * t;

	return Matrix3x3(x * b.x + 1.0f, x * b.y, x * b.z,
					 y * b.x, y * b.y + 1.0f, y * b.z,
					 z * b.x, z * b.y, z * b.z + 1.0f);
}

class Transform4x4 : public Matrix4x4 {
public:
	Transform4x4() = default;
	Transform4x4(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23) {
		
		n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
		n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
		n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
		n[3][0] = n03; n[3][1] = n13; n[3][2] = n23;

		n[0][3] = n[1][3] = n[2][3] = 0.0F;
		n[3][3] = 1.0F;
	}

	Transform4x4(const Vector3& a, const Vector3& b,
		const Vector3& c, const Point3& p)
	{
		n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
		n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
		n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
		n[3][0] = p.x; n[3][1] = p.y; n[3][2] = p.z;

		n[0][3] = n[1][3] = n[2][3] = 0.0F;
		n[3][3] = 1.0F;
	}

	Vector3& operator [](int j) { return *reinterpret_cast<Vector3*>(n[j]); }
	const Vector3& operator [](int j) const { return *reinterpret_cast<const Vector3*>(n[j]); }

	const Point3& GetTranslation() { return *reinterpret_cast<const Point3*>(n[3]); }
	void SetTranslation(const Point3& p) {
		n[3][0] = p.x;
		n[3][1] = p.y;
		n[3][2] = p.z;
	}
};

Transform4x4 Inverse(const Transform4x4& h) {
	const Vector3& a = h[0];
	const Vector3& b = h[1];
	const Vector3& c = h[2];
	const Vector3& d = h[3];

	Vector3 s = Cross(a, b);
	Vector3 t = Cross(c, d);

	float invDet = 1.0f / Dot(s, c);

	s *= invDet;
	t *= invDet;
	Vector3 v = c * invDet;

	Vector3 r0 = Cross(v, b);
	Vector3 r1 = Cross(v, a);

	return Transform4x4(r0.x, r0.y, r0.z, -Dot(b, t),
						r1.x, r1.y, r1.z, Dot(a, t),
						s.x, s.y, s.z, -Dot(d, s));
}

Transform4x4 operator *(const Transform4x4& A, const Transform4x4& B)
{
	return Transform4x4(
		A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
		A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
		A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
		A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3),
		A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
		A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
		A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
		A(1, 0) * B(0, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3),
		A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
		A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
		A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2),
		A(2, 0) * B(0, 3) + A(2, 1) * B(1, 3) + A(2, 2) * B(2, 3) + A(2, 3));
}

Vector3 operator *(const Transform4x4& H, const Vector3& v)
{
	return Vector3(H(0, 0) * v.x + H(0, 1) * v.y + H(0, 2) * v.z,
		H(1, 0) * v.x + H(1, 1) * v.y + H(1, 2) * v.z,
		H(2, 0) * v.x + H(2, 1) * v.y + H(2, 2) * v.z);
}
Vector3 operator *(const Vector3& n, const Transform4x4& h) {
	return Vector3(n.x * h(0, 0) + n.y * h(1, 0) + n.z * h(2, 0),
		n.x * h(0, 1) + n.y * h(1, 1) + n.z * h(2, 1),
		n.x * h(0, 2) + n.y * h(1, 2) + n.z * h(2, 2));
}
Point3 operator *(const Transform4x4& H, const Point3& p)
{
	return Point3(H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2) * p.z + H(0, 3),
		H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2) * p.z + H(1, 3),
		H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2) * p.z + H(2, 3));
}

Transform4x4 MakeReflection(const Plane& f) {
	float x = f.x * -2.0f;
	float y = f.y * -2.0f;
	float z = f.z * -2.0f;

	float nxny = x * f.y;
	float nxnz = x * f.z;
	float nynz = y * f.z;

	return Transform4x4(x * f.x + 1.0f, nxny, nxnz, x * f.w,
						nxny, y * f.y + 1.0f, nynz, y * f.w,
						nxnz, nynz, z * f.z + 1.0f, z * f.w);
}

using Mat3 = Matrix3x3;
using Mat4 = Matrix4x4;