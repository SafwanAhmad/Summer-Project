#include "header.h"
#define CLOCKID CLOCK_REALTIME



void SIMULATE();
int i = 0;
char instruction[12];
long long int TIMEPD = 1;

void CLOCK()
{

        timer_t timerid;
        struct sigevent EVENT;
        struct sigaction ACTION;
        struct itimerspec ITSPEC;
        
       
        
        
        //establish handler for signal
        printf("Establishing handler for signal %d\n",SIGRTMIN);
        ACTION.sa_flags = SA_SIGINFO;
        ACTION.sa_sigaction = SIMULATE;
        if(sigaction(SIGRTMIN, &ACTION, NULL) == -1)
        {
                printf("Failed to register handler\n");
        }
        
        //creating the timer
        
        EVENT.sigev_notify = SIGEV_SIGNAL; 
        EVENT.sigev_signo = SIGRTMIN;
        EVENT.sigev_value.sival_ptr = &timerid;
        
        if(timer_create(CLOCKID , &EVENT, &timerid) == -1)
        {
                printf("ERROR\n");
        }
        
        //starting the timer
       
        
        ITSPEC.it_value.tv_sec = 0;
        ITSPEC.it_value.tv_nsec = 250000000;
        
        ITSPEC.it_interval.tv_sec = ITSPEC.it_value.tv_sec;
        ITSPEC.it_interval.tv_nsec = ITSPEC.it_value.tv_nsec;
        
         if (timer_settime(timerid, 0, &ITSPEC, NULL))
         {
                printf("timer_settime\n");
                
         }
         
         
         while(1);
         

         
}

void SIMULATE()
{
        memcpy(instruction, ROM[STRING2INT(RAM[PCL],0,7)],12);
        
        if(CYCLE == 0)
        {
                DECODER();
                EXECUTE();
        }
        else if(CYCLE == -1)
        {
                EXECUTE();
        } 
        
       
        PRINTSTATUS();
        INCRPC();         
         
       // printf("INSIDE SIMULATE()\n");
         
     
}                 

