#pragma once
#include <math.h>
#include <string>
constexpr auto PI = 3.1415927f;
class Vector3
{
public:

    float x;
    float y;
    float z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
    Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
    Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
    Vector3& operator += (const float rhs) { return *this = *this + Vector3(rhs, rhs, rhs); }
    Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
    Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
    Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
    bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); } //AKA Magnitude
    Vector3 Normalize() const { return *this * (1 / Length()); } // 1/ Length() 
    float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
    Vector3& abs() { x = fabs(x); y = fabs(y); z = fabs(z); return *this; }
    void NormalizeAngle(); // Wraps around x from 0-360 and y from -90 to 90
    std::string ToString();

};

struct Vec4
{
    float x;
    float y;
    float z;
    float w;
};

using Vec3 = Vector3;
using vec3 = Vector3;
using Vec = Vector3;
using vec = Vector3;

Vec3 OpenGLWorldToScreen(Vec3& pos, const float matrix[16], int windowWidth, int windowHeight);
Vec3 DirectXWorldToScreen(Vec3& pos, const float matrix[16], int windowWidth, int windowHeight);
Vec3 CalcAngle(Vec3& origin, Vec3& target);


Vec3 DegreesToRadians(Vec3& vec);
float DegreesToRadians(float num);
Vec3 RadiansToDegrees(const Vec3& vec);
float RadiansToDegrees(float num);
