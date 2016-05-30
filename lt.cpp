
/*SKELETON CODES FOR AVC */
/*  A.Roberts, 5 Apr 2016*/
#include <stdio.h>

//#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
// sudo gcc -Wall
extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);
extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char const server_addr[15],int port);
extern "C" int send_to_server(char const message[24]);
extern "C" int receive_from_server(char const message[24]);


int v_left = 0;
int v_right = 0;

int main(){
    // connect camera to the screen
    open_screen_stream();
    int n_ones = 0;
    int i;
    init(1);
    // connect camera to the screen
    open_screen_stream();
    set_motor(1,30);
    set_motor(2,30);
    Sleep(1,0);
    set_motor(1,0);
    set_motor(2,0);
    int whit_thr[320];
    int np = 320;
    int a[320];
    int count = 0;
    int method = 1;
    int x_2 = 0;
//	 int e = 0;
//	 int p_e = 0;
//	 int d_signal = 0;
connect_to_server("130.195.6.196",1024);
send_to_server("Please");
char message[24];
receive_from_server(message);
send_to_server(message);

    while(1) {
if(method == 1){
     take_picture();      //take camera shot

       for(i=-160; i<np; i++){
          a[i] = i-160;
       }
     int x;
      count = 0;
      n_ones = 0;
//printf("number of points: %d\n", np);
     for ( i=0; i<np; i++) {
        x = get_pixel(i,120,3);
        if(x>120){
          whit_thr[i]=1;
          n_ones++;
//     printf("%d",whit_thr[i]);
        }
        else{
        whit_thr[i]=0;
        count++;
       }
//printf("%d",whit_thr[i]);
       }
int n_ones_b = 0;
for(i=0; i<np; i++){
   x_2 = get_pixel(i, 90, 3);
if(x_2 < 120){
n_ones_b++;
printf("Hello world");
}
}

int e = 0;
     for(i=0; i<np; i++){
        e += whit_thr[i]*a[i];
     }

       float p_constant = 0.00293;
       v_left = 60 - (int)(e*(p_constant));
       v_right = 60 + (int)(e*(p_constant));
       set_motor(1, v_left);
       set_motor(2, v_right);

if(n_ones == 0){
if(e<0){
set_motor(1,0);
set_motor(2,0);
set_motor(1,-50);
set_motor(2,50);
Sleep(0,100000);
}else if(e>0 || e==0){
set_motor(1,0);
set_motor(2,0);
set_motor(1,50);
set_motor(2,-50);
Sleep(0,100000);
}
}

//printf("left: %d, right:%d", v_left,v_right);
    if(n_ones >= 213 && n_ones_b >= 213){
       method = 1;
    }
}







if(method == 2){
//printf("hi");
	take_picture();
          n_ones = 0;
	  count = 0;
	  int y = 0;
	  int n_ones_y = 0;
          for(i=0; i<240; i++){
             y = get_pixel(40,i,3);
             if(y > 120){
               n_ones_y++;
	       n_ones++;
             }
             else{
             count++;
             }
          }
         if(n_ones_y > 0){
           printf("THE AVC IS COOL");
           set_motor(1,50);
	   set_motor(2,50);
           Sleep(0,0500000);
           set_motor(1,0);
           set_motor(2,0);
           set_motor(1, 50);
           set_motor(2, -50);
           set_motor(1,0);
           set_motor(2,0);
          }else{
 	   set_motor(1,0);
	   set_motor(2,0);
           set_motor(1,-50);
           set_motor(2,50);
           Sleep(1,000000);
           set_motor(1,0);
           set_motor(2,0);
         }

if(n_ones == 0 || n_ones <= 3){
printf("Testing\n");
set_motor(1,0);
set_motor(2,0);
Sleep(0,500000);
set_motor(1,-50);
set_motor(2,50);
Sleep(0,500000);
set_motor(1,0);
set_motor(2,0);
}

 }else {


method = false;
}


       // display picture
       update_screen();

    }//while 1 end

   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;


}

void terminate(int signum){
set_motor(1,0);
set_motor(2,0);
exit(signum);
}
