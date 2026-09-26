#include "raylib.h"
#include "screen.h"

enum SCREEN
{
    LOADING,
    HOME
};

enum OPTION
{
    CREATE_ROOM,
    JOIN_ROOM,
    SETTINGS
};

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Duel");
    InitAudioDevice();

    ToggleFullscreen();
    SetTargetFPS(60);

    Screen screen;

    SCREEN CURRENT_SCREEN = LOADING;
    OPTION CURRENT_OPTION = CREATE_ROOM;

    // --------------------------------------------------
    // Fonts
    // --------------------------------------------------

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

    Font poppinsBlackFont =
        LoadFontEx(
            "assets/fonts/poppins.black.ttf",
            200,
            nullptr,
            0
        );

    // --------------------------------------------------
    // Images
    // --------------------------------------------------

    Texture2D wallpaper =
        LoadTexture("assets/images/wallpaper4.png");

    // --------------------------------------------------
    // Audio
    // --------------------------------------------------

    // Main background music
    Music bgm =
        LoadMusicStream("assets/audio/bgm.ogg");

    bgm.looping = true;
    SetMusicVolume(bgm, 0.1f);

    // Menu switch sound
    Sound switchbg =
        LoadSound("assets/audio/switch.ogg");

    SetSoundVolume(switchbg, 0.7f);

    // Loading screen sound
    Sound loadingbg =
        LoadSound("assets/audio/loading.ogg");
    SetSoundVolume(loadingbg, 0.7f);

    // Start loading sound once.
    // Because looping = true, raylib keeps repeating it.
    PlaySound(loadingbg);

    // --------------------------------------------------
    // Loading screen timing
    // --------------------------------------------------

    float alpha = 0.0f;

    float fadeDuration = 5.0f;
    float elapsedTime = 0.0f;

    float loadingDuration = 8.0f;

    // --------------------------------------------------
    // Main loop
    // --------------------------------------------------

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // ==============================================
        // GLOBAL TIME
        // ==============================================

        elapsedTime += dt;

        // ==============================================
        // LOADING SCREEN
        // ==============================================

        if (CURRENT_SCREEN == LOADING)
        {
            // Fade DUEL text in
            if (alpha < 1.0f)
            {
                alpha += dt / fadeDuration;

                if (alpha > 1.0f)
                    alpha = 1.0f;
            }

            // ------------------------------------------
            // Finish loading
            // ------------------------------------------

            if (elapsedTime >= loadingDuration)
            {
                CURRENT_SCREEN = HOME;

                // Stop loading sound
                StopSound(loadingbg);

                // Start main music
                PlayMusicStream(bgm);
            }
        }

        // ==============================================
        // HOME SCREEN
        // ==============================================

        if (CURRENT_SCREEN == HOME)
        {
            // Music is streamed, so it needs to be
            // updated every frame.
            UpdateMusicStream(bgm);

            // ------------------------------------------
            // Menu navigation
            // ------------------------------------------

            if (IsKeyPressed(KEY_DOWN))
            {
                if (CURRENT_OPTION == CREATE_ROOM)
                {
                    CURRENT_OPTION = JOIN_ROOM;
                }
                else if (CURRENT_OPTION == JOIN_ROOM)
                {
                    CURRENT_OPTION = SETTINGS;
                }
                else
                {
                    CURRENT_OPTION = CREATE_ROOM;
                }

                PlaySound(switchbg);
            }

            if (IsKeyPressed(KEY_UP))
            {
                if (CURRENT_OPTION == CREATE_ROOM)
                {
                    CURRENT_OPTION = SETTINGS;
                }
                else if (CURRENT_OPTION == JOIN_ROOM)
                {
                    CURRENT_OPTION = CREATE_ROOM;
                }
                else
                {
                    CURRENT_OPTION = JOIN_ROOM;
                }

                PlaySound(switchbg);
            }
        }

        // ==============================================
        // DRAW
        // ==============================================

        BeginDrawing();

        ClearBackground(BLACK);

        // ----------------------------------------------
        // LOADING
        // ----------------------------------------------

        if (CURRENT_SCREEN == LOADING)
        {
            DrawTextEx(
                katsunoFont,
                "DUEL",
                {
                    screen.getScreenWidth() / 2.0f - 255,
                    screen.getScreenHeight() / 2.0f - 255
                },
                255,
                1,
                Fade(MAROON, alpha)
            );

            DrawTextEx(
                poppinsFont,
                "by BOKSHIVERSE",
                {
                    (screen.getScreenWidth() - 270) / 2.0f,
                    screen.getScreenHeight() - 100.0f
                },
                32,
                1,
                WHITE
            );
        }

        // ----------------------------------------------
        // HOME
        // ----------------------------------------------

        if (CURRENT_SCREEN == HOME)
        {
            // Wallpaper
            DrawTexturePro(
                wallpaper,
                {
                    0,
                    0,
                    (float)wallpaper.width,
                    (float)wallpaper.height
                },
                {
                    0,
                    0,
                    (float)GetScreenWidth(),
                    (float)GetScreenHeight()
                },
                {0, 0},
                0.0f,
                WHITE
            );

            // ------------------------------------------
            // Menu colors
            // ------------------------------------------

            Color createBg =
                CURRENT_OPTION == CREATE_ROOM
                    ? WHITE
                    : BLACK;

            Color createText =
                CURRENT_OPTION == CREATE_ROOM
                    ? BLACK
                    : WHITE;

            Color joinBg =
                CURRENT_OPTION == JOIN_ROOM
                    ? WHITE
                    : BLACK;

            Color joinText =
                CURRENT_OPTION == JOIN_ROOM
                    ? BLACK
                    : WHITE;

            Color settingsBg =
                CURRENT_OPTION == SETTINGS
                    ? WHITE
                    : BLACK;

            Color settingsText =
                CURRENT_OPTION == SETTINGS
                    ? BLACK
                    : WHITE;

            // ------------------------------------------
            // Menu rectangles
            // ------------------------------------------

            DrawRectangle(
                1470,
                720,
                500,
                95,
                createBg
            );

            DrawRectangle(
                1470,
                820,
                500,
                95,
                joinBg
            );

            DrawRectangle(
                1470,
                920,
                500,
                95,
                settingsBg
            );

            // ------------------------------------------
            // Menu text
            // ------------------------------------------

            DrawTextEx(
                poppinsBlackFont,
                "CREATE ROOM",
                {1500, 735},
                65,
                1,
                createText
            );

            DrawTextEx(
                poppinsBlackFont,
                "JOIN ROOM",
                {1500, 835},
                65,
                1,
                joinText
            );

            DrawTextEx(
                poppinsBlackFont,
                "SETTINGS",
                {1500, 935},
                65,
                1,
                settingsText
            );
        }

        EndDrawing();
    }

    // ==================================================
    // CLEANUP
    // ==================================================

    UnloadTexture(wallpaper);

    UnloadFont(katsunoFont);
    UnloadFont(poppinsFont);
    UnloadFont(poppinsBlackFont);

    UnloadSound(switchbg);
    UnloadSound(loadingbg);

    UnloadMusicStream(bgm);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
