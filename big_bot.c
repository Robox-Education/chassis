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
const int q1(13);
const int q2(12);
const int q3(11);
const int q4(10);

static const uint8_t enable(){
      digitalWrite(EN1A,HIGH);
      digitalWrite(EN1B,HIGH);
      digitalWrite(EN2A,HIGH);
      digitalWrite(EN2B,HIGH);
}
//right wheel is m1, left wheel m2, with drive wheels facing forward

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
    pinMode(C1, INPUT);
    pinMode(C2, INPUT);
    pinMode(q1, INPUT);
    pinMode(q2, INPUT);
    pinMode(q3, INPUT);
    pinMode(q4, INPUT);
    
    Serial.begin(9600);
}


struct ret
    {
    
    int16_t c_1;  //current one
    int16_t c_2;  //current two
    //quadrature encoder data can come in here
    //accelerometer data?
    };
struct ret *fwd_val;
static struct ret *stp_val;
static struct ret *rvs_val;
static struct ret *rgt_val;
static struct ret *lft_val;
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
 
uint8_t brake()
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

uint8_t lft()
  {
      enable();
      thrust("lft");
      struct ret ret_val;
      lft_val = &ret_val;

      lft_val->c_1 = analogRead(C1);
      lft_val->c_2 = analogRead(C2); // check current for both wheels
  
      return (0);
  }

uint8_t rgt()
  {
      enable();
      thrust("rgt");
      struct ret ret_val;
      rgt_val = &ret_val;

      rgt_val->c_1 = analogRead(C1);
      rgt_val->c_2 = analogRead(C2); // check current for both wheels
  
      return (0);
  }

void loop()
{
    
    forward();//debug
      Serial.print("C_1 ");
      Serial.print(fwd_val->c_1); 
      Serial.print ("     C_2");
      Serial.print(fwd_val->c_2);  
      Serial.println("q1 ");
      Serial.print("q1 ");
      Serial.println(analogRead(q1));
      Serial.print("q2 ");
      
      Serial.println(analogRead(q2));
      
      Serial.print("q3 ");
      Serial.println(analogRead(q3));
      
      Serial.print("q4 ");
      Serial.println(analogRead(q4));

      
}
