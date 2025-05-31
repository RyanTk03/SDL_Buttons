#ifndef BTN_H_INCLUDED
#define BTN_H_INCLUDED

#include "BTN_deps.h"

#include "BTN_Button.h"
#include "BTN_color.h"
#include "BTN_modify.h"
#include "BTN_update.h"
#include "BTN_utils.h"
#include "BTN_getter.h"

#define BTN_TRUE SDL_TRUE
#define BTN_FALSE SDL_FALSE

/**
 * @typedef SDL_bool BTN_bool
 * @brief Redefine the boolean from SDL_bool to BTN_bool.
 */
typedef SDL_bool BTN_bool;


/******************************************************************************
 * Create a button and initialize his components.
 *
 * @param drawingRenderer The render used to draw the button.
 * @param type The type of the button.
 * @param w The width of the button.
 * @param h The height of the button.
 * @param label The label of the button(text to draw in the button).
 * @param font The font used to draw render the label.
 *
 * @return The button created or NULL if an error occurred.
 *****************************************************************************/
extern BTN_Button* BTN_CreateButton(Uint8 type, int w, int h, const char *label, TTF_Font *font);


/******************************************************************************
 * Copy a button on a renderer.
 *
 * @param button The button to copy.
 * @param renderer The renderer where copy the button.
 * @param point The point where to copy the button.
 *
 * @return BTN_TRUE if all be done well, BTN_FALSE else.
 *****************************************************************************/
extern BTN_bool BTN_CopyButton(BTN_Button *button, SDL_Renderer *renderer, SDL_Point *dst);


/******************************************************************************
 * Free a button and it components.
 *
 * @param button The button to free.
 *****************************************************************************/
extern void BTN_FreeButton(BTN_Button *button);


/******************************************************************************
 * Hide a button.
 *
 * When hidden, a button is not showed.
 *
 * @param button The button to hide.
 * @param hide Set hide to true or false to hide or not the button.
 *****************************************************************************/
extern void BTN_HideButton(BTN_Button *button, BTN_bool hide);


/******************************************************************************
 * set an error string.
 *
 * @param error The string which represents the error message.
 *
 * @return BTN_TRUE if the error was set successfully or BTN_False else.
 *****************************************************************************/
BTN_bool BTN_SetError(char *error);


/******************************************************************************
 * Hide a button.
 *
 * When hidden, a button is not showed.
 *
 * @param button The button to hide.
 * @param hide Set hide to true or false to hide or not the button.
 *****************************************************************************/
char* BTN_GetError();

#endif // BTN_H_INCLUDED
