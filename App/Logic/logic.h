#ifndef LOGIC_H_
#define LOGIC_H_

#include <stdint.h>

/* IMPORTANT: Set Board Size Here */
#define BOARD_WIDTH 128
#define BOARD_HIGHT 64

#define BOARD_SIZE (BOARD_WIDTH * BOARD_HIGHT)

#define CELL_DEAD 0
#define CELL_ALIVE 1

#define SURVIVE_NEIGHBORS 2
#define BIRTH_NEIGHBORS 3

#define START_GAME_CELLS    30

void LOGIC_Init(void);
void LOGIC_BoardScan(void);

uint8_t *LOGIC_GetBoardScreen(void);

#endif /* LOGIC_H_ */
