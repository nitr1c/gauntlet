/*
Arduino Uno version of the Chorded Glove (working name).
Coded by nitr1c

The glove works through conductive pads, each connected to a pin on the
Arduino. Character output (through scancodes) is based off of the pin 
state: each high pin is recorded as high until the last pin goes low,
ensuring correctness and eliminating the need for timers to determine
the desired input.
*/

//Define the pin numbers for each pad (1 is base of index, 7 is pinkie)
const int ind1 = 2;
const int ind2 = 4;
const int ind3 = 6;
const int ind4 = 7;
const int ind5 = 8;
const int ind6 = 9;
const int ind7 = 12;

//Initialize the pin states
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 0;
int s7 = 0;

//States array
boolean ss[] = {0,0,0,0,0,0,0};
int sc_i = 0;


void setup(){
  //Set pins connected to pads to input
  pinMode(ind1, INPUT);
  pinMode(ind2, INPUT);
  pinMode(ind3, INPUT);
  pinMode(ind4, INPUT);
  pinMode(ind5, INPUT);
  pinMode(ind6, INPUT);
  pinMode(ind7, INPUT);

  //Open serial connection
  Serial.begin(9600);
}

void loop(){
  //Read the pin states
  s1 = digitalRead(ind1);
  s2 = digitalRead(ind2);
  s3 = digitalRead(ind3);
  s4 = digitalRead(ind4);
  s5 = digitalRead(ind5);
  s6 = digitalRead(ind6);
  s7 = digitalRead(ind7);
  
  //Update pin states if one is HIGH
  while(s1 || s2 || s3 || s4 || s5 || s6 || s7 == HIGH){
    
    //Update array based off of pin state
    if(s1 == HIGH){
      ss[0] = 1;
    }
    if(s2 == HIGH){
      ss[1] = 1;
    }
    if(s3 == HIGH){
      ss[2] = 1;
    }
    if(s4 == HIGH){
      ss[3] = 1;
    }
    if(s5 == HIGH){
      ss[4] = 1;
    }
    if(s6 == HIGH){
      ss[5] = 1;
    }
    if(s7 == HIGH){
      ss[6] = 1;
    }
    
    //Read pins again.
    s1 = digitalRead(ind1);
    s2 = digitalRead(ind2);
    s3 = digitalRead(ind3);
    s4 = digitalRead(ind4);
    s5 = digitalRead(ind5);
    s6 = digitalRead(ind6);
    s7 = digitalRead(ind7);
  }
  
  //Convert binary array into index for scancode array
  sc_i = 0;
  
  if(ss[0] == 1){
    sc_i += 1;
  }
  if(ss[1] == 1){
    sc_i += 2;
  }
  if(ss[2] == 1){
    sc_i += 4;
  }
  if(ss[3] == 1){
    sc_i += 8;
  }
  if(ss[4] == 1){
    sc_i += 16;
  }
  if(ss[5] == 1){
    sc_i += 32;
  }
  if(ss[6] == 1){
    sc_i += 64;
  }
  //This was a FOR loop. It is now one of the worst things I have ever written.
  
  
  //For debugging purposes only
  Serial.println(sc_i);
  //Seriously, don't use this in the actual code
  
  for(int i = 6; i >= 0; i--){
    ss[i] = 0;
  }
}
