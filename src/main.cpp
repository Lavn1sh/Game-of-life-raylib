#include <raylib.h>
#include "simulation.hpp"

int main(){
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    const int CELL_SIZE = 8;
    int FPS = 12;
    Color GREY = {29, 29, 29, 255};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game of Life");
    SetTargetFPS(FPS);
    Simulation simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};
    
    

    // Simulation loop
    while (WindowShouldClose() == false)
    {
        // 1. Event Handling
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            simulation.ToggleCell(row, column);
        }

        if(IsKeyPressed(KEY_ENTER)){
            simulation.Start();
            SetWindowTitle("Game of Life is running...");
        }
        else if(IsKeyPressed(KEY_SPACE)){
            simulation.Stop();
            if(simulation.IsRunning()) SetWindowTitle("Game of Life is running...");
            else SetWindowTitle("Game of Life has paused");
        }

        else if (IsKeyPressed(KEY_F)){
            if(FPS <= 16){
                FPS += 4;
                SetTargetFPS(FPS);
            }
        }
        else if(IsKeyPressed(KEY_S)){
            if(FPS >= 8){
                FPS -= 4;
                SetTargetFPS(FPS);
            }
        }
        else if(IsKeyPressed(KEY_R)) simulation.CreateRandomState();
        else if(IsKeyPressed(KEY_C)) simulation.ClearGrid();


        // 2. Updating the state
        simulation.Update();

        // 3. Rendering objects
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
    }
    

    CloseWindow();
}