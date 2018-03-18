#pragma once

#include "ISteering.h"

class CWanderSteering : public ISteering
{
public:
    CWanderSteering  (
        SEntity* const  owner,
        const float     radius,
        const float     disntance,
        const float     randomFactor,
        const float     limitX,
        const float     limitY,
        const CVector2D referencePoint);
    ~CWanderSteering (void) override;

    void SetRadius       (const float radius);
    void SetDistance     (const float disntance);
    void SetRandomFactor (const float randomFactor);
    void SetWanderAngle  (const float wanderAngle);

    float GetRadius       (void) const;
    float GetDistance     (void) const;
    float GetRandomFactor (void) const;
    float GetWanderAngle  (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Radius of the circle used to wander.
    float mRadius;
    // Distance from the owner to the center of the circle used to wander.
    float mDistance;
    // Random factor used to modify the wander angle (in degrees).
    float mRandomFactor;
    // Defines how big the offset to the target is.
    float mWanderAngle;
};
