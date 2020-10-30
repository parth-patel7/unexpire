#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <dirent.h>
#include <dlfcn.h>
#include <string.h>

// Name: Parth Patel


struct tm hardCodeTime;
char format[100];

time_t time(time_t *tloc){
  
  time_t (*my_time) (time_t *tloc);
  my_time = dlsym(RTLD_NEXT, "time");
  

  if (tloc != NULL) {
    
    hardCodeTime.tm_year = 2020 - 1900;
    hardCodeTime.tm_mon = 3 - 1;
    hardCodeTime.tm_mday = 1;
    hardCodeTime.tm_hour = 0;
    hardCodeTime.tm_min = 0;
    hardCodeTime.tm_sec = 1;
    hardCodeTime.tm_isdst = -1;
    
    
    if (mktime(&hardCodeTime) != -1){
      (void)strftime(format, sizeof(format), "%b %d %Y %X", &hardCodeTime);
    }

    if (tloc[0] != 0){
      return my_time(tloc);
    }
    
    time_t incorrectTime = mktime(&hardCodeTime);
    *tloc = incorrectTime;
    return incorrectTime;
  }  
  return my_time(tloc);
}

