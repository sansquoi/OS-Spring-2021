#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if( argc == 2 ) {
      //continue
   }
   else {
     //If no arguments were passed.
     printf(1, "(Only) one integer argument expected.\n");
     return 0;
   }
  
  int argPassed = atoi(argv[1]);
  int uptimeCounter = uptime();
  int uptimeUntil = uptimeCounter + argPassed;

  //Until Uptime counter reaches target Uptime
  while(uptimeCounter < uptimeUntil)
  {
    //Update Uptime
    uptimeCounter = uptime();
  }
  
  //Print number of pre-emptions
  printf(1, "%d\n", getticks());

  exit();
}
