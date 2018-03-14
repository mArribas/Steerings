#include "WanderSteering.h"

#include "DebugNew.h"
#include "SeekSteering.h"

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
{
    srand (static_cast<unsigned int>(time (nullptr)));

    mTarget         = new SEntity{};
    mWanderAngle    = 0.f;
    mLimitX         = limitX;
    mLimitY         = limitY;
    mReferencePoint = referencePoint;

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

    // Check out of limits.
    BackIfOutOfLimits (mTarget->position);

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