// define BUTTONS
#define BUTTON 32
#define BUTTON2 14

// define ISD1820
const int REC = 27;  // pin 27 is used for recording
const int PLAY = 25; // pin 25 is used for playback-edge trigger

// define LED pins
#define LED1 = 15;
#define LED2 = 33;
#define LED3 = 0;
#define LED4 = 12;
#define LED5 = 18;
#define LED6 = 17;

// define number of led's
#define NumberOfLeds 6

uint8_t leds [] = { 15, 33, 0, 12, 18, 17 }; // list of all the leds in the array

#define EVENT_UPDATE_TIME 6000 // in milliseconds 
volatile unsigned long timingMillis = 0; // volatile will work with interrupts

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int brightnessON = 250;
int brightnessOFF = 0;

// define status to reset the loops
char status = 0;

// define button's statuses
int buttonState = 0;
int buttonState2 = 0;


void setup() {
  // begin serial communication
  Serial.begin(115200);

  // BUTTONS set up + built in resistor, no need to add any to the board
  pinMode(BUTTON, INPUT_PULLUP); //oznaczan domyslnie na pinie stan HIGH _PULLUP
  pinMode(BUTTON, INPUT_PULLUP); //oznaczan domyslnie na pinie stan HIGH _PULLUP

  // ISD1820 set up
  pinMode(REC, OUTPUT);
  pinMode(PLAY, OUTPUT);

  //LEDs set up
  for (int k = 0; k < NumberOfLeds; k++) {
    ledcAttachPin(leds[k], ledChannel);
  }

  ledcSetup (0, 5000, 8);
}


void loop() {

  // READ BUTTON VALUE
  int buttonState = digitalRead(BUTTON);

  // if button is pressed, start LED's and recording
  if (( buttonState == LOW ) && (status == 0)) {
    status = 1;
    Serial.println("button wciśnięty");

//    FADE_IN_OUT_LED ();
    LEDs_ON ();
    RECORDING ();
  }
  // if button is no pressed, LED's OFF
  else {

    ( buttonState == HIGH );
    Serial.println("button puszczony");

    LEDs_OFF ();
  }

  // RESET BUTTON STATE TO AVOID CONTINUOUS LOOP
  if (( buttonState == HIGH ) && (status == 1)) {
    status = 0;
  }

  // READ BUTTON2 VALUE
  int buttonState2 = digitalRead(BUTTON2);
  if (( buttonState2 == LOW ) && (status == 0)) {
    status = 1;
    Serial.println("button2 wciśnięty");

    LEDs_ON ();
    PLAYBACK ();

  }
  // RESET BUTTON STATE2 TO AVOID CONTINUOUS LOOP
  if (( buttonState2 == HIGH ) && (status == 1)) {
    status = 0;
  }
}

void FADE_IN_OUT_LED () {
  //BREATHING PATTERN
  
  // PWM FADE IN
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }
  // PWM FADE OUT
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }
}

void LEDs_ON () {

  //ALL LEDS ON
  for ( int i = 0; i < NumberOfLeds; i++ ) {
    ledcWrite(ledChannel, brightnessON);
  }
}

void LEDs_OFF () {

  //ALL LEDS OFF
  for ( int i = 0; i < NumberOfLeds; i++ ) {
    ledcWrite(ledChannel, brightnessOFF);
  }
}

void RECORDING () {

  // FULL RECORDING FUNCTION
  digitalWrite(REC, HIGH);
  Serial.println("REC + LED started");
  delay(5000);
  digitalWrite(REC, LOW);
  Serial.println("REC finished");
}

void PLAYBACK () {

  // FULL PLAYBACK FUNCTION
  digitalWrite(PLAY, HIGH);
  Serial.println("PLAY + LED started");
  delay(5000);
  digitalWrite(PLAY, LOW);
  Serial.println("PLAY finished");
}
