#ifndef INCLUDE_H
#define INCLUDE_H

/*=================================INCLUDES===================================*/

#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>
#include <math.h>
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>

struct global;

#include "entities.h"
#include "maps.h"

/*=================================MACROS=====================================*/

#define NAME "Hardcore Bisounours"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

/*=================================ENUMS======================================*/
enum game_status
{
    MENU,
    RUNNING,
    STOPPED,
    DEAD,
    VICTORY,
    END
};

enum entity_texture
{
    WBD = 0,
    WBU = 1,
    WBL = 2,
    WBR = 3,
    DBD = 4,
    DBU = 5,
    DBL = 6,
    DBR = 7,
    WML = 8,
    WMR = 9,
    DML = 10,
    DMR = 11
};

enum block_texture
{
    WBACK = 0,
    DBACK = 1,
    WFLOOR = 2,
    DFLOOR = 3,
    WWALL = 4,
    DWALL = 5,
    WFLOWER = 6,
    DFIRE = 7,
    WPENTA = 8,
    DPORT = 9,
    WSWORD = 10,
    DPENTA = 11
};

enum sword_texture
{
    U = 0,
    UR = 1,
    R = 2,
    DR = 3,
    D = 4,
    DL = 5,
    L = 6,
    UL = 7
};

/*=================================STRUCTURES=================================*/

struct inputs
{
    // 1 if pressed, else 0
    int up;
    int down;
    int left;
    int right;
    int space;
    int escape;
};

struct global
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;

    SDL_Texture **entity_textures;
    SDL_Texture **block_textures;
    SDL_Texture **sword_textures;

    struct vector2 start;

    uint64_t last_frame;
    uint64_t game_counter;

    struct inputs inputs;
    enum game_status game_status;

    int nb_monsters;
    struct entity **monsters;

    int nb_fires;
    struct block **fires;

    int nb_pentas;
    struct block **pentas;

    int nb_swords;
    struct block **swords;

    struct entity *player;

    char *maps[4];
    int map;

    int kill_count;
};

/*=================================FUNCTIONS==================================*/

/* main.c */

/* init.c */
struct global *game_init(void);
void game_clean(struct global *global);
void game_load(struct global *global);

/* inputs.c */
void get_inputs(struct global *global);
void get_menu_input(struct global *global);
void get_gameover_input(struct global *global);

/* update.c */
void update(struct global *global);
void time(struct global *global);
int collision(struct entity *ent1, struct entity *ent2);

/* display.c */
void display_menu(struct global *global);
void display_game(struct global *global);
SDL_Texture *texture_load(struct global *global, char *path);
void texture_draw(struct global *global, SDL_Texture *texture,
                  int x, int y, int w, int h);

/* blocks.c */
void fire_init(struct global *global, struct vector2 pos, SDL_Texture *texture);
void penta_init(struct global *global, struct vector2 pos,
                SDL_Texture *texture, int proba);
void sword_init(struct global *global, struct vector2 pos, 
                                                          SDL_Texture *texture);

/* parsemap.c */
void map_parse(struct global *global);

#endif
