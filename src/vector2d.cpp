#include "vector2d.h"
#include "vector3d.h"
#include <cmath>

Vector2D::Vector2D()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::DirectionTo(const Vector2D& other)
{
    return (other - *this).Normalized();
}

Vector3D Vector2D::DirectionTo(const Vector3D& other)
{
    return (other - *this).Normalized();
}

float Vector2D::DistanceTo(const Vector2D& other)
{
    return std::sqrt(std::pow(other.x - this->x, 2) + std::pow(other.y - this->y, 2));
}

Vector2D Vector2D::Normalized()
{
    float length = std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
    if (length)
        return *this / length;
    else
        return *this;
}

bool Vector2D::AlmostEqual(const Vector2D& other)
{
    if (DistanceTo(other) < 0.01)
        return true;
    return false;
}

Vector2D& Vector2D::Add(const Vector2D& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& other)
{
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& other)
{
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}

Vector2D& Vector2D::Multiply(const float& other)
{
    this->x *= other;
    this->y *= other;
    return *this;
}

Vector2D& Vector2D::Divide(const float& other)
{
    this->x /= other;
    this->y /= other;
    return *this;
}

Vector2D& Vector2D::Multiply(const int& other)
{
    this->x *= other;
    this->y *= other;
    return *this;
}

Vector2D& Vector2D::Divide(const int& other)
{
    this->x /= other;
    this->y /= other;
    return *this;
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
{
    return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
{
    return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

Vector2D operator*(const Vector2D& v1, const Vector2D& v2)
{
    return Vector2D(v1.x * v2.x, v1.y * v2.y);
}

Vector2D operator/(const Vector2D& v1, const Vector2D& v2)
{
    return Vector2D(v1.x / v2.x, v1.y / v2.y);
}

Vector3D operator+(const Vector2D& v1, const Vector3D& v2)
{
    return Vector3D(v1.x + v2.x, v1.y + v2.y, v2.z);
}

Vector3D operator-(const Vector2D& v1, const Vector3D& v2)
{
    return Vector3D(v1.x - v2.x, v1.y - v2.y, v2.z);
}

Vector2D operator*(const Vector2D& v1, const float& other)
{
    return Vector2D(v1.x * other, v1.y * other);
}

Vector2D operator/(const Vector2D& v1, const float& other)
{
    return Vector2D(v1.x / other, v1.y / other);
}

Vector2D operator*(const Vector2D& v1, const int& other)
{
    return Vector2D(v1.x * other, v1.y * other);
}

Vector2D operator/(const Vector2D& v1, const int& other)
{
    return Vector2D(v1.x / other, v1.y / other);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    return this->Add(other);
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    return this->Subtract(other);
}

Vector2D& Vector2D::operator*=(const Vector2D& other)
{
    return this->Multiply(other);
}

Vector2D& Vector2D::operator/=(const Vector2D& other)
{
    return this->Divide(other);
}

Vector2D& Vector2D::operator*=(const float& other)
{
    return this->Multiply(other);
}

Vector2D& Vector2D::operator/=(const float& other)
{
    return this->Divide(other);
}

Vector2D& Vector2D::operator*=(const int& other)
{
    return this->Multiply(other);
}

Vector2D& Vector2D::operator/=(const int& other)
{
    return this->Divide(other);
}

bool Vector2D::operator==(const Vector2D& other)
{
    if (this->x == other.x && this->y == other.y)
        return true;
    return false;
}

bool Vector2D::operator!=(const Vector2D& other)
{
    if (this->x != other.x || this->y != other.y)
        return true;
    return false;
}

Vector2D& Vector2D::Zero()
{
    this->x = 0.0f;
    this->y = 0.0f;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}
