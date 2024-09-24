// This is a place holder for us to define basic geographic points used in graphics rendering.
// The objects I need to define are vectors, points, rays, and bounding boxes.
// We'll eventually need to be ablt to translate cartesian to spherical coordinates as well.


#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Define a 2d Tuple Template

template <template <typename> class Child, typename T>
class Tuple2 {
public:
	static const int nDimensions = 2;
	Tuple2() = default;
	Tuple2(T x, T y) : x(x), y(y) {}
	bool HasNaN() const { return std::isnan(x) || std::isnan(y); }
	T operator[](int i) const {
		switch (i) {
		case 0: return x;
		case 1: return y;
		}
		T& operator[](int i) {
			switch (i) {
			case 0: return x;
			case 1: return y;
			}
		}
		template <typename U>
		auto operator+(Child<U> c) const->Child<decltype(T{} + U{}) > {
			return (x + c.x, y + c.y);
		}

	}
};


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


// Define a simple 3d vector class (Used github copilot: note a bit cleaner code here).

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

// Define a simple 3d point class

template <typename T>
class Point3 : public Tuple3<Point3, T> {
public:
	Point3() : Tuple3<T>(0, 0, 0) {}
	Point3(T x, T y, T z) : Tuple3<T>(x, y, z) {}
};

// Define a ray class

class Ray {
public:
	bool HasNan() const { return (o.HasNaN() || d.HasNaN()); }
	std::string ToString() const;
	Point3<float> o;
	Vec3 d;
	float tMax;
	float time;
};

// Define a bounding box class

class BoundingBox
{
public:
	BoundingBox() {
		float minNum = std::numeric_limits<float>::lowest();
		float maxNum = std::numeric_limits<float>::max();
		pMin = Point3<float>(maxNum, maxNum, maxNum);
		pMax = Point3<float>(minNum, minNum, minNum);
	}
	BoundingBox(const Point3<float>& p) : pMin(p), pMax(p) {}
	BoundingBox(const Point3<float>& p1, const Point3<float>& p2) {
		pMin = Point3<float>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
		pMax = Point3<float>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
	}
	Point3<float> pMin, pMax;
};

int main() {
	return 1;
			}