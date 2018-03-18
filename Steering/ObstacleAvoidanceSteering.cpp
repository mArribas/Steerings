#include "ObstacleAvoidanceSteering.h"

#include "DebugNew.h"
#include "SeekSteering.h"

CObstacleAvoidanceSteering::CObstacleAvoidanceSteering (
    SEntity* const  owner,
    const Obstacles obstacles,
    const float     secondsAhead,
    const float     expandedRadius)
    : ISteering      { owner }
    , mObstacles     { obstacles }
    , mSecondsAhead  { secondsAhead }
    , mExpandedRadius{ expandedRadius }
{
}

CObstacleAvoidanceSteering::~CObstacleAvoidanceSteering (void)
{
}

void CObstacleAvoidanceSteering::SetSecondsAhead (const float secondsAhead)
{
    mSecondsAhead = secondsAhead;
}

void CObstacleAvoidanceSteering::SetExpandedRadius (const float expandedRadius)
{
    mExpandedRadius = expandedRadius;
}

float CObstacleAvoidanceSteering::GetSecondsAhead (void) const
{
    return mSecondsAhead;
}

float CObstacleAvoidanceSteering::GetExpandedRadius (void) const
{
    return mExpandedRadius;
}

ISteering* CObstacleAvoidanceSteering::GetSteering (void)
{
    CVector2D currentPosition{ mOwner->position };

    if (mObstacles.size () > 0)
    {
        CVector2D prediction     {
            mOwner->position
            + (mOwner->linearVelocity * mSecondsAhead) };
        SEntity*  mostThreatening{ nullptr };

        // Get closest obstacle.
        for (const auto& obstacle : mObstacles)
        {
            if (mostThreatening == nullptr
                || (obstacle->position.Dist (currentPosition)
                        < mostThreatening->position.Dist (currentPosition)))
            {
                mostThreatening = obstacle;
            }
        }

        // Avoid the closest obstacle if necessary.
        if (mostThreatening != nullptr)
        {
            mTarget           = new SEntity{};
            mTarget->position =
                ClosestPoint (
                    mostThreatening->position
                    , mOwner->position
                    , prediction);

            // Check if the closest point is in the segment formed by the owner
            // position and the prediction. Then, check if the owner would
            // collide with the obstacle if it were at the closest point.
            if (((mTarget->position.Dist (currentPosition)
                    < currentPosition.Dist (prediction))
                && (mTarget->position.Dist (prediction)
                    < currentPosition.Dist (prediction)))
                && ((mTarget->position.Dist (mostThreatening->position)
                        - mOwner->radius)
                    <= (mostThreatening->radius * mExpandedRadius)))
            {
                mLinearAcceleration  =
                    mTarget->position - mostThreatening->position;
                mLinearAcceleration.Normalize ();
                mLinearAcceleration *= mOwner->maxLinearAcceleration;
            }
            else
            {
                mLinearAcceleration = CVector2D{ 0.0f, 0.0f };
            }

            delete mTarget;
        }
    }

    return this;
}

void CObstacleAvoidanceSteering::DrawDebug (void) const
{
#pragma warning(push)
#pragma warning(disable: 4244)
    CVector2D debugWLV  { mOwner->position + mWantedLinearVelocity };
    CVector2D debugLA   { mOwner->position + mLinearAcceleration };
    CVector2D prediction{
        mOwner->position
        + (mOwner->linearVelocity * mSecondsAhead) };

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
    DrawLineV  (
        Vector2{ mOwner->position.mX, mOwner->position.mY }
        , Vector2{ prediction.mX, prediction.mY }
        , DARKBLUE);
    DrawCircle (
        prediction.mX
        , prediction.mY
        , 5.f
        , DARKBLUE);
    DrawText   (
        "PREDICTION"
        , prediction.mX - 45.f
        , prediction.mY - 15.f
        , 10
        , DARKBLUE);
    for (const auto& obstacle : mObstacles)
    {
        CVector2D closestPoint2Obstacle{
            ClosestPoint (obstacle->position, mOwner->position, prediction) };

        if ((closestPoint2Obstacle.Dist (obstacle->position)
            - mOwner->radius)
            <= (obstacle->radius * mExpandedRadius))
        {
            obstacle->sprite.tint = BURGUNDY;
        }
        else
        {
            obstacle->sprite.tint = DARKBLUE;
        }

        DrawCircle      (
            obstacle->position.mX
            , obstacle->position.mY
            , obstacle->radius
            , obstacle->sprite.tint);
        DrawCircle      (
            closestPoint2Obstacle.mX
            , closestPoint2Obstacle.mY
            , 5.f
            , obstacle->sprite.tint);
        DrawCircleLines (
            obstacle->position.mX
            , obstacle->position.mY
            , obstacle->radius * mExpandedRadius
            , obstacle->sprite.tint);
        DrawLineV       (
            Vector2{ closestPoint2Obstacle.mX, closestPoint2Obstacle.mY }
            , Vector2{ prediction.mX, prediction.mY }
        , obstacle->sprite.tint);
        DrawLineV       (
            Vector2{ closestPoint2Obstacle.mX, closestPoint2Obstacle.mY }
            , Vector2{ obstacle->position.mX, obstacle->position.mY }
        , obstacle->sprite.tint);
    }
#pragma warning(pop)
}

CVector2D CObstacleAvoidanceSteering::ClosestPoint (
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