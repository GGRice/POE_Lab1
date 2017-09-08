//Defining pins for LEDs, button, and POT
const byte led1 = 6;
const byte led2 = 11;
const byte led3 = 10;
const byte led4 = 9;
const byte button = 3;
const byte potPin = 0;

//Defining initial states
int value, value1, counter, time1, time2, countTime1, countTime2, var = 0;
int ledState1 = HIGH; //HIGH, or 1, turns light on
int ledState2 = 0; //LOW, or 0, turns light off
int states[] = {HIGH, LOW, LOW, LOW};
int statesSwitch[4];
int potState = 0;

void setup() {
  Serial.begin(9600); //"sets date rate in bits per second for sereal data transmission"
 
 //initializes pins as inputs (POT) or outputs (LEDs)
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  value1 = digitalRead(button);
  countTime2 = millis(); //creating clock to keep track fo time sense start
  
  if (value<value1) { //if button state goes from 0 to 1, aka is pressed
    countTime2 = millis(); //start another clock here
    if (countTime2 - countTime1 > 100) { //if 100 milliseconds has passed, aka the first clock is 100 larger than the second clock
                                         //This ensure that button won't accidentaly register multiple clicks with one press
      counter++; //tells how many times button was pressed
      countTime1 = countTime2; 
    }
  }

  value = value1; //updates the state of the button
    
  counter = counter%6; //determines which light state case should be run
  
  switch (counter) {
    case 1: //all lights on
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      break;
    case 2: //all lights blinking
      time2 = millis();
      if (time2-time1 >= 150){ //switch state every 150 milliseconds
        time1 = time2;

        if (ledState1 == LOW) //determine if lights are on or off to determine new state
          ledState1 = HIGH;
        else 
          ledState1 = LOW; 
      }
          
      digitalWrite(led1, ledState1);
      digitalWrite(led2, ledState1);
      digitalWrite(led3, ledState1);
      digitalWrite(led4, ledState1);
      break;
    case 3: //scrolling lights
      time2 = millis();
      if (time2-time1 >= 80){ //switch state every 80 milliseconds
        time1 = time2;

        var = states[3]; //turn one light after another on then off, create scrolling effect
        states[3] = states[2];
        states[2] = states[1];
        states[1] = states[0];
        states[0] = var; 
      }
       
      digitalWrite(led1, states[0]);
      digitalWrite(led2, states[1]);
      digitalWrite(led3, states[2]);
      digitalWrite(led4, states[3]);
    
      break;
    case 4: //alternating every other on/off (1&3 same state, 2&4 same state
      time2 = millis();
      if (time2-time1 >= 200){ //state change every 200 milliseconds
        time1 = time2;

        if (ledState1 == LOW) { //change two state, state of LED1&3 and opposite state of LED2&4
          ledState1 = HIGH;
          ledState2 = LOW; 
        }
        else {
          ledState1 = LOW;
          ledState2 = HIGH; 
        }

        //hold states in an array
        statesSwitch[0] = ledState2;
        statesSwitch[1] = ledState1;
        statesSwitch[2] = ledState2;
        statesSwitch[3] = ledState1;
      }
       
      digitalWrite(led1, statesSwitch[0]);
      digitalWrite(led2, statesSwitch[1]);
      digitalWrite(led3, statesSwitch[2]);
      digitalWrite(led4, statesSwitch[3]);
      break;
      break; 
    case 5: //all lights on, use POT to determine brightness of lights
      potState = analogRead(potPin); //reads POT state
      potState = map(potState, 0, 1023, 0, 255); //maps POT input of 0 to 1023 to led output of 0 to 255
      analogWrite(led1, potState);
      analogWrite(led2, potState);
      analogWrite(led3, potState);
      analogWrite(led4, potState);
      break;
    default: //all lights off
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      break;  
  }
  
}
