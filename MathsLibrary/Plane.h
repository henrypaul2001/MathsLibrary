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

bool IntersectLinePlane(const Point3& p, const Vector3& v, const Plane& f, Point3& q) {
	float fv = Dot(f, v);
	if (fabs(fv) > FLT_MIN) {
		q = p - v * (Dot(f, p) / fv);
		return true;
	}
	return false;
}

bool IntersectThreePlanes(const Plane& f1, const Plane& f2,
						  const Plane& f3, Point3& out_p)
{
	const Vector3& n1 = f1.GetNormal();
	const Vector3& n2 = f2.GetNormal();
	const Vector3& n3 = f3.GetNormal();

	Vector3 n1xn2 = Cross(n1, n2);
	float det = Dot(n1xn2, n3);
	if (fabs(det) > FLT_MIN) {
		out_p = (Cross(n3, n2) * f1.w + Cross(n1, n3) * f2.w - n1xn2 * f3.w) / det;
		return true;
	}
	return false;
}