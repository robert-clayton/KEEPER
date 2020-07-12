#pragma once

#include <iostream>

class Vector3D
{
public:
    float x;
    float y;
    float z;

    Vector3D();
    Vector3D(const class Vector2D& other);
    Vector3D(float x, float y, float z);

    Vector3D DirectionTo(const Vector3D& other);
    float DistanceTo(const Vector3D& other);
    Vector3D Normalized();
    bool AlmostEqual(const Vector3D& other);

    Vector3D& Add(const Vector3D& other);
    Vector3D& Subtract(const Vector3D& other);
    Vector3D& Multiply(const Vector3D& other);
    Vector3D& Divide(const Vector3D& other);

    Vector3D& Multiply(const float& other);
    Vector3D& Divide(const float& other);
    Vector3D& Multiply(const int& other);
    Vector3D& Divide(const int& other);

    friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator*(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator/(const Vector3D& v1, const Vector3D& v2);

    friend Vector3D operator*(const Vector3D& v1, const float& other);
    friend Vector3D operator/(const Vector3D& v1, const float& other);
    friend Vector3D operator*(const Vector3D& v1, const int& other);
    friend Vector3D operator/(const Vector3D& v1, const int& other);

    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    Vector3D& operator*=(const Vector3D& other);
    Vector3D& operator/=(const Vector3D& other);

    Vector3D& operator*=(const float& other);
    Vector3D& operator/=(const float& other);
    Vector3D& operator*=(const int& other);
    Vector3D& operator/=(const int& other);

    bool operator==(const Vector3D& other);
    bool operator!=(const Vector3D& other);

    Vector3D& Zero();
    class Vector2D To2D();

    friend std::ostream& operator<<(std::ostream& stream, const Vector3D& vec);
};
