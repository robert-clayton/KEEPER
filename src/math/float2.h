#pragma once

#include <iostream>

class float3;
class int2;

class float2
{
public:
    float x;
    float y;

    float2();
    float2(float x, float y);

    float2 DirectionTo(const float2& other);
    float3 DirectionTo(const float3& other);
    float DistanceTo(const float2& other);
    float2 Normalized();
    bool AlmostEqual(const float2& other);

    float2& Add(const float2& other);
    float2& Subtract(const float2& other);
    float2& Multiply(const float2& other);
    float2& Divide(const float2& other);

    float2& Multiply(const float& other);
    float2& Divide(const float& other);
    float2& Multiply(const int& other);
    float2& Divide(const int& other);

    friend float2 operator+(const float2& v1, const float2& v2);
    friend float2 operator-(const float2& v1, const float2& v2);
    friend float2 operator*(const float2& v1, const float2& v2);
    friend float2 operator/(const float2& v1, const float2& v2);

    friend float3 operator+(const float2& v1, const float3& v2);
    friend float3 operator-(const float2& v1, const float3& v2);

    friend float2 operator*(const float2& v1, const float& other);
    friend float2 operator/(const float2& v1, const float& other);
    friend float2 operator*(const float2& v1, const int& other);
    friend float2 operator/(const float2& v1, const int& other);

    float2& operator+=(const float2& other);
    float2& operator-=(const float2& other);
    float2& operator*=(const float2& other);
    float2& operator/=(const float2& other);

    float2& operator*=(const float& other);
    float2& operator/=(const float& other);
    float2& operator*=(const int& other);
    float2& operator/=(const int& other);

    bool operator==(const float2& other);
    bool operator!=(const float2& other);

    float2& Zero();
    int2 ToInt();

    friend std::ostream& operator<<(std::ostream& stream, const float2& vec);
};
