//for ultrasonic sensor, tree
int treeTrigPin = A1;
int treeEchoPin = A0;
int treeMaxDistance = 175;
int treeSensor[] = {treeTrigPin, treeEchoPin, treeMaxDistance};

//for ultrasonic sensor, rubbish bin
int binTrigPin = A2;
int binEchoPin = A3;
int binMaxDistance = 23;
int binSensor[] = {binTrigPin, binEchoPin, binMaxDistance};

//ultrasonic sensor, bin depth
int depthTrigPin = A4;
int depthEchoPin = A5;
int depthMaxDistance = 15;
int depthSensor[] = {depthTrigPin, depthEchoPin, depthMaxDistance};

int duration, distance;
int depthDistance;

//x=0 is the default value sent over serial communications: it means no users under tree
byte x = 0;

void setup()
{
  //Serial communication setup. Serial.write() to green MEGA(inner lights), Serial3.write() to blue lights
  Serial.begin(9600);
  Serial3.begin(9600);

  //ultrasonic sensor, tree
  pinMode(treeTrigPin, OUTPUT);
  pinMode(treeEchoPin, INPUT);

  //ultrasonic sensor, bin
  pinMode(binTrigPin, OUTPUT);
  pinMode(binEchoPin, INPUT);

  //ultrasonic sensor, bin depth
  pinMode(depthTrigPin, OUTPUT);
  pinMode(depthEchoPin, INPUT);
}

//give distanceMeasurer an ultrasonic sensor and associated distance to return whether object is within distance.
bool distanceMeasurer(int selectedSensor[]){
  digitalWrite(selectedSensor[0], LOW);
  delayMicroseconds(2);
  digitalWrite(selectedSensor[0], HIGH);
  delayMicroseconds(2);
  digitalWrite(selectedSensor[0], LOW);
  
  duration = pulseIn(selectedSensor[1], HIGH);
  distance = (duration*0.034)/2;
  if (distance<selectedSensor[2]){
    return true;
  }
  return false;
}

//returns distance in terms of length
int lengthDistanceMeasurer(int selectedSensor[]){
  digitalWrite(selectedSensor[0], LOW);
  delayMicroseconds(2);
  digitalWrite(selectedSensor[0], HIGH);
  delayMicroseconds(2);
  digitalWrite(selectedSensor[0], LOW);
  
  duration = pulseIn(selectedSensor[1], HIGH);
  distance = (duration*0.034)/2;
  return distance;
}

void loop(){

  if (distanceMeasurer(binSensor)){
    depthDistance = lengthDistanceMeasurer(depthSensor);
    //IF DEPTH DISTANCE<=10, BIN IS VERY FULL
    if (depthDistance<=10){
      //DEFAULT BIN LIGHT SHOW: Serial 2
      Serial.println("FILLED BIN LIGHT SHOW");
      Serial.write(4);
      Serial3.write(4);
      delay(100);
    }
    else if ((depthDistance<20) && (depthDistance>=10)){
      //HALF-FILLED LIGHT SHOW: Serial 3
      Serial.println("HALF-FILLED BIN LIGHT SHOW");
      Serial.write(3);
      Serial3.write(3);
      delay(100);
    }
    else if ((depthDistance<=60) && (depthDistance>=20)){
      //FULL BIN LIGHT SHOW: Serial 4
      Serial.println("NOT FILLED BIN LIGHT SHOW");
      Serial.write(2);
      Serial3.write(2);
      delay(100);
    } 
  }
  else{
    if (distanceMeasurer(treeSensor)){
      if (distanceMeasurer(treeSensor)){
      //user light show: serial 1
        Serial.println("USER LIGHT SHOW");
        Serial.write(1);
        Serial3.write(1);
        delay(100);
      }
    }
    else{
      //completely no light show: Serial 0
      Serial.println("NO LIGHT SHOW");
      Serial.write(0);
      Serial3.write(0);
      delay(100);
    }
  }
}