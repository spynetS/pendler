#include <stdio.h>
#include "./raylib-5.5_linux_amd64/include/raylib.h"
#include "./raylib-5.5_linux_amd64/include/raymath.h"
#include <math.h>

#define WINDOW_WIDTH  1225
#define WINDOW_HEIGHT 800

#define ROD_LENGTH 250

Vector2 gravity = {0, 1000};

void simulate(float dt, Vector2 *bob_vel, Vector2 *bob_position, Vector2 *pivot_position) {
  (*bob_vel) = Vector2Add(*bob_vel, Vector2Scale(gravity, dt));
  Vector2 new_bob_position =
    Vector2Add(*bob_position, Vector2Scale(*bob_vel, dt));

  Vector2 dir = Vector2Subtract(new_bob_position, *pivot_position);
  dir = Vector2Normalize(dir);
    
  float dot = bob_vel->x * dir.x + bob_vel->y * dir.y;
  Vector2 radial = Vector2Scale(dir, dot);
  (*bob_vel) = Vector2Subtract(*bob_vel, radial);
    
  (*bob_position) = Vector2Add(*pivot_position, Vector2Scale(dir, ROD_LENGTH));
}


int main() {

  
  Vector2 bob_position = {WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.8};
  Vector2 bob_vel = {1000,0};
  
  Vector2 pivot_position = {WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.25};

  Vector2 bob2_position = {WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.8};
  Vector2 bob2_vel = {1000,0};
  

  
  SetTargetFPS(60);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World!");
  
  while (!WindowShouldClose()) {

    float dt = GetFrameTime();

    simulate(dt, &bob_vel, &bob_position, &pivot_position);
    simulate(dt, &bob2_vel, &bob2_position, &bob_position);


    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 mpos = GetMousePosition();

      Vector2 dir = Vector2Subtract(mpos, bob2_position);
      dir = Vector2Normalize(dir);
      bob2_vel = Vector2Add(bob2_vel, Vector2Scale(dir, 100));

      dir = Vector2Subtract(mpos, bob_position);
      dir = Vector2Normalize(dir);
      bob_vel = Vector2Add(bob_vel, Vector2Scale(dir, 100));
    }
    else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Vector2 mpos = GetMousePosition();

      Vector2 dir = Vector2Subtract(bob2_position, mpos);
      dir = Vector2Normalize(dir);
      bob2_vel = Vector2Add(bob2_vel, Vector2Scale(dir, 100));

      dir = Vector2Subtract(bob_position, mpos);
      dir = Vector2Normalize(dir);
      bob_vel = Vector2Add(bob_vel, Vector2Scale(dir, 100));
    }




    BeginDrawing();
    ClearBackground(GetColor(0x181818));

    DrawLineEx(pivot_position, bob_position, 12, GetColor(0xffffffff));
    DrawLineEx(bob_position, bob2_position, 12, GetColor(0xffffffff));

    DrawCircle(bob_position.x, bob_position.y, 50, GetColor(0xff5050ff));
    DrawCircle(pivot_position.x, pivot_position.y, 15, GetColor(0x5050ffff));
    DrawCircle(bob2_position.x, bob2_position.y, 50, GetColor(0xff5050ff));


    /* DrawLineEx(bob_position, Vector2Add(bob_position, gravity), 10, GetColor(0xffffffff)); */
    /* DrawLineEx(bob_position, Vector2Scale(dir, ROD_LENGTH), 10, GetColor(0xff00ffff)); */
    
    EndDrawing();
  }
  return 0;
}
