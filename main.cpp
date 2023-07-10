//The headers
#include "SDL2/SDL.h"
#include <string>
#include <iostream>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int SNAKE_SPEED = 10; //pixel per update loop
const int START_SIZE = 1;
const char* name = "sn4k3";

//The surfaces
SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;
SDL_Window *window = NULL;
//The event structure that will be used


typedef enum moves {
    up,
    down,
    right,
    left
}moves;

typedef struct Pos{
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
    if (allocated) {snake->position = (Pos*) realloc(lenght * sizeof(Pos));}
    else {snake->position = (Pos*) malloc(lenght * sizeof(Pos)); }
    
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


    screen = SDL_GetWindowSurface(window);
    if (screen == nullptr) {
        cout << "can't get the window surface" << endl;
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
    SetSnake();
    SDL_Event event;
    bool quit = Init();

   
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
        UpdateSnake();
        SDL_UpdateWindowSurface( window );
    }
    clean_up();
}
