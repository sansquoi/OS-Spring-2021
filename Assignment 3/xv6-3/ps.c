#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"



int
main(int argc, char *argv[])
{
  int i;

  if (argc > 2){

    return -1; //Too many arguments

  }
  
  //process table data structure
  struct pstat* processInfo = (struct pstat*)malloc(sizeof(struct pstat));

  //when no -r
  if (argc == 1)
  {

    getpinfo(processInfo); //get process info

    printf(1,"PID TICKETS TICKS\n");

    for(i = 0; i < NPROC; i++){

      if( processInfo->inuse[i]) //if in use

        printf(1,"%d %d %d\n", processInfo->pid[i], processInfo->tickets[i], processInfo->ticks[i]);

    }
  }

  //recurring printout, for -r
  if(argc == 2)
  {
   if( strcmp(argv[1],"-r") == 0)
    {  
  
    while(1){//run it forever
	
      
      getpinfo(processInfo); //get process info
       

      printf(1,"PID TICKETS TICKS\n");

      for(i = 0; i < NPROC; i++){

        if(processInfo->inuse[i])

          printf(1,"%d %d %d\n", processInfo->pid[i], processInfo->tickets[i], processInfo->ticks[i]); 

      }

      sleep(100); //every 100 ticks ~ 1 sec
     }
    }
  }
  exit();
}

