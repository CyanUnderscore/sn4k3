//The headers
#include "SDL2/SDL.h"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::this_thread;
using namespace std::chrono;
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int SNAKE_SPEED = 10;
const int START_SIZE = 6;
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

void SetSnake(bool allocated) {
    snake = new Snake();
    snake->lenght = START_SIZE;
    snake->cur_mov = moves::right;
    if (allocated) {snake->positions = (Pos*) realloc(snake->positions, snake->lenght * sizeof(Pos));}
    else {snake->positions = (Pos*) malloc(snake->lenght * sizeof(Pos)); }
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
    SDL_RenderPresent(renderer);
}

void UpdateSnake() {
    for (int i = snake->lenght -1; i > 0; i--){
        snake->positions[i] = snake->positions[i-1];
    }
    snake->positions[0].x += SNAKE_SPEED;
    string strpos = snake->positions[0].x;
    cout << strpos << endl;
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


    /*screen = SDL_GetWindowSurface(window);
    if (screen == nullptr) {
        cout << "can't get the window surface" << endl;
        return true;
    }

    */
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
        
        UpdateSnake();
        sleep_for(nanoseconds(1000000));
        SDL_UpdateWindowSurface( window );
    }
    clean_up();
}
