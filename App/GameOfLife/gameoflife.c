#include "gameoflife.h"

#include "logic.h"
#include "oled.h"

#include <stdint.h>

static game_of_life_sm state_of_game = MAIN_SCREEN;

static void MainScreen(void);
static void StartGame(void);
static void Update(void);

void GOL_WriteState(game_of_life_sm state)
{
    state_of_game = state;
}

game_of_life_sm GOL_GetState(void)
{
    return state_of_game;
}

void GOL_Main(void)
{
    static game_of_life_sm prev_state = GAME_LOOP;

    switch (state_of_game)
    {
        case MAIN_SCREEN:
            if (prev_state != MAIN_SCREEN) DISPLAY_Clear();
            MainScreen();
            break;
        
        case GAME_INIT:
            if (prev_state != GAME_INIT) DISPLAY_Clear();
            StartGame();
            state_of_game = GAME_LOOP;
            break;

        case GAME_LOOP:
            if (prev_state != GAME_LOOP) DISPLAY_Clear();
            Update();
            break;
    }

    prev_state = state_of_game;
}

static void MainScreen(void)
{
    DISPLAY_TitleScreen();
}

static void StartGame(void)
{
    LOGIC_Init();
    DISPLAY_Clear();
    DISPLAY_Write((uint8_t *)LOGIC_GetBoardScreen());
}

static void Update(void)
{
    LOGIC_BoardScan();

    DISPLAY_Write(LOGIC_GetBoardScreen());
    DISPLAY_Update();
}