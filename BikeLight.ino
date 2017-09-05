const byte led1 = 6;
const byte led2 = 11;
const byte led3 = 10;
const byte led4 = 9;
const byte button = 3;
const byte potPin = 0;
int value = 0;
int value1 = 0;
int counter = 0;
int potState = 0;
int time1 = 0;
int time2 = 0;
int ledState1 = HIGH;
int ledState2 = 0;
int states[] = {HIGH, LOW, LOW, LOW};
int var = 0;
int statesSwitch[4];
int countTime1 = 0;
int countTime2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  value1 = digitalRead(button);
  countTime2 = millis();
  
  if (value<value1) {
    countTime2 = millis();
    if (countTime2 - countTime1 > 100) {
      Serial.println(countTime2);
      counter++;
      countTime1 = countTime2; } }

  value = value1;
    
  counter = counter%6;
  
  switch (counter) {
    case 1:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      break;
    case 2:
      time2 = millis();
      if (time2-time1 >= 150){
        time1 = time2;

        if (ledState1 == LOW) 
          ledState1 = HIGH;
        else 
          ledState1 = LOW; }
          
      digitalWrite(led1, ledState1);
      digitalWrite(led2, ledState1);
      digitalWrite(led3, ledState1);
      digitalWrite(led4, ledState1);
      break;
    case 3:
      time2 = millis();
      if (time2-time1 >= 80){
        time1 = time2;

        var = states[3];
        states[3] = states[2];
        states[2] = states[1];
        states[1] = states[0];
        states[0] = var; }
       
      digitalWrite(led1, states[0]);
      digitalWrite(led2, states[1]);
      digitalWrite(led3, states[2]);
      digitalWrite(led4, states[3]);
    
      break;
    case 4:
      time2 = millis();
      if (time2-time1 >= 200){
        time1 = time2;

        if (ledState1 == LOW) {
          ledState1 = HIGH;
          ledState2 = LOW; }
        else {
          ledState1 = LOW;
          ledState2 = HIGH; }
        
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
    case 5:
      potState = analogRead(potPin);
      potState = map(potState, 0, 1023, 0, 255); //maps pot input of 0 to 1023 to led output of 0 to 255
      analogWrite(led1, potState);
      analogWrite(led2, potState);
      analogWrite(led3, potState);
      analogWrite(led4, potState);
      break;
    default:
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      break;  
  }
  
}

      
