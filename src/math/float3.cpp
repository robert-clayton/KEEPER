#include "float3.h"
#include "float2.h"
#include <cmath>
#include <sstream>

float3::float3()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

float3::float3(const float2& other)
{
    this->x = other.x;
    this->y = other.y;
}

float3::float3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float3 float3::DirectionTo(const float3& other)
{
    return (other - *this).Normalized();
}

float3 float3::DirectionTo(const float2& other)
{
    return (other - *this).Normalized();
}

float float3::DistanceTo(const float3& other)
{
    return std::sqrt(std::pow(other.x - this->x, 2)
                     + std::pow(other.y - this->y, 2)
                     + std::pow(other.z - this->z, 2));
}

float3 float3::Normalized()
{
    float length = std::sqrt(std::pow(this->x, 2)
                             + std::pow(this->y, 2)
                             + std::pow(this->z, 2));
    if (length)
        return *this / length;
    else
        return *this;
}

bool float3::AlmostEqual(const float3& other)
{
    if (DistanceTo(other) < 0.01)
        return true;
    return false;
}

float3& float3::Add(const float3& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

float3& float3::Subtract(const float3& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

float3& float3::Multiply(const float3& other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

float3& float3::Divide(const float3& other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

float3& float3::Multiply(const float& other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

float3& float3::Divide(const float& other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

float3& float3::Multiply(const int& other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

float3& float3::Divide(const int& other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

float3 operator+(const float3& v1, const float3& v2)
{
    return float3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

float3 operator-(const float3& v1, const float3& v2)
{
    return float3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

float3 operator*(const float3& v1, const float3& v2)
{
    return float3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

float3 operator/(const float3& v1, const float3& v2)
{
    return float3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

float3 operator*(const float3& v1, const float& other)
{
    return float3(v1.x * other, v1.y * other, v1.z * other);
}

float3 operator/(const float3& v1, const float& other)
{
    return float3(v1.x / other, v1.y / other, v1.z / other);
}

float3 operator*(const float3& v1, const int& other)
{
    return float3(v1.x * other, v1.y * other, v1.z * other);
}

float3 operator/(const float3& v1, const int& other)
{
    return float3(v1.x / other, v1.y / other, v1.z / other);
}

float3& float3::operator+=(const float3& other)
{
    return this->Add(other);
}

float3& float3::operator-=(const float3& other)
{
    return this->Subtract(other);
}

float3& float3::operator*=(const float3& other)
{
    return this->Multiply(other);
}

float3& float3::operator/=(const float3& other)
{
    return this->Divide(other);
}

float3& float3::operator*=(const float& other)
{
    return this->Multiply(other);
}

float3& float3::operator/=(const float& other)
{
    return this->Divide(other);
}

float3& float3::operator*=(const int& other)
{
    return this->Multiply(other);
}

float3& float3::operator/=(const int& other)
{
    return this->Divide(other);
}

bool float3::operator==(const float3& other)
{
    if (this->x == other.x && this->y == other.y && this->z == other.z)
        return true;
    return false;
}

bool float3::operator!=(const float3& other)
{
    if (this->x != other.x || this->y != other.y || this->z != other.z)
        return true;
    return false;
}

float3& float3::Zero()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    return *this;
}

float2 float3::To2D()
{
    return float2(this->x, this->y);
}

std::string float3::ToStr()
{
    std::ostringstream oss;
    oss << "(" << this->x << ", " << this->y << ", " << this->z << ")";
    return oss.str();
}

std::ostream& operator<<(std::ostream& stream, const float3& vec)
{
    stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return stream;
}
