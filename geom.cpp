#include "geom.h"
#include <cmath>
#include <string>
#include <format>

// Calculates clip coordinates based on OpenGL's model-view-projection matrix and converts them to screen space
bool OpenGLWorldToScreen(vec3 pos, vec3& screen, const float matrix[16], int windowWidth, int windowHeight)
{
    Vec4 clipCoords;

    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
    clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
    clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    if (clipCoords.w < 0.1f) {
        return false;
    }

    vec3 NDC{ clipCoords.x / clipCoords.w, clipCoords.y / clipCoords.w, clipCoords.z / clipCoords.w };

    screen.x = (windowWidth / 2.0f) * (NDC.x + 1.0f);
    screen.y = (windowHeight / 2.0f) * (1.0f - NDC.y); // Y is inverted in screen space

    return true;
}

// Similar function for DirectX with column-major matrices
bool DirectXWorldToScreen(vec3 pos, vec3& screen, const float matrix[16], int windowWidth, int windowHeight)
{
    Vec4 clipCoords;

    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
    clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
    clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
    clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

    if (clipCoords.w < 0.1f) {
        return false;
    }

    vec3 NDC{ clipCoords.x / clipCoords.w, clipCoords.y / clipCoords.w, clipCoords.z / clipCoords.w };

    screen.x = (windowWidth / 2.0f) * (NDC.x + 1.0f);
    screen.y = (windowHeight / 2.0f) * (1.0f - NDC.y);

    return true;
}

// Wrapper function for OpenGL, assuming the user only calls this for OpenGL purposes
Vec3 OpenGLWorldToScreen(Vec3& pos, const float matrix[16], int windowWidth, int windowHeight)
{
    vec3 screen;

    if (OpenGLWorldToScreen(pos, screen, matrix, windowWidth, windowHeight))
        return screen;

    return vec3(0.0f, 0.0f, 0.0f); // Return a default vector if not visible
}

Vec3 DirectXWorldToScreen(Vec3& pos, const float matrix[16], int windowWidth, int windowHeight)
{
    vec3 screen;
    if (DirectXWorldToScreen(pos, screen, matrix, windowWidth, windowHeight))
        return screen;
    return vec3(0.0f, 0.0f, 0.0f); // Return a default vector if not visible
}

// Gets the angle of a ray from origin to target // InvertPitch means looking up leads to negative pitch
Vec3 CalcAngle(const Vec3& origin, const Vec3& target, bool invertYaw, bool invertPitch)
{
    Vec3 results{ 0.0f, 0.0f, 0.0f };
    Vec3 delta = target - origin; // Get the difference between the two vectors

    float distance = origin.Distance(target);
    if (distance == 0.0f) // Prevent division by zero
        return results;

    float yawSign = invertYaw ? -1.0f : 1.0f;
    float pitchSign = invertPitch ? -1.0f : 1.0f;

    results.x = yawSign * RadiansToDegrees(atan2f(delta.y, delta.x));
    results.y = pitchSign * RadiansToDegrees(asinf((delta.z) / distance));
    return results;
}

Vec3 DegreesToRadians(const Vec3& vec)
{
    return Vec3{ DegreesToRadians(vec.x), DegreesToRadians(vec.y), DegreesToRadians(vec.z) };
}

float DegreesToRadians(float num)
{
    return num / 180.0f * PI;
}

Vec3 RadiansToDegrees(const Vec3& vec)
{
    return Vec3{ vec.x / PI * 180.0f, vec.y / PI * 180.0f, vec.z / PI * 180.0f };
}

float RadiansToDegrees(float num)
{
    return num / PI * 180.0f;
}

void Vector3::NormalizeAngle(float yawMin, float yawMax, float pitchMin, float pitchMax)
{
    // Wrap yaw (x) to [yawMin, yawMax] (e.g., [-180, 180])
    while (x > yawMax)
        x -= (yawMax - yawMin);
    while (x < yawMin)
        x += (yawMax - yawMin);

    // Wrap pitch (y) to [pitchMin, pitchMax] (e.g., [-89, 89])
    while (y > pitchMax)
        y -= (pitchMax - pitchMin);
    while (y < pitchMin)
        y += (pitchMax - pitchMin);
}

std::string Vector3::ToString()
{
    return std::format("{} {} {}", x, y, z);
}
