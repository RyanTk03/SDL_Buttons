#ifndef BTN_GETTER_H_INCLUDED
#define BTN_GETTER_H_INCLUDED

#include <SDL2/SDL.h>

#include "BTN_Button.h"

SDL_Rect BTN_GetBoundingBox(BTN_Button *button);

#endif // BTN_GETTER_H_INCLUDED
