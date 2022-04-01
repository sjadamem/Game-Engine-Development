#include <iostream>

using namespace std;

#include "vector3d.h"
#include "matrix3d.h"

int main()
{
	cout << "hello world" << endl;

	Vector3d v1(1.0f, 1.0f, 1.0f);
	Vector3d v2(2.0f, 2.0f, 2.0f);
	Vector3d v3(3.0f, 3.0f, 3.0f);
	Matrix3d m1(v1, v2, v3);

	cout << "VECTOR::\nX\t" << v1.x << "\nY\t" << v1.y << "\nZ\t" << v1.z << endl;

	cout << "MATRIX[0][0]" << m1(0, 0) << endl;
	cout << "MATRIX[1][1]" << m1(1, 1) << endl;

	system("pause");
}