#pragma once

#include "ISteering.h"

class CFleeSteering : public ISteering
{
public:
    CFleeSteering  (SEntity* const owner, const float radius);
    ~CFleeSteering (void) override;

    void SetRadius (const float radius);

    float GetRadius (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // To know when should flee.
    float mRadius;
};