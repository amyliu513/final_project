#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#undef main
#include <iostream>
//START*****************************************************************************************
#include <cstring>
//END*****************************************************************************************

//don't do this, this is just an example
SDL_Renderer* renderer;
SDL_Window* window;
bool isRunning;
bool fullscreen;
void handleEvents();
void update();
void render();

//START*****************************************************************************************
int cnt = 0;
bool moveRight = true;
SDL_Event event;

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

};

class GameObject {
public:
    GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
    ~GameObject();
    void Update();
    void Render();

private:
    int xpos;
    int ypos;

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

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);

    xpos = x;
    ypos = y;
}

void GameObject::Update()
{

    srcRect.h = 416;
    srcRect.w = 576;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 3;
    destRect.h = srcRect.h / 3;

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        // case SDLK_w:
        //     ypos += -10;
        //     break;
        case SDLK_LEFT:
            xpos += -15;
            break;
        case SDLK_RIGHT:
            xpos += 15;
            break;
        // case SDLK_s:
        //     ypos += 10;
        //     break;
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

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

GameObject* player;
//END*****************************************************************************************


//please don't put all your code in main like I did.
int main() {

 fullscreen = false;
 int flags = 0;
 flags = SDL_WINDOW_RESIZABLE;
 if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
 }
 if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
  std::cout << "Subsystems Initialized!\n";

  window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 500, flags);
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

  //START*****************************************************************************************
    player = new GameObject("assets/spaceship.png", renderer, 0, 370);
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
player->Render();
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
 //END*****************************************************************************************
}