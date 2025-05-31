#ifndef BTN_BUTTON_H_INCLUDED
#define BTN_BUTTON_H_INCLUDED

#include "BTN_deps.h"

#include "BTN_Color.h"
#include "_BTN_const.h"


typedef enum
{
    BTN_BUTTON_SIMPLE, BTN_BUTTON_SCALETEXT, BTN_BUTTON_SCALEBOX
} BTN_EffectOnHover;

typedef enum
{
    BTN_HOVERED, BTN_CLICKED, BTN_UNDEFINED
} BTN_State;

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Rect rect;
    char label[BTN_LABEL_MAX_CHAR+1];
    BTN_Colors colors;
    TTF_Font *font;
    Uint8 type;
    SDL_bool hide;
} BTN_Button;


#endif // BTN_BUTTON_H_INCLUDED
