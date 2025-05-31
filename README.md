# SDL_Button

The SDL_Button library is a library for creating buttons with SDL.

## Installation

1. Clone the repository:
```bash
git clone https://github.com/RyanTk03/SDL_Buttons.git
```

3. Include the header files in your project:
``` c
#include "../inc/BTN.h"
```
Compile your project with the SDL_Button library source files:

```bash
gcc your_files.c BTN.c -o main -lSDL2 -lSDL2_ttf -lSDL2_image
```
## Usage
1. Creating a button
```c
BTN_Button* button = BTN_CreateButton(type, w, h, label, font);
```
type: the type of button (to be defined according to your needs)
w: the width of the button
h: the height of the button
label: the text of the button
font: the font to use for the button text

2. Copying the button to the renderer
```c
BTN_bool success = BTN_CopyButton(button, renderer, &dst);
```
renderer: the renderer to copy the button to
dst: the coordinates (x, y) to copy the button to on the renderer

3. Modifying the button
3.1. Modifying the button text
```c
char *newLabel = "New text";
BTN_Setlabel(button, newLabel);
```
3.2. Modifying the button font
```c
TTF_Font *newFont = TTF_OpenFont("path/to/font.ttf", size);
BTN_SetFont(button, newFont);
```
Modifying the button colors
```c
BTN_Colors colors;
colors.backColor = (SDL_Color){255, 255, 255, 255};
colors.backColorOnHover = (SDL_Color){0, 0, 255, 128};
colors.labelColor = (SDL_Color){0, 0, 0, 255};
colors.labelColorOnHover = (SDL_Color){255, 255, 255, 255};
colors.borderColor = (SDL_Color){0, 0, 255, 128};
colors.borderColorOnHover = (SDL_Color){255, 0, 0, 128};

short colorKey = BTN_COLORS_KEY_BACK | BTN_COLORS_KEY_HBACK | BTN_COLORS_KEY_LABEL |
BTN_COLORS_KEY_HLABEL | BTN_COLORS_KEY_BORDER | BTN_COLORS_KEY_HBORDER;

SDL_bool modified = BTN_setColors(button, &colors, colorKey);
```
## License
This library is distributed under the MIT license. See the LICENSE file for more information.
