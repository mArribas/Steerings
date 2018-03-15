#include "AlignSteering.h"

#include "DebugNew.h"

#define TODEG(x) (x * (180.f / PI))
#define TORAD(x) (x * (PI / 180.f))

CAlignSteering::CAlignSteering (
    SEntity* const       owner,
    const unsigned short softRadius,
    const unsigned short stopRadius)
    : ISteering  { owner }
    , mSoftRadius{ softRadius }
    , mStopRadius{ stopRadius }
{
}

CAlignSteering::~CAlignSteering (void)
{
}

void CAlignSteering::SetSoftRadius (const unsigned short radius)
{
    mSoftRadius = radius;
}

void CAlignSteering::SetStopRadius (const unsigned short radius)
{
    mStopRadius = radius;
}

unsigned short CAlignSteering::GetSoftRadius (void) const
{
    return mSoftRadius;
}

unsigned short CAlignSteering::GetStopRadius (void) const
{
    return mStopRadius;
}

ISteering* CAlignSteering::GetSteering (void)
{
    float maxAngularVelocity    {
        WrapRad (TORAD (mOwner->maxAngularVelocity)) };
    float maxAngularAcceleration{
        WrapRad (TORAD(mOwner->maxAngularAcceleration)) };
    float angularVelocity       { mOwner->angularVelocity };
    float rotation              { 0.0f };
    float rotationSize          { 0.0f };

    rotation     =
        mOwner->position.RadAngle (mTarget->position)
        - TORAD (WrapDeg (mOwner->angle));
    rotation     = WrapRad (rotation);
    rotationSize = abs (rotation);

    if (rotationSize <= WrapRad (TORAD (WrapDeg (mStopRadius))))
    {
        mOwner->angularVelocity = 0.f;
        mWantedAngularVelocity  = 0.f;
        mAngularAcceleration    = 0.f;

        return this;
    }

    if (rotationSize
        > WrapRad (TORAD (WrapDeg (mSoftRadius))))
    {
        mWantedAngularVelocity = maxAngularVelocity;
    }
    else
    {
        mWantedAngularVelocity = rotationSize * maxAngularVelocity;
    }

    if (mWantedAngularVelocity > maxAngularVelocity)
    {
        mWantedAngularVelocity = maxAngularVelocity;
    }

    mWantedAngularVelocity *= rotation / rotationSize;

    mAngularAcceleration =
        mWantedAngularVelocity - WrapRad (TORAD (angularVelocity));

    if (mAngularAcceleration > maxAngularAcceleration)
    {
        mAngularAcceleration = maxAngularAcceleration;
    }

    mAngularAcceleration   = TODEG (mAngularAcceleration);
    mWantedAngularVelocity = TODEG (mWantedAngularVelocity);

    return this;
}

void CAlignSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D target{
        mOwner->position.mX 
            * cos (mOwner->position.RadAngle (mTarget->position))
        , mOwner->position.mX
            * sin (mOwner->position.RadAngle (mTarget->position)) };

    DrawLineEx (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ mOwner->position.mX + (60.f * cos (TORAD (0)))
            , mOwner->position.mX + (60.f * sin (TORAD (0))) }
        , 3.f
        , RED);
    DrawLineEx (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ mOwner->position.mX + (60.f * cos (TORAD (90)))
            , mOwner->position.mX + (60.f * sin (TORAD (90))) }
        , 3.f
        , BLUE);
    DrawLineEx (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ mOwner->position.mX + (60.f * cos (TORAD (180)))
            , mOwner->position.mX + (60.f * sin (TORAD (180))) }
        , 3.f
        , YELLOW);
    DrawLineEx (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ mOwner->position.mX + (60.f * cos (TORAD (270)))
            , mOwner->position.mX + (60.f * sin (TORAD (270))) }
        , 3.f
        , GREEN);
    DrawLineV (
        Vector2{ mOwner->position.mX,  mOwner->position.mY }
        , Vector2{ mTarget->position.mX, mTarget->position.mY }
        , BURGUNDY);
#pragma warning(pop)
}

float CAlignSteering::WrapRad (float angle)
{
    while ((angle > PI) || (angle < -PI))
    {
        if      (angle > PI)  angle -= 2 * PI;
        else if (angle < -PI) angle += 2 * PI;
    }

    return angle;
}

float CAlignSteering::WrapDeg (float angle)
{
    while (angle < 0.0f || angle > 360.f)
    {
        if      (angle > 360) angle -= 360.0f;
        else if (angle < 0)   angle += 360.0f;
    }

    return angle;
}