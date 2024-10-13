int motor1pin1 = 2;
int motor1pin2 = 3;
int motor1speed = 9;
int motor2pin1 = 4;
int motor2pin2 = 5;
int motor2speed = 10;
int r = A0;
int mr = A1;
int m = A2;
int ml = A3;
int l = A4;
int spdl = 90 ;
int spdr = 90 ;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor1speed, OUTPUT); 
  pinMode(motor2speed, OUTPUT);
  Serial.begin(9600);
  pinMode(r, INPUT);
  pinMode(mr, INPUT);
  pinMode(m, INPUT);
  pinMode(ml, INPUT);
  pinMode(l, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
/*
 Serial.print("Analog Reading R=");
 Serial.println(digitalRead(r));
 Serial.print("Analog Reading RM=");
 Serial.println(digitalRead(mr));
 Serial.print("Analog Reading M=");
 Serial.println(digitalRead(m));
 Serial.print("Analog Reading LM =");
 Serial.println(digitalRead(ml));
 Serial.print("Analog Reading L=");
 Serial.println(digitalRead(l));
 delay(2000);
 
if (digitalRead(r) == 1 && digitalRead(mr) == 0 && digitalRead(m) == 0 && digitalRead(ml) == 0 && digitalRead(l) == 1) {
GoStraight();
}

/*
else if (digitalRead(r) == 0 && digitalRead(mr) == 0 && digitalRead(m) == 1 && digitalRead(ml) == 1 && digitalRead(l) == 1 ){
GoRight(); 
}
else if (digitalRead(r)  == 1 && digitalRead(mr) == 1 && digitalRead(m) == 1 && digitalRead(ml) == 0 && digitalRead(l) == 0 ){
GoLeft();
}
*/


//STRAIGHT-------------------------------------------------------------------------------------------------------------------------

if ((digitalRead(mr) == 1 && digitalRead(m) == 0 && digitalRead(ml) == 1 )) 
{
GoStraight();

}
 else if (( digitalRead(r) == 0 && digitalRead(mr) == 0 && digitalRead(m) == 0 && digitalRead(ml) == 0 && digitalRead(l) == 0 )){
  GoStraight();

}

/*
//if ((digitalRead(mr) == 0 && digitalRead(ml) == 0) //|| (digitalRead(mr) == 0 && digitalRead(m) == 0 && digitalRead(ml) == 0 ))
//{
//GoStraight();
//}
//if (digitalRead(mr) == 0 && digitalRead(m) == 0 && digitalRead(ml) == 0 ){
//GoStraight();
//}
*/
//RIGHT----------------------------------------------------------------------------------------------------------------------------
if ((digitalRead(mr) == 0 && digitalRead(ml) == 1 ) || (digitalRead(mr) == 0 && digitalRead(m) == 0 ) || (digitalRead(r) == 0 && digitalRead(mr) == 0 ))
{
GoRight(); 
}
//if (digitalRead(mr) == 0 && digitalRead(m) == 0 )
//{
//GoRight(); 
//}

//else if (digitalRead(r) == 0 && digitalRead(mr) == 0 ){
//GoRight(); 
//}

//LEFT-----------------------------------------------------------------------------------------------------------------------------
if ((digitalRead(mr)  == 1 && digitalRead(ml) == 0 ) || (digitalRead(ml)  == 0 && digitalRead(m) == 0 ) || (digitalRead(l)  == 0 && digitalRead(ml) == 0 ))
{
GoLeft();
}
//if (digitalRead(ml)  == 0 && digitalRead(m) == 0 )
//{
//GoLeft();
//}
/*
else if (digitalRead(l)  == 0 && digitalRead(ml) == 0 ){
GoLeft();
}
if (digitalRead(r) == 1 && digitalRead(mr) == 1 && digitalRead(m) == 1 && digitalRead(ml) == 1 && digitalRead(l) == 1){
 GoLeft();
}*/

}


void GoStraight ()
{
  digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,HIGH);
  digitalWrite(motor2pin2,LOW);
  analogWrite(motor1speed,spdr);
  analogWrite(motor2speed,spdl);

  }

void GoRight()
{
  digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,LOW);
  digitalWrite(motor2pin2,HIGH);
  analogWrite(motor1speed,65);
  analogWrite(motor2speed,65);

  }

void GoLeft()
{
  digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2,HIGH);
  digitalWrite(motor2pin1,HIGH);
  digitalWrite(motor2pin2,LOW);
  analogWrite(motor1speed,65);
  analogWrite(motor2speed,65);

  }
