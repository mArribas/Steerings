#pragma once

#include "ISteering.h"

class CPursueSteering : public ISteering
{
public:
    CPursueSteering  (
        SEntity* const  owner,
        const float     secondsAhead,
        const float     limitX,
        const float     limitY,
        const CVector2D referencePoint);
    ~CPursueSteering (void) override;

    void SetSecondsAhead (const float secondsAhead);

    float GetSecondsAhead (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Defines how far the prediction will go.
    float mSecondsAhead;
};