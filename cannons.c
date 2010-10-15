/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: cannons.c 21343 2010-10-13 04:18 $
 *
 * Copyright (C) 2010 Rory Sweeney, Caoilte Guiry
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#include "plugin.h"
#include "lib/helper.h"
#include "lib/playback_control.h"
#include "lib/fixedpoint.h"

#if (CONFIG_KEYPAD == IPOD_4G_PAD) || \
    (CONFIG_KEYPAD == IPOD_3G_PAD) || \
    (CONFIG_KEYPAD == IPOD_1G2G_PAD)

#define BTN_UP              BUTTON_MENU
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_PLAY

#elif (CONFIG_KEYPAD == IRIVER_H100_PAD) || \
      (CONFIG_KEYPAD == IRIVER_H300_PAD)

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == RECORDER_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_PLAY
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == ARCHOS_AV300_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == PLAYER_PAD

#define BTN_UP              BUTTON_MENU
#define BTN_FIRE            BUTTON_PLAY
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_STOP

#elif CONFIG_KEYPAD == ONDIO_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_MENU
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == IAUDIO_X5M5_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == SANSA_E200_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == SANSA_FUZE_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == SANSA_C200_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == SANSA_CLIP_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == SANSA_M200_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == IRIVER_H10_PAD

#define BTN_UP              BUTTON_LEFT
#define BTN_FIRE            BUTTON_RIGHT
#define BTN_LEFT            BUTTON_SCROLL_UP
#define BTN_RIGHT           BUTTON_SCROLL_DOWN
#define BTN_DOWN            BUTTON_FF

#elif CONFIG_KEYPAD == GIGABEAT_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == IRIVER_IFP7XX_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == GIGABEAT_S_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == MROBE100_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == IAUDIO_M3_PAD

#define BTN_UP              BUTTON_RC_MENU
#define BTN_FIRE            BUTTON_RC_PLAY
#define BTN_LEFT            BUTTON_RC_VOL_DOWN
#define BTN_RIGHT           BUTTON_RC_VOL_UP
#define BTN_DOWN            BUTTON_RC_FF

#elif CONFIG_KEYPAD == IAUDIO67_PAD

#define BTN_UP              BUTTON_MENU
#define BTN_FIRE            BUTTON_PLAY
#define BTN_LEFT            BUTTON_RIGHT
#define BTN_RIGHT           BUTTON_LEFT
#define BTN_DOWN            BUTTON_STOP      

#elif CONFIG_KEYPAD == CREATIVEZVM_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == PHILIPS_HDD1630_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

# elif CONFIG_KEYPAD == PHILIPS_SA9200_PAD

#define BTN_UP              BUTTON_MENU
#define BTN_FIRE            BUTTON_PLAY
#define BTN_LEFT            BUTTON_VOL_DOWN
#define BTN_RIGHT           BUTTON_VOL_UP
#define BTN_DOWN            BUTTON_NEXT    

#elif CONFIG_KEYPAD == SAMSUNG_YH_PAD

#define BTN_UP              BUTTON_UP
#define BTN_FIRE            BUTTON_PLAY
#define BTN_LEFT            BUTTON_LEFT
#define BTN_RIGHT           BUTTON_RIGHT
#define BTN_DOWN            BUTTON_DOWN

#elif CONFIG_KEYPAD == PBELL_VIBE500_PAD

#define BTN_UP              BUTTON_MENU
#define BTN_FIRE            BUTTON_OK
#define BTN_LEFT            BUTTON_PREV
#define BTN_RIGHT           BUTTON_NEXT
#define BTN_DOWN            BUTTON_CANCEL    

#elif CONFIG_KEYPAD == MPIO_HD200_PAD

#define BTN_UP              BUTTON_PREV
#define BTN_FIRE            BUTTON_SELECT
#define BTN_LEFT            BUTTON_VOL_DOWN
#define BTN_RIGHT           BUTTON_VOL_UP
#define BTN_DOWN            BUTTON_NEXT

#else
#error No keymap defined!
#endif

#ifdef HAVE_TOUCHSCREEN
#ifndef BTN_UP
#define BTN_UP              BUTTON_TOPMIDDLE
#endif
#ifndef BTN_FIRE
#define BTN_FIRE            BUTTON_CENTER
#endif
#ifndef BTN_LEFT
#define BTN_LEFT            BUTTON_MIDLEFT
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT           BUTTON_MIDRIGHT
#endif
#ifndef BTN_DOWN
#define BTN_DOWN            BUTTON_BOTTOMMIDDLE
#endif
#endif

#define HORIZON 4*LCD_HEIGHT/5

#define CANNON_RAD 30

#define POWER_BAR_WIDTH 100
#define POWER_BAR_HEIGHT 15

#define POWER_INCRIMENT 1.0
#define MAX_POWER 80.0

#define PLAYERS 2
#define PLAYER_ONE 0
#define PLAYER_TWO 1

#define CANNONBALL_SIZE 5

#define BLAST_RADIUS 30

#define MAX_SPEED 375.0

#if LCD_HEIGHT <= 64
#define CYCLES 20
#else
#define CYCLES 12
#endif

#define CYCLETIME ((CYCLES*HZ)/1000)

#define SET_ANGLE           0
#define SET_POWER           1
#define CANNONBALL_FLIGHT   2
#define EXPLODE             3

#define NUM_DOTS 10
#define SHRAPNEL_SIZE 10

bool button_left = 0;
bool button_right = 0;
bool button_up = 0;     //make private struct from these
bool button_down = 0;
bool button_fire = 0;

float gravity = 88.29;
int frames_per_second = 4;
bool quit_plugin = false;

float angle[PLAYERS] = {45, 45};
float power;

float cannonball_u;
float cannonball_v;
float cannonball_x;
float cannonball_y;

float explosion_radius;

int score[PLAYERS] = {0, 0};

float playerx[PLAYERS] = {(float) LCD_WIDTH*0.1, (float) LCD_WIDTH*0.9};

bool game_over = 0;

float dot_x[NUM_DOTS], dot_y[NUM_DOTS];
int dot_r[NUM_DOTS], dot_g[NUM_DOTS], dot_b[NUM_DOTS];

static const struct opt_items gravity_settings[4] = {
    { "Off",      -1 },
    { "Weak",     -1 },
    { "Moderate", -1 },
    { "Strong",   -1 },
};

int gravity_values[4] = {
    0.0, 5.0, 10.0, 15.0 };

static const struct opt_items fps_settings[9] = {
    { "20 FPS", -1 },
    { "25 FPS", -1 },
    { "30 FPS", -1 },
    { "35 FPS", -1 },
    { "40 FPS", -1 },
    { "45 FPS", -1 },
    { "50 FPS", -1 },
    { "55 FPS", -1 },
    { "60 FPS", -1 }
};

int fps_values[9] = {
    20, 25, 30, 35, 40, 45, 50, 55, 60 };

MENUITEM_STRINGLIST(menu, "Move Square Menu", NULL,
                    "Start", "Gravity",
                    "FPS (Speed)", "Playback Control", "Quit");

float dt = (float) CYCLETIME/HZ;

int max_score = 10;

/* startup/configuration menu. */
void cannons_menu(void)
{
    int selected = 0, result;
    bool menu_quit = false;

    rb->lcd_setfont(FONT_UI);
#ifdef HAVE_LCD_COLOR
    rb->lcd_set_background(LCD_BLACK);
    rb->lcd_set_foreground(LCD_WHITE);
#endif
    rb->lcd_clear_display();
    rb->lcd_update();

    rb->button_clear_queue();

    while(!menu_quit)
    {
        result = rb->do_menu(&menu, &selected, NULL, false);

        switch(result)
        {
            case 0:
                rb->lcd_setfont(FONT_SYSFIXED);

#ifdef HAVE_LCD_COLOR
                rb->lcd_set_background(LCD_BLACK);
                rb->lcd_set_foreground(LCD_WHITE);
#endif

                rb->lcd_clear_display();
                rb->lcd_update();

                menu_quit = true;
                break;

            case 1:
                rb->set_option("Gravity", &gravity, INT,
                                gravity_settings, 4, NULL);
                break;

            case 2:
                rb->set_option("FPS (Speed)", &frames_per_second, INT,
                                fps_settings, 9, NULL);
                break;

            case 3:
                playback_control(NULL);
                break;

            case 4:
                quit_plugin = true;
                menu_quit = true;
                break;
        }
    }
}

void win(int player)
{
    rb->splashf(HZ*1, "Player %d wins!", (int) player + 1);
    game_over = 1;
}

void check_score(void)
{
    if (cannonball_x < playerx[PLAYER_ONE] + BLAST_RADIUS && cannonball_x
        > playerx[PLAYER_ONE] - BLAST_RADIUS)
    {
        score[PLAYER_TWO]++;

        if (score[PLAYER_TWO] >= max_score)
        {
            win(PLAYER_TWO);
        }
    }
    if (cannonball_x < playerx[PLAYER_TWO] + BLAST_RADIUS && cannonball_x
        > playerx[PLAYER_TWO] - BLAST_RADIUS)
    {
        score[PLAYER_ONE]++;

        if (score[PLAYER_ONE] >= max_score)
        {
            win(PLAYER_ONE);
        }
    }   
}

void detect_keys(void)
{
    button_left = 0;
    button_right = 0;
    button_up = 0;
    button_down = 0;
    button_fire = 0;

    int button = rb->button_status();
    switch(button)
    {
        case BTN_UP:
            button_up = 1;
            break;

        case BTN_DOWN:
            button_down = 1;
            break;

        case BTN_LEFT:
            button_left = 1;
            break;

        case BTN_RIGHT:
           button_right = 1;
           break;

        case BTN_FIRE:
            button_fire = 1;
            break;
        }
}

void actions(int* mode, int player, bool* switch_player)
{
    if (button_up == 1)
    {
            cannons_menu();
            if (quit_plugin) return;
    }
    if (button_down == 1)
    {
        if (*mode == SET_ANGLE)
        {
            //change weapon
        }
        else if (*mode == CANNONBALL_FLIGHT)
        {
            //press down button to skip cannon flight
            int sign = (player == PLAYER_ONE) ?  1 : -1;
            cannonball_x = playerx[player] + sign * 2.0 * MAX_SPEED
                / MAX_POWER * power * (float) fp14_cos(angle[player])/16384.0
                * MAX_SPEED/MAX_POWER * power
                * (float) fp14_sin(angle[player]) / 16384.0 / gravity;

            *mode = EXPLODE;
            return;
        }
        //make sure explosion isn't instantly skipped when flight is.
        else if (*mode == EXPLODE)
        {
            check_score();
            *switch_player = 1;
            return;
        }
    }
    if (button_left == 1)
    {
        if (*mode == SET_ANGLE)
        {
            if (angle[player] < 90)
            {
                angle[player] += 2;
            }
        }
    }
    if (button_right == 1)
    {
        if (*mode == SET_ANGLE)
        {
            if (angle[player] > 0)
            {
                angle[player] -= 2;
            }
        }
    }
    if (button_fire == 1)
    {
        if (*mode == SET_ANGLE)
        {
            *mode = SET_POWER;
            return;
        }
        else if (*mode == SET_POWER)
        {
            if (power < MAX_POWER)
            {
                power += POWER_INCRIMENT;
            }
            else power = 0.0;
        }
    }
    else
    {
        if (*mode == SET_POWER)
        {
            *mode = CANNONBALL_FLIGHT;
            
            int sign = (player == PLAYER_ONE) ?  1 : -1;
            
            cannonball_u = (float) ((float) sign) * MAX_SPEED / MAX_POWER
                * power * (float) fp14_cos(angle[player]) / 16384.0;
            cannonball_v = (float) MAX_SPEED / MAX_POWER * power
                * (float) fp14_sin(angle[player]) / 16384.0;
            return;
        }
    }

    if (*mode == CANNONBALL_FLIGHT)
    {
        cannonball_x += cannonball_u*dt;
        cannonball_y -= cannonball_v*dt-0.5*gravity*dt*dt;
        cannonball_v -= gravity*dt;
        
        if (cannonball_y > HORIZON && cannonball_v < 0)
        {
            *mode = EXPLODE;

#if 0
            int dots = 0;
            while (dots < NUM_DOTS)
            {
                dot_x[dots] = (float) rb->rand();
                dot_x[dots] -= (float) dot_x[dots]/(2 * explosion_radius)
                    - explosion_radius;

                //rb->splashf(HZ*1, "dot_x %d", dot_x);
            
                dot_y[dots] = (float) rb->rand();
                dot_y[dots] -= (float) dot_y[dots]/explosion_radius;
            
                //rb->splashf(HZ*1, "dot_y %d", dot_y);
                        
                if (dot_x[dots]*dot_x[dots] + dot_y[dots]*dot_y[dots]
                    < explosion_radius*explosion_radius)
                {
                    dot_r[dots] = (int) rb->rand() % 255;
                    dot_g[dots] = (int) rb->rand() % 255;
                    dot_b[dots] = (int) rb->rand() % 255;
                
                    //rb->splashf(HZ*1, "rgb = (%d, %d, %d)", dot_red,
                        dot_green, dot_blue);

                    dots++;
                }
            }
#endif
            return;
        }
    }
    if (*mode == EXPLODE)
    {
        if (explosion_radius > BLAST_RADIUS)
        {
            check_score();
            *switch_player = 1;
            return;
        }

        //float old_explosion_radius = explosion_radius;
        explosion_radius += 0.5;
#if 0      
        int dots;
        for (dots = 0; dots < NUM_DOTS; dots++)
        {
            dot_x[dots] *= explosion_radius/old_explosion_radius;
            dot_y[dots] *= explosion_radius/old_explosion_radius;
        }
#endif
    }
}

void draw_scene(int mode)
{
    rb->lcd_clear_display();

#ifdef HAVE_LCD_COLOR
    //background
    rb->lcd_set_foreground(LCD_RGBPACK(100, 80, 40)); //yellowish
    rb->lcd_fillrect(0, (int) HORIZON, (int) LCD_WIDTH,
                     (int) LCD_HEIGHT - HORIZON);
    rb->lcd_set_foreground(LCD_RGBPACK(10, 20,120)); //blue
    rb->lcd_fillrect(0, 0, (int) LCD_WIDTH, (int) HORIZON);
#endif

    //draw cannons
#ifdef HAVE_LCD_COLOR
    rb->lcd_set_foreground(LCD_WHITE);
#endif

    int i;

    for (i = PLAYER_ONE; i<PLAYERS; i++)
    {
        int sign = (i == PLAYER_ONE) ?  1 : -1;
        
        rb->lcd_drawline((int) playerx[i], (int) HORIZON,
            (int) playerx[i] + sign*CANNON_RAD*fp14_cos(angle[i])/16384,
            (int) HORIZON - CANNON_RAD*fp14_sin(angle[i])/16384);
    }

/*
    //player two cannon
    rb->lcd_drawline((int) LCD_WIDTH*0.9, (int) HORIZON,
        (int) LCD_WIDTH*0.9 - CANNON_RAD*fp14_cos(angle[PLAYER_TWO])/16384,
        (int) HORIZON - CANNON_RAD*fp14_sin(angle[PLAYER_TWO])/16384);
*/

    if (mode == SET_POWER)
    {
#ifdef HAVE_LCD_COLOR
        rb->lcd_set_foreground(LCD_RGBPACK(0, 0, 255)); //blue
#endif
        rb->lcd_fillrect((int) (LCD_WIDTH - POWER_BAR_WIDTH)/2,
            (int) (LCD_HEIGHT + HORIZON - POWER_BAR_HEIGHT)/2,
            (int) POWER_BAR_WIDTH*power/MAX_POWER, (int) POWER_BAR_HEIGHT);

#ifdef HAVE_LCD_COLOR
        rb->lcd_set_foreground(LCD_RGBPACK(0, 0, 0)); //black
#endif
        rb->lcd_drawrect((int) (LCD_WIDTH - POWER_BAR_WIDTH)/2,
            (int) (LCD_HEIGHT + HORIZON - POWER_BAR_HEIGHT)/2,
            (int) POWER_BAR_WIDTH, (int) POWER_BAR_HEIGHT);
    }
    else if (mode == CANNONBALL_FLIGHT)
    {
        //draw cannonball
#ifdef HAVE_LCD_COLOR
        rb->lcd_set_foreground(LCD_RGBPACK(0, 0, 0)); //black
#endif

#if 1
        int x_val, y_val;
        
        for (x_val = -CANNONBALL_SIZE/2; x_val <= CANNONBALL_SIZE/2; x_val++)
        {
            //rb->lcd_putsxyf(1,LCD_HEIGHT-40, "x_val = %d", x_val);
                
            for (y_val = -(int) fp_sqrt(CANNONBALL_SIZE*CANNONBALL_SIZE/4
                - x_val*x_val, 16)/256;
                y_val <= (int) fp_sqrt(CANNONBALL_SIZE*CANNONBALL_SIZE/4
                - x_val*x_val, 16)/256; y_val++)
            {
                rb->lcd_drawpixel( cannonball_x + x_val,
                                   cannonball_y - y_val);
            }
        }
#endif
/*
        rb->lcd_fillrect((int) cannonball_x - CANNONBALL_SIZE/2,
        (int) cannonball_y - CANNONBALL_SIZE/2, CANNONBALL_SIZE,
        CANNONBALL_SIZE);
*/
    }
    else if (mode == EXPLODE)
    {
#if 0
        int dots = 0;

        for (dots = 0; dots < NUM_DOTS; dots++)
        {
#ifdef HAVE_LCD_COLOR
            rb->lcd_set_foreground(LCD_RGBPACK((int) dot_r[dots],
                (int) dot_g[dots], (int) dot_b[dots]));
#endif
            //rb->lcd_drawpixel( cannonball_x + dot_x[dots],
                HORIZON - dot_y[dots]);
            rb->lcd_fillrect((int) cannonball_x + dot_x[dots]
                - SHRAPNEL_SIZE/2, (int) HORIZON - dot_y[dots]
                - SHRAPNEL_SIZE/2,
                            SHRAPNEL_SIZE, SHRAPNEL_SIZE);
        }
#endif
    }

    //write score
    rb->lcd_putsxyf(LCD_WIDTH/2 - 15, 40, "%d - %d", score[PLAYER_ONE],
                    score[PLAYER_TWO]);

    rb->lcd_update();
}

/* plugin starts here */
enum plugin_status plugin_start(const void* parameter)
{
    (void)parameter;
    int mode;
    int player;
    int end;

    /* set everything up.. no BL timeout, no backdrop,
       white-text-on-black-background. */
    backlight_force_on(); /* backlight control in lib/helper.c */
#if LCD_DEPTH > 1
    rb->lcd_set_backdrop(NULL);
    rb->lcd_set_background(LCD_BLACK);
    rb->lcd_set_foreground(LCD_WHITE);
#endif

#ifdef HAVE_ADJUSTABLE_CPU_FREQ
    rb->cpu_boost(true);
#endif

    rb->srand(*rb->current_tick);

    bool switch_player = 0;

    while(!quit_plugin)
    {
        cannons_menu();
        game_over = 0;
        
        for (player=PLAYER_ONE; player < PLAYERS; player++)
        {
            score[player] = 0;
        }
        
        player = rb->rand() % PLAYERS;
        
        while(!quit_plugin && !game_over)
        {
            if (switch_player == 1)
            {
                player = (player == PLAYER_ONE) ?  PLAYER_TWO : PLAYER_ONE;
            }
            
            rb->splashf((int) HZ*0.5, "Player %d", (int) player + 1);
            
            power = 0.0;
    
            cannonball_x = playerx[player];
            cannonball_y = (float) HORIZON;

            explosion_radius = 3.0;
            
            mode = SET_ANGLE;
            switch_player = 0;
    
            while (switch_player == 0)
            {
                end = *rb->current_tick + CYCLETIME;

                detect_keys();

                actions(&mode, player, &switch_player);

                if (game_over || quit_plugin) break;

                draw_scene(mode);

                if (TIME_BEFORE(*rb->current_tick, end))
                    rb->sleep(end - *rb->current_tick);
                else
                    rb->yield();
            }
        }
    }

    /* Turn on backlight timeout (revert to settings) */
    backlight_use_settings(); /* backlight control in lib/helper.c */

#ifdef HAVE_ADJUSTABLE_CPU_FREQ
    rb->cpu_boost(false);
#endif

    return PLUGIN_OK;
}
