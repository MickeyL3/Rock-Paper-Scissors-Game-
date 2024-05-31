/**     @file graphics.c
 *      @authors Ngoc Le (Mickey), Luke Hyndman
 *      @date 17th October 2023
 *      @brief graphics module source file containing helper functions that display to the LEDMAT 
**/

#include "graphics.h"
#include "tinygl.h"
#include "navswitch.h"
#include "pacer.h"
/*
    Draws a given option char to the LEDMAT
*/
void draw_option(game_option_t option)
{
    tinygl_point_t point = {0,6};
    tinygl_draw_char(option_to_char(option),point);
}

/*
    Draws the score on the LEDMAT
*/
void draw_score(uint8_t scores)
{
    tinygl_point_t point = {0, 0};
    for (uint8_t i = 0; i < scores; i++) {
        point.x = i;
        tinygl_draw_point(point, 1);
    }
}

/*
    Scrolls given text across the screen until the navswitch is hit
*/
void scroll_text(char string[])
{
    tinygl_text(string);
    bool continue_scrolling = 1;

    while (continue_scrolling) {
        pacer_wait();
        navswitch_update();
        tinygl_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            continue_scrolling = 0;
            tinygl_clear();     // Clear the screen
        }
    }
}
