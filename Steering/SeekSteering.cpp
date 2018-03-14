#include "SeekSteering.h"

#include "DebugNew.h"

CSeekSteering::CSeekSteering (SEntity* const owner, const float radius)
    : ISteering{ owner }
    , mRadius{ radius }
{
}

CSeekSteering::~CSeekSteering (void)
{
}

void CSeekSteering::SetRadius (const float radius)
{
    mRadius = radius;
}

float CSeekSteering::GetRadius (void) const
{
    return mRadius;
}

ISteering* CSeekSteering::GetSteering (void)
{
    CVector2D currentPosition  { mOwner->position };
    float     maxLinearVelocity{ mOwner->maxLinearVelocity };
    float     dist             { mTarget->position.Dist (currentPosition) };

    mWantedLinearVelocity = mTarget->position - currentPosition;
    mWantedLinearVelocity.Normalize ();

    if (dist > mRadius) mWantedLinearVelocity *= maxLinearVelocity ;
    else                mWantedLinearVelocity  = CVector2D{ 0.f,0.f };

    mLinearAcceleration = mWantedLinearVelocity - mOwner->linearVelocity;
    mLinearAcceleration.Normalize ();
    mLinearAcceleration *= mOwner->maxLinearAcceleration;

    return this;
}

void CSeekSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D origin  { mOwner->position };
    CVector2D debugWLV{ origin + mWantedLinearVelocity };
    CVector2D debugLA { origin + mLinearAcceleration };

    DrawLineEx (
        Vector2{ origin.mX, origin.mY }
        , Vector2{ debugWLV.mX, debugWLV.mY }
        , 3.f
        , BLUE);
    DrawLineEx (
        Vector2{ origin.mX, origin.mY }
        , Vector2{ debugLA.mX, debugLA.mY }
        , 3.f
        , RED);
    DrawCircleLines (
        mTarget->position.mX
        , mTarget->position.mY
        , mRadius
        , DARKGRAY);
#pragma warning(pop)
}