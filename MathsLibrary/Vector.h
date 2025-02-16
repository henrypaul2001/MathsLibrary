#pragma once

class Vector3 {
public:
	float x, y, z;

	Vector3() = default;
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

	float& operator[](int i) { return ((&x)[i]); }
	const float& operator[](int i) const { return ((&x)[i]); }
	Vector3& operator *=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return (*this);
	}
	Vector3& operator /=(float s) {
		s = 1.0f / s;
		return *this *= s;
	}
	Vector3& operator +=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3& operator -=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
};

inline Vector3 operator *(const Vector3& v, float s) {
	return Vector3(v.x * s, v.y * s, v.z * s);
}
inline Vector3 operator /(const Vector3& v, float s) {
	return v * (1.0f / s);
}
inline Vector3 operator -(const Vector3& v) {
	return v * -1.0f;
}
inline Vector3 operator +(const Vector3& a, const Vector3& b) {
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline Vector3 operator -(const Vector3& a, const Vector3& b) {
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline float Magnitude(const Vector3& v) {
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
inline Vector3 Normalize(const Vector3& v) {
	return v / Magnitude(v);
}
inline float Dot(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline Vector3 Cross(const Vector3& a, const Vector3& b) {
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
inline Vector3 Project(const Vector3& a, const Vector3& b) {
	return b * (Dot(a, b) / Dot(b, b));
}
inline Vector3 ProjectUnitB(const Vector3& a, const Vector3& unitB) {
	return unitB * Dot(a, unitB);
}
inline Vector3 Reject(const Vector3& a, const Vector3& b) {
	return a - (b * (Dot(a, b) / Dot(b, b)));
}
inline Vector3 RejectUnitB(const Vector3& a, const Vector3& unitB) {
	return a - (unitB * Dot(a, unitB));
}

class Vector4 {
public:
	float x, y, z, w;

	Vector4() = default;
	Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}

	float& operator [](int i) { return ((&x)[i]); }
	const float& operator [](int i) const { return ((&x)[i]); }
	Vector4& operator *= (float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	Vector4& operator /= (float s) {
		s = 1.0f / s;
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	Vector4& operator += (const Vector4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	Vector4& operator -= (const Vector4& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
};

class Point3 : public Vector3 {
public:
	Point3() = default;
	Point3(float a, float b, float c) : Vector3(a, b, c) {}

	Point3& operator =(const Vector3& b) { x = b.x; y = b.y; z = b.z; return *this; }
};

inline Point3 operator +(const Point3& a, const Vector3& b) {
	return Point3(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline Point3 operator -(const Point3& a, const Vector3& b)
{
	return Point3(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline Vector3 operator -(const Point3& a, const Point3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

/*
* Get the distance between point and line
* @param q = point
* @param p = line origin
* @param v = line direction
*/
float DistancePointLine(const Point3& q, const Point3& p, const Vector3& v) {
	Vector3 a = Cross(p - q, v);
	return sqrt(Dot(a, a) / Dot(v, v));
}

float DistanceLineLine(const Point3& p1, const Vector3& v1, const Point3& p2, const Vector3& v2) {
	Vector3 dp = p2 - p1;

	float v12 = Dot(v1, v1);
	float v22 = Dot(v2, v2);
	float v1v2 = Dot(v1, v2);

	float det = v1v2 * v1v2 - v12 * v22;
	if (fabs(det) > FLT_MIN) {
		det = 1.0f / det;

		float dpv1 = Dot(dp, v1);
		float dpv2 = Dot(dp, v2);
		float t1 = (v1v2 * dpv2 - v22 * dpv1) * det;
		float t2 = (v12 * dpv2 - v1v2 * dpv1) * det;

		return Magnitude(dp + v2 * t2 - v1 * t1);
	}

	// The lines are nearly parallel
	Vector3 a = Cross(dp, v1);
	return sqrt(Dot(a, a) / v12);
}

using Vec3 = Vector3;
using Vec4 = Vector4;

class Line {
public:
	Vector3 direction;
	Vector3 moment;
	
	Line() = default;
	Line(float vx, float vy, float vz, float mx, float my, float mz) : direction(vx, vy, vz), moment(mx, my, mz) {}
	Line(const Vector3& v, const Vector3& m) : direction(v), moment(m) {}

private:
};