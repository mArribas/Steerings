#include "ArriveSteering.h"

#include "DebugNew.h"
#include "Entity.h"

CArriveSteering::CArriveSteering (SEntity* const owner, const float radius)
    : ISteering{ owner  }
    , mRadius  { radius }
{
}

CArriveSteering::~CArriveSteering (void)
{
}

void CArriveSteering::SetRadius (const float radius)
{
    mRadius = radius;
}

float CArriveSteering::GetRadius (void) const
{
    return mRadius;
}

ISteering* CArriveSteering::GetSteering (void)
{
    CVector2D currentPosition  { mOwner->position };
    float     maxLinearVelocity{ mOwner->maxLinearVelocity };
    float     dist             { mTarget->position.Dist (currentPosition) };

    mWantedLinearVelocity = mTarget->position - currentPosition;
    mWantedLinearVelocity.Normalize ();

    if (dist > mRadius)
    {
        mWantedLinearVelocity *= maxLinearVelocity;
    }
    else
    {
        float maxVel = (dist / mRadius) * maxLinearVelocity;
        mWantedLinearVelocity *= maxVel;
    }

    mLinearAcceleration = mWantedLinearVelocity - mOwner->linearVelocity;
    mLinearAcceleration.Normalize ();
    mLinearAcceleration *= mOwner->maxLinearAcceleration;

    return this;
}

void CArriveSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D origin  { mOwner->position };
    CVector2D debugWLV{ origin + mWantedLinearVelocity };
    CVector2D debugLA { origin + mLinearAcceleration };

    DrawLine        (origin.mX, origin.mY, debugWLV.mX, debugWLV.mY, BLUE);
    DrawLine        (origin.mX, origin.mY, debugLA.mX, debugLA.mY, RED);
    DrawCircleLines (
        mTarget->position.mX
        , mTarget->position.mY
        , mRadius
        , DARKGRAY);
#pragma warning(pop)
}