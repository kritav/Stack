#include <keypadc.h>
#include <stdlib.h>
#include <sys/lcd.h>
#include <sys/timers.h>
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
uint8_t colors[] = {0x10, 0x30, 0x50, 0x70, 0x90, 0xB0, 0xD0, 0xF0, 0xD0, 0xB0, 0x90, 0x70, 0x50, 0x30};
int num_layers;
int direction;
int x_pos;
int layer_width;
int game_over;

void draw_block (int x, int y, int width, uint8_t color) {
    gfx_SetColor(color);
    gfx_FillRectangle(x, y, width, 15);
}

uint8_t get_color(int index) {
    if ((index % 14) < 8) {
        return colors[index % 14];
    }
    else {
        return colors[14 - (index % 14)];
    }
}

int main(void) {
    gfx_Begin();
    gfx_SetDrawBuffer();

    layers[0].x = 110;
    layers[0].width = 100;
    layers[0].color = colors[0];
    num_layers = 1;

    x_pos = 110;
    layer_width = 100;
    direction = 1;
    game_over = 0;

    while (1) {
        kb_Scan();
        if (kb_Data[1] & kb_2nd) {
            Layer *prev = &layers[num_layers - 1];

            int left_overlap;
            if (x_pos > prev->x) {
                left_overlap = x_pos;
            }
            else {
                left_overlap = prev->x;
            }

            int right_overlap;
            if (x_pos + layer_width < prev->x + prev->width) {
                right_overlap = x_pos + layer_width;
            }
            else {
                right_overlap = prev->x + prev->width;
            }

            int new_width = right_overlap - left_overlap;
            if (new_width <= 0) {
                game_over = 1;
                break;
            }
            layers[num_layers].x = left_overlap;
            layers[num_layers].width = new_width;
            layers[num_layers].color = get_color(num_layers);
            num_layers++;

            x_pos = left_overlap;
            layer_width = new_width; 
            direction = -direction;

            while (kb_Data[1] & kb_2nd) kb_Scan();
        }

        if (kb_Data[6] & kb_Clear) break;
        x_pos += direction * 5;
        if ((x_pos <= 0) || (x_pos + layer_width >= SCREEN_WIDTH)) {
            direction = -direction;
        }

        gfx_FillScreen(0x15);

        int y_pos = 200;
        for (int i = 0; i < num_layers; i++) {
            draw_block(layers[i].x, y_pos - (i * 16), layers[i].width, layers[i].color);
        }
        draw_block(x_pos, y_pos - (num_layers * 16), layer_width, get_color(num_layers)); 
        gfx_BlitBuffer();
        delay(30);
    }

    gfx_End();
    return 0;
}
