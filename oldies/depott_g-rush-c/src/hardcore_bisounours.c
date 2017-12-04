#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "game.h"

void run_game(struct global *global);
void game_over(struct global *global);
static void restart(struct global *global, enum game_status gs);
static inline void menu_loop(struct global *global);

void set_background(struct global *global, char *path)
{
  global->background = texture_load(global, path);
}

static void victory(struct global *global)
{
  set_background(global, "./tests/Images/victory.png");
  while(global->game_status == VICTORY)
  {
    SDL_Event event;
    texture_draw(global, global->background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(global->renderer);
    SDL_WaitEvent(&event);
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_SPACE)
      {
        restart(global, MENU);
        return;
      }
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        global->game_status = END;
        return;
      }
    }
    time(global);
  }
}


static inline void menu_loop(struct global *global)
{
  set_background(global, "./tests/Images/title2.0.jpeg");

  global->game_status = MENU;
  SDL_Texture *button_play = texture_load(global, "tests/Images/play.png");
  SDL_Texture *button_quit = texture_load(global, "tests/Images/quit.png");
  SDL_Texture *level = texture_load(global, "tests/Images/level.png");
  while (global->game_status == MENU)
  {
    texture_draw(global, global->background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    texture_draw(global, button_play, SCREEN_WIDTH / 2 - 120,
        SCREEN_HEIGHT / 2, 211, 39);
    texture_draw(global, button_quit, SCREEN_WIDTH / 2 - 100,
        SCREEN_HEIGHT / 2 + 90, 177, 33);
    texture_draw(global, level, SCREEN_WIDTH / 2 - 90,
        SCREEN_HEIGHT / 2 + 50, 156, 33);
    SDL_RenderPresent(global->renderer);
    SDL_Delay(1);
    get_menu_input(global);
    time(global);
  }
  map_parse(global);
  if (global->game_status == RUNNING)
  {
    run_game(global);
  }
}

void run_game(struct global *global)
{
  global->player = player_init(global->start, global->entity_textures[WBR]);

  global->background = global->block_textures[WBACK];

  while (global->game_status == RUNNING)
  {
    get_inputs(global);

    update(global);
    display_game(global);
    time(global);
  }
  if (global->game_status == DEAD)
  {
    game_over(global);
    return;
  }
  if (global->game_status == VICTORY)
  {
    victory(global);
    return;
  }
  game_clean(global);

}

static void restart(struct global *global, enum game_status gs)
{
  int tmp = global->map;
  game_clean(global);
  global = game_init();
  global->map = tmp;
  if (gs == RUNNING)
  {
    map_parse(global);
    run_game(global);
  }
  if (gs == MENU)
    menu_loop(global);
}

void game_over(struct global *global)
{
  set_background(global, "./tests/Images/GameOver.png");

  SDL_Texture *button_play = texture_load(global, "tests/Images/reckless.png");
  SDL_Texture *button_quit = texture_load(global, "tests/Images/coward.png");
  SDL_Texture *weak = texture_load(global, "tests/Images/weak.png");
  while (global->game_status == DEAD)
  {
    texture_draw(global, global->background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    texture_draw(global, button_play, SCREEN_WIDTH / 2 - 120,
        SCREEN_HEIGHT / 2 + 30, 106, 41);
    texture_draw(global, weak, SCREEN_WIDTH / 2 - 120 + 200,
        SCREEN_HEIGHT / 2 + 30, 303, 37);
    texture_draw(global, button_quit, SCREEN_WIDTH / 2 - 100,
        SCREEN_HEIGHT / 2 + 90, 380, 35);
    SDL_RenderPresent(global->renderer);
    SDL_Delay(1);
    get_gameover_input(global);
    if (global->game_status != DEAD && global->game_status != END)
    {
      restart(global, global->game_status);
      return;
    }
    time(global);
  }
}

int main(void)
{
  struct global *global = game_init();
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
  {
    printf("%s", Mix_GetError());
  }
  Mix_Music *music;
  music = Mix_LoadMUS("tests/music.mp3");
  Mix_PlayMusic(music, -1);
  menu_loop(global);
  return 0;
}
