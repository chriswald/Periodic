#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

//Global Vars.
int  type_ticks=0;
bool all_halt  =false;

volatile bool ssdone=false;

BITMAP *screen_buff;
BITMAP *buffer;

pthread_mutex_t threadsafe=PTHREAD_MUTEX_INITIALIZER;

sem_t semaphore;

const int NUM_ELEMENTS=112;

namespace search_results
{
    Text results[NUM_ELEMENTS];
    int num_results;
    int num_results_reported;
    int func_indicator;
}

#endif // GLOBALS_H_INCLUDED
