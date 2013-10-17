#include <Allegro Header.h>

Element element[NUM_ELEMENTS];
void print_func(int ele_num);

//This was the old set up. Keep it incase something breaks. It's a backup.
/*void print_func(int ele_num)
{
    BITMAP *bmp=create_bitmap(635,110);

    string file_name="bitmaps/Elements/";
    file_name+=element[ele_num].name;
    file_name+=".bmp";

    BITMAP *print=load_bitmap_ex((char *) file_name.c_str(),NULL);
    int posy=0;

    if (errors.get_num_all()>0)
    {
        errors.disp_all_errors(EXIT_TRUE);
    }

    clear_bitmap(bmp);

    const int step=10;
    const int small_step=4;
    const int start_step=30+small_step;
    const int color_chunk=100;
    rectfill(bmp,0,0,bmp->w,bmp->h,GREY); posy+=2*step;


    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"%s",element[ele_num].name);
    textprintf_right_ex(bmp,font,510,posy,BLACK,CLEAR,"%s",element[ele_num].type); posy+=step;

    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Symbol:       %s",element[ele_num].symbol); posy+=step;
    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Number:       %s",element[ele_num].number); posy+=step;
    if (element[ele_num].group!="") {
        textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Group:        %s",element[ele_num].group); posy+=step;
    }
    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Atomic Mass:  %sg",element[ele_num].mass); posy+=step;
    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Common Ions:  %s",element[ele_num].ions); posy+=step;

    posy=start_step;

    textprintf_ex(bmp,font,260,posy,BLACK,CLEAR,"Common Uses:"); posy+=step;
    textprintf_ex(bmp,font,265,posy,BLACK,CLEAR,"%s",element[ele_num].uses1); posy+=step;

    if (element[ele_num].uses2!=""){
        textprintf_ex(bmp,font,265,posy,BLACK,CLEAR,"%s",element[ele_num].uses2); posy+=step;}
    if (element[ele_num].uses3!=""){
        textprintf_ex(bmp,font,265,posy,BLACK,CLEAR,"%s",element[ele_num].uses3); posy+=step;}
    if (element[ele_num].uses4!=""){
        textprintf_ex(bmp,font,265,posy,BLACK,CLEAR,"%s",element[ele_num].uses4); posy+=step;}

    if (element[ele_num].radioactive==true)
        textprintf_ex(bmp,font,10,100,RED,CLEAR,"Radioactive");

    stretch_blit(print,bmp,0,0,print->w,print->h,520,0,110,110);
    destroy_bitmap(print);

    draw_sprite(element[ele_num].bmp,bmp,0,0);

    destroy_bitmap(bmp);
}*/

//This is the new style
void print_func(int ele_num)
{
    BITMAP *bmp=create_bitmap(635,110);

    string file_name="bitmaps/Elements/";
    file_name+=element[ele_num].name;
    file_name+=".bmp";

    BITMAP *print=load_bitmap_ex((char *) file_name.c_str(),NULL);
    int posy=0;

    if (errors.get_num_all()>0)
    {
        errors.disp_all_errors(EXIT_TRUE);
    }

    clear_bitmap(bmp);

    const int step=10;
    const int small_step=4;
    const int start_step=30+small_step;
    const int color_chunk=100;
    rectfill(bmp,0,0,bmp->w,bmp->h,GREY); posy+=2*step;


    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"%s",element[ele_num].name);
    textprintf_right_ex(bmp,font,bmp->w-10,posy,BLACK,CLEAR,"%s",element[ele_num].type); posy+=step;
    line(bmp,7,posy-1,277,posy-1,makecol(color_chunk,color_chunk,color_chunk));
    line(bmp,393,posy-1,bmp->w-7,posy-1,makecol(color_chunk,color_chunk,color_chunk)); posy+=small_step;

    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Symbol:       %s",element[ele_num].symbol); posy+=step;
    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Number:       %s",element[ele_num].number); posy+=step;
    if (element[ele_num].group!="") {
        textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Group:        %s",element[ele_num].group); posy+=step;
    }
    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Atomic Mass:  %sg/mol",element[ele_num].mass); posy+=step;
    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"State (289K): %s",element[ele_num].state);posy+=step;
    textprintf_ex(bmp,font,10,posy,BLACK,CLEAR,"Common Ions:  %s",element[ele_num].ions); posy+=step;

    posy=start_step;

    textprintf_right_ex(bmp,font,bmp->w-10,posy,BLACK,CLEAR,"Common Uses:"); posy+=step;
    textprintf_right_ex(bmp,font,bmp->w-10,posy,BLACK,CLEAR,"%s",element[ele_num].uses1); posy+=step;

    if (element[ele_num].uses2!=""){
        textprintf_right_ex(bmp,font,bmp->w-10,posy,BLACK,CLEAR,"%s",element[ele_num].uses2); posy+=step;}
    if (element[ele_num].uses3!=""){
        textprintf_right_ex(bmp,font,bmp->w-10,posy,BLACK,CLEAR,"%s",element[ele_num].uses3); posy+=step;}
    if (element[ele_num].uses4!=""){
        textprintf_right_ex(bmp,font,bmp->w-10,posy,BLACK,CLEAR,"%s",element[ele_num].uses4); posy+=step;}

    if (element[ele_num].radioactive==true)
        textprintf_ex(bmp,font,10,100,RED,CLEAR,"Radioactive");

    stretch_blit(print,bmp,0,0,print->w,print->h,280,0,110,110);
    destroy_bitmap(print);

    draw_sprite(element[ele_num].bmp,bmp,0,0);

    destroy_bitmap(bmp);
}
