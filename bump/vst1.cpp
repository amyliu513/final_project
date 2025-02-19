﻿// vst1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
using namespace std;
#define SDL_MAIN_INCLUDED
#include <iostream>
#include<Windows.h>
#include<stdio.h>
#include<SDL.h>
#include <SDL_image.h>
#undef main
#include <cstring>



SDL_Renderer* renderer;
SDL_Window* window;
bool isRunning;
bool fullscreen;
void handleEvents();
void update();
void render();

int windowW, windowH;

//START*****************************************************************************************
//int cnt = 0;
//bool moveRight = true;
SDL_Event event;

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

};

class GameObject {
public:
    GameObject(const char* texturesheet, SDL_Renderer* ren, double x, double y, int h, int w);
    ~GameObject();
    void Update();
    void Update2();
    //+
    void Fall();
    void Fallbump();
    void Fallbump2();
    //+
    void Render();

private:
    double xpos;
    double ypos;
    int objH;
    int objW;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
};

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, double x, double y, int h, int w)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);

    xpos = x;
    ypos = y;
    objH = h;
    objW = w;
}

void GameObject::Update()
{
    srcRect.h = objH;
    srcRect.w = objW;

    srcRect.h = 1248.0;
    srcRect.w = 1728.0;
    srcRect.x = 0.0;
    srcRect.y = 0.0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 3;
    destRect.h = srcRect.h / 3;

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            ypos += -10;
            break;
            //START*****************************************************************************************
        case SDLK_LEFT:
            if (xpos >= -195)
                xpos += -15;
            break;
        case SDLK_RIGHT:
            if (xpos <= 425)
                xpos += 15;
            break;
            //END*****************************************************************************************
        case SDLK_s:
            ypos += 10;
            break;
        default:
            break;
        }
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            xpos += 0;
            break;
        case SDLK_a:
            xpos += 0;
            break;
        case SDLK_d:
            ypos += 0;
            break;
        case SDLK_s:
            ypos += 0;
            break;
        default:
            break;
        }
    }
}

void GameObject::Update2()
{

    srcRect.h = 1800.0;
    srcRect.w = 2400.0;
    srcRect.x = 0.0;
    srcRect.y = 0.0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 3;
    destRect.h = srcRect.h / 3;

}

//+
void GameObject::Fall()
{
    srcRect.h = 1800.0;
    srcRect.w = 2400.0;
    srcRect.x = 0.0;
    srcRect.y = 0.0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 3;
    destRect.h = srcRect.h / 3;

    for (int i = 0; i < 100; i++)
    {
        if (ypos != 400.0)
        {
            ypos += 0.05;
        }
        else
        {
            ypos = -400.0;
            xpos += 20;
        }
    }
    
    
}
//+

void GameObject::Fallbump()
{
    srcRect.h = 600.0;
    srcRect.w = 800.0;
    srcRect.x = 0.0;
    srcRect.y = 0.0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 3;
    destRect.h = srcRect.h / 3;

    for (int i = 0; i < 100; i++)
    {
        if (i / 2 == 0) {
            continue;
        }
        if (xpos > 200) {
            xpos = (xpos - 150);
        }
        //SDL_Delay(100);
        else if (ypos < 400)
        {
            ypos += 0.05;
        }
        else if (ypos > 300)
        {
            ypos = -400.0;
            xpos += 30;
        }
    }
}
void GameObject::Fallbump2()
{
    srcRect.h = 1800.0;
    srcRect.w = 2400.0;
    srcRect.x = 0.0;
    srcRect.y = 0.0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 3;
    destRect.h = srcRect.h / 3;

    for (int i = 0; i < 100; i++)
    {
        if ((i / 5 == 0) or (i / 3 == 0)) {
            continue;
        }
        if (xpos > 700) {
            xpos = (xpos + 400);
        }
        else if (ypos < 400)
        {
            ypos += 0.05;
        }
        else if (ypos > 300)
        {
            ypos = -400.0;
            xpos += 30;
        }
    }
}


void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

GameObject* player;
GameObject* bg;
GameObject* trash;
GameObject* dog;
GameObject* dog2;



int main(int argc, char** argv)

{
    fullscreen = false;
    int flags = 0;
    flags = SDL_WINDOW_RESIZABLE;
    if (fullscreen) {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialized!\n";

        window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
        if (window) {
            std::cout << "Window Created!\n";
            SDL_SetWindowMinimumSize(window, 100, 100);
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
            std::cout << "Renderer created!\n";
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            isRunning = true;
        }

        int playerW = 1000, playerH = 600;
        SDL_GetRendererOutputSize(renderer, &windowW, &windowH);
        //START*****************************************************************************************
        player = new GameObject("cloud.png", renderer, 0, 290, playerH, playerW);
        bg = new GameObject("bg.png", renderer, 0, 0, playerH, playerW);
        trash = new GameObject("cat.png", renderer, 0, -350, playerH, playerW);
        dog = new GameObject("planet.png", renderer, 0, -300, playerH, playerW);
        dog2 = new GameObject("cat.png", renderer, 300, -300, playerH, playerW);

        std::cout << "windowH: " << windowH << std::endl;
        std::cout << "windowW: " << windowW << std::endl;
        std::cout << "playerH: " << playerH << std::endl;
        
        //END*****************************************************************************************

    }

    //START*****************************************************************************************
    const int FPS = 60;
    const int frameDelay = 400 / FPS; //max time between frames

    Uint32 frameStart;
    int frameTime;
    //END*****************************************************************************************

    while (isRunning) {
        //START*****************************************************************************************
        frameStart = SDL_GetTicks(); //how many miliseconds from we first initialized
        //END*****************************************************************************************
        handleEvents();
        update();
        render();

        //+
        
        //+
        // 
        //START*****************************************************************************************
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) // To smoothen our the movement
        {
            SDL_Delay(frameDelay - frameTime);
        }
        //END*****************************************************************************************
    }

    //frees memory associated with renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window); //error here
    SDL_Quit();

    return 0;
}

//handles any events that SDL noticed.
void handleEvents() {
    //the only event we'll check is the SDL_QUIT event.
    //SDL_Event event; change to global

    SDL_PollEvent(&event);


    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

//simple render function
void render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);


    //START*****************************************************************************************
    bg->Render();
    player->Render();
    trash->Render();
    dog->Render();
    dog2->Render();
   
    
    //END*****************************************************************************************

     //your stuff to render would typically go here.
    SDL_RenderPresent(renderer);
}

//simple update function
void update() {
    //if things could update the code would go in here.
    //START*****************************************************************************************
   //  if (cnt == 800) {
   //     moveRight = false;
   //  }
   //  else if (cnt == 0) {
   //     moveRight = true;
   //  }
   //  if (moveRight == true) {
   //     cnt++;
   //  }
   //  else { cnt--; }
   //  destR.h = 96;
   //  destR.w = 96;
   //  destR.x = cnt;

    player->Update();
    bg->Update2();
    trash->Fall();
    dog->Fallbump();
    dog2->Fallbump2();
    
    //END*****************************************************************************************
}