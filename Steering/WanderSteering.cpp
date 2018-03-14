#include "WanderSteering.h"

#include "DebugNew.h"
#include "Entity.h"
#include "SeekSteering.h"

#include <cmath>
#include <ctime>

CWanderSteering::CWanderSteering (
    SEntity* const  owner,
    const float     radius,
    const float     disntance,
    const float     randomFactor,
    const float     limitX,
    const float     limitY,
    const CVector2D referencePoint)
    : ISteering      { owner }
    , mRadius        { radius }
    , mDistance      { disntance }
    , mRandomFactor  { randomFactor }
    , mLimitX        { limitX }
    , mLimitY        { limitY }
    , mReferencePoint{referencePoint}
{
    srand (static_cast<unsigned int>(time (nullptr)));

    mTarget      = new SEntity{};
    mWanderAngle = 0.f;

    mTarget->label       = "TARGET";
    mTarget->position    = mReferencePoint;
    mTarget->sprite.tint = BURGUNDY;
}

CWanderSteering::~CWanderSteering (void)
{
    delete mTarget;
}

void CWanderSteering::SetRadius (const float radius)
{
    mRadius = radius;
}

void CWanderSteering::SetDistance (const float disntance)
{
    mDistance = disntance;
}

void CWanderSteering::SetRandomFactor (const float randomFactor)
{
    mRandomFactor = randomFactor;
}

void CWanderSteering::SetWanderAngle (const float wanderAngle)
{
    mWanderAngle = wanderAngle;
}

void CWanderSteering::SetLimitX (const float limitX)
{
    mLimitX = limitX;
}

void CWanderSteering::SetLimitY (const float limitY)
{
    mLimitY = limitY;
}

void CWanderSteering::SetReferencePoint (const CVector2D referencePoint)
{
    mReferencePoint = referencePoint;
}

float CWanderSteering::GetRadius (void) const
{
    return mRadius;
}

float CWanderSteering::GetDistance (void) const
{
    return mDistance;
}

float CWanderSteering::GetRandomFactor (void) const
{
    return mRandomFactor;
}

float CWanderSteering::GetWanderAngle (void) const
{
    return mWanderAngle;
}

float CWanderSteering::GetLimitX (void) const
{
    return mLimitX;
}

float CWanderSteering::GetLimitY (void) const
{
    return mLimitY;
}

CVector2D CWanderSteering::GetReferencePoint (void) const
{
    return mReferencePoint;
}

ISteering* CWanderSteering::GetSteering (void)
{
    CVector2D currentPosition { mOwner->position };

    // Set the target.

    mWanderAngle += -mRandomFactor
        + ((rand () % static_cast<int>(mRandomFactor * 2.0f)) + 1.0f);

    CVector2D circleloc{ mOwner->linearVelocity };
    circleloc.Normalize ();
    circleloc *= mDistance;
    circleloc += currentPosition;

    float angle = atan2 (
            mTarget->position.mY - currentPosition.mY
            , mTarget->position.mX - currentPosition.mX);

    CVector2D circleOffSet = CVector2D{
        mRadius * cos (mWanderAngle + angle)
        , mRadius * sin (mWanderAngle + angle) };

    mTarget->position  = circleloc;
    mTarget->position += circleOffSet;

    // Move to the target.

    CSeekSteering* seek = new CSeekSteering{ mOwner, 0.f };
    seek->SetTarget (mTarget);
    seek->GetSteering ();
    mWantedLinearVelocity = seek->GetWantedLinearVelocity ();
    mLinearAcceleration   = seek->GetLinearAcceleration ();

    delete seek;

    // Check 'x' and 'y' axes limits.

    if (mTarget->position.mX < (mReferencePoint.mX - mLimitX))
    {
        mWantedLinearVelocity.mX = abs (mWantedLinearVelocity.mX);
        mLinearAcceleration.mX   = abs (mLinearAcceleration.mX);
    }

    if (mTarget->position.mX > (mReferencePoint.mX + mLimitX))
    {
        mWantedLinearVelocity.mX = -abs (mWantedLinearVelocity.mX);
        mLinearAcceleration.mX   = -abs (mLinearAcceleration.mX);
    }

    if (mTarget->position.mY < (mReferencePoint.mY - mLimitY))
    {
        mWantedLinearVelocity.mY = abs (mWantedLinearVelocity.mY);
        mLinearAcceleration.mY   = abs (mLinearAcceleration.mY);
    }

    if (mTarget->position.mY > (mReferencePoint.mY + mLimitY))
    {
        mWantedLinearVelocity.mY = -abs (mWantedLinearVelocity.mY);
        mLinearAcceleration.mY   = -abs (mLinearAcceleration.mY);
    }

    return this;
}

void CWanderSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D origin   { mOwner->position };
    CVector2D debugWLV { origin + mWantedLinearVelocity };
    CVector2D debugLA  { origin + mLinearAcceleration };
    CVector2D circleloc{ mOwner->linearVelocity };

    circleloc.Normalize ();
    circleloc *= mDistance;
    circleloc += origin;

    DrawLine           (origin.mX, origin.mY, debugWLV.mX, debugWLV.mY, BLUE);
    DrawLine           (origin.mX, origin.mY, debugLA.mX, debugLA.mY, RED);
    DrawCircleLines    (circleloc.mX, circleloc.mY, mRadius, DARKGRAY);
    DrawLine           (origin.mX, origin.mY, circleloc.mX, circleloc.mY, GREEN);
    DrawLine           (
        circleloc.mX
        , circleloc.mY
        , mTarget->position.mX
        , mTarget->position.mY
        , GREEN);
    mTarget->DrawDebug ();
    DrawRectangleLines (
        mReferencePoint.mX - mLimitX
        , mReferencePoint.mY - mLimitY
        , mLimitX * 2
        , mLimitY * 2
        , DARKGRAY);
    DrawText           (
        "LIMIT X"
        , mReferencePoint.mX - mLimitX - 45.f
        , mReferencePoint.mY
        , 10
        , DARKGRAY);
    DrawText           (
        "LIMIT X"
        , mReferencePoint.mX + mLimitX + 5.f
        , mReferencePoint.mY
        , 10
        , DARKGRAY);
    DrawText           (
        "LIMIT Y"
        , mReferencePoint.mX - 35.f
        , mReferencePoint.mY - mLimitY - 15.f
        , 10
        , DARKGRAY);
    DrawText           (
        "LIMIT Y"
        , mReferencePoint.mX - 35.f
        , mReferencePoint.mY + mLimitY + 5.f
        , 10
        , DARKGRAY);
#pragma warning(pop)
}