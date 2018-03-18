#include "DebugNew.h"
#include "Entity.h"
#include "SeekSteering.h"
#include "FleeSteering.h"
#include "ArriveSteering.h"
#include "WanderSteering.h"
#include "PursueSteering.h"
#include "EvadeSteering.h"
#include "AlignSteering.h"
#include "PathFolllowingSteering.h"
#include "ObstacleAvoidanceSteering.h"

int main ()
{
    int screenWidth { 800 };
    int screenHeight{ 800 };
    int mouseX      { 0 };
    int mouseY      { 0 };

    float elapsed{ 0.f };

    InitWindow (screenWidth, screenHeight, "C++ STEERINGS");

    // ------------------------------------------------------------------------
    SEntity entity;

    entity.label                                     = "ARRIVE";
    entity.position                                  = CVector2D{ 100, 100 };
    entity.maxLinearVelocity                         = 40.f;
    entity.maxLinearAcceleration                     = 20.f;
    entity.maxAngularVelocity                        = 50.f;
    entity.maxAngularAcceleration                    = 40.f;
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
        (entity.sprite.spriteSheet.frameWidth * entity.sprite.scale) / 2;
    // ------------------------------------------------------------------------

    // ------------------------------------------------------------------------
    SEntity seeker;

    seeker.label                                     = "SEEK";
    seeker.position                                  = CVector2D{ 400, 600 };
    seeker.maxLinearVelocity                         = 40.f;
    seeker.maxLinearAcceleration                     = 20.f;
    seeker.maxAngularVelocity                        = 50.f;
    seeker.maxAngularAcceleration                    = 40.f;
    seeker.sprite.texture                            =
        LoadTexture ("../Resources/dragon-shape.png");
    seeker.sprite.spriteSheet.framesPerRow           = 1;
    seeker.sprite.spriteSheet.framesPerColumn        = 1;
    seeker.sprite.spriteSheet.frameWidth             =
        seeker.sprite.texture.width / seeker.sprite.spriteSheet.framesPerRow;
    seeker.sprite.spriteSheet.frameHeight            =
        seeker.sprite.texture.height
        / seeker.sprite.spriteSheet.framesPerColumn;
    seeker.sprite.spriteSheet.currentFrameRec.x      = 0;
    seeker.sprite.spriteSheet.currentFrameRec.y      = 0;
    seeker.sprite.spriteSheet.currentFrameRec.width  =
        seeker.sprite.spriteSheet.frameWidth;
    seeker.sprite.spriteSheet.currentFrameRec.height =
        seeker.sprite.spriteSheet.frameHeight;
    seeker.sprite.scale                              = 0.5f;
    seeker.sprite.tint                               = VIOLET;
    seeker.radius                                    =
        (seeker.sprite.spriteSheet.frameWidth * seeker.sprite.scale) / 2;
    // ------------------------------------------------------------------------

    // ------------------------------------------------------------------------
    SEntity fleer;

    fleer.label                                     = "FLEE";
    fleer.position                                  = CVector2D{ 600, 100 };
    fleer.maxLinearVelocity                         = 40.f;
    fleer.maxLinearAcceleration                     = 20.f;
    fleer.maxAngularVelocity                        = 50.f;
    fleer.maxAngularAcceleration                    = 40.f;
    fleer.sprite.texture                            =
        LoadTexture ("../Resources/dragon-shape.png");
    fleer.sprite.spriteSheet.framesPerRow           = 1;
    fleer.sprite.spriteSheet.framesPerColumn        = 1;
    fleer.sprite.spriteSheet.frameWidth             =
        fleer.sprite.texture.width / fleer.sprite.spriteSheet.framesPerRow;
    fleer.sprite.spriteSheet.frameHeight            =
        fleer.sprite.texture.height
        / fleer.sprite.spriteSheet.framesPerColumn;
    fleer.sprite.spriteSheet.currentFrameRec.x      = 0;
    fleer.sprite.spriteSheet.currentFrameRec.y      = 0;
    fleer.sprite.spriteSheet.currentFrameRec.width  =
        fleer.sprite.spriteSheet.frameWidth;
    fleer.sprite.spriteSheet.currentFrameRec.height =
        fleer.sprite.spriteSheet.frameHeight;
    fleer.sprite.scale                              = 0.5f;
    fleer.sprite.tint                               = SKYBLUE;
    fleer.radius                                    =
        (fleer.sprite.spriteSheet.frameWidth * fleer.sprite.scale) / 2;
    // ------------------------------------------------------------------------

    // ------------------------------------------------------------------------
    SEntity pursuer;

    pursuer.label                                     = "PURSUE";
    pursuer.position                                  = CVector2D{ 100, 100 };
    pursuer.maxLinearVelocity                         = 32.f;
    pursuer.maxLinearAcceleration                     = 15.f;
    pursuer.maxAngularVelocity                        = 10.f;
    pursuer.maxAngularAcceleration                    = 5.f;
    pursuer.sprite.texture                            =
        LoadTexture ("../Resources/dragon-shape.png");
    pursuer.sprite.spriteSheet.framesPerRow           = 1;
    pursuer.sprite.spriteSheet.framesPerColumn        = 1;
    pursuer.sprite.spriteSheet.frameWidth             =
        pursuer.sprite.texture.width / pursuer.sprite.spriteSheet.framesPerRow;
    pursuer.sprite.spriteSheet.frameHeight            =
        pursuer.sprite.texture.height
        / pursuer.sprite.spriteSheet.framesPerColumn;
    pursuer.sprite.spriteSheet.currentFrameRec.x      = 0;
    pursuer.sprite.spriteSheet.currentFrameRec.y      = 0;
    pursuer.sprite.spriteSheet.currentFrameRec.width  =
        pursuer.sprite.spriteSheet.frameWidth;
    pursuer.sprite.spriteSheet.currentFrameRec.height =
        pursuer.sprite.spriteSheet.frameHeight;
    pursuer.sprite.scale                              = 0.5f;
    pursuer.sprite.tint                               = VIOLET;
    pursuer.radius                                    =
        (pursuer.sprite.spriteSheet.frameWidth * pursuer.sprite.scale) / 2;
    // ------------------------------------------------------------------------

    // ------------------------------------------------------------------------
    SEntity evader;

    evader.label                                     = "EVADE";
    evader.position                                  = CVector2D{ 600, 600 };
    evader.maxLinearVelocity                         = 40.f;
    evader.maxLinearAcceleration                     = 20.f;
    evader.maxAngularVelocity                        = 50.f;
    evader.maxAngularAcceleration                    = 20.f;
    evader.sprite.texture                            =
        LoadTexture ("../Resources/dragon-shape.png");
    evader.sprite.spriteSheet.framesPerRow           = 1;
    evader.sprite.spriteSheet.framesPerColumn        = 1;
    evader.sprite.spriteSheet.frameWidth             =
        evader.sprite.texture.width / evader.sprite.spriteSheet.framesPerRow;
    evader.sprite.spriteSheet.frameHeight            =
        evader.sprite.texture.height
        / evader.sprite.spriteSheet.framesPerColumn;
    evader.sprite.spriteSheet.currentFrameRec.x      = 0;
    evader.sprite.spriteSheet.currentFrameRec.y      = 0;
    evader.sprite.spriteSheet.currentFrameRec.width  =
        evader.sprite.spriteSheet.frameWidth;
    evader.sprite.spriteSheet.currentFrameRec.height =
        evader.sprite.spriteSheet.frameHeight;
    evader.sprite.scale                              = 0.5f;
    evader.sprite.tint                               = DARKBLUE;
    evader.radius                                    =
        (evader.sprite.spriteSheet.frameWidth * evader.sprite.scale) / 2;
    // ------------------------------------------------------------------------

    // ---------------------------Simple target--------------------------------
    SEntity target;

    target.label                                     = "TARGET";
    target.position                                  = CVector2D{ 200.f,400.f };
    target.maxLinearVelocity                         = 80.f;
    target.maxLinearAcceleration                     = 80.f;
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
    // ------------------------------------------------------------------------

    // ------------------------------Path--------------------------------------
    /*Path path;

    SEntity node1;
    SEntity node2;
    SEntity node3;
    SEntity node4;
    SEntity node5;

    node1.position = CVector2D{ 50, 100 };
    node2.position = CVector2D{ 100, 300 };
    node3.position = CVector2D{ 300, 300 };
    node4.position = CVector2D{ 300, 500 };
    node5.position = CVector2D{ 600, 600 };

    path.push_back (std::make_pair (&node1, false));
    path.push_back (std::make_pair (&node2, false));
    path.push_back (std::make_pair (&node3, false));
    path.push_back (std::make_pair (&node4, false));
    path.push_back (std::make_pair (&node5, false));
    // ------------------------------------------------------------------------

    // ---------------------------Obstacles------------------------------------
    Obstacles obstacles;

    SEntity obstacle1;
    SEntity obstacle2;

    obstacle1.position = CVector2D{ 310, 400 };
    obstacle1.radius = 20.f;
    obstacle2.position = CVector2D{ 200, 320 };
    obstacle2.radius = 15.f;

    obstacles.push_back (&obstacle1);
    obstacles.push_back (&obstacle2);*/
    // ------------------------------------------------------------------------

    //CAlignSteering* steering = new CAlignSteering{ &entity, 5, 1 };
    CArriveSteering* steering = new CArriveSteering{ &entity, 60.f };
    steering->SetTarget (&target);

    CSeekSteering* seek = new CSeekSteering{ &seeker, 60.f };
    seek->SetTarget (&target);

    CFleeSteering* flee = new CFleeSteering{ &fleer, 160.f };
    flee->SetTarget (&target);

    /*CPathFolllowingSteering* steering =
        new CPathFolllowingSteering{ &entity, path, 1.8f, 10.f };
    CObstacleAvoidanceSteering* avoidObstacles =
        new CObstacleAvoidanceSteering{ &entity, obstacles, 4.f, 1.f };*/

    bool checkObstacles = false;

    /*CWanderSteering* steering = new CWanderSteering{
        &entity
        , 40.f
        , 100.f
        , 20.f
        , 350.f
        , 350.f
        , CVector2D{ 400.f,400.f } };

    CPursueSteering* pursue  = new CPursueSteering{
        &pursuer
        , 7.f
        , 350.f
        , 350.f
        , CVector2D{ 400.f,400.f } };

    pursue->SetTarget (&entity);

    CEvadeSteering* evade = new CEvadeSteering{
        &evader
        , 3.f
        , 160.f
        , 350.f
        , 350.f
        , CVector2D{ 400.f,400.f } };

    evade->SetTarget (&entity);*/

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
        if (steering && !checkObstacles)
        {
            ISteering* st = steering->GetSteering ();

            CVector2D linearAcceleration{
                st->GetLinearAcceleration () };
            entity.position       += entity.linearVelocity * elapsed;
            entity.linearVelocity += linearAcceleration * elapsed;

            float angularAcceleration{
                st->GetAngularAcceleration () };
            entity.angle           += entity.angularVelocity * elapsed;
            entity.angularVelocity += angularAcceleration * elapsed;

            entity.Adjust ();
            //checkObstacles = true;
        }

        /*if (avoidObstacles && checkObstacles)
        {
            ISteering* st = avoidObstacles->GetSteering ();

            CVector2D linearAcceleration{
                st->GetLinearAcceleration () };
            entity.position       += entity.linearVelocity * elapsed;
            entity.linearVelocity += linearAcceleration * elapsed;

            entity.Adjust ();
            if (linearAcceleration.mX == 0 && linearAcceleration.mY == 0)
                checkObstacles = false;
        }*/

        if (seek)
        {
            CVector2D linearAcceleration{
                seek->GetSteering ()->GetLinearAcceleration () };
            seeker.position += seeker.linearVelocity * elapsed;
            seeker.linearVelocity += linearAcceleration * elapsed;

            seeker.Adjust ();
        }

        if (flee)
        {
            CVector2D linearAcceleration{
                flee->GetSteering ()->GetLinearAcceleration () };
            fleer.position += fleer.linearVelocity * elapsed;
            fleer.linearVelocity += linearAcceleration * elapsed;

            fleer.Adjust ();
        }

        /*if (pursue)
        {
            CVector2D linearAcceleration{
                pursue->GetSteering ()->GetLinearAcceleration () };
            pursuer.position       += pursuer.linearVelocity * elapsed;
            pursuer.linearVelocity += linearAcceleration * elapsed;

            pursuer.Adjust ();
        }

        if (evade)
        {
            CVector2D linearAcceleration{
                evade->GetSteering ()->GetLinearAcceleration () };
            evader.position += evader.linearVelocity * elapsed;
            evader.linearVelocity += linearAcceleration * elapsed;

            evader.Adjust ();
        }*/

        // Draw.
        BeginDrawing ();

        ClearBackground (RAYWHITE);

        // Debug.
        //avoidObstacles->DrawDebug ();
        steering->DrawDebug ();
        seek->DrawDebug ();
        flee->DrawDebug ();
        //pursue->DrawDebug ();
        //evade->DrawDebug ();
        target.DrawDebug ();
        entity.DrawDebug ();
        seeker.DrawDebug ();
        fleer.DrawDebug ();
        //pursuer.DrawDebug ();
        //evader.DrawDebug ();

        // Entities.
        entity.Draw ();
        target.Draw ();
        seeker.Draw ();
        fleer.Draw ();
        //pursuer.Draw ();
        //evader.Draw ();

        EndDrawing ();
    }

    delete steering;

    CloseWindow ();

    return 0;
}