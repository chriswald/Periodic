void *thread0(void *data)
{
    bool      insert_flag=false;
    bool      call_search=false;
    const int posx=675;
    const int posy=15;
    int       cursor_posx=posx-1;
    int       cursor_posy=posy;
    int       search_int=0;
    int       search_size=0;
    string    search;

    for (int i=0; i<19; i++)
        search[i]='\0';


    BITMAP *search_bar=load_bitmap_ex("bitmaps/Search.bmp",NULL);
    /*draw_sprite(screen,search_bar,665,5);*/

    BITMAP *search_buff=create_bitmap(SCREEN_W-642,SCREEN_H);
    rectfill(search_buff,0,0,search_buff->w,search_buff->h,GREY);
    draw_sprite(search_buff,search_bar,23,5);


    //Set up the typing
    vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,BLACK);

    //Used just to tick off seconds
    install_int(tick_tock,500);
    LOCK_VARIABLE(type_ticks);

    //while (!ssdone){rest(1);}

    while (!done)
    {
        if (pthread_mutex_lock(&threadsafe))
            allegro_message("ERROR: Thread Mutex was Locked");

        while (all_halt)
        {
            search="";
            sem_wait(&semaphore);
        }

        ////////////////////
        //                //
        // TYPING ROUTINE //
        //                //
        ////////////////////


        //If the mouse is clicked over the
        //text, move the cursor there
        if (mouse_over(posx-3,posy-2,posx+(search_size+1)*8+3,posy+13) && LB)
        {
            vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);

            for (int i=0; i<search_size+1; i++)
            {
                int mx1=((i*8)-4)+posx;
                int mx2=((i*8)+4)+posx;
                if (mouse_over(mx1,posy-2,mx2,posy+13))
                {
                    search_int=i;
                    cursor_posx=i*8+posx-1;
                    vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,BLACK);
                }
            }
        }
        //Make the typing bar blink
        if ((type_ticks*2)%3==0 || (type_ticks*2)%3==1)
        {
            vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,BLACK);
        }

        if ((type_ticks*2)%3==2)
        {
            vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);
        }
        //Change the cursors between edit and normal
        if (mouse_over(670,10,823,30))
            show_os_cursor(MOUSE_CURSOR_EDIT);
        else
            show_os_cursor(MOUSE_CURSOR_ARROW);

        ///////////////////////
        //IF A KEY IS PRESSED//
        ///////////////////////
        if (keypressed())
        {
            call_search=true;

            //Read the key
            int  newkey   = readkey();
            char ascii    = newkey & 0xff;
            int  scancode = newkey>>8;

            //If is a standard key...
            if (ascii >= 32 && ascii <= 126)
            {
                //Clear out the line before typing
                vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);

                if (insert_flag==true && search_int!=search_size)
                {
                    search[search_int]=(char) ascii;
                    search_size--;
                }

                else if (search_size==search_int || (search_int==search_size && insert_flag==true))
                {
                    search[search_int]=(char) ascii;
                }

                else
                {
                    for (int i=search_size; i>=search_int; i--)
                    {
                        search[i+1]=search[i];
                    }
                    search[search_int]=(char) ascii;
                }
                search_int++;
                search_size++;
                cursor_posx+=8;
            }


            //Handle special keys here...
            else
            {
                switch (scancode)
                {
                case KEY_BACKSPACE:
                    if (search_int>0)
                    {
                        vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);

                        if (search_size==search_int)
                        {
                            search_int--;
                            search_size--;
                            search[search_int]='\0';
                        }
                        else
                        {
                            for (int i=search_int; i<=search_size; i++)
                            {
                                search[i-1]=search[i];
                            }
                            search[search_size]='\0';
                            search_int--;
                            search_size--;
                        }

                        cursor_posx-=8;
                    }
                    break;
                case KEY_LEFT:
                    if (search_int>0)
                    {
                        search_int--;
                        vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);
                        cursor_posx-=8;
                    }
                    break;
                case KEY_RIGHT:
                    if (search_int<search_size)
                    {
                        search_int++;
                        vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);
                        cursor_posx+=8;
                    }
                    break;
                case KEY_INSERT:
                    insert_flag=!insert_flag;
                    break;
                case KEY_DEL:
                    if (search_int!=search_size)
                    {
                        search_int++;
                        for (int i=search_int; i<=search_size; i++)
                        {
                            search[i-1]=search[i];
                        }
                        search_int--;

                        search[search_size]='\0';
                        search_size--;
                    }
                    break;
                case KEY_HOME:
                    vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);
                    search_int=0;
                    cursor_posx=posx-1;
                    break;
                case KEY_END:
                    vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,WHITE);
                    search_int=search_size;
                    cursor_posx=(search_size*8)+posx-1;
                    break;
                case KEY_F1:
                    open_notepad("readme.txt");
                    break;
                default:
                    break;
                }
            }
            draw_sprite(screen,search_buff,642,0);
            textprintf_ex(screen,font,posx,posy,BLACK,WHITE,"%s ",search.c_str());
            vline(screen,cursor_posx,cursor_posy-3,cursor_posy+7,BLACK);
        }



        if (search_size!=0 && call_search==true)
        {
            search_func(search,search_size);
            call_search=false;
        }

        if (search_size==0)
        {
            textprintf_centre_ex(screen,font,(642+(SCREEN_W-642)/2),200,makecol(205,205,205),CLEAR,"No Search");
            textprintf_ex(screen,font,posx,posy,makecol(205,205,205),WHITE,"Enter A Search");
        }


        if (mouse_over(645,45,SCREEN_W,SCREEN_H))
        {
            if ((search_results::results[0].over() && LB) && search_results::func_indicator)
            {
                switch (search_results::func_indicator)
                {
                    case 1:
                        all_halt=true;
                        game();
                        all_halt=false;
                        sem_post(&semaphore);
                        break;
                    case 2:
                        all_halt=true;
                        about();
                        all_halt=false;
                        sem_post(&semaphore);
                        break;
                    case 3:
                        done=true;
                        break;
                    default:
                        break;
                }
            }


            for (int i=0; i<search_results::num_results; i++)
            {
                if ((search_results::results[i].over()) && LB)
                {
                    position_mouse(search_results::results[i].ele.x1+10,search_results::results[i].ele.y1+10);
                    while(LB){rest(1);}
                }
            }
        }

        //sem_wait(&semaphore2);

        if (pthread_mutex_unlock(&threadsafe))
            allegro_message("ERROR: Thread Mutex unlock error");
    }

    destroy_bitmap(search_bar);
    destroy_bitmap(search_buff);

    pthread_exit(NULL);
    return NULL;
}
