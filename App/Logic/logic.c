#include "logic.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <stm32f4xx_hal.h>

// TODO: Get rid of magic numbers

static uint8_t board[BOARD_HIGHT][BOARD_WIDTH];
static uint8_t screen_board[8][BOARD_WIDTH];

static uint8_t LOGIC_IsCellAlive(uint8_t ypos, uint8_t xpos);
static void LOGIC_ParseBoardToScreen(void);

void LOGIC_Init(void)
{
    uint32_t seed = HAL_GetTick();
    srand(seed);

    memset(board, 0, BOARD_SIZE);

    for (uint8_t y = 0; y < BOARD_HIGHT; y++)
    {
        for (uint8_t x = 0; x < BOARD_WIDTH; x++)
        {
            board[y][x] = (rand() % 100 < START_GAME_CELLS);
        }
    }
}

void LOGIC_BoardScan(void)
{
    uint8_t tmp_board[BOARD_HIGHT][BOARD_WIDTH];

    memcpy(tmp_board, board, BOARD_SIZE);

    for (uint32_t i = 0; i < BOARD_HIGHT; i++)
    {
        for (uint32_t j = 0; j < BOARD_WIDTH; j++)
        {
            tmp_board[i][j] = LOGIC_IsCellAlive(i, j);
        }
    }

    memcpy(board, tmp_board, BOARD_SIZE);
}

uint8_t *LOGIC_GetBoardScreen(void)
{
    LOGIC_ParseBoardToScreen();
    return (uint8_t *)screen_board;
}

//  ###
//  #*#
//  ###

static uint8_t LOGIC_IsCellAlive(uint8_t y, uint8_t x)
{
    uint8_t alive = 0;
    for (int8_t dy = -1; dy <= 1; dy++)
    {
        for (int8_t dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
                continue;

            uint8_t ny = y + dy;
            uint8_t nx = x + dx;

            alive += board[ny][nx];
        }
    }

    if (board[y][x])
        return (alive == 2 || alive == 3);

    return (alive == 3);
}

static void LOGIC_ParseBoardToScreen(void)
{
    uint8_t tmp[8][BOARD_WIDTH];

    memset(tmp, 0, sizeof(tmp));

    for (uint8_t y = 0; y < BOARD_HIGHT; y++)
    {

        uint8_t page = y >> 3;
        uint8_t bit = y & 7;

        for (uint8_t x = 0; x < BOARD_WIDTH; x++)
        {
            tmp[page][x] |= (board[y][x] << bit);
        }
    }

    memcpy(screen_board, tmp, sizeof(tmp));
}
