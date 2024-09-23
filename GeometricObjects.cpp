// This is a place holder for us to define basic geographic points used in graphics rendering.
// The objects I need to define are vectors, points, rays, and bounding boxes.
// We'll eventually need to be ablt to translate cartesian to spherical coordinates as well.


#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846;
#endif



// Define a 3d Tuple template

template <template <typename> class Child, typename T>
class Tuple3 {
	Tuple3(T x, T y, T z) : x(x), y(y), z(z) {}
	bool HasNaN() const { return std::isnan(x) || std::isnan(y) || std::isnan(z); }
	T operator[](int i) const {
		switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
		T& operator[](int i) {
			switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			}
		}
		template <typename U>
		auto operator+(Child<U> c) const->Child<decltype(T{} + U{}) > {
			return (x + c.x, y + c.y, z + c.z);
		}
		static const int nDimensions = 3;
	};


// Define a simple vector class (Used github copilot: note a bit cleaner code here).

struct Vec3 {
	float x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
	Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
	Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
	Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }

	float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
	Vec3 cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	float length() const { return std::sqrt(x * x + y * y + z * z); }
	Vec3 normalize() const { return *this / length(); }
};



int main() {
	return 1;
			}