#include "equals.cpp"
#include "About Periodic.cpp"

void search_func(string search,int search_size)
{
    char game_string[]="al_game::init()";
    char about_string[]="al_about::init()";
    char exit_string[]="al_prgm::exit()";
    char play_game[]="Play Game...";
    char about_periodic[]="About Periodic...";
    char exit_prgm[]="Exit Periodic...";

    BITMAP *circle=load_bitmap("bitmaps/circle.bmp",NULL);

    int posx=650;
    int posy=47;
    int num=0;

    search_results::func_indicator=0;
    search_results::num_results=0;
    search_results::num_results_reported=0;


    //start the game
    if (equals((char *) search.c_str(),game_string,strlen(game_string)))
    {
        for (int i=0; i<50; i++)
            search_results::results[0].text[i]='\0';

        for (int i=0; i<(int) strlen(play_game); i++)
            search_results::results[0].text[i]=play_game[i];

        search_results::func_indicator=1;
    }


    //Show some about info
    if (equals((char *) search.c_str(),about_string,strlen(about_string)))
    {
        for (int i=0; i<50; i++)
            search_results::results[0].text[i]='\0';

        for (int i=0; i<(int) strlen(about_periodic); i++)
            search_results::results[0].text[i]=about_periodic[i];

        search_results::func_indicator=2;
    }

    //Exit
    if (equals((char *) search.c_str(),exit_string,strlen(exit_string)))
    {
        for (int i=0; i<50; i++)
            search_results::results[0].text[i]='\0';

        for (int i=0; i<(int) strlen(exit_prgm); i++)
            search_results::results[0].text[i]=exit_prgm[i];

        search_results::func_indicator=3;
    }

    if (search_results::func_indicator!=0)
    {
        search_results::results[0].box_x=posx-2;
        search_results::results[0].box_y=posy-1;
        search_results::results[0].x=posx;
        search_results::results[0].y=posy;
        search_results::results[0].width=178;
        search_results::results[0].height=11;
        search_results::results[0].ele.set(-100,-100,-101,-101);
        search_results::num_results++;
        search_results::num_results_reported++;
        textprintf_ex(screen,font,
                      search_results::results[0].x,search_results::results[0].y,
                      BLACK,GREY,
                      "%s",search_results::results[0].text);
    }

    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        char *ele=element[i].name;
        char *sym=element[i].symbol;
        char *nmb=element[i].number;
        char *mat=element[i].state;
        char *us1=element[i].uses1;
        char *us2=element[i].uses2;
        char *us3=element[i].uses3;
        char *us4=element[i].uses4;
        char *sch=(char *) search.c_str();

        string full="";
        full+=ele;
        full+=sym;
        full+=nmb;
        full+=mat;
        full+=us1;
        full+=us2;
        full+=us3;
        full+=us4;
        char *prt=(char *) full.c_str();

        for (int j=0; prt[j]!='\0'; j++)
            prt[j]=tolower(prt[j]);
        for (int j=0; sch[j]!='\0'; j++)
            sch[j]=tolower(sch[j]);

        int  k=0;

        for (int j=0; prt[j]!='\0'; j++)
        {
            if (prt[j]==sch[k])
                k++;
            if (k==search_size)
            {
                if (posy>590)
                {
                    posy+=5;
                }

                search_results::results[num].box_x=posx-2;
                search_results::results[num].box_y=posy-1;
                search_results::results[num].x=posx;
                search_results::results[num].y=posy;
                search_results::results[num].width=178;
                search_results::results[num].height=11;
                search_results::results[num].ele=element[i];

                if (search_results::num_results<46)
                {
                    textprintf_ex(screen,font,posx,posy,BLACK,GREY,"%s",element[i].name);
                    textprintf_ex(screen,font,posx+125,posy,BLACK,GREY,"%s",element[i].symbol);
                    textprintf_ex(screen,font,posx+175,posy,BLACK,GREY,"%s",element[i].number);
                    search_results::num_results_reported++;
                }
                posy+=12;
                search_results::num_results++;
                num++;
                break;
            }
        }
    }


    textprintf_ex(screen,font,650,35,BLACK,GREY,"%i/%i Results Displayed   ",search_results::num_results_reported,search_results::num_results);

    destroy_bitmap(circle);
}
