#include <iostream>

#include "vector3d.h"
#include "matrix3d.h"

using namespace std;

int main()
{
	cout << "hello world" << endl;

	Vector3d v1(3.0f, 2.0f, 1.0f);
	Matrix3d m1(
		1.0f, 6.0f, 9.0f,
		2.0f, 5.0f, 8.0f,
		3.0f, 4.0f, 7.0f
	);
	Matrix3d m2(
		3.0f, 3.0f, 3.0f,
		2.0f, 2.0f, 2.0f,
		1.0f, 1.0f, 1.0f
	);
	Vector3d v2 = m1 * v1;
	Matrix3d m3 = m1 * m2;

	cout << "VECTOR::\nX\t" << v2.x << "\nY\t" << v2.y << "\nZ\t" << v2.z << endl;

	cout << "MATRIX::\n[0] -> " << m3(0, 0) << endl;
	cout << "[1] -> " << m3(1, 0) << endl;
	cout << "[2] -> " << m3(2, 0) << endl;
	cout << "[3] -> " << m3(0, 1) << endl;
	cout << "[4] -> " << m3(1, 1) << endl;
	cout << "[5] -> " << m3(2, 1) << endl;
	cout << "[6] -> " << m3(0, 2) << endl;
	cout << "[7] -> " << m3(1, 2) << endl;
	cout << "[8] -> " << m3(2, 2) << endl;
	
	cout << "DOT PRODUCT (v1 * v2)\n" << dot(v1, v2) << endl;
	cout << "DETERMINANT (m1)\n" << determinant(m2) << endl;
	
	system("pause");
}