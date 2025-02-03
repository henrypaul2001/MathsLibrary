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
};

inline Point3 operator +(const Point3& a, const Vector3& b) {
	return Point3(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline Vector3 operator -(const Point3& a, const Vector3& b) {
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

using Vec3 = Vector3;
using Vec4 = Vector4;