//array corresponding to digital pin number on the arduino
int mypinArray[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
//track the state of the pins
int pinstates[12];

//potentiometers
int pitchSlide1;
int pitchSlide2;
int pitchSlide3;
int pitchSlide4;
int modWheel;
int pitchBend;

//potentiometers
int pitchSlide1Ref;
int pitchSlide2Ref;
int pitchSlide3Ref;
int pitchSlide4Ref;
int modWheelRef;
int pitchBendRef;

//potentiometers
int pitchSlide1Avg;
int pitchSlide2Avg;
int pitchSlide3Avg;
int pitchSlide4Avg;
int modWheelAvg;
int pitchBendAvg;

int potVal = 0;
int mappedPotVal = 0;
int prevPotVal = 0; 

int i = 0;
int tempDigitalInput;
int note;
int previousstate[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};


void setup() {
  //  Set MIDI baud rate:
  Serial.begin(31250);
for (i = 0; i < 12; i++)
  {
  pinMode(mypinArray[i], INPUT);
  }
}

//button control
void loop() 
{
  
  //iterate and assign digital pins to notes
  for (i = 0; i < 12; i++) {
    if (i==0){
    note = 60;}
    if (i==1){
    note = 62;}
    if (i==2){
    note = 64;}
    if (i==3){
    note = 65;}
    if (i==4){
    note = 67;}
    if (i==5){
    note = 69;}
    if (i==6){
    note = 71;}
    if (i==7){
    note = 72;}
    if (i==8){
    note = 74;}
    if (i==9){
    note = 76;}
    if (i==10){
    note = 77;}
    if (i==11){
    note = 79;}
    //read pins, compare states
    tempDigitalInput = digitalRead(mypinArray[i]);
    if (tempDigitalInput == HIGH) {
    pinstates[i] = HIGH; }
    else {
    pinstates[i] = LOW; 
    }  
    if (pinstates[i] == HIGH && previousstate[i] == LOW) {
    noteOn(144, note, 120);
    }
    else if (pinstates[i] == LOW && previousstate[i] == HIGH) {
    noteOn(144, note, 0);}
    else {
    }
    previousstate[i] = tempDigitalInput;  
    delay(1);
   }
 
 //assign pots to analog ports in arduino and assign range corresponding to midi data
 //read analog pins
  pitchSlide1 = analogRead(0);
  pitchSlide1Avg = (pitchSlide1 * 0.5) + (pitchSlide1Avg * 0.5);
  pitchSlide1 = map(pitchSlide1Avg, 0, 1023, 0, 127);
  
  pitchSlide2 = analogRead(1);
  pitchSlide2Avg = (pitchSlide2 * 0.5) + (pitchSlide2Avg * 0.5);
  pitchSlide2 = map(pitchSlide2Avg, 0, 1023, 0, 127);
  
  pitchSlide3 = analogRead(2);
  pitchSlide3Avg = (pitchSlide3 * 0.5) + (pitchSlide3Avg * 0.5);
  pitchSlide3 = map(pitchSlide3Avg, 0, 1023, 0, 127);
  
  pitchSlide4 = analogRead(3);
  pitchSlide4Avg = (pitchSlide4 * 0.5) + (pitchSlide4Avg * 0.5);
  pitchSlide4 = map(pitchSlide4Avg, 0, 1023, 0, 127);
  
  modWheel = analogRead(4);
  modWheelAvg = (modWheel * 0.5) + (modWheelAvg * 0.5);
  modWheel = map(modWheelAvg, 0, 1023, 0, 127);
  
  pitchBend = analogRead(5);
  pitchBendAvg = (pitchBend * 0.5) + (pitchBendAvg * 0.5);
  pitchBend = map(pitchBendAvg, 0, 1023, 0, 127);
  
  if (pitchSlide1 != pitchSlide1Ref)
  {
    pitchSlider(pitchSlide1);
    pitchSlide1Ref=pitchSlide1;
   
  }
  
  if (pitchSlide2 != pitchSlide2Ref)
  {
    pitchSlider1(pitchSlide2);
    pitchSlide2Ref=pitchSlide2;
  }
  
  if (pitchSlide3 != pitchSlide3Ref)
  {
    pitchSlider2(pitchSlide3);
    pitchSlide3Ref=pitchSlide3;
  }
  
  if (pitchSlide4 != pitchSlide4Ref)
  {
    pitchSlider3(pitchSlide4);
    pitchSlide4Ref=pitchSlide4; 
  }
 
  if(modWheel != modWheelRef)
    {
      modulation(modWheel);
      modWheelRef = modWheel;
    }
  
  if(pitchBend != pitchBendRef)
  {
    pitchBendWheel(pitchBend);
    pitchBendRef = pitchBend;
  }
 
  
}


//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(byte cmd, byte data1, byte data2) 
{
  Serial.write(cmd);
  Serial.write(data1);
  Serial.write(data2);
}

void modulation(byte modVal)
{
  Serial.write(176);
  Serial.write(10);
  Serial.write(modVal);
  delay(1);
}

void pitchBendWheel(byte bendVal)
{
  Serial.write(176);
  Serial.write(11);
  Serial.write(bendVal);
  delay(1);
}

void pitchSlider (byte slideVal)
{
  Serial.write(176);
  Serial.write(12);
  Serial.write(slideVal);
}

void pitchSlider1 (byte slideVal)
{
  Serial.write(176);
  Serial.write(13);
  Serial.write(slideVal);
}

void pitchSlider2 (byte slideVal)
{
  Serial.write(176);
  Serial.write(14);
  Serial.write(slideVal);
}

void pitchSlider3 (byte slideVal)
{
  Serial.write(176);
  Serial.write(15);
  Serial.write(slideVal);
}

