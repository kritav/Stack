#include <stdlib.h>
#include <sys/lcd.h>
#include <graphx.h>
#include <ti/getcsc.h>
#include <ti/screen.h>


void FillScreen(uint8_t color);

/* Main function, called first */
int main(void) {
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_FillScreen(0x15);
    gfx_BlitBuffer();
    while (!os_GetCSC());

    gfx_End();
    return 0;
}
