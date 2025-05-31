#ifndef BTN_UPDATE_H_INCLUDED
#define BTN_UPDATE_H_INCLUDED

#include "BTN_deps.h"

#include "BTN_Button.h"


/******************************************************************************
 * Hide a button.
 *
 * When hidden, a button is not showed.
 *
 * @param button The button to hide.
 * @param hide Set hide to true or false to hide or not the button.
 *****************************************************************************/
extern BTN_State BTN_Update(BTN_Button *button, SDL_Event *event, SDL_Rect relativeTo);

#endif // BTN_UPDATE_H_INCLUDED
