    #include "raylib.h"
    #include <cmath>
    #include <bits/stdc++.h>
    #include <list>
    #include "bits/stdc++.h" 
    #include <iostream>
 
        const int screenHeight = 1200;
        int screenWidth = 1500;
        const int mapLength = 24;
        const int mapWidth = 24;
        const int tileSize = 40;

        

        int map[mapLength][mapWidth] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,3,3,3,0,3,3,3,3,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };


enum side
{
    X,
    Y, 
    NONE
};

struct ray
{
    float perpwall;
    side m_side;
    int mapx;
    int mapy;
    Color color;
};



        


ray CastRay(float posY, float posX, float rayDirX, float rayDirY)
    {
        ray mray;
        Color col;
        int stepX = 0; int stepY = 0;
        float sideDistX = 0; float sideDistY = 0;
        float perpWallDist = 0;

        //DrawLine(10,10,100,100,RED);
        int mapX = (int)posX;
        int mapY = (int)posY;

        float deltaDistX = 1/ std:: abs(rayDirX); // deltaDist is how far you move along the ray to move a full box in that axis
        float deltaDistY = 1/ std:: abs(rayDirY);
        
        if (rayDirX < 0) 
        {
            stepX = -1; //could possibly be stepX = -1
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else 
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }

        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else 
        {
            stepY  = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        bool hit = false;
        side side = NONE;
        int steps = 0;
        int max_steps = mapWidth * mapLength + 1;
        

        while (!hit && steps < max_steps)
        {
            
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = X;
            }
            else 
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = Y;
            }

            if (mapX < 0 || mapX >= mapWidth || mapY < 0 || mapY >= mapLength)
            {
                break;
            }

            if(map[mapY][mapX] != 0)
            {
                hit = true;
            }

            steps += 1;
        }

        // switch (map[mapX][mapY])
        // {
        //     case 0:
        //     {
        //         mray.color = BLACK;
        //     }
        //     case 1:
        //     {
        //         mray.color = WHITE;
        //     }
        //     case 2:
        //     {
        //         mray.color = RED;
        //     }
        //     // case 3:
        //     // {
        //     //     mray.color = GREEN;
        //     // }
        // }

        
        

        if(hit == false)
        {
            mray.perpwall = std::numeric_limits<float>::infinity();
            mray.m_side = NONE;
            return mray;
        }

        if(side == X)
            {
                mray.perpwall = sideDistX - deltaDistX;
                
            }
            else
            {
                mray.perpwall = sideDistY - deltaDistY;
            }

        if(map[mapX][mapY] == 0)
        {
            mray.color = BLACK;
            col = mray.color;
        }
        else if(map[mapX][mapY] == 1)
        {
            mray.color = WHITE;
            col = mray.color;
        }
        else if(map[mapX][mapY] == 2)
        {
            mray.color = RED;
            col = mray.color;
        }
        else if(map[mapX][mapY] == 3)
        {
            mray.color = GREEN;
            col = mray.color;
        }
        else if(map[mapX][mapY] == 4)
        {
            mray.color = PINK;
            col = mray.color;
        }

            mray.m_side = side;
            mray.mapx = mapX;
            mray.mapy = mapY;
            mray.color = col;
        return mray;
    }
 

    float dirX = 0.0f;
    float dirY =1.0f;

    float plane = 0.66f;
    float planeX = dirY;
    float planeY = -dirX;

    float posX = 2.5f;
    float posY = 2.5f;

    float mouse_sensitivity = 0.01f;

    float movespeed = 5.0f;


    bool isWall(float worldX, float worldY)
    {
        int cellX = (int)worldX;
        int cellY = (int)worldY;

        if(map[cellX][cellY] > 0)
        {
            return true;
        }
        else{
            return false;
        }
    }
    void Handle_Input()
    {

       //mouse rotation
        Vector2 mouse_Delta = {GetMouseDelta().x, GetMouseDelta().y};
        //std:: cout << mouse_Delta.x << "mouse delta x angle: "<<std:: endl;
        float angle = -mouse_Delta.x * mouse_sensitivity;

        if(angle != 0)
        {
            float s = sin(angle);
            float c = cos(angle);
            //std:: cout << mouse_Delta.x << "mouse delta x angle: "<<std:: endl;
            float oldDirX = dirX;
            //std:: cout << oldDirX << "old_dirx: "<<std:: endl;
            dirX = oldDirX * c - dirY *s;
            //std:: cout << v.dirX << "CURRENT DIRX: "<<std:: endl;
            dirY = oldDirX * s + dirY * c;

            float OldPlaneX = planeX;
            //std:: cout << OldPlaneX << "old_planeX: "<<std:: endl;
            planeX = OldPlaneX * c - planeY * s;
            //std:: cout << v.planeX << "CURRENT VPLANEX: "<<std:: endl;
            planeY = OldPlaneX * s + planeY * c;
        }

        //player movement
        float movestep = movespeed * GetFrameTime();
        float forward = 0.0f;
        float strafe = 0.0f;

        if(IsKeyDown(KEY_W))
        {
            forward +=1.0f;
        }
        if(IsKeyDown(KEY_S))
        {
            forward -=1.0f;
        }
        if(IsKeyDown(KEY_D))
        {
            strafe +=1;
        }
        if(IsKeyDown(KEY_A))
        {
            strafe -=1;
        }

        
        float moveX = (dirX * forward + planeX * strafe) * movestep;
        float moveY = (dirY * forward + planeY * strafe) * movestep;

        if(!isWall(posX + moveX, posY))
        {
            posX = posX + moveX;

        }   
        if(!isWall(posX, moveY + posY))
        {
            posY = posY + moveY;
        }     

    }

    void renderFrame()
    {
        for (int x = 0; x < screenWidth -1; x++)
        {
            
            //fstd:: cout << "X_COUNT: " << x << std:: endl;

             float cameraX = 2.0f * (float)x / (float)screenWidth - 1.0f;
             float rayDirX = dirX + planeX * cameraX;
             float rayDirY = dirY + planeY * cameraX;
             ray mray = CastRay(posY,posX, rayDirX, rayDirY);
            

            float lineHeight = screenHeight / mray.perpwall; //inverse proportion
            //std:: cout << mray.perpwall << std:: endl;
             //std:: cout << mray.mapx << std:: endl;
             //std:: cout << mray.mapy << std:: endl;
             //std:: cout << lineHeight << std:: endl;


            float drawStart = screenHeight / 2 - lineHeight /2; //center it on the horizon
            float drawEnd = screenHeight / 2 + lineHeight / 2;

            //clamp - close wall gives a huge lineHeight

            if(drawStart < 0)
            {
                drawStart = 0;
            }
            if(drawEnd >= screenHeight)
            {
                drawEnd = screenHeight - 1;
            }

            Color color = WHITE;
            if(mray.m_side == Y)
            {
                mray.color = GRAY;
            }

            DrawLine(x, drawStart, x, drawEnd, mray.color);
            //DrawLine(10,10,100 + x,400,RED);

        }
        
    }


int main()
{
    InitWindow(screenWidth, screenHeight, "raycaster draft");
    
   while (!WindowShouldClose())
    {
        
        SetTargetFPS(60);
        HideCursor();
        Handle_Input();
        BeginDrawing();
        ClearBackground(BLACK);
        renderFrame();
        DrawFPS(10,10);
        EndDrawing();
    }
}