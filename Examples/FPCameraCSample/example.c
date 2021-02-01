/*******************************************************************************************
*
*   raylib [core] example - Third Person Orbit Camera Example
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "FPCamera.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [camera] example - third person orbit camera");
    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------

    Image img = GenImageChecked(256, 256, 64, 64, LIGHTGRAY, WHITE);
    Texture tx = LoadTextureFromImage(img);

    // setup initial camera data
    FPCamera cam;
    InitFPCamera(&cam, 45, (Vector3){ 1, 0 ,0 });
    cam.MoveSpeed.z = 10;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateFPCamera(&cam);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(cam.ViewCamera);
       
        // grid of cubes on a plane to make a "world"
		DrawPlane((Vector3){ 0,0,0 }, (Vector2){ 50,50 }, BLUE); // simple world plane
        float spacing = 3;
        int count = 5;

        for (float x = -count * spacing; x <= count * spacing; x += spacing)
        {
            for (float z = -count * spacing; z <= count * spacing; z += spacing)
            {
                DrawCubeTexture(tx, (Vector3){ x, 0.5f, z }, 1, 1, 1, WHITE);
            }
        }
        
        EndMode3D();

        // instructions
        DrawFPS(0, 0);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}