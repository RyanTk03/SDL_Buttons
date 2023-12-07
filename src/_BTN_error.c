#include <stddef.h>

#include "../inc/_BTN_error.h"


char* _BTN_error(BTN_erroraction action, char *e)
{
    static char error[255];

    if(action == BTN_ERROR_SET && e != NULL)
        return SDL_strlcpy(error, e, 254) < SDL_strlen(e) ? NULL : error;

    return error;
}
