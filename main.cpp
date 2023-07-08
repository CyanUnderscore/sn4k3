//The headers
#include "SDL2/SDL.h"
#include <string>
#include <iostream>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
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

typedef struct Snake {
    int lenght;
    moves cur_mov;
}Snake;

Snake *snake = NULL;

void SetSnake() {
    snake = new Snake();
    snake->lenght = 0;
    snake->cur_mov = moves::right;
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
            
            switch (event.type) {
                case SDL_QUIT:
                    //quit the program
                    quit = true;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_e:
                            quit = true;
                        case SDLK_t:
                            cout << "you pressed t" << endl;
                        case SDLK_z:{
                            snake->cur_mov = moves::up;
                            cout << "up" << endl;
                        };
                        case SDLK_s:{
                            snake->cur_mov = moves::down;
                            cout << "down" << endl;
                        };
                        case SDLK_d:{
                            snake->cur_mov = moves::right;
                            cout << "right" << endl;
                        };
                        case SDLK_q:{
                            snake->cur_mov = moves::left;
                            cout << "left" << endl;
                        };
                        default:
                            {}

                        
                    }
                default: 
                    {}
            }
        }
        SDL_UpdateWindowSurface( window );
    }
    clean_up();
}
