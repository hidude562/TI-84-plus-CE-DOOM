////////////////////////////////////////
// { PROGRAM NAME } { VERSION }
// Author:
// License:
// Description:
////////////////////////////////////////

/*
* The comments in this file are here to guide you initially. Note that you shouldn't actually
* write comments that are pointless or obvious in your own code, write useful ones instead!
* See this for more details: https://ce-programming.github.io/toolchain/static/coding-guidelines.html
*
* Have fun!
*/

/* You probably want to keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Here are some standard headers. Take a look at the toolchain for more. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
/* Put function prototypes here or in a header (.h) file */

struct player1 {
    int x;
    int y;
    int z;

    int rotX; //Set to unsigned probably
} player;

struct wall_loaded {
    int vert_x0[10];
    int vert_y0[10];

    int vert_x1[10];
    int vert_y1[10];

    int line_layer1_z[10];
    int line_layer2_z[10];
    int line_layer3_z[10];
};

struct map_loaded {
    struct wall_loaded wall;
} map;
void RenderWalls();
void init_map();
void Debug_render();

/* This is the entry point of your program. */
/* argc and argv can be there if you need to use arguments, see the toolchain example. */
int main() {

    boot_Set48MHzMode();

    uint8_t backc = 0x19;
    init_map();
    os_ClrHomeFull();
    gfx_Begin(gfx_8bpp);
    //gfx_SetDrawBuffer(); Use this in a loop or something

    gfx_SetTextFGColor(0xFE);

    while (true){ // Refer to https://ce-programming.github.io/toolchain/libraries/keypadc.html for key register info
        gfx_FillScreen(backc);
        Debug_render();

        if(kb_On){
            break; //Stops program
        }
    }

        //A for loop that copies temp_life to lifez
    gfx_End();
    return 0;
}

void init_map(){
    uint16_t i;
    for(i = 0; i < 10; i++){
        map.wall.vert_x0[i] = rand()%320;
        map.wall.vert_x1[i] = rand()%320;

        map.wall.vert_y0[i] = rand()%240;
        map.wall.vert_y1[i] = rand()%240;

        map.wall.line_layer1_z[i] = 5;
        map.wall.line_layer1_z[i] = 10;
        map.wall.line_layer1_z[i] = 15;
    }
}

void Debug_render(){
    uint16_t i; //Reinitializing i is probably slow
    gfx_SetColor(255);
    for(i = 0; i < 10; i++){
        gfx_Line_NoClip(map.wall.vert_x0[i],map.wall.vert_y0[i],map.wall.vert_x1[i],map.wall.vert_y1[i]);
    }
    //gfx_FillCircle(player.x, player.y, 20);
}

void RenderWalls() {
    gfx_FillScreen(0x00);
}
