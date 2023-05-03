#define turn_start 8

#include <AccelStepper.h>
#include <Servo.h>
// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, 5, 11);

int pos = -10000; //10.000° um sicher zu stellen das der motor lang genug dreht
int posmapped = 10*pos*2.65; //stepper dreht das ritzel, relevant ist jedoch die drehung vom Tisch (Übersetzungsverhältnis & umrechnung für die Library)
unsigned long myTime;

Servo servo;


void setup()
{ 
  Serial.begin(9600);
  pinMode(turn_start, INPUT);
  pinMode(Button_break_on, INPUT_PULLUP); 
  pinMode(Button_break_off, INPUT_PULLUP);  
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(2000);

  servo.attach(7);

}

void loop() {
  myTime = millis();
  bool temp_start = false;

  if(digitalRead(turn_start)){
    temp_start = true;
  }
  else{
    temp_start = false;
  }

  while(temp_start){

  if(digitalRead(turn_start)){
    temp_start = true;
  }
  else{
    temp_start = false;
  }
  //Stepper dreht solange bis "posmapped" erreicht ist oder kein Signal von dem Steuergerät kommt

  servo.write(55); //Servo ist eingefahren
  while(millis() < myTime + 200){} //sicherstellung das bremse eingefahren ist
  stepper.moveTo(posmapped);
  stepper.run();
  
  }
  servo.write(0); // servo ist ausgefahren

}
