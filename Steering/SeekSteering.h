#pragma once

#include "ISteering.h"

class CSeekSteering : public ISteering
{
public:
    CSeekSteering  (SEntity* const owner, const float radius);
    ~CSeekSteering (void) override;

    void SetRadius (const float radius);

    float GetRadius (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // To know when should stop.
    float mRadius;
};