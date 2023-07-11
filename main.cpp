//The headers
#include "SDL2/SDL.h"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h> 

using namespace std::this_thread;
using namespace std::chrono;
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int SNAKE_SPEED = 10;
const int START_SIZE = 2;
const char* name = "sn4k3";

//The surfaces
SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
//The event structure that will be used


typedef enum moves {
    up,
    down,
    right,
    left
}moves;

typedef struct Pos {
    int x;
    int y;
}Pos;

typedef struct Snake {
    int lenght;
    moves cur_mov;
    Pos *positions;
}Snake;

Snake *snake = NULL;
Pos *power_up = NULL;

void SetSnake(bool allocated) {
    snake = new Snake();
    snake->lenght = START_SIZE;
    snake->cur_mov = moves::right;
    if (allocated) {snake->positions = (Pos*) realloc(snake->positions, snake->lenght * sizeof(Pos));}
    else {snake->positions = (Pos*) malloc(snake->lenght * sizeof(Pos)); }
}

void PlacePowerUp() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    power_up->x = (rand() % SCREEN_WIDTH/10) * 10;
    power_up->y = (rand() % SCREEN_HEIGHT/10) *10;
}

void GrowSnake(){
    snake->lenght++;
    snake->positions = (Pos*) realloc(snake->positions, snake->lenght * sizeof(Pos));
    snake->positions[snake->lenght-1] = snake->positions[snake->lenght-1];
}

void DrawRect() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255 , 255 , 255, 255);
    
    for (int i = 0; i < snake->lenght; i++) {
        // draw rect for sanke > position [i]
        SDL_Rect snake_part;
        snake_part.w = 8;
        snake_part.h = snake_part.w;
        snake_part.x = snake->positions[i].x;
        snake_part.y = snake->positions[i].y;
        SDL_RenderDrawRect(renderer, &snake_part);
    }
    SDL_Rect power_up_rect;
    power_up_rect.w = 8;
    power_up_rect.h = power_up_rect.w;
    power_up_rect.x = power_up->x;
    power_up_rect.y = power_up->y;
    SDL_SetRenderDrawColor(renderer, 255 , 0 , 0, 255);
    SDL_RenderDrawRect(renderer, &power_up_rect);

    SDL_RenderPresent(renderer);
}

void Update() {
    // moves
    for (int i = snake->lenght -1; i > 0; i--){
        snake->positions[i] = snake->positions[i-1];
    }
    switch(snake->cur_mov){
        case moves::up:
            snake->positions[0].y -= SNAKE_SPEED;
            break;
        case moves::down:
            snake->positions[0].y += SNAKE_SPEED;
            break;
        case moves::left:
            snake->positions[0].x -= SNAKE_SPEED;
            break;
        case moves::right:
            snake->positions[0].x += SNAKE_SPEED;
            break;
    }

    if (snake->positions[0].x == power_up->x && snake->positions[0].y == power_up->y) {
        PlacePowerUp();
        GrowSnake();
    }

    DrawRect();
}


void PlaceSnake() {
    snake->positions[0].x = SCREEN_WIDTH/2;
    snake->positions[0].y = SCREEN_HEIGHT/2;
    for (int i = 1; i < snake->lenght;i++){
        snake->positions[i].x = SCREEN_WIDTH/2+i*10;
        snake->positions[i].y = SCREEN_HEIGHT/2;
    }
    DrawRect();
}

bool IsItDead() {
    if (snake->positions[0].x < 0 || snake->positions[0].x > SCREEN_WIDTH || snake->positions[0].y < 0 || snake->positions[0].y > SCREEN_HEIGHT) {
        return true;
    }
    for (int i = 2; i < snake->lenght; i++){
        if (snake->positions[0].x == snake->positions[i].x && snake->positions[0].y == snake->positions[i].y) {
            return true;
        }
    }
    return false;
}


bool Init() {
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1 ){
        cout << "error while the initialization of SDL submodules" << endl;
        return true;
    }
    window = SDL_CreateWindow( name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == nullptr){
        cout << "error while creating the window" << endl;
        return true;
    }

    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        cout << "error while creating the window" << endl;
        return true;
    }

    cout << "initialization completed" << endl;
    return false;
}

void clean_up(){
    cout << "end" << endl;
    // PUT ALL ALLOCATION OF SDL HERE TO CLEAN IT 
    SDL_Quit();
}

int main() {
    
    SetSnake(false);
    SDL_Event event;
    bool quit = Init();
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    power_up = new Pos();
    PlacePowerUp();
    PlaceSnake();
    
   
    while (!quit) {
        // as long as there is event in the queue
        while( SDL_PollEvent(&event) ){
            
            if (event.type == SDL_QUIT) {
                //quit the program
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_e){
                        quit = true;
                }
                else if (event.key.keysym.sym == SDLK_t){
                    cout << "you pressed t" << endl;
                }
                else if (event.key.keysym.sym == SDLK_z){
                    snake->cur_mov = moves::up;
                        cout << "up" << endl;
                }
                else if (event.key.keysym.sym == SDLK_s){
                    snake->cur_mov = moves::down;
                        cout << "down" << endl;
                }
                else if (event.key.keysym.sym == SDLK_d){
                    snake->cur_mov = moves::right;
                        cout << "right" << endl;
                }
                else if (event.key.keysym.sym == SDLK_q){
                    snake->cur_mov = moves::left;
                        cout << "left" << endl;
                }
            }
        }
        //gameplay loop here 
        
        Update();
        quit = IsItDead();
        sleep_for(nanoseconds(100000000));
        SDL_UpdateWindowSurface( window );
    }
    clean_up();
}
