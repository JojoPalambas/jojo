#include "game.h"

void get_inputs(struct global *global)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
    if (event.type == SDL_QUIT)
      global->game_status = END;
    else if (event.type == SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          global->inputs.escape = 1;
          break;
        case SDLK_LEFT:
          global->inputs.left = 1;
          break;
        case SDLK_RIGHT:
          global->inputs.right = 1;
          break;
        case SDLK_UP:
          global->inputs.up = 1;
          break;
        case SDLK_DOWN:
          global->inputs.down = 1;
          break;
        case SDLK_SPACE:
          global->inputs.space = 1;
          break;
      }
    }
    else if (event.type == SDL_KEYUP)
    {
      switch(event.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          global->inputs.escape = 0;
          break;
        case SDLK_LEFT:
          global->inputs.left = 0;
          break;
        case SDLK_RIGHT:
          global->inputs.right = 0;
          break;
        case SDLK_UP:
          global->inputs.up = 0;
          break;
        case SDLK_DOWN:
          global->inputs.down = 0;
          break;
        case SDLK_SPACE:
          global->inputs.space = 0;
          break;
      }
    }
}

void get_gameover_input(struct global *global)
{

  SDL_Event click;
  SDL_WaitEvent(&click);
  if (click.type == SDL_MOUSEBUTTONUP)
  {
    if (click.button.x > SCREEN_WIDTH / 2 - 120
        && click.button.x <= SCREEN_WIDTH / 2 - 120 + 106
        && click.button.y > SCREEN_HEIGHT / 2 + 30
        && click.button.y <= SCREEN_HEIGHT / 2 + 30 + 41)
      global->game_status = RUNNING;
    else if (click.button.x > SCREEN_WIDTH / 2 - 120 + 200
        && click.button.x <= SCREEN_WIDTH / 2 - 120 + 200 + 303
        && click.button.y > SCREEN_HEIGHT / 2 + 30
        && click.button.y <= SCREEN_HEIGHT / 2 + 30 + 37)
      global->game_status = MENU;
    else if (click.button.x > SCREEN_WIDTH / 2 - 100
        && click.button.x <= SCREEN_WIDTH / 2 - 100 + 380
        && click.button.y > SCREEN_HEIGHT / 2 + 90
        && click.button.y <= SCREEN_HEIGHT / 2 + 90 + 35)
      global->game_status = END;
  }
}

void get_menu_input(struct global *global)
{
  SDL_Event click;
  SDL_WaitEvent(&click);
  if (click.type == SDL_MOUSEBUTTONUP)
  {
    if (click.button.x > SCREEN_WIDTH / 2 - 120
        && click.button.x <= SCREEN_WIDTH / 2 - 120 + 211
        && click.button.y > SCREEN_HEIGHT / 2
        && click.button.y <= SCREEN_HEIGHT / 2 + 39)
    {
      global->map = 0;
      global->game_status = RUNNING;
    }
    if (click.button.x > SCREEN_WIDTH / 2 - 100
        && click.button.x <= SCREEN_WIDTH / 2 - 100 + 177
        && click.button.y > SCREEN_HEIGHT / 2 + 90
        && click.button.y <= SCREEN_HEIGHT / 2 + 90 + 33)
    {
      global->game_status = END;
      return;
    }
    if (click.button.x > SCREEN_WIDTH / 2 - 90
        && click.button.x <= SCREEN_WIDTH / 2 - 90 + 39
        && click.button.y > SCREEN_HEIGHT / 2 + 50
        && click.button.y <= SCREEN_HEIGHT / 2 + 50 + 33)
    {
      global->map = 0;
      global->game_status = RUNNING;
    }
    if (click.button.x > SCREEN_WIDTH / 2 - 90 + 39
        && click.button.x <= SCREEN_WIDTH / 2 - 90 + 78
        && click.button.y > SCREEN_HEIGHT / 2 + 50
        && click.button.y <= SCREEN_HEIGHT / 2 + 50 + 33)
    {
      global->map = 1;
      global->game_status = RUNNING;
    }
    if (click.button.x > SCREEN_WIDTH / 2 - 90 + 78
        && click.button.x <= SCREEN_WIDTH / 2 - 90 + 117
        && click.button.y > SCREEN_HEIGHT / 2 + 50
        && click.button.y <= SCREEN_HEIGHT / 2 + 50 + 33)
    {
      global->map = 2;
      global->game_status = RUNNING;
    }
    if (click.button.x > SCREEN_WIDTH / 2 - 90 + 117
        && click.button.x <= SCREEN_WIDTH / 2 - 90 + 156
        && click.button.y > SCREEN_HEIGHT / 2 + 50
        && click.button.y <= SCREEN_HEIGHT / 2 + 50 + 33)
    {
      global->map = 3;
      global->game_status = RUNNING;
    }
  }
}
