#include <keypadc.h>
#include <stdlib.h>
#include <sys/lcd.h>
#include <graphx.h>
#include <ti/getcsc.h>
#include <ti/screen.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAX_HEIGHT 30

typedef struct {
    int x;
    int width;
    uint8_t color;
} Layer;

Layer layers[MAX_HEIGHT];
int num_layers;
int direction;
int game_over;

void draw_block (int x, int y, int width, uint8_t color) {
    gfx_SetColor(color);
    gfx_FillRectangle(x, y, width, 15);
}

/* Main function, called first */
int main(void) {
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_FillScreen(0x15); // light blue
    gfx_SetColor(0xe0); // red
    gfx_FillRectangle(110, 200, 100, 15);

    gfx_BlitBuffer();




    while (!os_GetCSC());

    gfx_End();
    return 0;
}
