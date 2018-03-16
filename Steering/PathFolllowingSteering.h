#pragma once

#include "ISteering.h"

#include <vector>

typedef std::vector<SEntity*> Path;

class CPathFolllowingSteering : public ISteering
{
public:
    CPathFolllowingSteering  (
        SEntity* const owner,
        const Path     path,
        const float    secondsAhead = 1.75f);
    ~CPathFolllowingSteering (void) override;

    void SetSecondsAhead (const float secondsAhead);

    float GetSecondsAhead (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Returns the closest point to the origin from the segment formed by
    // pointA and pointB.
    CVector2D ClosestPoint (
        const CVector2D origin,
        const CVector2D pointA,
        const CVector2D pointB) const;

    // Defines how far the prediction will go (values lesser or equal to 1.5
    // may lead to problems if there are rect angles in the path).
    float mSecondsAhead;
    // Vector of SEntity* that contain the path positions.
    Path  mPath;
};