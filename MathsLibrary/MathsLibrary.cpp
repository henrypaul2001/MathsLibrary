#include <iostream>
#include "Vector.h"
#include "Matrix.h"
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
}
