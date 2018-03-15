#pragma once

#include "Entity.h"

#include <cfloat>
#include <cmath>

struct SEntity;

class ISteering
{
public:
    ISteering (SEntity* const owner)
        : mOwner                { owner }
        , mWantedLinearVelocity { 0.f,0.f }
        , mLinearAcceleration   { 0.f,0.f }
        , mWantedAngularVelocity{0.f}
        , mAngularAcceleration  {0.f}
        , mReferencePoint       { 0.f,0.f }
        , mLimitX               { FLT_MAX }
        , mLimitY               { FLT_MAX }
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
    void SetLimitX (const float limitX)
    {
        mLimitX = limitX;
    }
    void SetLimitY (const float limitY)
    {
        mLimitY = limitY;
    }
    void SetReferencePoint (const CVector2D referencePoint)
    {
        mReferencePoint = referencePoint;
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

    float GetLimitX (void) const
    {
        return mLimitX;
    }
    float GetLimitY (void) const
    {
        return mLimitY;
    }
    CVector2D GetReferencePoint (void) const
    {
        return mReferencePoint;
    }

    virtual ISteering* GetSteering (void) = 0;

    virtual void DrawDebug (void) const = 0;

protected:
    // Checks if the position passed is out of limits. If true, sets
    // 'mWantedLinearVelocity' and 'mLinearAcceleration' in a direction that
    // faces the region.
    void BackIfOutOfLimits (const CVector2D position)
    {
        if (position.mX < (mReferencePoint.mX - mLimitX))
        {
            mWantedLinearVelocity.mX = abs (mWantedLinearVelocity.mX);
            mLinearAcceleration.mX   = abs (mLinearAcceleration.mX);
        }

        if (position.mX > (mReferencePoint.mX + mLimitX))
        {
            mWantedLinearVelocity.mX = -abs (mWantedLinearVelocity.mX);
            mLinearAcceleration.mX   = -abs (mLinearAcceleration.mX);
        }

        if (position.mY < (mReferencePoint.mY - mLimitY))
        {
            mWantedLinearVelocity.mY = abs (mWantedLinearVelocity.mY);
            mLinearAcceleration.mY   = abs (mLinearAcceleration.mY);
        }

        if (position.mY > (mReferencePoint.mY + mLimitY))
        {
            mWantedLinearVelocity.mY = -abs (mWantedLinearVelocity.mY);
            mLinearAcceleration.mY   = -abs (mLinearAcceleration.mY);
        }
    }

    SEntity* const mOwner;
    SEntity*       mTarget;
    CVector2D      mWantedLinearVelocity;
    CVector2D      mLinearAcceleration;
    float          mWantedAngularVelocity;
    float          mAngularAcceleration;
    // Defines how far in the 'x' axis the owner can move (from a reference
    // point).
    float          mLimitX;
    // Defines how far in the 'y' axis the owner can move (from a reference
    // point).
    float          mLimitY;
    // Center of the "region" in which the owner will "move".
    CVector2D      mReferencePoint;
};
