//initialising colours
int baseColour[] = {255,255,255};
int sakuraColour[] = {255,20,147};
int lightPink[] = {255,182,193};
int noColour[] = {0,0,0};
int redColour[] = {255,0,0};
int orangeColour[] = {255,165,0};
int yellowColour[] = {255,215,0};

//4 LEDs, outer level, left to right
//this shows most LED pins available for use!
int analogPinArray[] = {A0,A1,A2,A3,A4,A5,A7,A8,A9,A10,A11,A12,13,12,11,10,9,8,7,6,5,4,3,2};
int analogPinArrayRevamped[][3]= {{A0,A1,A2},{A3,A4,A5},{A7,A8,A9},{A10,A11,A12},{13,12,11},{10,9,8},{7,6,5},{4,3,2}};
int lengthPinArray = 8;
int pinCount = 24;
int innerArrayLength = 3;

//pins
int pin1[] = {A0,A1,A2};
int pin2[] = {A3,A4,A5};
int pin3[] = {A7,A8,A9};
int pin4[] = {A10,A11,A12};
int pin5[] = {13,12,11};
int pin6[] = {10,9,8};
int pin7[] = {7,6,5};
int pin8[] = {4,3,2};

//byte data received
byte data = 0;
  
void setup(){

  //Setup code, serial communications
  Serial.begin(9600);
  Serial3.begin(9600);

  //pin setup, LEDs
  for (int i=0; i<pinCount; i++){
    pinMode(analogPinArray[i], OUTPUT);
  }
}

//function that changes the colour of lights for a selected pin
void changeLights(int selectedPin[], int RGBColour[]){
  analogWrite(selectedPin[0],RGBColour[0]);
  analogWrite(selectedPin[1],RGBColour[1]);
  analogWrite(selectedPin[2],RGBColour[2]);
}

//no light show
void baseLightShow(){
  for (int i=0; i<lengthPinArray; i++){
    changeLights(analogPinArrayRevamped[i], noColour);
  }
}

//random light show
void randomLightShow(){
  int counter = 8;
  for (int i=0; i<counter; i++){
    changeLights(analogPinArrayRevamped[random(0,8)], sakuraColour);
    delay(500);
  }
}

//RANDOM LIGHT SHOW DELETE PLS
void RANDOMbinLightShow(){
  for (int i=0; i<lengthPinArray; i++){
    int colourToChange[] = {random(0,255),random(0,255),random(0,255)};
    int timeDelay = random(100,2000);
    changeLights(analogPinArrayRevamped[i], redColour);
    delay(timeDelay);
  }
}

void waveBinLightShow(int timeDelay, int colourToChange[]){
  for (int i=0; i<lengthPinArray; i++){
    changeLights(analogPinArrayRevamped[i], noColour);
  }
  changeLights(analogPinArrayRevamped[7], lightPink);
  changeLights(analogPinArrayRevamped[6], lightPink);
  delay(timeDelay);
  changeLights(analogPinArrayRevamped[5], lightPink);
  changeLights(analogPinArrayRevamped[4], lightPink);
  changeLights(analogPinArrayRevamped[3], lightPink);
  delay(timeDelay);
  changeLights(analogPinArrayRevamped[2], lightPink);
  changeLights(analogPinArrayRevamped[1], lightPink);
  changeLights(analogPinArrayRevamped[0], lightPink);
  delay(timeDelay);
  delay(timeDelay*2);
  for (int i=0; i<lengthPinArray; i++){
    changeLights(analogPinArrayRevamped[i], noColour);
  }
}

void colouredBinLightShow(int colourToChange[]){
   for (int i=0; i<lengthPinArray; i++){
    changeLights(analogPinArrayRevamped[i], colourToChange);
  }
}

//user light show
void userLightShow(){
   for (int i=0; i<lengthPinArray; i++){
    changeLights(analogPinArrayRevamped[i], sakuraColour);
  }
}

void loop() {
  if (Serial3.available()>0){
    int x = Serial3.read();
    data = x;
  }
  
  if (data==1) {
    Serial.println("USER LIGHT SHOW");
    userLightShow();
  }
  else if (data==2) {
    Serial.println("NOT FILLED RUBBISH LIGHT SHOW");
    colouredBinLightShow(redColour);
  }
  else if (data==3){
    Serial.println("HALF-FILLED FIGHT SHOW");
    colouredBinLightShow(orangeColour);
  }
  else if (data==4){
    Serial.println("FILLED LIGHT SHOW");
    colouredBinLightShow(yellowColour);
  }
  else if (data==0){
    Serial.println("NO USER");
    colouredBinLightShow(noColour);
  }
}
