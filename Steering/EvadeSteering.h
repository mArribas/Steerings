#include "ISteering.h"

class CEvadeSteering : public ISteering
{
public:
    CEvadeSteering (
        SEntity* const  owner,
        const float     secondsAhead,
        const float     radius,
        const float     limitX,
        const float     limitY,
        const CVector2D referencePoint);
    ~CEvadeSteering (void) override;

    void SetSecondsAhead (const float secondsAhead);
    void SetRadius       (const float radius);

    float GetSecondsAhead (void) const;
    float GetRadius       (void) const;

    ISteering* GetSteering (void) final;

    void DrawDebug (void) const final;
private:
    // Defines how far the prediction will go.
    float mSecondsAhead;
    // To know when should flee.
    float mRadius;
};