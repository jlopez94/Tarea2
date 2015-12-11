#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<SDL2/SDL_mixer.h>

#define TICK_INTERVAL 4

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*mov, *mov2;
SDL_Texture *right1, *left1, *up1, *down1, *right2, *left2, *up2, *down2;
SDL_Rect rect_background,mir, mir2;
Mix_Music *music = NULL;
bool one = true;
int frames = 0;
static Uint32 next_time;

using namespace std;

//Que corra a la misma velocidad en diferentes computadoras
Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

int main( int argc, char* args[] )
{
    //Init SDL



    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Survival Game", 100, 100, 1280/*WIDTH*/, 720/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) { return false; }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    mov = IMG_LoadTexture(renderer, "personajedown.png");
    SDL_QueryTexture(mov, NULL, NULL, &w, &h);
    mir.x = 0; mir.y = 100; mir.w = w; mir.h = h;


    mov2 = IMG_LoadTexture(renderer, "personajedown.png");
    SDL_QueryTexture(mov2, NULL, NULL, &w, &h);
    mir.x = 200; mir2.y = 100; mir2.w = w; mir2.h = h;

    //Texturas
    down1 = IMG_LoadTexture(renderer, "personajedown.png");
    up1 = IMG_LoadTexture(renderer, "personajeup.png");
    left1 = IMG_LoadTexture(renderer, "personajeleft.png");
    right1 = IMG_LoadTexture(renderer, "personajeright.png");

    down2 = IMG_LoadTexture(renderer, "personajedown2.png");
    up2 = IMG_LoadTexture(renderer, "personajeup2.png");
    left2 = IMG_LoadTexture(renderer, "personajeleft2.png");
    right2 = IMG_LoadTexture(renderer, "personajeright2.png");


    //Que corra a la misma velocidad
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int xvel = 0, yvel = 0, xvel2 = 0, yvel2 = 0;
    next_time = SDL_GetTicks() + TICK_INTERVAL;

    music = Mix_LoadMUS( "music.wav" );

    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            switch(Event.type){
                case SDL_QUIT:
                    return 0;
                    break;
            }
        }
        // PERSONAJE UNO ANIMACION CUADRO POR CUADRO
        if(state[SDL_SCANCODE_D] == 1){
            xvel = 1;
            if(state[SDL_SCANCODE_A] == 0){
                if(one)
                    mov = right1;
                else
                    mov = right2;
            }
        }if(state[SDL_SCANCODE_A] == 1){
            xvel = -1;
            if(state[SDL_SCANCODE_D] == 0){
                if(one)
                    mov = left1;
                else
                    mov = left2;
            }
        }if(state[SDL_SCANCODE_D] == 1 && state[SDL_SCANCODE_A] == 1){
            xvel = 0;
        }if(state[SDL_SCANCODE_D] == 0 && state[SDL_SCANCODE_A] == 0){
            xvel = 0;
        }if(state[SDL_SCANCODE_W] == 1){
            yvel = -1;
            if(state[SDL_SCANCODE_S] == 0){
                if(one)
                    mov = up1;
                else
                    mov = up2;
            }
        }if(state[SDL_SCANCODE_S] == 1){
            yvel = 1;
            if(state[SDL_SCANCODE_W] == 0){
                if(one)
                    mov = down1;
                else
                    mov = down2;
            }
        }if(state[SDL_SCANCODE_W] == 1 && state[SDL_SCANCODE_S] == 1){
            yvel = 0;
        }if(state[SDL_SCANCODE_W] == 0 && state[SDL_SCANCODE_S] == 0){
            yvel = 0;
        }

        mir.x += xvel;
        mir.y += yvel;


        //PERSONAJE 2 ANIMACION CUADRO POR CUADRO
        if(state[SDL_SCANCODE_RIGHT] == 1){
            xvel2 = 1;
            if(state[SDL_SCANCODE_LEFT] == 0){
                if(one)
                    mov2 = right1;
                else
                    mov2 = right2;
            }
        }if(state[SDL_SCANCODE_LEFT] == 1){
            xvel2 = -1;
            if(state[SDL_SCANCODE_RIGHT] == 0){
                if(one)
                    mov2 = left1;
                else
                    mov2 = left2;
            }
        }if(state[SDL_SCANCODE_RIGHT] == 1 && state[SDL_SCANCODE_LEFT] == 1){
            xvel2 = 0;
        }if(state[SDL_SCANCODE_RIGHT] == 0 && state[SDL_SCANCODE_LEFT] == 0){
            xvel2 = 0;
        }if(state[SDL_SCANCODE_UP] == 1){
            yvel2 = -1;
            if(state[SDL_SCANCODE_DOWN] == 0){
                if(one)
                    mov2 = up1;
                else
                    mov2 = up2;
            }
        }if(state[SDL_SCANCODE_DOWN] == 1){
            yvel2 = 1;
            if(state[SDL_SCANCODE_UP] == 0){
                if(one)
                    mov2 = down1;
                else
                    mov2 = down2;
            }
        }if(state[SDL_SCANCODE_UP] == 1 && state[SDL_SCANCODE_DOWN] == 1){
            yvel2 = 0;
        }if(state[SDL_SCANCODE_UP] == 0 && state[SDL_SCANCODE_DOWN] == 0){
            yvel2 = 0;
        }

        mir2.x += xvel2;
        mir2.y += yvel2;

        //renderer
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, mov, NULL, &mir);
        SDL_RenderCopy(renderer, mov2, NULL, &mir2);

        SDL_RenderPresent(renderer);

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
        frames += 1;

        if(frames % 60 == 0){
            one = !one;
        }


        if( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic( music, -1 );
        }
    }

	return 0;
}
