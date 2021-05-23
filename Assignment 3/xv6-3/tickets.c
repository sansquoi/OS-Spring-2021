#include "types.h"
#include "user.h"
#include "stat.h"

int
main(int argc, char * argv[]){

  if(argc != 3){

    printf(1,"Error: Invalid number of arguments.\n");


    exit();
  }
 
 if(argv[1][0] == '-')
 {  
    //printf("Sorry, you have negative value. \n");
    printf(1,"Error: Invalid Number of Tickets.\n");

    exit();
 } 

 int num_tickets = atoi(argv[1]); //The first argument indicates the number of tickets the process should run with.

 //printf(1, "num = %d", num_tickets);
 
 settickets(num_tickets);

 exec(argv[2], &argv[2]); 

 exit();
 
}
