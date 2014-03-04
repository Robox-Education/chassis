#include <stdint.h>


#define EN1A 9
#define M1A  8
#define EN1B 3
#define M1B  2
#define EN2A 4
#define M2A  5
#define EN2B 7
#define M2B  6
#define C1 A0
#define C2 A1


static const uint8_t enable(){
      digitalWrite(EN1A,HIGH);
      digitalWrite(EN1B,HIGH);
      digitalWrite(EN2A,HIGH);
      digitalWrite(EN2B,HIGH);
}

static const uint8_t thrust(char* dir){
      if(dir=="fwd"){
        digitalWrite(M1A,HIGH);
        digitalWrite(M1B,HIGH);
        digitalWrite(M2A,LOW);
        digitalWrite(M2B,LOW);
        }
      if(dir=="rvs"){
        digitalWrite(M1A,LOW);
        digitalWrite(M1B,LOW);
        digitalWrite(M2A,HIGH);
        digitalWrite(M2B,HIGH);
        }        
      if(dir=="rgt"){
        digitalWrite(M1A,LOW);
        digitalWrite(M1B,LOW);
        digitalWrite(M2A,LOW);
        digitalWrite(M2B,LOW);
        }      
      if(dir=="lft"){
        digitalWrite(M1A,HIGH);
        digitalWrite(M1B,HIGH);
        digitalWrite(M2A,HIGH);
        digitalWrite(M2B,HIGH); 
        }
      if(dir=="stp"){    
        digitalWrite(EN1A,LOW);  //brake -roll-to-stop
        digitalWrite(EN1B,LOW); //brake  -roll-to-stop right
        digitalWrite(EN2A,LOW);  //brake -roll-to-stop left
        digitalWrite(EN2B,LOW); //brake  -roll-to-stop left
        } 
}  
      
void setup()
{

    pinMode(EN1A,OUTPUT);
    pinMode( M1A,OUTPUT);
    pinMode(EN1B,OUTPUT);
    pinMode( M1B,OUTPUT);
    pinMode(EN2A,OUTPUT);
    pinMode( M2A,OUTPUT);
    pinMode(EN2B,OUTPUT);
    pinMode( M2B,OUTPUT);
    
    Serial.begin(9600);
}


struct ret
    {
    
    uint8_t c_1;  //current one
    uint8_t c_2;  //current two
    //quadrature encoder data can come in here
    //accelerometer data?
    };
static struct ret *fwd_val;
static struct ret *stp_val;
static struct ret *rvs_val;

uint8_t forward()
  {
      enable();
      thrust("fwd");
      struct ret ret_val;
      fwd_val = &ret_val;

      fwd_val->c_1 = analogRead(C1);
      fwd_val->c_2 = analogRead(C2); // check current for both wheels
  
      return (0);
  }
 
uint8_t stop()
  {
       
      struct ret ret_val;
      stp_val = &ret_val;
      enable();
      thrust("stp");
      
      stp_val->c_1 = analogRead(C1);
      stp_val->c_2 = analogRead(C2); // check current for both wheels
      return (0);
  }
  
  
uint8_t reverse()
  {
      struct ret ret_val;
      rvs_val = &ret_val;
      //right wheel channel 1
      enable();
      thrust("rvs");
      
      rvs_val->c_1 = analogRead(C1);
      rvs_val->c_2 = analogRead(C2); // check current for both wheels
      return (0);
}

void loop()
{
    
    forward();
      Serial.print("C_2 ");
      Serial.print(fwd_val->c_1);
      Serial.print("C_1");
      Serial.print(fwd_val->c_2);  

}
