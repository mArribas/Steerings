#include "FleeSteering.h"

#include "DebugNew.h"

CFleeSteering::CFleeSteering (SEntity* const owner, const float radius)
    : ISteering{ owner }
    , mRadius  { radius }
{
}

CFleeSteering::~CFleeSteering (void)
{
}

void CFleeSteering::SetRadius (const float radius)
{
    mRadius = radius;
}

float CFleeSteering::GetRadius (void) const
{
    return mRadius;
}

ISteering* CFleeSteering::GetSteering (void)
{
    float dist{ mTarget->position.Dist (mOwner->position) };

    mWantedLinearVelocity = mOwner->position - mTarget->position;
    mWantedLinearVelocity.Normalize ();

    if (dist <= mRadius) mWantedLinearVelocity *= mOwner->maxLinearVelocity;
    else                 mWantedLinearVelocity  = CVector2D{ 0.f,0.f };

    mLinearAcceleration  = mWantedLinearVelocity - mOwner->linearVelocity;
    mLinearAcceleration.Normalize ();
    mLinearAcceleration *= mOwner->maxLinearAcceleration;

    return this;
}

void CFleeSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D debugWLV{ mOwner->position + mWantedLinearVelocity };
    CVector2D debugLA { mOwner->position + mLinearAcceleration };

    DrawLineEx      (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ debugWLV.mX, debugWLV.mY }
        , 3.f
        , BLUE);
    DrawLineEx      (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
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