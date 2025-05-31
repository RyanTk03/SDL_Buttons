#include "../inc/_BTN_draw.h"


BTN_bool _BTN_draw(BTN_Button *button)
{
    if(SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h}, &button->rect) < 0)
        return BTN_FALSE;

    SDL_RenderPresent(button->renderer);
    return BTN_TRUE;
}
