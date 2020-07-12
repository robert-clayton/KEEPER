#include "vector3d.h"
#include "vector2d.h"
#include <cmath>

Vector3D::Vector3D()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3D::Vector3D(const Vector2D& other)
{
    this->x = other.x;
    this->y = other.y;
}

Vector3D::Vector3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D Vector3D::DirectionTo(const Vector3D& other)
{
    return (other - *this).Normalized();
}

float Vector3D::DistanceTo(const Vector3D& other)
{
    return std::sqrt(std::pow(other.x - this->x, 2)
                     + std::pow(other.y - this->y, 2)
                     + std::pow(other.z - this->z, 2));
}

Vector3D Vector3D::Normalized()
{
    float length = std::sqrt(std::pow(this->x, 2)
                             + std::pow(this->y, 2)
                             + std::pow(this->z, 2));
    if (length)
        return *this / length;
    else
        return *this;
}

bool Vector3D::AlmostEqual(const Vector3D& other)
{
    if (DistanceTo(other) < 0.01)
        return true;
    return false;
}

Vector3D& Vector3D::Add(const Vector3D& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vector3D& Vector3D::Subtract(const Vector3D& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vector3D& Vector3D::Multiply(const Vector3D& other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

Vector3D& Vector3D::Divide(const Vector3D& other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

Vector3D& Vector3D::Multiply(const float& other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

Vector3D& Vector3D::Divide(const float& other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

Vector3D& Vector3D::Multiply(const int& other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

Vector3D& Vector3D::Divide(const int& other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

Vector3D operator+(const Vector3D& v1, const Vector3D& v2)
{
    return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3D operator-(const Vector3D& v1, const Vector3D& v2)
{
    return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3D operator*(const Vector3D& v1, const Vector3D& v2)
{
    return Vector3D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3D operator/(const Vector3D& v1, const Vector3D& v2)
{
    return Vector3D(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vector3D operator*(const Vector3D& v1, const float& other)
{
    return Vector3D(v1.x * other, v1.y * other, v1.z * other);
}

Vector3D operator/(const Vector3D& v1, const float& other)
{
    return Vector3D(v1.x / other, v1.y / other, v1.z / other);
}

Vector3D operator*(const Vector3D& v1, const int& other)
{
    return Vector3D(v1.x * other, v1.y * other, v1.z * other);
}

Vector3D operator/(const Vector3D& v1, const int& other)
{
    return Vector3D(v1.x / other, v1.y / other, v1.z / other);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    return this->Add(other);
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    return this->Subtract(other);
}

Vector3D& Vector3D::operator*=(const Vector3D& other)
{
    return this->Multiply(other);
}

Vector3D& Vector3D::operator/=(const Vector3D& other)
{
    return this->Divide(other);
}

Vector3D& Vector3D::operator*=(const float& other)
{
    return this->Multiply(other);
}

Vector3D& Vector3D::operator/=(const float& other)
{
    return this->Divide(other);
}

Vector3D& Vector3D::operator*=(const int& other)
{
    return this->Multiply(other);
}

Vector3D& Vector3D::operator/=(const int& other)
{
    return this->Divide(other);
}

bool Vector3D::operator==(const Vector3D& other)
{
    if (this->x == other.x && this->y == other.y && this->z == other.z)
        return true;
    return false;
}

bool Vector3D::operator!=(const Vector3D& other)
{
    if (this->x != other.x || this->y != other.y || this->z != other.z)
        return true;
    return false;
}

Vector3D& Vector3D::Zero()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    return *this;
}

Vector2D Vector3D::To2D()
{
    return Vector2D(this->x, this->y);
}

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
{
    stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return stream;
}
