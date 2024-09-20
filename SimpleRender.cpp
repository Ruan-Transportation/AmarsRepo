// SimpleRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define a simple vector class
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

// Define a simple ray class
struct Ray {
    Vec3 origin, direction;

    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction.normalize()) {}
};

// Define a simple sphere class
struct Sphere {
    Vec3 center;
    float radius;

    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}

    bool intersect(const Ray& ray, float& t) const {
        Vec3 oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return false;
        }
        else {
            t = (-b - std::sqrt(discriminant)) / (2.0f * a);
            return true;
        }
    }
};

// Implement a simple clamp function
template <typename T>
T clamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Render function
void render(const std::vector<Sphere>& spheres) {
    const int width = 800;
    const int height = 600;
    const float aspect_ratio = float(width) / float(height);
    const float fov = 90.0f;
    const float scale = std::tan(fov * 0.5f * M_PI / 180.0f);

    std::vector<Vec3> framebuffer(width * height);

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = (2 * (i + 0.5f) / float(width) - 1) * aspect_ratio * scale;
            float y = (1 - 2 * (j + 0.5f) / float(height)) * scale;
            Vec3 dir = Vec3(x, y, -1).normalize();
            Ray ray(Vec3(0, 0, 0), dir);

            Vec3 color(0, 0, 0);
            float t_min = std::numeric_limits<float>::max();
            for (const auto& sphere : spheres) {
                float t;
                if (sphere.intersect(ray, t) && t < t_min) {
                    t_min = t;
                    color = Vec3(1, 0, 0); // Red color for the sphere
                }
            }
            framebuffer[j * width + i] = color;
        }
    }

    // Output the framebuffer as a PPM image
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& color : framebuffer) {
        int r = static_cast<int>(255 * clamp(color.x, 0.0f, 1.0f));
        int g = static_cast<int>(255 * clamp(color.y, 0.0f, 1.0f));
        int b = static_cast<int>(255 * clamp(color.z, 0.0f, 1.0f));
        std::cout << r << " " << g << " " << b << "\n";
    }
}

//int main() {
//    std::vector<Sphere> spheres = {
//        Sphere(Vec3(0, 0, -5), 1)
//    };
//
//    render(spheres);
//
//    return 0;
//}
