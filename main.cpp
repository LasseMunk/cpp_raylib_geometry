#include <iostream>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    // SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(windowWidth, windowHeight, "Geometry");
    SetTargetFPS(60);

    float deltatime;

    int xyUnits = 10;

    Vector2 center = {(windowWidth - 300) / 2.0f, windowHeight / 2.0f};
    float innerRadius = 80.0f;
    float outerRadius = 190.0f;

    float startAngle = 0.0f;
    float endAngle = 360.0f;
    float segments = 0.0f;

    bool drawRing = true;
    bool drawRingLines = false;
    bool drawCircleLines = false;

    Rectangle startAngleSlider{600, 40, 120, 20};
    Rectangle endAngleSlider{600, 70, 120, 20};
    Rectangle innerRadiusSlider{600, 140, 120, 20};
    Rectangle outerRadiusSlider{600, 170, 120, 20};
    Rectangle segmentsSlider{600, 240, 120, 20};

    while (!WindowShouldClose())
    {
        deltatime = GetFrameTime();

        endAngle += 360.0f * deltatime;
        startAngle = endAngle - 10.0f;

        if (endAngle >= 360.0f)
        {
            startAngle = -10.0f;
            endAngle = 0.0f;
        }

        BeginDrawing();

        ClearBackground(WHITE); // avoid flickering while double buffering
        DrawLine(500, 0, 500, windowHeight, Fade(LIGHTGRAY, 0.6f));
        DrawRectangle(500, 0, windowWidth - 500, windowHeight, Fade(LIGHTGRAY, 0.3f));

        // ==================================================================================================

        // TODO - do calculation of start/end line segments outside of while loop, and only draw them here
        // Coordinate system
        DrawLine(0, windowHeight / 2, windowWidth - 300, windowHeight / 2, Fade(LIGHTGRAY, 0.6f));                // X axis
        DrawLine((windowWidth - 300) / 2.0f, 0, (windowWidth - 300) / 2.0f, windowHeight, Fade(LIGHTGRAY, 0.6f)); // Y axis

        for (int i = 0; i < (xyUnits * 2); i++)
        {
            DrawLine(center.x - (xyUnits * (windowWidth - 300) / (xyUnits * 2)) + ((windowWidth - 300) / (xyUnits * 2) * i), 0, center.x - (xyUnits * (windowWidth - 300) / (xyUnits * 2)) + ((windowWidth - 300) / (xyUnits * 2) * i), windowWidth - 300, Fade(LIGHTGRAY, 0.3f)); // X axis grid lines
            DrawLine(0, center.y - (xyUnits * (windowWidth - 300) / (xyUnits * 2)) + ((windowWidth - 300) / (xyUnits * 2) * i), windowWidth - 300, center.y - (xyUnits * (windowWidth - 300) / (xyUnits * 2)) + ((windowWidth - 300) / (xyUnits * 2) * i), Fade(LIGHTGRAY, 0.3f)); // Y axis grid lines
        }

        // ==================================================================================================

        if (drawRing)
            DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, (int)segments, Fade(MAROON, 0.3f));
        if (drawRingLines)
            DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, (int)segments, Fade(BLACK, 0.4f));
        if (drawCircleLines)
            DrawCircleSectorLines(center, outerRadius, startAngle, endAngle, (int)segments, Fade(BLACK, 0.4f));

        // Draw GUI controls
        //------------------------------------------------------------------------------
        GuiSliderBar(startAngleSlider, "StartAngle", NULL, &startAngle, 0, 360);
        GuiSliderBar(endAngleSlider, "EndAngle", NULL, &endAngle, 0, 360);

        GuiSliderBar(innerRadiusSlider, "InnerRadius", NULL, &innerRadius, 0, 100);
        GuiSliderBar(outerRadiusSlider, "OuterRadius", NULL, &outerRadius, 0, 200);

        GuiSliderBar(segmentsSlider, "Segments", NULL, &segments, 0, 100);

        // GuiCheckBox((Rectangle){600, 320, 20, 20}, "Draw Ring", &drawRing);
        // GuiCheckBox((Rectangle){600, 3xyUnits0, 20, 20}, "Draw RingLines", &drawRingLines);
        // GuiCheckBox((Rectangle){600, 380, 20, 20}, "Draw CircleLines", &drawCircleLines);
        //------------------------------------------------------------------------------

        int minSegments = (int)ceilf((endAngle - startAngle) / 90);
        // DrawText(TextFormat("MODE: %s", (segments >= minSegments) ? "MANUAL" : "AUTO"), 600, 270, 10, (segments >= minSegments) ? MAROON : DARKGRAY);

        // DrawFPS(10, 10);
        EndDrawing();
    }

    // Clean up
    CloseWindow();
}
