#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int tmp = A0;
int LED = 3;
int BUZZER_PIN = 5;

#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_C5  523
#define NOTE_D5  587

#define REST 0

//melody
int melody[] = {
  REST, NOTE_D4,
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_D5,
  NOTE_C5,
  NOTE_A4,
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_F4, NOTE_GS4,
  NOTE_D4
};

int durations[] = {
  2, 4,
  4, 8, 4,
  2, 4,
  2,
  2,
  4, 8, 4,
  2, 4,
  1
};

//threshold
const int TEMP_LOW = 68;
const int TEMP_HIGH = 75;

//set up
void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Thermometer");
  delay(1000);
  lcd.clear();
}

//loop
void loop() {

  //read sensor
  int reading = analogRead(tmp);
  float voltage = reading * 5.0 / 1024.0;

  int tempC = (voltage - 0.5) * 100;
  int tempF = (tempC * 9.0 / 5.0) + 32;

  //display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("F: ");
  lcd.print(tempF);

  lcd.setCursor(0, 1);
  lcd.print("C: ");
  lcd.print(tempC);

  Serial.print("TempF: ");
  Serial.print(tempF);
  Serial.print(" | TempC: ");
  Serial.println(tempC);

  //alert mode
  if (tempF < TEMP_LOW || tempF > TEMP_HIGH) {

    // LED warning blink
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(150);

    // Play alert melody ONCE per loop cycle
    int size = sizeof(melody) / sizeof(melody[0]);

    for (int i = 0; i < size; i++) {

      int duration = 1000 / durations[i];

      tone(BUZZER_PIN, melody[i], duration);

      int pause = duration * 1.30;
      delay(pause);

      noTone(BUZZER_PIN);
    }
  }

  //normal mode
  else {

    digitalWrite(LED, LOW);
    noTone(BUZZER_PIN);
  }

  delay(500);
}
