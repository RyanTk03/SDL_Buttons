#include "../inc/BTN_update.h"

BTN_State BTN_Update(BTN_Button *button, SDL_Event *event, SDL_Rect relativeTo)
{
    if(button == NULL || button->hide == SDL_TRUE)
        return BTN_UNDEFINED;

    SDL_Point cursor = {event->button.x - relativeTo.x, event->button.y - relativeTo.y};
    BTN_State status = BTN_UNDEFINED;

    if(event->type != SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&cursor, &button->rect))
    {
        status = BTN_HOVERED;

        if(button->type == BTN_BUTTON_SCALEBOX)
            SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){button->rect.w-1, 0, button->rect.w, button->rect.h},
                           &(SDL_Rect){button->rect.x - 1, button->rect.y - 1, button->rect.w + 2, button->rect.h + 2});
        else
            SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){button->rect.w, 0, button->rect.w, button->rect.h},
                           &button->rect);
    }
    else if(event->type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&cursor, &button->rect))
    {
        status = BTN_CLICKED;
        SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h}, &button->rect);
    }
    else
    {
        SDL_RenderCopy(button->renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h},
                           &button->rect);
    }
    return status;
}
