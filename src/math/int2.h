#pragma once

#include <iostream>

class float2;

class int2
{
public:
    int x;
    int y;

    int2();
    int2(int x, int y);

    float2 DirectionTo(const int2& other);
    float DistanceTo(const int2& other);
    float2 Normalized();

    int2& Add(const int2& other);
    int2& Subtract(const int2& other);
    int2& Multiply(const int2& other);
    int2& Divide(const int2& other);

    float2 Multiply(const float& other);
    float2 Divide(const float& other);
    int2& Multiply(const int& other);
    int2& Divide(const int& other);

    friend int2 operator+(const int2& v1, const int2& v2);
    friend int2 operator-(const int2& v1, const int2& v2);
    friend int2 operator*(const int2& v1, const int2& v2);
    friend float2 operator/(const int2& v1, const int2& v2);

    friend float2 operator*(const int2& v1, const float& other);
    friend float2 operator/(const int2& v1, const float& other);
    friend float2 operator*(const int2& v1, const int& other);
    friend float2 operator/(const int2& v1, const int& other);

    int2& operator+=(const int2& other);
    int2& operator-=(const int2& other);
    int2& operator*=(const int2& other);

    int2& operator*=(const int& other);

    bool operator==(const int2& other);
    bool operator!=(const int2& other);

    int2& Zero();
    float2 ToFloat();
    std::string ToStr();

    friend std::ostream& operator<<(std::ostream& stream, const int2& vec);
};
