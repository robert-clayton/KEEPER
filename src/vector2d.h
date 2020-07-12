#pragma once

#include <iostream>

class Vector2D
{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D DirectionTo(const Vector2D& other);
    float DistanceTo(const Vector2D& other);
    Vector2D Normalized();
    bool AlmostEqual(const Vector2D& other);

    Vector2D& Add(const Vector2D& other);
    Vector2D& Subtract(const Vector2D& other);
    Vector2D& Multiply(const Vector2D& other);
    Vector2D& Divide(const Vector2D& other);

    Vector2D& Multiply(const float& other);
    Vector2D& Divide(const float& other);
    Vector2D& Multiply(const int& other);
    Vector2D& Divide(const int& other);

    friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator*(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator/(const Vector2D& v1, const Vector2D& v2);

    friend Vector2D operator*(const Vector2D& v1, const float& other);
    friend Vector2D operator/(const Vector2D& v1, const float& other);
    friend Vector2D operator*(const Vector2D& v1, const int& other);
    friend Vector2D operator/(const Vector2D& v1, const int& other);

    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(const Vector2D& other);
    Vector2D& operator/=(const Vector2D& other);

    Vector2D& operator*=(const float& other);
    Vector2D& operator/=(const float& other);
    Vector2D& operator*=(const int& other);
    Vector2D& operator/=(const int& other);

    bool operator==(const Vector2D& other);
    bool operator!=(const Vector2D& other);

    Vector2D& Zero();

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};
