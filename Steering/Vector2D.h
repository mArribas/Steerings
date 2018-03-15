#pragma once

class CVector2D
{
public:
    float mX, mY;

    CVector2D ();
    CVector2D (const float x, const float y);
    CVector2D (const CVector2D& v);

    CVector2D& operator=  (const CVector2D& other);
    CVector2D  operator+  (const CVector2D& other) const;
    CVector2D& operator+= (const CVector2D& other);
    CVector2D  operator-  (const CVector2D& other) const;
    CVector2D& operator-= (const CVector2D& other);

    CVector2D  operator+  (const float scalar) const;
    CVector2D& operator+= (const float scalar);
    CVector2D  operator-  (const float scalar) const;
    CVector2D& operator-= (const float scalar);
    CVector2D  operator*  (const float scalar) const;
    CVector2D& operator*= (const float scalar);
    CVector2D  operator/  (const float scalar) const;
    CVector2D& operator/= (const float scalar);

    void Set (const float x, const float y);

    // Rotate the vector by the "degrees" passed.
    void Rotate (const float deg);

    CVector2D& Normalize     ();
    // Returns the perpendicular of the vector normalized.
    CVector2D& Perpendicular ();

    float Dist     (const CVector2D other) const;
    float DegAngle (const CVector2D other) const;
    float RadAngle (const CVector2D other) const;
    float Length   () const;
    void  Truncate (const float length);

    float Dot   (const CVector2D other) const;
    float Cross (const CVector2D other) const;
};