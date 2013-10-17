#include <Allegro Header.h>

void about()
{
    int red1=192,gre1=192,blu1=192;
    int red2=192,gre2=192,blu2=192;
    int red3=192,gre3=192,blu3=192;
    int red4=192,gre4=192,blu4=192;
    int color1=0,color2=0,color3=0,color4=0;

    const int posx=640/2;

    BITMAP *tray=load_bitmap("bitmaps/tray.bmp",NULL);
    BITMAP *close=load_bitmap_ex("bitmaps/x.bmp",NULL);
    rectfill(screen,0,0,639,480,GREY);

    draw_sprite(screen,close,625,5);

    for (int i=480; i>-110; i--)
    {
        exit_event(mouse_over(625,5,635,15) && LB);

        if (i<480)
        {
            if (red1>5 && gre1>5 && blu1>5)
            {
                red1-=3;
                gre1-=3;
                blu1-=3;
                color1=makecol(red1,gre1,blu1);
            }

            textprintf_centre_ex(screen,font,posx,i,color1,GREY,"Periodic");
        }

        if (i<470)
        {
            if (red2>5 && gre2>5 && blu2>5)
            {
                red2-=3;
                gre2-=3;
                blu2-=3;
                color2=makecol(red2,gre2,blu2);
            }

            textprintf_centre_ex(screen,font,posx,i+10,color2,GREY,"A Program Writen By:");
        }

        if (i<460)
        {
            textprintf_centre_ex(screen,font,posx,i+18,GREY,GREY,"                       ");
        }

        if (i<450)
        {
            if (red3>5 && gre3>5 && blu3>5)
            {
                red3-=3;
                gre3-=3;
                blu3-=3;
                color3=makecol(red3,gre3,blu3);
            }

            textprintf_centre_ex(screen,font,posx,i+30,color3,GREY,"Christopher Wald");
        }

        if (i<440)
        {
            textprintf_centre_ex(screen,font,posx,i+38,GREY,GREY,"                       ");
        }

        if (i<410)
        {
            if (red4>5 && gre4>5 && blu4>5)
            {
                red4-=3;
                gre4-=3;
                blu4-=3;
                color4=makecol(red4,gre4,blu4);
            }

            textprintf_centre_ex(screen,font,posx,i+60,color4,GREY,"2009");
        }

        draw_sprite(screen,tray,0,480);

        exit_event(done==true);

        rest(37);
    }
    destroy_bitmap(tray);
    destroy_bitmap(close);
}
