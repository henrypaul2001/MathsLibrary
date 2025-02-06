#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Plane.h"
int main()
{
    std::cout << "Hello World!\n";
    Vec3 test = Vec3(10.0f, 5.0f, -10.0f);
    test[2] = 1000.0f;
    std::cout << test.z << std::endl;

    Vec3 test2 = Vec3(100.0f, 10.0f, 10.0f);
    Vec3 result = test2 * 5.0f;

    float mag = Magnitude(result);
    Vec3 normalized = Normalize(result);
    Vec3 inverseTest2 = -test2;

    Vec3 dividedBy = Vec3(10.0f, 10.0f, 10.0f) / 2.0f;
    Vec3 normalizedTest2 = Normalize(Vec3(10.0f, 2.433f, 5.6f));

    Vec3 addition = Vec3(10.0f, 5.0f, 1.0f) + Vec3(12.0f, 2.5f, -1.5f);

    float dotProduct = Dot(Vec3(1.0f, 2.55f, 10.5), Vec3(0.02f, 1.55f, -10.5f));
    Vec3 crossProduct = Cross(Vec3(1.0f, 2.0f, 3.0f), Vec3(3.0f, 4.0f, 5.0f));

    float d = Determinant(Matrix3x3(1.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f));

    Matrix3x3 original = Matrix3x3(10.0f, 1.0f, 1.0f,
                                    0.0f, 20.0f, 0.0f,
                                    1.0f, 1.0f, 50.0f);
    Matrix3x3 inverseTest = Inverse(original);
}
