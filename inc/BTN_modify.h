#ifndef BTN_MODIFY_H_INCLUDED
#define BTN_MODIFY_H_INCLUDED

#include "BTN_deps.h"

#include "BTN_Button.h"


char *BTN_Setlabel(BTN_Button *button, char *label);
TTF_Font *BTN_SetFont(BTN_Button *button, TTF_Font *font);
SDL_bool BTN_setColors(BTN_Button *button, BTN_Colors *colors, short colorKey);
void BTN_SetPosition(BTN_Button *button, Uint32 x, Uint32 y);

#endif // BTN_MODIFY_H_INCLUDED
