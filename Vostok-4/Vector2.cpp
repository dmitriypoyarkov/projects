#include "Vector2.h"

    Vector2::Vector2()
    {
        x = 0; y = 0;
    }
    Vector2::Vector2(const float x, const float y)
    {
        this->x = x; this->y = y;
    }

    Vector2 Vector2::operator + (const Vector2& A) const
    {
        return Vector2(x + A.x, y + A.y);
    }

    Vector2 Vector2::operator - (const Vector2& A) const
    {
        return Vector2(x - A.x, y - A.y);
    }

    Vector2 Vector2::operator + (const float A) const
    {
        return Vector2(x + A, y + A);
    }

    Vector2 Vector2::operator += (const Vector2& A)
    {
        x += A.x; y += A.y;
        return *this;
    }

    Vector2 Vector2::operator / (const float A) const
    {
        return Vector2(x / A, y / A);
    }

    Vector2 Vector2::operator * (const float A) const
    {
        return Vector2(x * A, y * A);
    }

	float Vector2::magnitude() const
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

    Vector2 Vector2::normalized()
    {
		if (magnitude() != 0)
		{
			return *this / magnitude();
		}
		else
		{
			return *this;
		}
    }

    float Vector2::Dot(const Vector2& A) const
    {
        return A.x * x + A.y * y;
    }

	float Vector2::Angle(const Vector2 a, const Vector2 b)
	{
		float cosin = VectorCos(a, b);
		float acosin = acosf(cosin);
		if (b.y - a.y < 0)
			acosin = -acosin;
		return acosin;
	}

	float Vector2::AngleDeg(const Vector2 a, const Vector2 b)
	{
		return Angle(a,b)/ 0.0174533f;
	}

	float Vector2::VectorSin(const Vector2 a, const Vector2 b)
	{
		float sinus = 1 - pow(VectorCos(a, b), 2);
		if (a.y < b.y)
			sinus = -sinus;
		return sinus;
	}

	float Vector2::VectorCos(const Vector2 a, const Vector2 b)
	{
		if (a.magnitude() == 0 || b.magnitude() == 0) return 0;
		float cosin = a.Dot(b) / (a.magnitude() * b.magnitude());
		return cosin;
	}
	
	bool operator == (const Vector2 left, const Vector2 right)
	{
		if (left.x == right.x && left.y == right.y)
			return true;
		else
			return false;
	}