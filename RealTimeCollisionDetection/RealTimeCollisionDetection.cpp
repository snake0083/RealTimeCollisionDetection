#include <iostream>
#include <assert.h>

class Vector;

class Point {
public:
	Point();
	Point(float x,float y,float z);

	bool			operator == (const Point & rhs) const;
	bool			operator != (const Point & rhs) const;
	Point			operator + (const Point & rhs) const;
	Point			operator + (const Vector & rhs) const;
	const Point &	operator += (const Point & rhs);
	const Point &	operator += (const Vector & rhs);
	const Point &	operator -= (const Point & rhs);
	Point			operator - (const Point & rhs) const;
	Point			operator * (const float rhs) const;
	Point			operator / (const float rhs) const;
	const Point &	operator *= (const float rhs);
	const Point &	operator /= (const float rhs);
	float			operator [] (const int idx) const;
	float &			operator [] (const int idx);
public:
	float x, y, z;
};

class Vector {
public:
	Vector();
	Vector(float value);
	Vector(const Vector& rhs);
	Vector(const Point& rhs);
	Vector(float X, float Y, float Z);
	Vector(const float * xyz);
	Vector & operator = (const Vector & rhs);
	Vector & operator = (const float * rhs);

	bool			operator == (const Vector & rhs) const;
	bool			operator != (const Vector & rhs) const;
	Vector			operator + (const Vector & rhs) const;
	const Vector &	operator += (const Vector & rhs);
	const Vector &	operator -= (const Vector & rhs);
	Vector			operator - (const Vector & rhs) const;
	Vector			operator * (const float rhs) const;
	Vector			operator / (const float rhs) const;
	const Vector &	operator *= (const float rhs);
	const Vector &	operator /= (const float rhs);
	float			operator [] (const int idx) const;
	float &			operator [] (const int idx);
public:
	float x, y, z;
};

class Sphere {
public:
	Sphere();
public:
	Point c;
	float r;
};

Point::Point() :
	x(0), y(0), z(0) {

}

Point::Point(float _x, float _y, float _z) :
	x(_x), y(_y), z(_z) {

}

Point Point::operator + (const Point & rhs) const
{
	Point temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	temp.z = z + rhs.z;
	return temp;
}

Point Point::operator + (const Vector & rhs) const
{
	Point temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	temp.z = z + rhs.z;
	return temp;
}

Point Point::operator - (const Point & rhs) const
{
	return Point(x-rhs.x,y-rhs.y,z-rhs.z);
}


Vector::Vector() :
	x(0), y(0), z(0) {
}

Vector::Vector(float value) :
	x(value),
	y(value),
	z(value) {
}

Vector::Vector(const Vector & rhs) :
	x(rhs.x), y(rhs.y), z(rhs.z) {
}

Vector::Vector(const Point& rhs) :
	x(rhs.x), y(rhs.y), z(rhs.z) {
}

Vector::Vector(float X, float Y, float Z) :
	x(X),
	y(Y),
	z(Z) {
}

Vector::Vector(const float * xyz) :
	x(xyz[0]),
	y(xyz[1]),
	z(xyz[2]) {
}

Vector & Vector::operator = (const Vector & rhs) {
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

Vector& Vector::operator = (const float * rhs) {
	x = rhs[0];
	y = rhs[1];
	z = rhs[2];
	return *this;
}

bool Vector::operator == (const Vector & rhs) const {
	if (x != rhs.x) {
		return false;
	}

	if (y != rhs.y) {
		return false;
	}

	if (z != rhs.z) {
		return false;
	}

	return true;
}

bool Vector::operator != (const Vector & rhs) const {
	if (*this == rhs) {
		return false;
	}

	return true;
}

Vector Vector::operator + (const Vector & rhs) const {
	Vector temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	temp.z = z + rhs.z;
	return temp;
}

const Vector & Vector::operator += (const Vector & rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

const Vector & Vector::operator -= (const Vector & rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector Vector::operator - (const Vector & rhs) const {
	Vector temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	temp.z = z - rhs.z;
	return temp;
}

Vector Vector::operator * (const float rhs) const {
	Vector temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	temp.z = z * rhs;
	return temp;
}

Vector Vector::operator / (const float rhs) const {
	Vector temp;
	temp.x = x / rhs;
	temp.y = y / rhs;
	temp.z = z / rhs;
	return temp;
}

const Vector & Vector::operator *= (const float rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

const Vector & Vector::operator /= (const float rhs) {
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

float Vector::operator [] (const int idx) const {
	assert(idx >= 0 && idx < 3);
	return (&x)[idx];
}

float & Vector::operator [] (const int idx) {
	assert(idx >= 0 && idx < 3);
	return (&x)[idx];
}

Vector operator * (float Scale, const Vector& V)
{
	return V.operator*(Scale);
}

Sphere::Sphere() :
	r(0) {
}

float Dot(const Vector& a, const Vector& b)
{
	return a.x*b.x + a.y*b.y+a.z*b.z;
}

float Sqrt(float x)
{
	return sqrt(x);
}


// Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
// returns t value of intersection and intersection point q
int IntersectRaySphere(Point p, Vector d, Sphere s, float &t, Point &q)
{
	Vector m = p - s.c;
	float b = Dot(m, d);
	float c = Dot(m, m) - s.r * s.r;
	// Exit if r’s origin outside s (c > 0)and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f) return 0;
	float discr = b * b - c;
	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0f) return 0;
	// Ray now found to intersect sphere, compute smallest t value of intersection
	t = -b - Sqrt(discr);
	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.0f) t = 0.0f;
	q = p + t * d;
	return 1;
}


int main()
{
	Point p;
	Vector d = Vector(0,0,1);
	Sphere s;
	s.r = 1;
	float t;
	Point q;
	if (IntersectRaySphere(p, d, s, t, q))
	{
		std::cout << "Ray Intersect by Sphere! \n";
	}
    std::cout << "Hello World!\n";
}