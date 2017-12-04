#include "game.h"

SDL_Texture *texture_load(struct global *global, char *path)
{
    SDL_Surface *surface = IMG_Load(path);
    if (!surface)
        err(-1, "Cannot load %s", path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(global->renderer,
                                                        surface);
    SDL_FreeSurface(surface);
    return texture;
}

void texture_draw(struct global *global, SDL_Texture *texture,
                  int x, int y, int w, int h)
{
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;

    SDL_RenderCopy(global->renderer, texture, NULL, &rectangle);
}

void display_menu(struct global *global)
{
    texture_draw(global, global->background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Updates the window
    SDL_RenderPresent(global->renderer);

    SDL_Delay(1);
}

static void player_sword_display(struct global *global)
{
    if (global->player->sword->step == -1)
        return;
    if (global->player->sword->v_dir == UP)
    {
        if (global->player->sword->step < 3)
            texture_draw(global, global->sword_textures[UL],
                         global->player->pos.x - global->player->sword->width,
                         global->player->pos.y - global->player->sword->height,
                         global->player->sword->width,
                         global->player->sword->height);
        else if (global->player->sword->step < 6)
            texture_draw(global, global->sword_textures[U],
                         global->player->pos.x,
                         global->player->pos.y - global->player->sword->height,
                         global->player->sword->width,
                         global->player->sword->height);
        else
            texture_draw(global, global->sword_textures[UR],
                         global->player->pos.x + global->player->sword->width,
                         global->player->pos.y - global->player->sword->height,
                         global->player->sword->width,
                         global->player->sword->height);
    }
    if (global->player->sword->v_dir == LEFT)
    {
        if (global->player->sword->step < 3)
            texture_draw(global, global->sword_textures[DL],
                         global->player->pos.x - global->player->sword->width,
                         global->player->pos.y + global->player->sword->height,
                         global->player->sword->width,
                         global->player->sword->height);
        else if (global->player->sword->step < 6)
            texture_draw(global, global->sword_textures[L],
                         global->player->pos.x - global->player->sword->width,
                         global->player->pos.y,
                         global->player->sword->width,
                         global->player->sword->height);
        else
            texture_draw(global, global->sword_textures[UL],
                         global->player->pos.x - global->player->sword->width,
                         global->player->pos.y - global->player->sword->height,
                         global->player->sword->width,
                         global->player->sword->height);
    }
    if (global->player->sword->v_dir == RIGHT)
    {
        if (global->player->sword->step < 3)
            texture_draw(global, global->sword_textures[UR],
                         global->player->pos.x + global->player->width,
                         global->player->pos.y - global->player->sword->height,
                         global->player->sword->width,
                         global->player->sword->height);
        else if (global->player->sword->step < 6)
            texture_draw(global, global->sword_textures[R],
                         global->player->pos.x + global->player->width,
                         global->player->pos.y,
                         global->player->sword->width,
                         global->player->sword->height);
        else
            texture_draw(global, global->sword_textures[DR],
                         global->player->pos.x + global->player->width,
                         global->player->pos.y + global->player->sword->height,
                         global->player->sword->width,
                         global->player->sword->height);
    }
    if (global->player->sword->v_dir == DOWN)
    {
        if (global->player->sword->step < 3)
            texture_draw(global, global->sword_textures[DR],
                         global->player->pos.x + global->player->sword->width,
                         global->player->pos.y + global->player->height,
                         global->player->sword->width,
                         global->player->sword->height);
        else if (global->player->sword->step < 6)
            texture_draw(global, global->sword_textures[D],
                         global->player->pos.x,
                         global->player->pos.y + global->player->height,
                         global->player->sword->width,
                         global->player->sword->height);
        else
            texture_draw(global, global->sword_textures[DL],
                         global->player->pos.x - global->player->sword->width,
                         global->player->pos.y + global->player->height,
                         global->player->sword->width,
                         global->player->sword->height);
    }
}

static void draw_player(struct global *global)
{
    
    if (global->swords[0])
    {
        if (global->player->v_dir == UP)
            texture_draw(global, global->entity_textures[WBU],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
        else if (global->player->v_dir == LEFT)
            texture_draw(global, global->entity_textures[WBL],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
        else if (global->player->v_dir == RIGHT)
            texture_draw(global, global->entity_textures[WBR],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
        else
            texture_draw(global, global->entity_textures[WBD],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
    }
    else
    {
        if (global->player->v_dir == UP)
            texture_draw(global, global->entity_textures[DBU],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
        else if (global->player->v_dir == LEFT)
            texture_draw(global, global->entity_textures[DBL],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
        else if (global->player->v_dir == RIGHT)
            texture_draw(global, global->entity_textures[DBR],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
        else
            texture_draw(global, global->entity_textures[DBD],
                         global->player->pos.x, global->player->pos.y,
                         global->player->width, global->player->height);
    }
}

void display_game(struct global *global)
{
    // Drawing the background
    if (global->swords[0])
        texture_draw(global, global->block_textures[WBACK],
                     0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    else
        texture_draw(global, global->block_textures[DBACK],
                     0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Drawing the fires
    if (global->swords[0])
    {
        for (int i = 0; i < global->nb_fires; i++)
        {
            texture_draw(global, global->block_textures[WFLOWER],
                         global->fires[i]->pos.x, global->fires[i]->pos.y,
                         global->fires[i]->width, global->fires[i]->height);
        }
    }
    else
    {
        for (int i = 0; i < global->nb_fires; i++)
        {
            texture_draw(global, global->block_textures[DFIRE],
                         global->fires[i]->pos.x, global->fires[i]->pos.y,
                         global->fires[i]->width, global->fires[i]->height);
        }
    }

    // Drawing the pentagrams
    if (global->swords[0])
    {
        for (int i = 0; i < global->nb_pentas; i++)
        {
            texture_draw(global, global->block_textures[WPENTA],
                         global->pentas[i]->pos.x, global->pentas[i]->pos.y,
                         global->pentas[i]->width, global->pentas[i]->height);
        }
    }
    else
    {
        for (int i = 0; i < global->nb_pentas; i++)
        {
            texture_draw(global, global->block_textures[DPENTA],
                         global->pentas[i]->pos.x, global->pentas[i]->pos.y,
                         global->pentas[i]->width, global->pentas[i]->height);
        }
    }

    // Drawing the sword
    for (int i = 0; i < global->nb_swords; i++)
    {
        if (!global->swords[i])
            continue;
        texture_draw(global, global->swords[i]->texture,
                     global->swords[i]->pos.x, global->swords[i]->pos.y,
                     global->swords[i]->width, global->swords[i]->height);
    }
    // Drawing the player's sword
    player_sword_display(global);
    // Drawing the player
    draw_player(global);

    // Drawing the monsters
    for (int i = 0; i < global->nb_monsters; i++)
    {
        if (!global->monsters[i])
            continue;
        if (global->swords[0])
        {
            if (global->monsters[i]->v_dir == RIGHT)
                texture_draw(global, global->entity_textures[WMR],
                             global->monsters[i]->pos.x,
                             global->monsters[i]->pos.y,
                             global->monsters[i]->width,
                             global->monsters[i]->height);
            else
                texture_draw(global, global->entity_textures[WML],
                             global->monsters[i]->pos.x,
                             global->monsters[i]->pos.y,
                             global->monsters[i]->width,
                             global->monsters[i]->height);
        }
        else
        {
            if (global->monsters[i]->v_dir == RIGHT)
                texture_draw(global, global->entity_textures[DMR],
                             global->monsters[i]->pos.x,
                             global->monsters[i]->pos.y,
                             global->monsters[i]->width,
                             global->monsters[i]->height);
            else
                texture_draw(global, global->entity_textures[DML],
                             global->monsters[i]->pos.x,
                             global->monsters[i]->pos.y,
                             global->monsters[i]->width,
                             global->monsters[i]->height);
        }
    }

    // Updates the window
    SDL_RenderPresent(global->renderer);

    SDL_Delay(1);
}
