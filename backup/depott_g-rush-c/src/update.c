#include "game.h"

void time(struct global *global)
{
    uint64_t delta_time = SDL_GetTicks() - global->last_frame;
    if (delta_time < 16)
    {
        SDL_Delay(16 - delta_time);
        global->game_counter += 16;
    }
    else
    {
        global->game_counter += delta_time;
    }
    global->last_frame = SDL_GetTicks();
}

int entity_collision(struct entity *ent1, struct entity *ent2)
{
    int l1 = ent1->pos.x + ent1->width / 4;
    int r1 = ent1->pos.x + ent1->width * 3 / 4;
    int l2 = ent2->pos.x + ent2->width / 4;
    int r2 = ent2->pos.x + ent2->width * 3 / 4;

    int u1 = ent1->pos.y + ent1->height / 2;
    int d1 = ent1->pos.y + ent1->height;
    int u2 = ent2->pos.y + ent2->height / 2;
    int d2 = ent2->pos.y + ent2->height;

    int coll_hor = (l1 > l2 && l1 < r2) || (r1 > l2 && r1 < r2);
    int coll_ver = (u1 > u2 && u1 < d2) || (d1 > u2 && d1 < d2);
    return coll_hor && coll_ver;
}

int block_collision(struct entity *ent, struct block *blk)
{
    int l1 = ent->pos.x + ent->width / 4;
    int r1 = ent->pos.x + ent->width * 3 / 4;
    int l2 = blk->pos.x + blk->width / 4;
    int r2 = blk->pos.x + blk->width * 3 / 4;

    int u1 = ent->pos.y + ent->height / 2;
    int d1 = ent->pos.y + ent->height;
    int u2 = blk->pos.y + blk->height / 2;
    int d2 = blk->pos.y + blk->height;

    int coll_hor = (l1 > l2 && l1 < r2) || (r1 > l2 && r1 < r2);
    int coll_ver = (u1 > u2 && u1 < d2) || (d1 > u2 && d1 < d2);
    return coll_hor && coll_ver;
}

int sword_collision(struct entity *ent, struct global *global)
{
    if (global->player->sword->step == -1)
        return 0;

    int l1 = ent->pos.x + ent->width / 4;
    int r1 = ent->pos.x + ent->width * 3 / 4;
    int u1 = ent->pos.y + ent->height / 2;
    int d1 = ent->pos.y + ent->height;

    int l2 = global->player->sword->pos.x;
    int r2 = global->player->sword->pos.x + global->player->sword->width;
    int u2 = global->player->sword->pos.y;
    int d2 = global->player->sword->pos.y + global->player->sword->height;

    if (global->player->sword->v_dir == UP)
    {
        if (global->player->sword->step < 3)
        {
            l2 -= global->player->sword->width;
            r2 -= global->player->sword->width;
            u2 -= global->player->sword->height;
            d2 -= global->player->sword->height;
        }
        else if (global->player->sword->step < 6)
        {
            u2 -= global->player->sword->height;
            d2 -= global->player->sword->height;
        }
        else
        {
            l2 += global->player->sword->width;
            r2 += global->player->sword->width;
            u2 -= global->player->sword->height;
            d2 -= global->player->sword->height;
        }
    }

    if (global->player->sword->v_dir == LEFT)
    {
        if (global->player->sword->step < 3)
        {
            l2 -= global->player->sword->width;
            r2 -= global->player->sword->width;
            u2 += global->player->sword->height;
            d2 += global->player->sword->height;
        }
        else if (global->player->sword->step < 6)
        {
            l2 -= global->player->sword->width;
            r2 -= global->player->sword->width;
        }
        else
        {
            l2 -= global->player->sword->width;
            r2 -= global->player->sword->width;
            u2 -= global->player->sword->height;
            d2 -= global->player->sword->height;
        }
    }

    if (global->player->sword->v_dir == RIGHT)
    {
        if (global->player->sword->step < 3)
        {
            l2 += global->player->sword->width;
            r2 += global->player->sword->width;
            u2 -= global->player->sword->height;
            d2 -= global->player->sword->height;
        }
        else if (global->player->sword->step < 6)
        {
            l2 += global->player->sword->width;
            r2 += global->player->sword->width;
        }
        else
        {
            l2 += global->player->sword->width;
            r2 += global->player->sword->width;
            u2 += global->player->sword->height;
            d2 += global->player->sword->height;
        }
    }

    if (global->player->sword->v_dir == DOWN)
    {
        if (global->player->sword->step < 3)
        {
            l2 += global->player->sword->width;
            r2 += global->player->sword->width;
            u2 += global->player->sword->height;
            d2 += global->player->sword->height;
        }
        else if (global->player->sword->step < 6)
        {
            u2 += global->player->sword->height;
            d2 += global->player->sword->height;
        }
        else
        {
            l2 -= global->player->sword->width;
            r2 -= global->player->sword->width;
            u2 += global->player->sword->height;
            d2 += global->player->sword->height;
        }
    }

    int coll_hor = (l1 > l2 && l1 < r2) || (r1 > l2 && r1 < r2);
    int coll_ver = (u1 > u2 && u1 < d2) || (d1 > u2 && d1 < d2);
    return coll_hor && coll_ver;
}

void update_player_sword(struct global *global)
{
    global->player->sword->pos = global->player->pos;
    global->player->sword->v_dir = global->player->v_dir;
    global->player->sword->cooldown--;

    // Go to next animation step
    if (global->player->sword->step == 8)
        global->player->sword->step = -1;
    else if (global->player->sword->step != -1)
        global->player->sword->step++;
    // Hit
    if (global->inputs.space && global->player->sword->cooldown <= 0
                             && global->player->armed)
    {
        global->player->sword->cooldown = 30;
        global->player->sword->step = 0;
    }
}

void update_player(struct global *global)
{
    // Move
    if (!global->inputs.right && global->inputs.left)
    {
        if (global->player->pos.x >= -10)
            global->player->pos.x -= global->player->speed;
        global->player->v_dir = LEFT;
        global->player->texture = global->entity_textures[WBL];
    }
    else if (global->inputs.right && !global->inputs.left)
    {
        if (global->player->pos.x + global->player->width <= SCREEN_WIDTH + 10)
            global->player->pos.x += global->player->speed;
        global->player->v_dir = RIGHT;
        global->player->texture = global->entity_textures[WBR];
    }

    if (!global->inputs.down && global->inputs.up)
    {
        if (global->player->pos.y + global->player->height / 4 >= -10)
            global->player->pos.y -= global->player->speed;
        global->player->v_dir = UP;
        global->player->texture = global->entity_textures[WBU];
    }
    else if (global->inputs.down && !global->inputs.up)
    {
        if (global->player->pos.y + global->player->height <= SCREEN_HEIGHT)
            global->player->pos.y += global->player->speed;
        global->player->v_dir = DOWN;
        global->player->texture = global->entity_textures[WBD];
    }
    // Manage sword
    update_player_sword(global);
    // Manage collisions
    if (!global->swords[0])
    {
        for (int i = 0; i < global->nb_monsters; i++)
        {
            if (!global->monsters[i])
                continue;
            if (entity_collision(global->player, global->monsters[i]))
                global->game_status = DEAD;
        }
    }
    if (!global->swords[0])
    {
        for (int i = 0; i < global->nb_fires; i++)
        {
            if (block_collision(global->player, global->fires[i]))
                global->game_status = DEAD;
        }
    }
    if (global->swords[0] && block_collision(global->player, global->swords[0]))
    {
        global->player->armed = 1;
        free(global->swords[0]);
        global->swords[0] = NULL;
    }
}

void update(struct global *global)
{
    for (int i = 0; i < global->nb_pentas; i++)
    {
        int r = rand();
        if (r < RAND_MAX / global->pentas[i]->proba)
        {
            SDL_Texture *texture = global->entity_textures[DML];
            monster_init(global, global->pentas[i]->pos, texture);
        }
    }

    if (global->inputs.escape)
        global->game_status = END;

    update_player(global);

    for (int i = 0; i < global->nb_monsters; i++)
    {
        if (!global->monsters[i])
            continue;
        update_monster(global, global->monsters[i], global->player->pos);
        // Manage collisions between monsters
        for (int j = 0; j < global->nb_monsters; j++)
        {
            if (!global->monsters[j])
                continue;
            if (i != j
                && entity_collision(global->monsters[i], global->monsters[j]))
                flee(global->monsters[i], global->monsters[j]->pos);
        }
        // Manage collisions with sword
        if (sword_collision(global->monsters[i], global))
        {
            global->kill_count--;
            free(global->monsters[i]);
            global->monsters[i] = NULL;
        }
        if(global->kill_count <= 0)
        {
          global->game_status = VICTORY;
        }
    }
}
