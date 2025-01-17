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
inline float Magnitude(const Vector3& v) {
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
inline Vector3 Normalize(const Vector3& v) {
	return v / Magnitude(v);
}

using Vec3 = Vector3;