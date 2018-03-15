#include "Vector2D.h"

#include "DebugNew.h"

#include <cmath>

const float PI = 3.14159265359f;

CVector2D::CVector2D () : mX{ 0.0 }, mY{ 0.0 }
{

}

CVector2D::CVector2D (const float x, const float y) : mX{ x }, mY{ y }
{

}

CVector2D::CVector2D (const CVector2D& other) : mX{ other.mX }, mY{ other.mY }
{

}

CVector2D& CVector2D::operator= (const CVector2D& other)
{
    mX = other.mX;
    mY = other.mY;

    return *this;
}

CVector2D CVector2D::operator+ (const CVector2D& other) const
{
    return CVector2D (mX + other.mX, mY + other.mY);
}

CVector2D& CVector2D::operator+= (const CVector2D& other)
{
    mX += other.mX;
    mY += other.mY;

    return *this;
}

CVector2D CVector2D::operator- (const CVector2D& other) const
{
    return CVector2D (mX - other.mX, mY - other.mY);
}

CVector2D& CVector2D::operator-= (const CVector2D& other)
{
    mX -= other.mX;
    mY -= other.mY;

    return *this;
}

CVector2D CVector2D::operator+ (const float scalar) const
{
    return CVector2D (mX + scalar, mY + scalar);
}

CVector2D& CVector2D::operator+= (const float scalar)
{
    mX += scalar;
    mY += scalar;

    return *this;
}

CVector2D CVector2D::operator- (const float scalar) const
{
    return CVector2D (mX - scalar, mY - scalar);
}

CVector2D& CVector2D::operator-= (const float scalar)
{
    mX -= scalar;
    mY -= scalar;

    return *this;
}

CVector2D CVector2D::operator* (const float scalar) const
{
    return CVector2D (mX * scalar, mY * scalar);
}

CVector2D& CVector2D::operator*= (const float scalar)
{
    mX *= scalar;
    mY *= scalar;

    return *this;
}

CVector2D CVector2D::operator/ (const float scalar) const
{
    return CVector2D (mX / scalar, mY / scalar);
}

CVector2D& CVector2D::operator/= (const float scalar)
{
    mX /= scalar;
    mY /= scalar;

    return *this;
}

void CVector2D::Set (const float x, const float y)
{
    this->mX = x;
    this->mY = y;
}

void CVector2D::Rotate (const float deg)
{
    float theta { deg / 180.f * PI        };
    float cosine{ cos (theta)             };
    float sine  { sin (theta)             };
    float x     { mX * cosine - mY * sine };
    float y     { mX * sine + mY * cosine };

    mX = x;
    mY = y;
}

CVector2D& CVector2D::Normalize ()
{
    float length = Length ();

    if (length == 0)
        return *this;

    *this *= (1.f / length);

    return *this;
}

CVector2D& CVector2D::Perpendicular ()
{
    // The perpendicular of a vector (x, y) can be (-y, x) or (y, -x).
    float x{ mX };
    float y{ mY };

    mX = -y;
    mY = x;

    return this->Normalize ();
}

float CVector2D::Dist (const CVector2D other) const
{
    CVector2D distance{ other.mX - mX, other.mY - mY };

    return distance.Length ();
}

float CVector2D::DegAngle (const CVector2D other) const
{
    return atan2 (mY - other.mY, other.mX - mX) * 180 / PI;
}

float CVector2D::RadAngle (const CVector2D other) const
{
    return atan2 (mY - other.mY, other.mX - mX);
}

float CVector2D::Length () const
{
    return std::sqrt (mX * mX + mY * mY);
}

void CVector2D::Truncate (const float length)
{
    float angle{ atan2 (mY, mX) };

    mX = length * cos (angle);
    mY = length * sin (angle);
}

float CVector2D::Dot (const CVector2D other)const
{
    return (mX * other.mX) + (mY * other.mY);
}

float CVector2D::Cross (const CVector2D other) const
{
    return (mX * other.mY) - (mY * other.mX);
}