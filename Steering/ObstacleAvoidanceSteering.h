#pragma once

#include "ISteering.h"

#include <vector>

typedef std::vector<SEntity*> Obstacles;

class CObstacleAvoidanceSteering : public ISteering
{
public:
    CObstacleAvoidanceSteering  (
        SEntity* const  owner,
        const Obstacles obstacles,
        const float     secondsAhead   = 1.75f,
        const float     expandedRadius = 1.5f);
    ~CObstacleAvoidanceSteering (void) override;

    void SetSecondsAhead   (const float secondsAhead);
    void SetExpandedRadius (const float expandedRadius);

    float GetSecondsAhead   (void) const;
    float GetExpandedRadius (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Returns the closest point to the origin from the segment formed by
    // pointA and pointB.
    CVector2D ClosestPoint (
        const CVector2D origin,
        const CVector2D pointA,
        const CVector2D pointB) const;

    // Defines how far the prediction will go.
    float mSecondsAhead;
    // Defines how big will be the radius of the circle to check (obstacle
    // radius * 'mExpandedRadius').
    float mExpandedRadius;
    // Vector of SEntity* that contain the obstacles positions and radius.
    Obstacles  mObstacles;
};