#include "PathFolllowingSteering.h"

#include "DebugNew.h"
#include "SeekSteering.h"

CPathFolllowingSteering::CPathFolllowingSteering (
    SEntity* const owner,
    const Path     path,
    const float    secondsAhead)
    : ISteering    { owner }
    , mPath        { path }
    , mSecondsAhead{ secondsAhead }
{
    mTarget = new SEntity{};
}

CPathFolllowingSteering::~CPathFolllowingSteering (void)
{
    delete mTarget;
}

void CPathFolllowingSteering::SetSecondsAhead (const float secondsAhead)
{
    mSecondsAhead = secondsAhead;
}

float CPathFolllowingSteering::GetSecondsAhead (void) const
{
    return mSecondsAhead;
}

ISteering* CPathFolllowingSteering::GetSteering (void)
{
    CVector2D currentPosition{ mOwner->position };

    if (mPath.size () > 0)
    {
        CVector2D prediction{
            mOwner->position
            + (mOwner->linearVelocity * mSecondsAhead) };

        float mindist = FLT_MAX;

        for (unsigned int i = 0; i < mPath.size () - 1; ++i)
        {

            CVector2D pointA = mPath[i]->position;
            CVector2D pointB = mPath[i + 1]->position;

            CVector2D closestLocation =
                ClosestPoint (prediction, pointA, pointB);

            if ((closestLocation.mX < pointA.mX
                    || closestLocation.mX > pointB.mX) ||
                (((closestLocation.mY < pointA.mY)
                        && (closestLocation.mY < pointB.mY))
                    || ((closestLocation.mY > pointA.mY)
                        && (closestLocation.mY > pointB.mY))))
            {
                if (i < mPath.size () - 2) closestLocation = pointA;
                else closestLocation = pointB;
            }

            float dist = closestLocation.Dist (prediction);

            if (dist < mindist)
            {
                mindist           = dist;
                mTarget->position = closestLocation;
            }
        }

        CSeekSteering* seek = new CSeekSteering (mOwner, 0.f);
        seek->SetTarget (mTarget);
        seek->GetSteering ();

        mWantedLinearVelocity = seek->GetWantedLinearVelocity ();
        mLinearAcceleration   = seek->GetLinearAcceleration ();

        delete seek;
    }

    return this;
}

void CPathFolllowingSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D origin    { mOwner->position };
    CVector2D debugWLV  { origin + mWantedLinearVelocity };
    CVector2D debugLA   { origin + mLinearAcceleration };
    CVector2D prediction{
        mOwner->position
        + (mOwner->linearVelocity * mSecondsAhead) };

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

    for (unsigned int i = 0; i < mPath.size () - 1; ++i)
    {
        DrawLineV (
            Vector2{ mPath[i]->position.mX, mPath[i]->position.mY }
            , Vector2{ mPath[i + 1]->position.mX, mPath[i + 1]->position.mY }
            , BURGUNDY);
        DrawCircle (
            mPath[i]->position.mX
            , mPath[i]->position.mY
            , 5.f
            , BURGUNDY);
        DrawCircle (
            mPath[i + 1]->position.mX
            , mPath[i + 1]->position.mY
            , 5.f
            , BURGUNDY);
    }
    DrawCircle (
        prediction.mX
        , prediction.mY
        , 5.f
        , GREEN);
    DrawText (
        "PREDICTION"
        , prediction.mX - 45.f
        , prediction.mY - 15.f
        , 10
        , GREEN);
    DrawCircle (
        mTarget->position.mX
        , mTarget->position.mY
        , 5.f
        , DARKGREEN);
    DrawText (
        "TARGET"
        , mTarget->position.mX - 45.f
        , mTarget->position.mY + 5.f
        , 10
        , DARKGREEN);
#pragma warning(pop)
}

CVector2D CPathFolllowingSteering::ClosestPoint (
    const CVector2D origin,
    const CVector2D pointA,
    const CVector2D pointB) const
{
    // CVector2D that points from pointA to origin.
    CVector2D a2o = origin - pointA;
    // CVector2D that points from pointA to pointB.
    CVector2D a2b = pointB - pointA;

    a2b.Normalize ();
    a2b *= a2o.Dot (a2b);

    return pointA + a2b;
}