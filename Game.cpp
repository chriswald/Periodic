#include "Allegro Header.h"
#include "Class Worm.h"

void game();
void scoreing();

void scoreing()
{
    if (score>0)
        score--;
}

void game()
{
    //Save the screen so we can redraw it later
    BITMAP *save_screen=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(save_screen);
    draw_sprite(save_screen,screen,0,0);

    game_end=false;
    srand(time(NULL));

    scare_mouse();
    score=0;
    game_rest=10;
    level_up=false;

    fill_screen(BLACK);
    Worm worm;
    worm.ch_dir(Right);
    worm.draw_start();
    worm.draw_food();
    install_int(scoreing,3000);

    while (!done)
    {
        if (keypressed())
        {
            int  newkey   =readkey();
            int  scancode =newkey>>8;

            switch(scancode)
            {
                case KEY_UP:
                    worm.ch_dir(Up);
                    break;
                case KEY_DOWN:
                    worm.ch_dir(Down);
                    break;
                case KEY_RIGHT:
                    worm.ch_dir(Right);
                    break;
                case KEY_LEFT:
                    worm.ch_dir(Left);
                    break;
                case KEY_ESC:
                    game_end=true;
                    while(keypressed()){rest(1);}
                    break;
                default:
                    break;
            }
        }

        worm.update();
        worm.draw_worm();
        worm.collide();
        textprintf_ex(screen,font,10,0,ORANGE,BLACK,"Score: %i ",score);
        run_timer_precise(screen,100,0,ORANGE,BLACK);

        if (game_rest==5 && level_up==false)
        {
            level_up=true;
            game_rest=10;
        }

        if (game_end==true)
            break;

        rest(5);
    }


    draw_sprite(screen,save_screen,0,0);
    destroy_bitmap(save_screen);
    unscare_mouse();
}
