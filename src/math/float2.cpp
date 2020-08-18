#include "float2.h"
#include "int2.h"
#include "float3.h"
#include <cmath>
#include <sstream>

float2::float2()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

float2::float2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float2 float2::DirectionTo(const float2& other)
{
    return (other - *this).Normalized();
}

float3 float2::DirectionTo(const float3& other)
{
    return (other - *this).Normalized();
}

float float2::DistanceTo(const float2& other)
{
    return std::sqrt(std::pow(other.x - this->x, 2) + std::pow(other.y - this->y, 2));
}

float2 float2::Normalized()
{
    float length = std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
    if (length)
        return *this / length;
    else
        return *this;
}

bool float2::AlmostEqual(const float2& other)
{
    if (DistanceTo(other) < 0.01)
        return true;
    return false;
}

float2& float2::Add(const float2& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

float2& float2::Subtract(const float2& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

float2& float2::Multiply(const float2& other)
{
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

float2& float2::Divide(const float2& other)
{
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}

float2& float2::Multiply(const float& other)
{
    this->x *= other;
    this->y *= other;
    return *this;
}

float2& float2::Divide(const float& other)
{
    this->x /= other;
    this->y /= other;
    return *this;
}

float2& float2::Multiply(const int& other)
{
    this->x *= other;
    this->y *= other;
    return *this;
}

float2& float2::Divide(const int& other)
{
    this->x /= other;
    this->y /= other;
    return *this;
}

float2 operator+(const float2& v1, const float2& v2)
{
    return float2(v1.x + v2.x, v1.y + v2.y);
}

float2 operator-(const float2& v1, const float2& v2)
{
    return float2(v1.x - v2.x, v1.y - v2.y);
}

float2 operator*(const float2& v1, const float2& v2)
{
    return float2(v1.x * v2.x, v1.y * v2.y);
}

float2 operator/(const float2& v1, const float2& v2)
{
    return float2(v1.x / v2.x, v1.y / v2.y);
}

float3 operator+(const float2& v1, const float3& v2)
{
    return float3(v1.x + v2.x, v1.y + v2.y, v2.z);
}

float3 operator-(const float2& v1, const float3& v2)
{
    return float3(v1.x - v2.x, v1.y - v2.y, v2.z);
}

float2 operator*(const float2& v1, const float& other)
{
    return float2(v1.x * other, v1.y * other);
}

float2 operator/(const float2& v1, const float& other)
{
    return float2(v1.x / other, v1.y / other);
}

float2 operator*(const float2& v1, const int& other)
{
    return float2(v1.x * other, v1.y * other);
}

float2 operator/(const float2& v1, const int& other)
{
    return float2(v1.x / other, v1.y / other);
}

float2& float2::operator+=(const float2& other)
{
    return this->Add(other);
}

float2& float2::operator-=(const float2& other)
{
    return this->Subtract(other);
}

float2& float2::operator*=(const float2& other)
{
    return this->Multiply(other);
}

float2& float2::operator/=(const float2& other)
{
    return this->Divide(other);
}

float2& float2::operator*=(const float& other)
{
    return this->Multiply(other);
}

float2& float2::operator/=(const float& other)
{
    return this->Divide(other);
}

float2& float2::operator*=(const int& other)
{
    return this->Multiply(other);
}

float2& float2::operator/=(const int& other)
{
    return this->Divide(other);
}

bool float2::operator==(const float2& other)
{
    if (this->x == other.x && this->y == other.y)
        return true;
    return false;
}

bool float2::operator!=(const float2& other)
{
    if (this->x != other.x || this->y != other.y)
        return true;
    return false;
}

float2& float2::Zero()
{
    this->x = 0.0f;
    this->y = 0.0f;
    return *this;
}

int2 float2::ToInt()
{
    return int2((int)this->x, (int)this->y);
}

std::string float2::ToStr()
{
    std::ostringstream oss;
    oss << "(" << this->x << ", " << this->y << ")";
    return oss.str();
}

std::ostream& operator<<(std::ostream& stream, const float2& vec)
{
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}
