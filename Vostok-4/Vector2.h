#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

class Vector2
{
public:
    float x, y;

    Vector2();

    Vector2(const float x, const float y);

    Vector2 operator + (const Vector2& A) const;

    Vector2 operator + (const float A) const;

    Vector2 operator += (const Vector2& A);

    Vector2 operator - (const Vector2& A) const;

    Vector2 operator / (const float A) const;

    Vector2 operator * (const float A) const;

	float magnitude() const;

    Vector2 normalized();

	friend bool operator == (const Vector2 left, const Vector2 right);

    float Dot(const Vector2& A) const;
	static float Angle(const Vector2 a, const Vector2 b);
	static float AngleDeg(const Vector2 a, const Vector2 b);
	static float VectorSin(const Vector2 a, const Vector2 b);
	static float VectorCos(const Vector2 a, const Vector2 b);

	operator sf::Vector2f() const;
};