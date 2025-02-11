#pragma once
#include "Vector.h"

class Plane {
public:
	float x, y, z, w;

	Plane() = default;
	Plane(float nx, float ny, float nz, float d) : x(nx), y(ny), z(nz), w(d) {}

	Plane(const Vector3& n, float d) : x(n.x), y(n.y), z(n.z), w(d) {}

	const Vector3& GetNormal() const { return reinterpret_cast<const Vector3&>(x); }
};

float Dot(const Plane& f, const Vector3& v) {
	return f.x * v.x + f.y * v.y + f.z * v.z;
}
float Dot(const Plane& f, const Point3& p) {
	return f.x * p.x + f.y * p.y + f.z * p.z + f.w;
}