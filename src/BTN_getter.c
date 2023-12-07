#include "../inc/BTN_getter.h"

SDL_Rect BTN_GetBoundingBox(BTN_Button *button)
{
    return button->rect;
}
