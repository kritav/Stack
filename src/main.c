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
int x_pos;
int width;
int game_over;

void draw_block (int x, int y, int width, uint8_t color) {
    gfx_SetColor(color);
    gfx_FillRectangle(x, y, width, 15);
}

/* Main function, called first */
int main(void) {
    gfx_Begin();
    gfx_SetDrawBuffer();
    //gfx_FillScreen(0x15); // light blue

    layers[0].x = 110;
    layers[0].width = 100;
    layers[0].color = 0xe0;
    num_layers = 1;

    x_pos = 110;
    width = 100;
    direction = 1;
    game_over = 0;

    while (1) {
        kb_Scan();
        if (kb_Data[6] & kb_Clear) break;
        x_pos += direction * 5;
        if ((x_pos <= 0) || (x_pos + width >= SCREEN_WIDTH)) {
            direction = -direction;
        }

        gfx_FillScreen(0x15);

        int y_pos = 200;
        for (int i = 0; i < num_layers; i++) {
            draw_block(layers[i].x, y_pos - (i * 16), layers[i].width, layers[i].color);
        }
        draw_block(x_pos, y_pos - (num_layers * 16), width, 0xe0); 
        gfx_BlitBuffer();
        delay(30);
    }

    gfx_End();
    return 0;
}
