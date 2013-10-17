#include <Allegro Header.h>

MP3FILE *elements;
MP3FILE *golliwog;
bool music_timer_installed=false;

void *Music_Thread(void *data)
{
            golliwog     =load_mp3("Music/Golliwog's Cake Walk.mp3");

    BITMAP *volume_tray  =load_bitmap_ex("bitmaps/Volume Tray.bmp",NULL);
    BITMAP *volume_bar   =load_bitmap_ex("bitmaps/Volume Bar.bmp",NULL);
    BITMAP *vol_bar_temp =create_bitmap(volume_bar->w,volume_bar->h);

    clear_bitmap(vol_bar_temp);

    bool volume_visable=false;
    bool add_music=false;
    int  curz=mouse_z;
    int  num_ticks=0;
    int  volume=125;

    if (errors.get_num_all()>0)
    {
        errors.disp_all_errors(EXIT_TRUE);
    }

    while (!ssdone){}

    while (!done)
    {
        while (all_halt)
        {
            if (add_music==true)
                poll_mp3_file(golliwog);
        }

        if (add_music==true)
        {
            poll_mp3_file(golliwog);
        }


        //Lock the tread
        if (pthread_mutex_lock(&music_threadsafe))
            textprintf_ex(screen,font,0,0,RED,WHITE,"ERROR: Music Thread Mutex was Locked");

        if (play_additional_music==true)
        {
            install_int(music_timer,1000);

            play_mp3_file(golliwog,BUF_SIZE,volume,PANNING);
            add_music=true;
            play_additional_music=false;
        }
        if (stop_additional_music==true)
        {
            remove_int(music_timer);
            music_int=0;

            stop_mp3_file(golliwog);
            close_mp3_file(golliwog);
            golliwog=load_mp3("Music/Golliwog's Cake Walk.mp3");
            stop_additional_music=false;
            play_additional_music=false;
            add_music=false;
        }


        //Adjust the volume using
        //the mouse wheel
        if (curz<mouse_z && volume<=254)
        {
            volume+=mouse_z-curz;
            if (volume>255) volume=255;

            curz=mouse_z;
            adjust_mp3_file(golliwog,volume,PANNING,1000);

            draw_sprite(screen_buff,volume_tray,170,440);
            clear_bitmap(vol_bar_temp);
            stretch_blit(volume_bar,vol_bar_temp,0,0,volume_bar->w,volume_bar->h,0,0,vol_bar_temp->w-(255-volume),vol_bar_temp->h);
            draw_sprite(screen_buff,vol_bar_temp,180,450);

            num_ticks=ticks;
            volume_visable=true;
        }
        if (curz>mouse_z && volume>=0)
        {
            volume-=curz-mouse_z;
            if (volume<0) volume=0;

            curz=mouse_z;
            adjust_mp3_file(golliwog,volume,PANNING,1000);

            draw_sprite(screen_buff,volume_tray,170,440);
            clear_bitmap(vol_bar_temp);
            stretch_blit(volume_bar,vol_bar_temp,0,0,volume_bar->w,volume_bar->h,0,0,vol_bar_temp->w-(255-volume),vol_bar_temp->h);
            draw_sprite(screen_buff,vol_bar_temp,180,450);

            num_ticks=ticks;
            volume_visable=true;
        }

        //Hold it on the screen for one second
        if (ticks-num_ticks<=1 && volume_visable==true)
        {
            draw_sprite(screen_buff,volume_tray,170,440);
            clear_bitmap(vol_bar_temp);
            stretch_blit(volume_bar,vol_bar_temp,0,0,volume_bar->w,volume_bar->h,0,0,vol_bar_temp->w-(255-volume),vol_bar_temp->h);
            draw_sprite(screen_buff,vol_bar_temp,180,450);
        }

        else if (ticks-num_ticks>1 && volume_visable==true)
        {
            volume_visable=false;
            rectfill(screen_buff,170,440,170+volume_tray->w,440+volume_tray->h,makecol(127,122,227));
        }

        rest(10);

        //Lock the tread
        if (pthread_mutex_unlock(&music_threadsafe))
            textprintf_ex(screen,font,0,0,RED,WHITE,"ERROR: Music Thread Mutex Unlock Error");
    }

    destroy_bitmap(volume_tray);
    destroy_bitmap(volume_bar);
    destroy_bitmap(vol_bar_temp);

    close_mp3_file(golliwog);

    pthread_exit(NULL);
    return NULL;
}
