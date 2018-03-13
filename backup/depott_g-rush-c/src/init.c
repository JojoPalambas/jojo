#include "game.h"

void load_textures(struct global *global)
{
    global->entity_textures[WBD] = texture_load(global,
                                                "./tests/Images/wbd.png");
    global->entity_textures[WBU] = texture_load(global,
                                                "./tests/Images/wbu.png");
    global->entity_textures[WBL] = texture_load(global,
                                                "./tests/Images/wbl.png");
    global->entity_textures[WBR] = texture_load(global,
                                                "./tests/Images/wbr.png");
    global->entity_textures[DBD] = texture_load(global,
                                                "./tests/Images/dbd.png");
    global->entity_textures[DBU] = texture_load(global,
                                                "./tests/Images/dbu.png");
    global->entity_textures[DBL] = texture_load(global,
                                                "./tests/Images/dbl.png");
    global->entity_textures[DBR] = texture_load(global,
                                                "./tests/Images/dbr.png");
    global->entity_textures[WML] = texture_load(global,
                                                "./tests/Images/wml.png");
    global->entity_textures[WMR] = texture_load(global,
                                                "./tests/Images/wmr.png");
    global->entity_textures[DML] = texture_load(global,
                                                "./tests/Images/dml.png");
    global->entity_textures[DMR] = texture_load(global,
                                                "./tests/Images/dmr.png");
    global->block_textures[WBACK] = texture_load(global,
                                        "./tests/Textures/wbackground.jpg");
    global->block_textures[DBACK] = texture_load(global,
                                        "./tests/Textures/dbackground.jpeg");
    global->block_textures[WFLOOR] = texture_load(global,
                                        "./tests/Textures/wfloor.jpeg");
    global->block_textures[DFLOOR] = texture_load(global,
                                        "./tests/Textures/dfloor.jpeg");
    global->block_textures[WWALL] = texture_load(global,
                                        "./tests/Textures/wwall.jpeg");
    global->block_textures[DWALL] = texture_load(global,
                                        "./tests/Textures/dwall.jpg");
    global->block_textures[WFLOWER] = texture_load(global,
                                        "./tests/Textures/wflower.png");
    global->block_textures[DFIRE] = texture_load(global,
                                        "./tests/Textures/dfire.png");
    global->block_textures[WPENTA] = texture_load(global,
                                        "./tests/Textures/wpenta.png");
    global->block_textures[DPORT] = texture_load(global,
                                        "./tests/Textures/dport.jpeg");
    global->block_textures[WSWORD] = texture_load(global,
                                        "./tests/Textures/wsword.png");
    global->block_textures[DPENTA] = texture_load(global,
                                        "./tests/Textures/dpenta.png");
    global->sword_textures[U] = texture_load(global,
                                        "./tests/Images/su.png");
    global->sword_textures[UR] = texture_load(global,
                                        "./tests/Images/sur.png");
    global->sword_textures[R] = texture_load(global,
                                        "./tests/Images/sr.png");
    global->sword_textures[DR] = texture_load(global,
                                        "./tests/Images/sdr.png");
    global->sword_textures[D] = texture_load(global,
                                        "./tests/Images/sd.png");
    global->sword_textures[DL] = texture_load(global,
                                        "./tests/Images/sdl.png");
    global->sword_textures[L] = texture_load(global,
                                        "./tests/Images/sl.png");
    global->sword_textures[UL] = texture_load(global,
                                        "./tests/Images/sul.png");
    
}

void game_load(struct global *global)
{
    global->entity_textures = calloc(12, sizeof(void*));
    global->block_textures = calloc(12, sizeof(void*));
    global->sword_textures = calloc(8, sizeof(void*));
    if (!global->entity_textures || !global->block_textures)
        err(-1, "Cannot allocate memory to store textures");
    load_textures(global);
    global->background = global->block_textures[WBACK];
}

struct global *game_init(void)
{
    int ans = SDL_Init(SDL_INIT_VIDEO);
    if (ans)
        err(1, "Cannot initialize SDL");

    struct global *global = calloc(1, sizeof (struct global));
    if (!global)
        err(-1, "Cannot initialize global structure");

    global->window = SDL_CreateWindow(NAME,
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      SCREEN_WIDTH,
                                      SCREEN_HEIGHT,
                                      SDL_WINDOW_SHOWN);
    if (!global->window)
        err(-1, "Cannot initialize game window");

    global->renderer = SDL_CreateRenderer(global->window,
                                          -1,
                                          SDL_RENDERER_ACCELERATED);
    if (!global->renderer)
        err(-1, "Cannot initialize renderer");

    game_load(global);

    global->last_frame = SDL_GetTicks();
/*    global->game_counter = 0;
    
    global->start.x = 0;
    global->start.y = 0;

    global->inputs.up = 0;
    global->inputs.down = 0;
    global->inputs.left = 0;
    global->inputs.right = 0;
    global->inputs.space = 0;
    global->inputs.escape = 0; */

    global->game_status = RUNNING;

    // Player has to be initialized outside
/*
    global->nb_monsters = 0;
    global->monsters = NULL;

    global->nb_fires = 0;
    global->fires = NULL;

    global->nb_pentas = 0;
    global->pentas = NULL;
*/
    /*struct vector2 v2 =
    {
        600, 600
    };*/
  //  global->sword = NULL;
    char *tab[4] = {"tests/Maps/map1.map", "tests/Maps/map2.map",
                                "tests/Maps/map3.map", "tests/Maps/map4.map"};
    for (int i = 0 ; i < 4 ; i++)
      global->maps[i] = tab[i];
    //map_parse(global);
    //sword_init(global, v2, global->block_textures[WSWORD]);

    return global;
}

static void free_global(struct global *global)
{
    for (int i = 0; i < 12; i++)
    {
        SDL_DestroyTexture(global->entity_textures[i]);
        SDL_DestroyTexture(global->block_textures[i]);
    }
    free(global->entity_textures);
    free(global->block_textures);

    for (int i = 0; i < global->nb_monsters; i++)
    {
        if (!global->monsters[i])
           continue;
        free(global->monsters[i]);
    }
    if (global->monsters)
        free(global->monsters);

    for (int i = 0; i < global->nb_fires; i++)
    {
        free(global->fires[i]);
    }
    if (global->fires)
        free(global->fires);

    for (int i = 0; i < global->nb_pentas; i++)
    {
        free(global->pentas[i]);
    }
    if (global->pentas)
        free(global->pentas);

    if (global->swords[0])
        free(global->swords[0]);
    free(global->swords);

    free(global);
}

void game_clean(struct global *global)
{
    SDL_DestroyRenderer(global->renderer);
    SDL_DestroyWindow(global->window);

    SDL_DestroyTexture(global->background);

    free_global(global);

    SDL_Quit();
}
