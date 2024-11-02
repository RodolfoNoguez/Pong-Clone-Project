#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{51, 153, 102, 255};
Color Pale_Green = Color{223, 246, 200, 255};




int p1_points = 0;
int cpu_points = 0;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;


    void Draw()
    {
        DrawCircle(x, y, radius, Pale_Green);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) 
        {
            cpu_points ++;
            ResetBall();
        } 
        
        if (x - radius <= 0)
        {
            p1_points++;
            ResetBall();
        }
    }



    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = { -1,1 };
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];

    }

};


class Paddle {

protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;
    


    void Draw()
    {
        DrawRectangle(x, y, width, height, RED); 
    }

    void Update() {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();
        
    }
};

class CpuPaddle : public Paddle
{

public:
    void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }
        LimitMovement();
    
    }

    void Draw()
    {
        DrawRectangle(x, y, width, height, BLUE);
    }
};




Ball ball;
Paddle p1;
CpuPaddle cpu;


int main()
{
    cout << "starting game" << endl;
    const int screen_w = 1280;
    const int screen_h = 800;
    InitWindow(screen_w, screen_h, "Pong clone : tennis map");
    SetTargetFPS(120);

    ball.x = screen_w / 2;
    ball.y = screen_h / 2;
    ball.speed_x = 5;
    ball.speed_y = 5;
    ball.radius = 25;


    p1.width = 25;
    p1.height = 120;
    p1.x = screen_w - p1.width - 10;
    p1.y = screen_h / 2 - p1.height / 2;
    p1.speed = 6;

    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_h / 2 - cpu.height / 2;
    cpu.speed = 6;

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        ball.Update();
        p1.Update();
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y}, ball.radius, Rectangle{p1.x, p1.y, p1.width, p1.height}))
        {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
        {
            ball.speed_x *= -1;
        }

        ClearBackground(WHITE);

        
        DrawRectangle(984, 100, 296, 600, Green);
        DrawRectangle(0, 100, 296, 600, Green);

        DrawRectangle(0, 0, 1280, 90, Green);
        DrawRectangle(0, 710, 1280, 90, Green);

        DrawRectangle(305, 100, 334, 295, Green);
        DrawRectangle(305, 405, 334, 295, Green);

        DrawRectangle(640, 100, 334, 295, Green);
        DrawRectangle(640, 405, 334, 295, Green);

        DrawRectangle(635, 0, 10, 800, DARKGRAY);
        

        
        ball.Draw();
        cpu.Draw();
        p1.Draw();
        DrawText(TextFormat("%i", cpu_points), screen_w / 4 - 20, 20, 80, BLACK);
        DrawText(TextFormat("%i", p1_points), 3 * screen_w / 4 - 20, 20, 80, BLACK);

        
        


        EndDrawing();
    }

    CloseWindow();
    return 0;
}