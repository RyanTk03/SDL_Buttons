#ifndef BTN_COLOR_H_INCLUDED
#define BTN_COLOR_H_INCLUDED

#include <SDL2/SDL.h>


typedef enum BTN_ColorsKey
{
    BTN_COLORS_KEY_BACK = 0x1,
    BTN_COLORS_KEY_HBACK,
    BTN_COLORS_KEY_LABEL,
    BTN_COLORS_KEY_HLABEL,
    BTN_COLORS_KEY_BORDER,
    BTN_COLORS_KEY_HBORDER,
} BTN_ColorsKey;


typedef struct
{
    SDL_Color backColor;
    SDL_Color backColorOnHover;
    SDL_Color labelColor;
    SDL_Color labelColorOnHover;
    SDL_Color borderColor;
    SDL_Color borderColorOnHover;
} BTN_Colors;


#endif // BTN_COLOR_H_INCLUDED
