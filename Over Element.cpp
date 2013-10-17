#include <Allegro Header.h>

bool over_element()
{
    for (int i=0; i<NUM_ELEMENTS; i++)
        if (element[i].over())
            return true;
    return false;
}
