#ifndef GAME_OF_LIFE_H_
#define GAME_OF_LIFE_H_

#include "logic.h"
#include "oled.h"

#include <stdint.h>

typedef enum
{
    MAIN_SCREEN,
    GAME_INIT,
    GAME_LOOP
} game_of_life_sm;

void GOL_WriteState(game_of_life_sm state);
game_of_life_sm GOL_GetState(void);
void GOL_Main(void);

#endif /* GAME_OF_LIFE_H_ */