#pragma once

#include "Vector2D.h"

struct SEntity;

class ISteering
{
public:
    ISteering (SEntity* const owner) : mOwner{owner}
    {
    }

    virtual ~ISteering (void) = default;

    void SetTarget (SEntity* target)
    {
        mTarget = target;
    }
    void SetWantedLinearVelocity (const CVector2D velocity)
    {
        mWantedLinearVelocity = velocity;
    }
    void SetLinearAcceleration (const CVector2D acceleration)
    {
        mLinearAcceleration = acceleration;
    }
    void SetWantedAngularVelocity (const float velocity)
    {
        mWantedAngularVelocity = velocity;
    }
    void SetAngularAcceleration (const float acceleration)
    {
        mAngularAcceleration = acceleration;
    }

    SEntity* GetTarget (void) const
    {
        return mTarget;
    }
    CVector2D GetWantedLinearVelocity (void) const
    {
        return mWantedLinearVelocity;
    }
    CVector2D GetLinearAcceleration (void) const
    {
        return mLinearAcceleration;
    }
    float GetWantedAngularVelocity (void) const
    {
        return mWantedAngularVelocity;
    }
    float GetAngularAcceleration (void) const
    {
        return mAngularAcceleration; 
    }

    virtual ISteering* GetSteering (void) = 0;

    virtual void DrawDebug (void) const = 0;

protected:
    SEntity* const mOwner;
    SEntity*       mTarget;
    CVector2D      mWantedLinearVelocity;
    CVector2D      mLinearAcceleration;
    float          mWantedAngularVelocity;
    float          mAngularAcceleration;
};
