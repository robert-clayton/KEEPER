#pragma once

#include <iostream>

class float2;

class float3
{
public:
    float x;
    float y;
    float z;

    float3();
    float3(const class float2& other);
    float3(float x, float y, float z);

    float3 DirectionTo(const float3& other);
    float3 DirectionTo(const float2& other);
    float DistanceTo(const float3& other);

    float3 Normalized();
    bool AlmostEqual(const float3& other);

    float3& Add(const float3& other);
    float3& Subtract(const float3& other);
    float3& Multiply(const float3& other);
    float3& Divide(const float3& other);

    float3& Multiply(const float& other);
    float3& Divide(const float& other);
    float3& Multiply(const int& other);
    float3& Divide(const int& other);

    friend float3 operator+(const float3& v1, const float3& v2);
    friend float3 operator-(const float3& v1, const float3& v2);
    friend float3 operator*(const float3& v1, const float3& v2);
    friend float3 operator/(const float3& v1, const float3& v2);

    friend float3 operator*(const float3& v1, const float& other);
    friend float3 operator/(const float3& v1, const float& other);
    friend float3 operator*(const float3& v1, const int& other);
    friend float3 operator/(const float3& v1, const int& other);

    float3& operator+=(const float3& other);
    float3& operator-=(const float3& other);
    float3& operator*=(const float3& other);
    float3& operator/=(const float3& other);

    float3& operator*=(const float& other);
    float3& operator/=(const float& other);
    float3& operator*=(const int& other);
    float3& operator/=(const int& other);

    bool operator==(const float3& other);
    bool operator!=(const float3& other);

    float3& Zero();
    float2 To2D();

    friend std::ostream& operator<<(std::ostream& stream, const float3& vec);
};
