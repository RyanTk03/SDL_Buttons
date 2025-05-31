#ifndef BTN_ERROR_H_INCLUDED
#define BTN_ERROR_H_INCLUDED


typedef enum BTN_erroraction BTN_erroraction;
enum BTN_erroraction
{
    BTN_ERROR_GET, BTN_ERROR_SET
};

char* _BTN_error(BTN_erroraction action, char *e);

#endif // BTN_ERROR_H_INCLUDED
