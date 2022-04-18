#include <iostream>

#include "vector3d.h"
#include "matrix3d.h"
#include "transform4d.h"

using namespace std;

int main()
{
	Matrix3d a(
		0.0F, 1.0F, 2.0F,
		2.0F, 3.0F, 4.0F,
		2.0F, 2.0F, 1.0F
	);
	Matrix3d b(
		3.0F, 1.0F, 0.0F,
		4.0F, 2.0F, 1.0F,
		1.0F, 3.0F, 4.0F
	);
	Matrix3d c = a * b;
	cout << "MATRIX C :: Product of Matrix3d A and B" << endl;
	printf("[0]\t-> %5.2f\n", c(0, 0));
	printf("[1]\t-> %5.2f\n", c(1, 0));
	printf("[2]\t-> %5.2f\n", c(2, 0));
	printf("[3]\t-> %5.2f\n", c(0, 1));
	printf("[4]\t-> %5.2f\n", c(1, 1));
	printf("[5]\t-> %5.2f\n", c(2, 1));
	printf("[6]\t-> %5.2f\n", c(0, 2));
	printf("[7]\t-> %5.2f\n", c(1, 2));
	printf("[8]\t-> %5.2f\n", c(2, 2));

	Matrix3d d = c * 5.0F;
	cout << "\nMATRIX D :: Product of Matrix3d C and 5.0F" << endl;
	printf("[0]\t-> %6.2f\n", d(0, 0));
	printf("[1]\t-> %6.2f\n", d(1, 0));
	printf("[2]\t-> %6.2f\n", d(2, 0));
	printf("[3]\t-> %6.2f\n", d(0, 1));
	printf("[4]\t-> %6.2f\n", d(1, 1));
	printf("[5]\t-> %6.2f\n", d(2, 1));
	printf("[6]\t-> %6.2f\n", d(0, 2));
	printf("[7]\t-> %6.2f\n", d(1, 2));
	printf("[8]\t-> %6.2f\n", d(2, 2));

	d = -d;
	cout << "\nMATRIX D :: Negative Matrix3d D" << endl;
	printf("[0]\t-> %7.2f\n", d(0, 0));
	printf("[1]\t-> %7.2f\n", d(1, 0));
	printf("[2]\t-> %7.2f\n", d(2, 0));
	printf("[3]\t-> %7.2f\n", d(0, 1));
	printf("[4]\t-> %7.2f\n", d(1, 1));
	printf("[5]\t-> %7.2f\n", d(2, 1));
	printf("[6]\t-> %7.2f\n", d(0, 2));
	printf("[7]\t-> %7.2f\n", d(1, 2));
	printf("[8]\t-> %7.2f\n", d(2, 2));

	Vector3d a1(1.0F, 2.0F, 3.0F);
	Vector3d b1(6.0F, 5.0F, 4.0F);
	Vector3d c1(7.0F, 8.0F, 9.0F);
	Matrix3d e(
		a1, b1, c1
	);
	cout << "\nMATRIX E :: Create Matrix3d E with 3 Vector3ds" << endl;
	printf("[0]\t-> %5.2f\n", e(0, 0));
	printf("[1]\t-> %5.2f\n", e(1, 0));
	printf("[2]\t-> %5.2f\n", e(2, 0));
	printf("[3]\t-> %5.2f\n", e(0, 1));
	printf("[4]\t-> %5.2f\n", e(1, 1));
	printf("[5]\t-> %5.2f\n", e(2, 1));
	printf("[6]\t-> %5.2f\n", e(0, 2));
	printf("[7]\t-> %5.2f\n", e(1, 2));
	printf("[8]\t-> %5.2f\n", e(2, 2));

	cout << "\nMATRIX E :: Determinant of Matrix3d E\n" << determinant(e) << endl;

	Matrix3d f(
		3.0F, 4.0F, 5.0F,
		5.0F, 1.0F, 2.0F,
		5.0F, 2.0F, 1.0F
	);
	f = inverse(f);
	cout << "\nMATRIX C :: Inverse of Matrix3d F" << endl;
	printf("[0]\t-> %7.3f\n", f(0, 0));
	printf("[1]\t-> %7.3f\n", f(1, 0));
	printf("[2]\t-> %7.3f\n", f(2, 0));
	printf("[3]\t-> %7.3f\n", f(0, 1));
	printf("[4]\t-> %7.3f\n", f(1, 1));
	printf("[5]\t-> %7.3f\n", f(2, 1));
	printf("[6]\t-> %7.3f\n", f(0, 2));
	printf("[7]\t-> %7.3f\n", f(1, 2));
	printf("[8]\t-> %7.3f\n", f(2, 2));

	Matrix3d g = identity() * rotateZ(30.0F) * rotateY(20.0F) * rotateX(40.0F);
	cout << "\nMATRIX C :: Rotation Matrix3d G (40, 20, 30)" << endl;
	printf("[0]\t-> %7.3f\n", g(0, 0));
	printf("[1]\t-> %7.3f\n", g(1, 0));
	printf("[2]\t-> %7.3f\n", g(2, 0));
	printf("[3]\t-> %7.3f\n", g(0, 1));
	printf("[4]\t-> %7.3f\n", g(1, 1));
	printf("[5]\t-> %7.3f\n", g(2, 1));
	printf("[6]\t-> %7.3f\n", g(0, 2));
	printf("[7]\t-> %7.3f\n", g(1, 2));
	printf("[8]\t-> %7.3f\n", g(2, 2));

	system("pause");
}