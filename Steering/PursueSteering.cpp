#include "PursueSteering.h"

#include "DebugNew.h"
#include "SeekSteering.h"

CPursueSteering::CPursueSteering (
    SEntity* const  owner,
    const float     secondsAhead,
    const float     limitX,
    const float     limitY,
    const CVector2D referencePoint)
    : ISteering    { owner }
    , mSecondsAhead{ secondsAhead }
{
    mLimitX = limitX;
    mLimitY = limitY;
    mReferencePoint = referencePoint;
}

CPursueSteering::~CPursueSteering (void)
{
}

void CPursueSteering::SetSecondsAhead (const float secondsAhead)
{
    mSecondsAhead = secondsAhead;
}

float CPursueSteering::GetSecondsAhead (void) const
{
    return mSecondsAhead;
}

ISteering* CPursueSteering::GetSteering (void)
{
    CVector2D currentPosition{ mOwner->position };
    SEntity* aheadTarget = new SEntity{};

    aheadTarget->position =
        mTarget->position
        + (mTarget->linearVelocity * mSecondsAhead);

    // Move to the ahead target.
    CSeekSteering* seek = new CSeekSteering{ mOwner, 0.f };
    seek->SetTarget (aheadTarget);
    seek->GetSteering ();
    mWantedLinearVelocity = seek->GetWantedLinearVelocity ();
    mLinearAcceleration   = seek->GetLinearAcceleration ();

    delete seek;
    delete aheadTarget;

    // Check out of limits.
    BackIfOutOfLimits (mOwner->position);

    return this;
}

void CPursueSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D origin    { mOwner->position };
    CVector2D debugWLV  { origin + mWantedLinearVelocity };
    CVector2D debugLA   { origin + mLinearAcceleration };
    CVector2D prediction{
        mTarget->position
        + (mTarget->linearVelocity * mSecondsAhead) };

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
    DrawLine (origin.mX, origin.mY, prediction.mX, prediction.mY, BURGUNDY);
    DrawCircle (
        prediction.mX
        , prediction.mY
        , 5.f
        , BURGUNDY);
    DrawText (
        "PREDICTION"
        , prediction.mX - 45.f
        , prediction.mY + 5.f
        , 10
        , BURGUNDY);
    DrawRectangleLines (
        mReferencePoint.mX - mLimitX
        , mReferencePoint.mY - mLimitY
        , mLimitX * 2
        , mLimitY * 2
        , DARKGRAY);
    DrawText (
        "LIMIT X"
        , mReferencePoint.mX - mLimitX - 45.f
        , mReferencePoint.mY
        , 10
        , DARKGRAY);
    DrawText (
        "LIMIT X"
        , mReferencePoint.mX + mLimitX + 5.f
        , mReferencePoint.mY
        , 10
        , DARKGRAY);
    DrawText (
        "LIMIT Y"
        , mReferencePoint.mX - 35.f
        , mReferencePoint.mY - mLimitY - 15.f
        , 10
        , DARKGRAY);
    DrawText (
        "LIMIT Y"
        , mReferencePoint.mX - 35.f
        , mReferencePoint.mY + mLimitY + 5.f
        , 10
        , DARKGRAY);
#pragma warning(pop)
}