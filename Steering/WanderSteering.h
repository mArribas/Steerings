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

    void SetRadius         (const float radius);
    void SetDistance       (const float disntance);
    void SetRandomFactor   (const float randomFactor);
    void SetWanderAngle    (const float wanderAngle);
    void SetLimitX         (const float limitX);
    void SetLimitY         (const float limitY);
    void SetReferencePoint (const CVector2D referencePoint);

    float     GetRadius         (void) const;
    float     GetDistance       (void) const;
    float     GetRandomFactor   (void) const;
    float     GetWanderAngle    (void) const;
    float     GetLimitX         (void) const;
    float     GetLimitY         (void) const;
    CVector2D GetReferencePoint (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Radius of the circle used to wander.
    float      mRadius;
    // Distance from the owner to the center of the circle used to wander.
    float      mDistance;
    // Random factor used to modify the wander angle.
    float      mRandomFactor;
    // Defines how big the offset to the target is.
    float      mWanderAngle;
    // Defines how far can wander in the 'x' axis, from a reference point.
    float      mLimitX;
    // Defines how far can wander in the 'y' axis, from a reference point.
    float      mLimitY;
    // Center of the wandering "zone".
    CVector2D  mReferencePoint;
};
