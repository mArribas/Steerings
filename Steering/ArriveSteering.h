#pragma once

#include "ISteering.h"

class CArriveSteering : public ISteering
{
public:
    CArriveSteering  (SEntity* const owner, const float radius);
    ~CArriveSteering (void) override;

    void SetRadius (const float radius);

    float GetRadius (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // To know when should the interpolation to the target start.
    float mRadius;
};