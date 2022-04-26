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

//Fix the warnings probably
static const int total_walls = 1;
static const int fixed_t = 1000; //All integers are scaled to this value,

/* Put function p

rototypes here or in a header (.h) file */

struct player1 {
    int x;
    int y;
    int z;

    int rotX; //Set to unsigned probably
} player;

struct cache {
    int16_t cos[360];
} cache;



struct wall_loaded {
    int vert_x0[total_walls];
    int vert_y0[total_walls];

    int vert_x1[total_walls];
    int vert_y1[total_walls];

    int line_layer1_z[total_walls];
    int line_layer2_z[total_walls];
    int line_layer3_z[total_walls];
};

struct map_loaded {
    struct wall_loaded wall;
} map;
void RenderWalls();
void init_cache();
void init_map();
void Debug_render();
void render();

/* This is the entry point of your program. */
/* argc and argv can be there if you need to use arguments, see the toolchain example. */
int main() {

    boot_Set48MHzMode();

    uint8_t backc = 0x19;
    init_map();
    os_ClrHomeFull();
    gfx_Begin(gfx_8bpp);
    gfx_SetDrawBuffer(); //Use this in a loop or something

    gfx_SetTextFGColor(0xFE);

    while (true){ // Refer to https://ce-programming.github.io/toolchain/libraries/keypadc.html for key register info
        gfx_FillScreen(backc);
        Debug_render();
        gfx_SwapDraw();

        if(kb_On){
            break; //Stops program
        }

        if(kb_Data[1] & kb_2nd) {
            player.rotX+=15;
        }
        if(kb_Data[1] & kb_Mode) {
            player.rotX-=15;
        }

        //Make the moving relative to the players rotation

        if(kb_Data[7] & kb_Down){
            player.y-=50;
        }
        if(kb_Data[7] & kb_Up){
            player.y+=50;
        }
        if(kb_Data[7] & kb_Right){
            player.x+=50;
        }
        if(kb_Data[7] & kb_Left){
            player.x-=50;
        }
    }

        //A for loop that copies temp_life to lifez
    gfx_End();
    return 0;
}

void init_map(){
    uint16_t i;
    for(i = 0; i < total_walls; i++){
        map.wall.vert_x0[i] = rand()%320;
        map.wall.vert_x1[i] = rand()%320;

        map.wall.vert_y0[i] = rand()%240;
        map.wall.vert_y1[i] = rand()%240;

        map.wall.line_layer1_z[i] = 5;
        map.wall.line_layer1_z[i] = 10;
        map.wall.line_layer1_z[i] = 15;
    }
}

void init_cache() {
    for(float i = 0; i < 360; i++) {
        cache.cos[(int)i] = (int16_t)((cos(i*0.0174533)) * fixed_t);
    }
}

void render(){
    //The primary renderng technique
    int distance0;
    int distance1;

    int temp_x_val;
    int temp_y_val;

    int x0_projection;
    int x1_projection;

    for(int i = 0; i < total_walls; i++){
        temp_x_val = (map.wall.vert_x0[i] - player.x);
        temp_y_val = (map.wall.vert_y0[i] - player.y);
        distance0 = sqrt((temp_x_val*temp_x_val) + (temp_y_val * temp_y_val)); //Square roots may be a bit slow

        //x0_projection goes here


        temp_x_val = (map.wall.vert_x1[i] - player.x);
        temp_y_val = (map.wall.vert_y1[i] - player.y);
        distance1 = sqrt((temp_x_val*temp_x_val) + (temp_y_val * temp_y_val)); //Square roots may be a bit slow

        //x1_projection goes here

        //The y of the raycaster is relative to the camera (player.z - wall.z0), take the inverse of that
        //Possibly the tangent of the direction to the point - player.rotX
    }
}

void Debug_render(){
    gfx_SetColor(255);
    for(uint16_t i = 0; i < total_walls; i++){
        gfx_Line_NoClip(map.wall.vert_x0[i],map.wall.vert_y0[i],map.wall.vert_x1[i],map.wall.vert_y1[i]);
    }
    //gfx_FillCircle(player.x, player.y, 20);
}

void RenderWalls() {
    gfx_FillScreen(0x00);
}


//Note, put this function into its own file, but IDK how to
void load_wad_file() {
    
}
