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

//Bounds2 Definition - 2d Bounding Class

template <typename T>
class Bounds2 {
public:
	Bounds2() {
		T minNum = std::numeric_limits<T>::lowest();
		T maxNum = std::numeric_limits<T>::max();
		pMin = Point2<T>(maxNum, maxNum);
		pMax = Point2<T>(minNum, minNum);
	}
	explicit Bounds2(const Point2<T>& p) : pMin(p), pMax(p) {}
	template <typename U>
	Bounds2(const Bounds2<U>& b) {
		if (b.IsEmpty())
			*this = Bounds2<T>();
		else {
			pMin = Point2<T>(b.pMin);
			pMax = Point2<T>(b.pMax);
		}
	}
	Vector2<T> Diagonal() const { return pMax - pMin; }
	T Area() const {
		Vector2<T> d = Diagonal();
		return d.x * d.y;
	}
	bool IsEmpty() const {
		return (pMin.x >= pMax.x || pMin.y >= pMax.y);
	}

	bool IsDegenerate() const { return pMin.x > pMax.x || pMin.y > pMax.y; }

	int MaxDimension() const {
		Vector2<T> diag = Diagonal();
		if (diag.x > diag.y)
			return 0;
		else
			return 1;
	}
};
