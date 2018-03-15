#pragma once

#include "ISteering.h"

class CAlignSteering : public ISteering
{
public:
    CAlignSteering  (
        SEntity* const       owner,
        const unsigned short softRadius = 5,
        const unsigned short stopRadius = 1);
    ~CAlignSteering (void) override;

    void SetSoftRadius (const unsigned short radius);
    void SetStopRadius (const unsigned short radius);

    unsigned short GetSoftRadius (void) const;
    unsigned short GetStopRadius (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Wraps the angle passed into a value between -PI and PI.
    float WrapRad (float angle);
    // Wraps the angle passed into a value between 0 and 360.
    float WrapDeg (float angle);

    // To know when should the angular velocity reduce.
    unsigned short mSoftRadius;
    // To know when should the rotation stop.
    unsigned short mStopRadius;
};