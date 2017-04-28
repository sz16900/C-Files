/* I assume Neills dont want any undercook, so I wrote a while bunch of conditions*/

#include <stdio.h>
#include <math.h>

int timeCalc(void);

int main (void) {
  timeCalc();
return 0;
}

int timeCalc(void){
int req_time, buttons_pressed = 0, calculated_time, a, b, c, z, microwave_time[3] = {600,60,10};

  printf("Type the time required \n");
  scanf("%d", &req_time);
  if (req_time < microwave_time[1]) { /*Check for seconds */
    if ((microwave_time[1] - req_time) < 10) {
      buttons_pressed = 1;
    }
    else {
      while(calculated_time < req_time) {
        buttons_pressed++;
        calculated_time = calculated_time + microwave_time[2];
      }
    }
  }
  else if(req_time < microwave_time[0]){ /* Check for minutes unde 10 */
    if ((microwave_time[0] - req_time) <= 10) {
      buttons_pressed = 1;
    }
    else {
      a = floor(req_time / microwave_time[1]);
      buttons_pressed = a;
      calculated_time = microwave_time[1] * a;
      while( calculated_time <= req_time){
        buttons_pressed++;
        calculated_time = calculated_time + microwave_time[2];
      }
    }
  } /* Check for minutes unde 10 */
  else {
    if (req_time == 600) {
      buttons_pressed = 1;
    }
    else {
      a = floor(req_time / microwave_time[0]);
      buttons_pressed = a;
      calculated_time = microwave_time[0] * a;
      b = req_time - calculated_time;
      calculated_time = 0;
      while((calculated_time < b) && z <= b){
        buttons_pressed++;
        calculated_time = calculated_time + microwave_time[1];
        z = calculated_time + calculated_time; /*this is to check whether it should loop again*/
      }
      c = b - calculated_time;
      calculated_time = 0;
      while(calculated_time <= c){
        buttons_pressed++;
        calculated_time = calculated_time + microwave_time[2];
      }
    }
  }

  printf("Number of buttons pressed: %d \n", buttons_pressed);
}
