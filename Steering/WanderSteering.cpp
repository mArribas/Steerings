#include "WanderSteering.h"

#include "DebugNew.h"
#include "SeekSteering.h"

#include <ctime>

#define TORAD(x) (x * (PI / 180.f))

CWanderSteering::CWanderSteering (
    SEntity* const  owner,
    const float     radius,
    const float     disntance,
    const float     randomFactor,
    const float     limitX,
    const float     limitY,
    const CVector2D referencePoint)
    : ISteering    { owner }
    , mRadius      { radius }
    , mDistance    { disntance }
    , mRandomFactor{ randomFactor }
{
    srand (static_cast<unsigned int>(time (nullptr)));

    mWanderAngle    = 0.f;
    mLimitX         = limitX;
    mLimitY         = limitY;
    mReferencePoint = referencePoint;
}

CWanderSteering::~CWanderSteering (void)
{
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
    mTarget           = new SEntity{};
    mTarget->position = mReferencePoint;

    // Set the target.
    mWanderAngle += -mRandomFactor
        + ((rand () % static_cast<int>(mRandomFactor * 2.0f)) + 1.0f);

    float     angle       {
        atan2 (mOwner->position.mY, mOwner->position.mX) };
    CVector2D circleOffSet{
        mRadius * cos (TORAD (mWanderAngle) + angle)
        , mRadius * sin (TORAD (mWanderAngle) + angle) };
    CVector2D circleloc   { mOwner->linearVelocity };
    circleloc.Normalize ();
    circleloc *= mDistance;
    circleloc += mOwner->position;

    mTarget->position  = circleloc;
    mTarget->position += circleOffSet;

    // Move to the target.
    CSeekSteering* seek{ new CSeekSteering{ mOwner, 0.f } };
    seek->SetTarget (mTarget);
    seek->GetSteering ();
    mWantedLinearVelocity = seek->GetWantedLinearVelocity ();
    mLinearAcceleration   = seek->GetLinearAcceleration ();

    delete seek;

    // Check out of limits.
    BackIfOutOfLimits (mTarget->position);
    BackIfOutOfLimits (mOwner->position);

    delete mTarget;

    return this;
}

void CWanderSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D debugWLV    { mOwner->position + mWantedLinearVelocity };
    CVector2D debugLA     { mOwner->position + mLinearAcceleration };
    float     angle       {
        atan2 (mOwner->position.mY, mOwner->position.mX) };
    CVector2D circleOffSet{
        mRadius * cos (TORAD (mWanderAngle) + angle)
        , mRadius * sin (TORAD (mWanderAngle) + angle) };
    CVector2D circleloc   { mOwner->linearVelocity };
    circleloc.Normalize ();
    circleloc *= mDistance;
    circleloc += mOwner->position;
    CVector2D target      { circleloc + circleOffSet };

    DrawLineEx         (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ debugWLV.mX, debugWLV.mY }
        , 3.f
        , BLUE);
    DrawLineEx         (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ debugLA.mX, debugLA.mY }
        , 3.f
        , RED);
    DrawCircleLines    (circleloc.mX, circleloc.mY, mRadius, DARKGRAY);
    DrawLine           (
        mOwner->position.mX
        , mOwner->position.mY
        , circleloc.mX
        , circleloc.mY
        , GREEN);
    DrawLine           (
        circleloc.mX
        , circleloc.mY
        , target.mX
        , target.mY
        , GREEN);
    DrawCircle         (
        target.mX
        , target.mY
        , 5.f
        , BURGUNDY);
    DrawText           (
        "TARGET"
        , target.mX
        , target.mY
        , 10
        , BURGUNDY);
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