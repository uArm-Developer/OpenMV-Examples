#include <FlexiTimer2.h>

char data[50] = {0};
unsigned long rev_cnt = 0; 
unsigned long timer_tick_cnt = 0;
bool timeout_flag = false;
unsigned long timeout_cnt = 0;
bool is_fan_open = false;

enum uart_state_e {
  RECV_DATA = 0,
  PARSE_DATA,
}uart_state = RECV_DATA;
enum uarm_mode_e {
  SEEK_MODE = 0,
  FOLLOW_MODE,
  WAIT_MODE,
} uarm_mode = WAIT_MODE;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(115200);

  Serial.println( "openMV kit demo" );
  delay(1000);
  Serial2.write("M2400 S0\n");
  delay(100);
  Serial2.write("G0 X200 Y0 Z150 F1000000\n");    // <! set the start position
  delay(100);
  Serial2.write("M2305 P9 N13\n");
  delay(100); 
  Serial2.write("M2307 P9 V0\n");

  FlexiTimer2::set(100, timer_callback);
  FlexiTimer2::start();
}

void timer_callback(void){                        // <! period = 100ms
  timer_tick_cnt++;
  if( timeout_flag ){
    if( timeout_cnt++ > 30 ){                     // <! 3s
      Serial.println( "t!" );
      timeout_flag = false;
      timer_tick_cnt = 0;
      
      Serial2.write("M2307 P9 V0\n");
      is_fan_open = false;
      uarm_mode =  SEEK_MODE;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  static int angle = 90, height = 150;

  char cmd[128] = {0};
  switch( uart_state ){
    case RECV_DATA:                                 // <! recv uart data
          memset( data, 0x00, 50 );
          rev_cnt = 0;
          while(Serial1.available()){
            data[rev_cnt++] = char(Serial1.read());
//            Serial.println(rev_cnt);
            if(rev_cnt>49){
              data[49] = '\0';
              break;
            }
            delay(2); 
          }
          if( rev_cnt == 0){
            break;
          }
          uart_state = PARSE_DATA;
          
    case PARSE_DATA:                              // <! parse uart data
         if( uarm_mode != FOLLOW_MODE ){
            uarm_mode = FOLLOW_MODE;
            Serial.println( "detach human face!" );
            break;
          }
    
          char x_str[20]={0}, y_str[20]={0};
          float camera_x = 0, camera_y = 0;
          int rtn = sscanf( data, "#%[^,],%[0-9-+.]#\r\n",x_str, y_str );
          if( rtn == 2 ){
            camera_x = atof(x_str);
            camera_y = atof(y_str);      
            if( camera_x > 125 ){
              Serial.println(">>>>");
              angle -= 1;
              if( angle < 30 ){
                angle = 30;
              }  
            }else if( camera_x < 115 ){
              Serial.println("<<<<");
              angle += 1;
              if(angle > 150){
                angle = 150;
              }
            }
           sprintf( cmd, "G2202 N0 V%d F800\n", angle );
           Serial2.write(cmd);
           timeout_flag = true;
           timeout_cnt = 0;
           delay(30);
           if( !is_fan_open ){                  // <! open fan
             is_fan_open = true;
             Serial2.write("M2307 P9 V120\n");
             delay(100);
           }
            
          } 
          uart_state = RECV_DATA;
      break;
  } 
  
  switch( uarm_mode ){
    case SEEK_MODE:                             // <! move around to look for human face
          static bool toggle_dir = false;
          
          if( toggle_dir ){
            angle -= 10;
          }else{
            angle += 10;
          }
          if( angle > 150 ){
            angle = 150;
            toggle_dir = true;
          }else if( angle<30 ){
            angle = 30;
            toggle_dir = false;
          }
          sprintf( cmd, "G2202 N0 V%d F500\n", angle );
          Serial2.write(cmd);
          uarm_mode = WAIT_MODE;
      break;
    case FOLLOW_MODE:

      break;
    case WAIT_MODE:
         if(timer_tick_cnt>10 && timer_tick_cnt%12==0){
          uarm_mode =  SEEK_MODE;
          timer_tick_cnt += 1;
         }
      break;
  }

   
}
