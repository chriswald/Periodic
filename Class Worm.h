#ifndef CLASS_WORM_H
#define CLASS_WORM_H


enum Direction{Up=0,Down,Right,Left};
bool game_end;
long game_rest;
int  score;
bool level_up;

class Worm
{
public:
    Worm();
    ~Worm();
    void ch_dir(int dir);
    int  draw_worm();
    void update();
    void draw_start();
    void collide();
    void draw_food();
    void grow();

private:
    bool out_of_screen();
    void game_over();

    int head_posx;
    int head_posy;
    int tail_posx;
    int tail_posy;
    int direction;
    int tail_movex;
    int tail_movey;
    int bgcolor;
    int food_x;
    int food_y;
    int food_color;
    int num_eaten;
    BITMAP *food;
    SAMPLE *munch;
    SAMPLE *burp;
};

Worm::Worm()
{
    srand(time(NULL));
    head_posx=150;
    head_posy=20;
    tail_posx=20;
    tail_posy=20;
    direction=Right;
    tail_movex=1;
    tail_movey=0;
    num_eaten=0;

    bgcolor=get_pixel_color(screen,0,0);

    food_x=rand()%(SCREEN_W-6)+3;
    food_y=rand()%(SCREEN_H-6)+3;

    food=create_bitmap(3,3);
    rectfill(food,0,0,3,3,ORANGE);
    food_color=get_pixel_color(food,1,1);

    munch=load_sample("Music/Chomp.wav");
    burp =load_sample("Music/burp.wav");
}

Worm::~Worm()
{}

void Worm::ch_dir(int dir)
{
    if ((direction==Right && dir==Left) ||
       (direction==Left && dir==Right)  ||
       (direction==Up && dir==Down)     ||
       (direction==Down && dir==Up))
    {}
    else
        direction=dir;
}


void Worm::update()
{
    switch (direction)
    {
        case Right:
            head_posx++;
            break;
        case Left:
            head_posx--;
            break;
        case Up:
            head_posy--;
            break;
        case Down:
            head_posy++;
            break;
        default:
            break;
    }
}

int Worm::draw_worm()
{
    putpixel(screen,tail_posx,tail_posy,BLACK);
    putpixel(screen,head_posx,head_posy,WHITE);

    //Test 1 pixel away
    if (get_pixel_color(screen,tail_posx+tail_movex,tail_posy+tail_movey)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx+=tail_movex;
        tail_posy+=tail_movey;
        return 0;
    }

    if (get_pixel_color(screen,tail_posx-1,tail_posy)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx--;
        tail_movex=-1;
        tail_movey=0;
        return Left;
    }

    if (get_pixel_color(screen,tail_posx+1,tail_posy)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx++;
        tail_movex=1;
        tail_movey=0;
        return Right;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy-1)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posy--;
        tail_movex=0;
        tail_movey=-1;
        return Up;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy+1)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posy++;
        tail_movex=0;
        tail_movey=1;
        return Down;
    }


    //Test 2 pixles away
    if (get_pixel_color(screen,tail_posx-2,tail_posy)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx--;
        tail_movex=-1;
        tail_movey=0;
        return Left;
    }

    if (get_pixel_color(screen,tail_posx+2,tail_posy)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx++;
        tail_movex=1;
        tail_movey=0;
        return Right;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy-2)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posy--;
        tail_movex=0;
        tail_movey=-1;
        return Up;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy+2)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posy++;
        tail_movex=0;
        tail_movey=1;
        return Down;
    }

    if (get_pixel_color(screen,tail_posx+(tail_movex+tail_movex),tail_posy+(tail_movey+tail_movey))!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx+=tail_movex;
        tail_posy+=tail_movey;
        return 0;
    }

    //Test 3 pixels away
    if (get_pixel_color(screen,tail_posx-3,tail_posy)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx--;
        tail_movex=-1;
        tail_movey=0;
        return Left;
    }

    if (get_pixel_color(screen,tail_posx+3,tail_posy)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx++;
        tail_movex=1;
        tail_movey=0;
        return Right;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy-3)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posy--;
        tail_movex=0;
        tail_movey=-1;
        return Up;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy+3)!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posy++;
        tail_movex=0;
        tail_movey=1;
        return Down;
    }

    if (get_pixel_color(screen,tail_posx+(tail_movex+tail_movex+tail_movex),tail_posy+(tail_movey+tail_movey+tail_movey))!=bgcolor)
    {
        putpixel(screen,tail_posx,tail_posy,BLACK);
        tail_posx+=tail_movex;
        tail_posy+=tail_movey;
        return 0;
    }

    PRINT(NONE ARE TRUE,0,400);
    return -1;
}

void Worm::draw_start()
{
    line(screen,head_posx,head_posy,tail_posx,tail_posy,WHITE);
    rect(screen,1,11,SCREEN_W-2,SCREEN_H-2,WHITE);
}

void Worm::collide()
{
    int a;
    switch (direction)
    {
        case Right:
            a=get_pixel_color(screen,head_posx+1,head_posy);
            if (a==food_color)
            {
                draw_food();
                grow();
                break;
            }
            if (((a!=bgcolor) || out_of_screen()) && game_end==false)
            {
                game_over();
            }
            break;
        case Left:
            a=get_pixel_color(screen,head_posx-1,head_posy);
            if (a==food_color)
            {
                draw_food();
                grow();
                break;
            }
            if (((a!=bgcolor) || out_of_screen()) && game_end==false)
            {
                game_over();
            }
            break;
        case Up:
            a=get_pixel_color(screen,head_posx,head_posy-1);
            if (a==food_color)
            {
                draw_food();
                grow();
                break;
            }
            if (((a!=bgcolor) || out_of_screen()) && game_end==false)
            {
                game_over();
            }
            break;
        case Down:
            a=get_pixel_color(screen,head_posx,head_posy+1);
            if (a==food_color)
            {
                draw_food();
                grow();
                break;
            }
            if (((a!=bgcolor) || out_of_screen()) && game_end==false)
            {
                game_over();
            }
            break;
        default:
            break;
    }
}

bool Worm::out_of_screen()
{
    if (head_posx>SCREEN_W ||
        head_posx<0        ||
        head_posy>SCREEN_H ||
        head_posy<0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

void Worm::game_over()
{
    textout_centre_ex(screen,font,"GAME OVER",(SCREEN_W/2),SCREEN_H/2-5,RED,CLEAR);
    textprintf_centre_ex(screen,font,(SCREEN_W/2),SCREEN_H/2+5,RED,CLEAR,"SCORE: %i",score);
    rest(1000);
    while (!LB);
    game_end=true;
}

void Worm::draw_food()
{
    srand(time(NULL));

    rectfill(screen,food_x,food_y,food_x+2,food_y+2,BLACK);

    food_x=2+rand()%(SCREEN_W-5);

    do
    {
        food_y=12+rand()%(SCREEN_H-20);
    }
    while (food_y<20);

    draw_sprite(screen,food,food_x,food_y);
}

void Worm::grow()
{
    int grow_amt;
    play_sample(munch,VOLUME,PANNING,PITCH,false);
    num_eaten++;
    if (num_eaten%10==0)
    {
        play_sample(burp,VOLUME,PANNING,PITCH,false);
    }


    score+=10;
    if (level_up==false)
        game_rest-=(long int) .5;
    if (level_up==false)
        grow_amt=30;
    else
        grow_amt=60;

    if (get_pixel_color(screen,tail_posx-1,tail_posy)!=bgcolor)
    {
        line(screen,tail_posx,tail_posy,tail_posx+grow_amt,tail_posy,WHITE);
        tail_posx+=grow_amt;
    }

    if (get_pixel_color(screen,tail_posx+1,tail_posy)!=bgcolor)
    {
        line(screen,tail_posx,tail_posy,tail_posx-grow_amt,tail_posy,WHITE);
        tail_posx-=grow_amt;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy-1)!=bgcolor)
    {
        line(screen,tail_posx,tail_posy,tail_posx,tail_posy+grow_amt,WHITE);
        tail_posy+=grow_amt;
    }

    if (get_pixel_color(screen,tail_posx,tail_posy+1)!=bgcolor)
    {
        line(screen,tail_posx,tail_posy,tail_posx,tail_posy-grow_amt,WHITE);
        tail_posy-=grow_amt;
    }
}

#endif // CLASS_WORM_H
