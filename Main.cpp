/*

     _________     __      __    _________    __________    _______
   /\    ___  \  /\  \   /\  \ /\   ____  \ /\____   ___\ /\   ____\
   \ \  \__/\__\ \ \  \__\_\  \\ \  \_/_\  \\/___/\  \__/ \ \  \___/_
    \ \  \ \/__/  \ \   _____  \\ \   ___  <     \ \  \    \ \_____  \
     \ \  \    _ _ \ \  \___/\  \\ \  \ /\  \     \ \  \    \/____/\  \
      \ \  \_/_\  \ \ \  \  \ \  \\ \  \\ \  \    _\_\  \____   __\_\  \
       \ \_________\ \ \__\  \ \__\\ \__\\ \__\  /\__________\ /\_______\
        \/_________/  \/__/   \/__/ \/__/ \/__/  \/__________/ \/_______/
                __        __     _________     __          _______
              /\  \     /\  \  /\    ___  \  /\  \       /\    __ `\
              \ \  \    \ \  \ \ \  \__/\  \ \ \  \      \ \  \_/\  \
               \ \  \    \ \  \ \ \  \_\_\  \ \ \  \      \ \  \\ \  \
                \ \  \   _\ \  \ \ \    ___  \ \ \  \      \ \  \\ \  \
                 \ \  \_\  \_\  \ \ \  \__/\  \ \ \  \_____ \ \  \\_\  \
                  \ \____________\ \ \__\ \ \__\ \ \_______\ \ \_______/
                   \/____________/  \/__/  \/__/  \/_______/  \/______/

           ->Developed By Chris Wald
           ->Main.cpp

*/
#define USING_WINDOWS  //Needed so that the windows functions load
#include <Allegro Header.h>
#include <semaphore.h>
#include "Globals.h"


void music_timer();
void ticker();
void tick_tock();
//BITMAP *draw_pictures(int num);

#include "Element.cpp"
#include "Game.cpp"
#include "Over Element.cpp"
#include "Search.cpp"
#include "Thread.cpp"
#include "Timers.cpp"

int main()
{
    //Start the program in Windowed mode
    start_program(WINDOW,880,600,"Periodic");
    sem_init(&semaphore,0,1);

    //set up the elements
    set_up_elements();

    //MUSIC STUFF
    bool can_play[NUM_ELEMENTS];
    int  on_element=-1;

    for (int i=0; i<NUM_ELEMENTS; i++)
        can_play[i]=true;

    bool showing_pictures=false;

    //Startup
    SAMPLE *click    =load_sample_ex("Music/Click.wav");

    BITMAP *periodic =load_bitmap_ex("bitmaps/Periodic.bmp",NULL);
    BITMAP *tray     =load_bitmap_ex("bitmaps/tray.bmp",NULL);
    BITMAP *circle   =load_bitmap_ex("bitmaps/Circle.bmp",NULL);
    BITMAP *searchbar=load_bitmap_ex("bitmaps/Search.bmp",NULL);
            buffer   =create_bitmap(SCREEN_W,SCREEN_H);

    screen_buff=create_bitmap(640,480);
    draw_sprite(screen_buff,periodic,0,0);

    BITMAP *clear=create_bitmap(440,80);
    rectfill(clear,0,0,440,80,GREY);

    if (errors.get_num_all()>0)
    {
        errors.disp_all_errors(EXIT_TRUE);
    }



    //Do some prelim stuff

    fill_screen(GREY);
    rectfill(buffer,0,0,buffer->w,buffer->h,GREY);
    draw_sprite(buffer,periodic,1,0);
    draw_sprite(buffer,tray,0,480);
    draw_sprite(buffer,searchbar,665,5);
    draw_sprite(screen,buffer,0,0);
    rectfill(screen,640,0,641,480,BLACK); //Draws line between table and search panel

    show_mouse(screen);

    //Initialize the Text Thread
    int id;
    pthread_t pthread0;
    int threadid0=0;
    id=pthread_create(&pthread0,NULL,thread0,(void *)&threadid0);

    //ssdone=true;

    /////////////
    //Main Loop//
    /////////////

    while (!done)
    {
        //Lock the tread
        if (pthread_mutex_lock(&threadsafe))
            textprintf_ex(screen,font,0,0,RED,WHITE,"ERROR: Text Thread Mutex was Locked");

        if (all_halt)
        {
            sem_wait(&semaphore);
        }


        ////////////////////////
        //Begining of elements//
        ////////////////////////

        for (int j=0; j<NUM_ELEMENTS; j++)
        {
            if (element[j].over())
            {
                if (on_element!=j)
                {
                    draw_sprite(screen,screen_buff,0,0);
                    draw_sprite(screen,circle,element[j].x1-1,element[j].y1-1);
                    if (showing_pictures==false)
                        draw_sprite(screen,element[j].bmp,0,485);

                    on_element=j;
                }

                for (int k=0; k<NUM_ELEMENTS; k++)
                {
                    if (k==j){}
                    else
                    {
                        can_play[k]=true;
                    }
                }
                if (can_play[j]==true)
                {
                    play_sample(click,50,PANNING,PITCH,false);
                    can_play[j]=false;
                }
            }
            else if (over_element()==false)
            {
                rectfill(screen,0,482,639,600,GREY);
                draw_sprite(screen,screen_buff,0,0);
                on_element=-1;
                for (int i=0; i<111; i++)
                    can_play[i]=true;
            }
        }

        //Unlock the thread;
        if (pthread_mutex_unlock(&threadsafe))
            textprintf_ex(screen,font,0,0,RED,WHITE,"ERROR: Text Thread Mutex unlock error");
    }


    //Tell the thread it's
    //time to end and delete it
    done=true;
    pthread_mutex_destroy(&threadsafe);

    destroy_bitmap(periodic);
    destroy_bitmap(tray);
    destroy_bitmap(buffer);
    destroy_bitmap(circle);
    destroy_bitmap(screen_buff);
    destroy_bitmap(searchbar);

    for (int i=0; i<111; i++)
    {
        destroy_bitmap(element[i].bmp);
    }

    //Music
    destroy_sample(click);
    sem_destroy(&semaphore);

    allegro_exit();
    return 0;
}

END_OF_MAIN()