#include "int2.h"
#include "float2.h"
#include <cmath>

int2::int2()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

int2::int2(int x, int y)
{
    this->x = x;
    this->y = y;
}

float2 int2::DirectionTo(const int2& other)
{
    return (other - *this).Normalized();
}

float int2::DistanceTo(const int2& other)
{
    return std::sqrt(std::pow(other.x - this->x, 2) + std::pow(other.y - this->y, 2));
}

float2 int2::Normalized()
{
    float length = std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
    if (length)
        return *this / length;
    else
        return this->ToFloat();
}

int2& int2::Add(const int2& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

int2& int2::Subtract(const int2& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

int2& int2::Multiply(const int2& other)
{
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

int2& int2::Divide(const int2& other)
{
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}

float2 int2::Multiply(const float& other)
{
    float2 newF = this->ToFloat();
    newF *= other;
    return newF;
}

float2 int2::Divide(const float& other)
{
    float2 newF = this->ToFloat();
    newF /= other;
    return newF;
}

int2& int2::Multiply(const int& other)
{
    this->x *= other;
    this->y *= other;
    return *this;
}

int2& int2::Divide(const int& other)
{
    this->x /= other;
    this->y /= other;
    return *this;
}

int2 operator+(const int2& v1, const int2& v2)
{
    return int2(v1.x + v2.x, v1.y + v2.y);
}

int2 operator-(const int2& v1, const int2& v2)
{
    return int2(v1.x - v2.x, v1.y - v2.y);
}

int2 operator*(const int2& v1, const int2& v2)
{
    return int2(v1.x * v2.x, v1.y * v2.y);
}

float2 operator/(const int2& v1, const int2& v2)
{
    return float2(v1.x / (float)v2.x, v1.y / (float)v2.y);
}

float2 operator*(const int2& v1, const float2& other)
{
    return float2(v1.x * other.x, v1.y * other.y);
}

float2 operator/(const int2& v1, const float2& other)
{
    return float2(v1.x / other.x, v1.y / other.y);
}

float2 operator*(const int2& v1, const float& other)
{
    return float2(v1.x * other, v1.y * other);
}

float2 operator/(const int2& v1, const float& other)
{
    return float2(v1.x / other, v1.y / other);
}

int2& int2::operator+=(const int2& other)
{
    return this->Add(other);
}

int2& int2::operator-=(const int2& other)
{
    return this->Subtract(other);
}

int2& int2::operator*=(const int2& other)
{
    return this->Multiply(other);
}

int2& int2::operator*=(const int& other)
{
    return this->Multiply(other);
}

bool int2::operator==(const int2& other)
{
    if (this->x == other.x && this->y == other.y)
        return true;
    return false;
}

bool int2::operator!=(const int2& other)
{
    if (this->x != other.x || this->y != other.y)
        return true;
    return false;
}

int2& int2::Zero()
{
    this->x = 0;
    this->y = 0;
    return *this;
}

float2 int2::ToFloat()
{
    return float2(this->x, this->y);
}

std::ostream& operator<<(std::ostream& stream, const int2& vec)
{
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}
