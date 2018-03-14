#include "DebugNew.h"
#include "Entity.h"
#include "SeekSteering.h"
#include "FleeSteering.h"
#include "ArriveSteering.h"
#include "WanderSteering.h"

int main ()
{
    int screenWidth { 800 };
    int screenHeight{ 800 };
    int mouseX      { 0 };
    int mouseY      { 0 };

    float elapsed{ 0.f };

    InitWindow (screenWidth, screenHeight, "Wander Steering");

    SEntity entity;

    entity.label                                     = "STEERING";
    entity.position                                  = CVector2D{
        (float)screenWidth / 2, (float)screenHeight / 2 };
    entity.maxLinearVelocity                         = 40.f;
    entity.maxLinearAcceleration                     = 20.f;
    entity.maxAngularVelocity                        = 10.f;
    entity.maxAngularAcceleration                    = 5.f;
    entity.sprite.texture                            =
        LoadTexture ("../Resources/dragon-shape.png");
    entity.sprite.spriteSheet.framesPerRow           = 1;
    entity.sprite.spriteSheet.framesPerColumn        = 1;
    entity.sprite.spriteSheet.frameWidth             =
        entity.sprite.texture.width / entity.sprite.spriteSheet.framesPerRow;
    entity.sprite.spriteSheet.frameHeight            =
        entity.sprite.texture.height
        / entity.sprite.spriteSheet.framesPerColumn;
    entity.sprite.spriteSheet.currentFrameRec.x      = 0;
    entity.sprite.spriteSheet.currentFrameRec.y      = 0;
    entity.sprite.spriteSheet.currentFrameRec.width  =
        entity.sprite.spriteSheet.frameWidth;
    entity.sprite.spriteSheet.currentFrameRec.height =
        entity.sprite.spriteSheet.frameHeight;
    entity.sprite.scale                              = 0.5f;
    entity.sprite.tint                               = DARKGOLD;
    entity.radius                                    =
        entity.sprite.spriteSheet.frameWidth * 1.f;

    SEntity target;

    target.label                                     = "TARGET";
    target.position                                  = CVector2D{ 200.f,200.f };
    target.maxLinearVelocity                         = 40.f;
    target.maxLinearAcceleration                     = 20.f;
    target.maxAngularVelocity                        = 10.f;
    target.maxAngularAcceleration                    = 5.f;
    target.sprite.texture                            =
        LoadTexture ("../Resources/dragon.png");
    target.sprite.spriteSheet.framesPerRow           = 1;
    target.sprite.spriteSheet.framesPerColumn        = 1;
    target.sprite.spriteSheet.frameWidth             =
        target.sprite.texture.width / target.sprite.spriteSheet.framesPerRow;
    target.sprite.spriteSheet.frameHeight            =
        target.sprite.texture.height
        / target.sprite.spriteSheet.framesPerColumn;
    target.sprite.spriteSheet.currentFrameRec.x      = 0;
    target.sprite.spriteSheet.currentFrameRec.y      = 0;
    target.sprite.spriteSheet.currentFrameRec.width  =
        target.sprite.spriteSheet.frameWidth;
    target.sprite.spriteSheet.currentFrameRec.height =
        target.sprite.spriteSheet.frameHeight;
    target.sprite.scale                              = 0.5f;
    target.sprite.tint                               = BURGUNDY;

    //CArriveSteering* steering = new CArriveSteering{ &entity, 60.f };

    //steering->SetTarget (&target);

    CWanderSteering* steering = new CWanderSteering{
        &entity
        , 40.f
        , 100.f
        , 3.f
        , 350.f
        , 350.f
        , CVector2D{ 400.f,400.f } };

    SetTargetFPS (60);

    while (!WindowShouldClose ())
    {
        elapsed = GetFrameTime ();

        // Update target.
        mouseX = GetMouseX ();
        mouseY = GetMouseY ();

        if (target.position.mX != mouseX) target.position.mX = mouseX * 1.f;
        if (target.position.mY != mouseY) target.position.mY = mouseY * 1.f;

        // Update entity.
        if (steering)
        {
            CVector2D linearAcceleration{
                steering->GetSteering ()->GetLinearAcceleration () };
            entity.position       += entity.linearVelocity * elapsed;
            entity.linearVelocity += linearAcceleration * elapsed;
        }

        // Draw.
        BeginDrawing ();

        ClearBackground (RAYWHITE);

        entity.Draw ();

        // Debug.
        steering->DrawDebug ();
        //target.Draw ();
        //target.DrawDebug ();
        entity.DrawDebug ();

        EndDrawing ();
    }

    delete steering;

    CloseWindow ();

    return 0;
}