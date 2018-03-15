#pragma once

#include "Vector2D.h"

#include <raylib.h>

#define DARKGOLD CLITERAL{ 163, 141, 28, 255 }
#define BURGUNDY CLITERAL{ 166, 6, 76, 255 }

struct SSpriteSheet
{
    // Number of spritesheet frames shown by second.
    int       frameSpeed     { 1 };
    // Total number of frames in the texture.
    int       numFrames      { 1 };
    // Total number of frames in a row.
    int       framesPerRow   { 1 };
    // Total number of frames in a column.
    int       framesPerColumn{ 1 };
    // Current frame of the sprite
    int       currnetFrame   { 0 };
    // Next frame of the sprite.
    float     nextFrame      { 0.f };
    // Width of a frame in the texture.
    int       frameWidth     { 0 };
    // Height of a frame in the texture.
    int       frameHeight    { 0 };
    // Rectangle of the texture that will be draw.
    Rectangle currentFrameRec{ 0,0,0,0 };
};

struct SSprite
{
    // Texture of the sprite.
    Texture2D    texture    {};
    // Contains the information of the sprite sheet.
    SSpriteSheet spriteSheet{};
    // The tint with which the texture will be drawn.
    Color        tint       { 255,255,255,255 };
    // Scale of the sprite.
    float        scale      { 1.f };
};

struct SEntity
{
    SEntity (void) = default;
    ~SEntity (void)
    {
        UnloadTexture (sprite.texture);
    }

    void Adjust (void)
    {
        if (linearVelocity.mX > maxLinearVelocity)
        {
            linearVelocity.mX = maxLinearVelocity;
        }

        if (linearVelocity.mY > maxLinearVelocity)
        {
            linearVelocity.mY = maxLinearVelocity;
        }

        if (angularVelocity > maxAngularVelocity)
        {
            angularVelocity  = maxAngularVelocity;
        }
    }

    void Draw (void) const
    {
        // Destination rectangle (screen rectangle where drawing part of
        // texture)
        Rectangle destRec;

        destRec.width = static_cast<int>(
            sprite.spriteSheet.frameWidth * sprite.scale);
        destRec.height = static_cast<int>(
            sprite.spriteSheet.frameHeight * sprite.scale);
        destRec.x = static_cast<int>(position.mX);
        destRec.y = static_cast<int>(position.mY);

        // Origin of the texture (rotation/scale point), it's relative to
        // destination rectangle size.
        Vector2 origin;

        origin.x = destRec.width / 2.f;
        origin.y = destRec.height / 2.f;

        DrawTexturePro (
            sprite.texture
            , sprite.spriteSheet.currentFrameRec
            , destRec
            , origin
            , -angle
            , sprite.tint);
    }

    void DrawDebug (void) const
    {
#pragma warning(push)
#pragma warning(disable: 4244)

        DrawCircle (
            position.mX
            , position.mY
            , 5.f
            , sprite.tint);
        DrawText (
            label
            , position.mX - (sprite.spriteSheet.frameWidth / 7)
            , position.mY + (sprite.spriteSheet.frameHeight / 3)
            , 10
            , sprite.tint);

#pragma warning(pop)
    }

    char*     label                 {"ENTITY"};
    // Current position in the screen.
    CVector2D position              { 0.f,0.f };
    CVector2D linearVelocity        { 0.f,0.f };
    float     maxLinearVelocity     { 0.f };
    float     maxLinearAcceleration { 0.f };
    // Current angle in degrees.
    float     angle                 { 0.f };
    float     angularVelocity       { 0.f };
    float     maxAngularVelocity    { 0.f };
    float     maxAngularAcceleration{ 0.f };
    float     targetRotation        { 0.f };
    SSprite   sprite                {};
    float     radius                { 0.f };
};
