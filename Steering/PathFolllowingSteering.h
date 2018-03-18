#pragma once

#include "ISteering.h"

#include <vector>
#include <utility>

typedef std::pair<SEntity*, bool> Node;
typedef std::vector<Node>         Path;

class CPathFolllowingSteering : public ISteering
{
public:
    CPathFolllowingSteering  (
        SEntity* const owner,
        const Path     path,
        const float    secondsAhead = 1.75f, 
        const float    radius       = 1.f);
    ~CPathFolllowingSteering (void) override;

    void SetSecondsAhead (const float secondsAhead);
    void SetRadius       (const float radius);

    float GetSecondsAhead (void) const;
    float GetRadius       (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Returns the closest point to the origin from the segment formed by
    // pointA and pointB.
    CVector2D ClosestPoint (
        const CVector2D origin,
        const CVector2D pointA,
        const CVector2D pointB) const;

    // Marks the nodes traversed as passed, and if the node passed was the
    // first or the last one, resets the path.
    void RecordPassedNodes (void);
    // Sets all the bool variables of the path to false.
    void ResetPath         (void);

    // Defines how far the prediction will go.
    float mSecondsAhead;
    // Defines how wide the path is.
    float mRadius;
    // A vector of SEntity* that contain the position of each "node" of the
    // path, as well as a bool variable which indicates if the "node" has been
    // traversed.
    Path  mPath;
};