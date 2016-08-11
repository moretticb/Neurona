/////////////////////////////////////////////////////////////////////////////////
//
//  ColorSensor.ino - Color sensor prototype using artificial neural networks
//  Developed by Caio Benatti Moretti <www.moretticb.com>
//  More details at:
//  http://www.moretticb.com/blog/color-sensor-prototype-using-neural-networks/
//
/////////////////////////////////////////////////////////////////////////////////

#include <Neurona.h>
#include <LiquidCrystal.h>

#define BACKLIGHT 7
#define BTN_PIN 6
#define LDR_PIN 0
#define THRESHOLD 2000
#define LED_DELAY 500

#define RECOGNIZE 1
#define CALIBRATE 2
#define CALIBRATE_B 3
#define CALIBRATE_W 4

#define NET_INPUTS 3
#define NET_OUTPUTS 10
#define NET_LAYERS 2

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int lastState=0, op=0;
unsigned long pressTime = 0;

int rgb[] = {8, 9, 10}; //led pins
int input[] = {0, 0, 0}; //RGB values
double netInput[] = {-1.0, 0.0, 0.0, 0.0};
int calib[3][2] = {{329, 778}, {166, 569}, {140, 528}};

char *colors[] = {"BLACK", "RED", "GREEN", "BLUE", "YELLOW", "BROWN", "PURPLE", "ORANGE", "PINK", "WHITE"};

int layerSizes[] = {6, NET_OUTPUTS, -1};
int offset=0, iOffset=0, yOffset=0;
double PROGMEM const initW[] = {2.753086,-11.472257,-3.311738,16.481226,19.507006,20.831778,7.113330,-6.423491,1.907215,6.495393,-27.712126,26.228203,-0.206367,-5.724560,-22.278070,30.065610,6.139262,-10.814282,28.513130,-9.784946,6.467021,0.055005,3.730361,4.145092,2.479019,0.013003,-3.582416,-16.364391,14.133357,-5.089288,1.637492,5.894826,1.415764,-3.315533,14.814289,-20.906571,-1.568656,1.917658,4.910184,4.039419,-10.848469,-5.641680,-4.132432,10.711442,3.759935,19.507702,17.728724,-3.210244,-2.476992,8.988450,5.196827,2.636043,17.357207,2.005429,11.713386,-5.453253,-6.940325,10.752005,0.666605,-7.266082,-3.587120,-9.921817,-12.682059,-15.456143,-13.740927,0.508265,15.179410,-11.143178,-19.085120,1.251235,22.006491,-4.227328,-0.444516,3.589025,0.649661,13.675598,-13.026884,-11.229070,-15.300703,-1.718191,6.737973,-28.176802,-2.505471,5.197970,7.007983,-2.869269,3.650349,18.029204,4.098356,10.481188,-2.566311,9.927770,2.344936,4.524327};

MLP mlp(NET_INPUTS,NET_OUTPUTS,layerSizes,MLP::LOGISTIC,initW,true);

void setup(){
  lcd.begin(16, 2);
  pinMode(BACKLIGHT, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  
  for(int i=0;i<3;i++){
    pinMode(rgb[i], OUTPUT);
    digitalWrite(rgb[i], HIGH);
  }
  
  digitalWrite(BACKLIGHT, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("- Color Sensor -");
  lcd.setCursor(0, 1);
  lcd.print("Caio B. Moretti");
  delay(2000);
}

void loop(){
  checkListeners();
  lcd.setCursor(0, 0);
  if(op==CALIBRATE){
    lcd.print("- CALIBRATION  -");
    lcd.setCursor(0, 1);
    lcd.print("Show BLACK color");
    for(int i=0;i<3;i++){
      calib[i][0] = -1;
      calib[i][1] = -1;
    }
  } else if(op==CALIBRATE_W || op==CALIBRATE_B){
    if(calib[0][0]==-1 && op==CALIBRATE_B || calib[0][1]==-1 && op==CALIBRATE_W){
      getRGB(1);
      for(int i=0;i<3;i++)
        calib[i][op-CALIBRATE_B] = input[i];
      lcd.setCursor(0, 1);
      lcd.print("Show WHITE color");
    }
  }else if(op==RECOGNIZE){
    lcd.print("Recognizing...  ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    
    getRGB(0);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    for(int i=0;i<3;i++){
      lcd.print(input[i]);
      if(i<2)
        lcd.print(" / ");
      netInput[i+1] = (double)input[i]/255.0;
    }
    lcd.setCursor(0, 1);
    lcd.print(colors[mlp.getActivation(netInput)]);
    delay(5000);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("PRESS- Recognize");
    lcd.setCursor(0, 1);
    lcd.print("HOLD - Calibrate");
  }
  if(op==4 || op == 1)
    op=0;
}

void checkListeners(){
  int pressed = digitalRead(BTN_PIN);
  if(lastState != pressed){
    lastState = pressed;
    if(pressed)
      onPress();
    else
      onRelease();
  }
}

void onPress(){
  pressTime = millis();
}

void onRelease(){
  pressTime = millis()-pressTime;
  if(op==0){
    if(pressTime < THRESHOLD){
      op=RECOGNIZE;
    }else{
      op=CALIBRATE;
    }
  } else if(op==CALIBRATE){
    op=CALIBRATE_B;
  } else if(op==CALIBRATE_B){
    op=CALIBRATE_W;
  }
}

void getRGB(int calibration){
  for(int i=0;i<3;i++){
    digitalWrite(rgb[i], LOW); //ligar
    delay(LED_DELAY);
    
    input[i] = analogRead(LDR_PIN);
    if(!calibration){
      input[i] = map(input[i], calib[i][0], calib[i][1], 0, 255);
      input[i] = input[i]<0?0:input[i]>255?255:input[i];
    }
    
    digitalWrite(rgb[i], HIGH); //desligar
    delay(LED_DELAY);
  }
}
