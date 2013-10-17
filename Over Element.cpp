#include <Allegro Header.h>

bool over_element()
{
    bool over=false;
    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        if (element[i].over())
	{
            over=true;
	    break;
	}
    }

    return over;
}
