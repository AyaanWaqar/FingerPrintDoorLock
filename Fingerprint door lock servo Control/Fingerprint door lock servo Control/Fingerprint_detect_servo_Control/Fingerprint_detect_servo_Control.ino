#include <Servo.h>
#include <Adafruit_Fingerprint.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 4);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);
int relay =8;
int led = 13;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Servo myServo; 
void setup()  
{
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  myServo.attach(12);
  myServo.write(0);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  while (!Serial);  
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  myServo.write(0);
}

void loop()                     // run over and over again
{
  lcd.clear();
  lcd.setCursor(0,0);
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  myServo.write(0);
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      lcd.print("Converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.print("Too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.print("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.print("Features Error");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.print("Features Error");
      return p;
    default:
      lcd.print("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    lcd.print("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.print("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    lcd.print("Did not find a match");
    return p;
  } else {
    lcd.print("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  lcd.print("Hello ");
  lcd.setCursor(2,1);
  lcd.print("FingerPrint ");
  lcd.print(finger.fingerID);
  myServo.write(90); Serial.println("lock  open"); 
  delay(5000); 
  digitalWrite(led, LOW);
  myServo.write(0); Serial.print("lock  close"); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
