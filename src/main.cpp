#include <iostream>

#include "raylib.h"

#include "screen.h"

Color darkRed = (Color){100, 0, 0, 255};

enum SCREEN
{
    LOADING,
    HOME
};

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Duel");

	InitAudioDevice();

    ToggleFullscreen();

    SetTargetFPS(60);

    SCREEN CURRENT_SCREEN = LOADING;

    Font katsunoFont =
        LoadFontEx(
            "assets/fonts/katsuno-japan-demo.regular.ttf",
            200,
            nullptr,
            0
        );

    Font poppinsFont =
        LoadFontEx(
            "assets/fonts/poppins.regular.ttf",
            200,
            nullptr,
            0
        );

	Music bgm = LoadMusicStream("assets/audio/bgm.wav");

    PlayMusicStream(bgm);

    Screen screen;

    float alpha = 0.0f;
    float fadeDuration = 3.0f;

    float elapsedTime = 0.0f;
    float loadingDuration = 3.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

		UpdateMusicStream(bgm);

        // -------------------------
        // Loading screen timer
        // -------------------------

        if (CURRENT_SCREEN == LOADING)
        {
            elapsedTime += dt;

            if (elapsedTime >= loadingDuration)
            {
                CURRENT_SCREEN = HOME;
				PlayMusicStream(bgm);
            }
        }

        // -------------------------
        // Fade
        // -------------------------

        if (alpha < 1.0f)
        {
            alpha += dt / fadeDuration;

            if (alpha > 1.0f)
                alpha = 1.0f;
        }

        // -------------------------
        // Rendering
        // -------------------------

        BeginDrawing();

        ClearBackground(BLACK);

        if (CURRENT_SCREEN == LOADING)
        {
            DrawTextEx(
                katsunoFont,
                "DUEL",
                {
                    screen.getScreenWidth() / 2 - 255,
                    screen.getScreenHeight() / 2 - 255
                },
                255,
                1,
                Fade(MAROON, alpha)
            );

            DrawTextEx(
                poppinsFont,
                "by BOKSHIVERSE",
                {
                    (screen.getScreenWidth() - 270) / 2,
                    screen.getScreenHeight() - 100
                },
                32,
                1,
                WHITE
            );
        }
        else if (CURRENT_SCREEN == HOME)
        {
            // HOME SCREEN
			//

			render image full screen from assets/images/wallpaper.jpg
            DrawText(
                "HOME",
                100,
                100,
                50,
                WHITE
            );
        }

        EndDrawing();
    }

    UnloadFont(katsunoFont);
    UnloadFont(poppinsFont);

	UnloadMusicStream(bgm);
	CloseAudioDevice();

    CloseWindow();
}
