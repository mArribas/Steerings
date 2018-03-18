#include "PathFolllowingSteering.h"

#include "DebugNew.h"
#include "SeekSteering.h"

#include <cassert>

CPathFolllowingSteering::CPathFolllowingSteering (
    SEntity* const owner,
    const Path     path,
    const float    secondsAhead,
    const float    radius)
    : ISteering    { owner }
    , mPath        { path }
    , mSecondsAhead{ secondsAhead }
    , mRadius      { radius }
{
    assert (mRadius > 0.f);
}

CPathFolllowingSteering::~CPathFolllowingSteering (void)
{
}

void CPathFolllowingSteering::SetSecondsAhead (const float secondsAhead)
{
    mSecondsAhead = secondsAhead;
}

void CPathFolllowingSteering::SetRadius (const float radius)
{
    if (radius <= 0.f) return;

    mRadius = radius;
}

float CPathFolllowingSteering::GetSecondsAhead (void) const
{
    return mSecondsAhead;
}

float CPathFolllowingSteering::GetRadius (void) const
{
    return mRadius;
}

ISteering* CPathFolllowingSteering::GetSteering (void)
{
    mTarget = new SEntity{};

    if (mPath.size () > 0)
    {
        CVector2D prediction{
            mOwner->position
            + (mOwner->linearVelocity * mSecondsAhead) };
        float     minDist   { FLT_MAX };

        // Set a target.
        for (unsigned int i = 0; i < mPath.size () - 1; ++i)
        {
            if (mPath[i].second && mPath[i + 1].second) continue;

            CVector2D pointA      { mPath[i].first->position };
            CVector2D pointB      { mPath[i + 1].first->position };
            CVector2D closestPoint{ ClosestPoint (prediction, pointA, pointB) };

            if ((closestPoint.mX < pointA.mX
                || closestPoint.mX > pointB.mX) ||
                (((closestPoint.mY < pointA.mY)
                    && (closestPoint.mY < pointB.mY))
                    || ((closestPoint.mY > pointA.mY)
                        && (closestPoint.mY > pointB.mY))))
            {
                if (i < mPath.size () - 2) closestPoint = pointA;
                else                       closestPoint = pointB;
            }

            float dist = closestPoint.Dist (prediction);

            if (dist < minDist)
            {
                minDist           = dist;
                mTarget->position = closestPoint;
            }
        }

        // "Update" the path.
        RecordPassedNodes ();

        // Keep the owner on the path.
        if (mOwner->position.Dist (mTarget->position) > mRadius)
        {
            CSeekSteering* seek{ new CSeekSteering{ mOwner, 0.f } };
            seek->SetTarget (mTarget);
            seek->GetSteering ();

            mWantedLinearVelocity = seek->GetWantedLinearVelocity ();
            mLinearAcceleration   = seek->GetLinearAcceleration ();

            delete seek;
        }
    }

    delete mTarget;

    return this;
}

void CPathFolllowingSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D debugWLV  { mOwner->position + mWantedLinearVelocity };
    CVector2D debugLA   { mOwner->position + mLinearAcceleration };
    CVector2D prediction{
        mOwner->position
        + (mOwner->linearVelocity * mSecondsAhead) };
    CVector2D target    {};
    float     minDist   { FLT_MAX };

    DrawLineEx (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ debugWLV.mX, debugWLV.mY }
        , 3.f
        , BLUE);
    DrawLineEx (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ debugLA.mX, debugLA.mY }
        , 3.f
        , RED);

    for (unsigned int i = 0; i < mPath.size () - 1; ++i)
    {
        CVector2D pointA      { mPath[i].first->position };
        CVector2D pointB      { mPath[i + 1].first->position };
        CVector2D closestPoint{ ClosestPoint (prediction, pointA, pointB) };
            

        if ((closestPoint.mX < pointA.mX
            || closestPoint.mX > pointB.mX) ||
            (((closestPoint.mY < pointA.mY)
                && (closestPoint.mY < pointB.mY))
                || ((closestPoint.mY > pointA.mY)
                    && (closestPoint.mY > pointB.mY))))
        {
            if (i < mPath.size () - 2) closestPoint = pointA;
            else                       closestPoint = pointB;
        }

        float dist = closestPoint.Dist (prediction);

        if (dist < minDist)
        {
            minDist = dist;
            target  = closestPoint;
        }

        DrawLineV  (
            Vector2{ mPath[i].first->position.mX
                , mPath[i].first->position.mY }
            , Vector2{ mPath[i + 1].first->position.mX
                , mPath[i + 1].first->position.mY }
        , GRAY);
        DrawCircle (
            mPath[i].first->position.mX
            , mPath[i].first->position.mY
            , 5.f
            , DARKGRAY);
        DrawCircle (
            mPath[i + 1].first->position.mX
            , mPath[i + 1].first->position.mY
            , 5.f
            , DARKGRAY);
    }
    DrawCircle (
        prediction.mX
        , prediction.mY
        , 5.f
        , GREEN);
    DrawText   (
        "PREDICTION"
        , prediction.mX - 45.f
        , prediction.mY + 5.f
        , 10
        , GREEN);
    DrawCircle (
        target.mX
        , target.mY
        , 5.f
        , DARKGREEN);
    DrawText   (
        "TARGET"
        , target.mX - 45.f
        , target.mY + 5.f
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

void CPathFolllowingSteering::RecordPassedNodes (void)
{
    assert (mPath.size () > 0);

    if ((mOwner->position.Dist (mPath.front ().first->position)
            - mOwner->radius)
        < mRadius)
    {
        ResetPath ();
        mPath.front ().second = true;
    }
    else if ((mOwner->position.Dist (mPath.back ().first->position)
            - mOwner->radius)
        < mRadius)
    {
        ResetPath ();
        mPath.back ().second = true;
    }
    else
    {
        for (unsigned int i = 1; i < mPath.size () - 1; ++i)
        {
            if (mPath[i].second == true) continue;

            if ((mOwner->position.Dist (mPath[i].first->position)
                    - mOwner->radius)
                < mRadius)
            {
                mPath[i].second = true;
            }
        }
    }
}

void CPathFolllowingSteering::ResetPath (void)
{
    for (auto& node : mPath)
    {
        node.second = false;
    }
}