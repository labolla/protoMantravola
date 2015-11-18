#include <CapacitiveSensor.h>

int RED_PIN = 9;
int GREEN_PIN = 10;
int BLUE_PIN = 11;
int SPK_PIN = 12;

#define VALUE_MAX  0
#define VALUE_OFF  255
#define VALUE_STEP   5

#define R_IDX 0
#define G_IDX 1
#define B_IDX 2

#define  SOFT_BTN_THRESHOLD   100

// define class for LED display
class RGB_Led
{
  public:
  int pin[3];
  int value[3];
  int vote[3];

  RGB_Led(int r,int g,int b)
  {
    pin[R_IDX] = r;
    pin[G_IDX] = g;
    pin[B_IDX] = b;

    value[R_IDX] = value[G_IDX] = value[B_IDX] = VALUE_OFF;

    pinMode(pin[R_IDX], OUTPUT);
    pinMode(pin[G_IDX], OUTPUT);
    pinMode(pin[B_IDX], OUTPUT);
  }

  void voting(boolean red, boolean green, boolean blue)
  {
    if (red) vote[R_IDX]++;
    if (green) vote[G_IDX]++;
    if (blue) vote[B_IDX]++;
  }
  
  boolean update_values(void)
  {
    boolean ret = false;

    for (int i = R_IDX ; i <= B_IDX; i++)
    {
//      Serial.print(vote[i]);
//      Serial.print("\t");
      if (vote[i])
      {
        if (value[i] != VALUE_MAX)    value[i] = value[i] - VALUE_STEP;

        vote[i] = 0;
      }
      else
      {
        if (value[i] != VALUE_OFF)    value[i] = value[i] + VALUE_STEP;
      }

      if (value[i] != 255)
         ret = true;

//      Serial.print(value[i]);
//      Serial.print("\t");
      analogWrite(pin[i], value[i]);
    }
//    Serial.println();

    return ret;
  }
};

CapacitiveSensor HR_4_2 = CapacitiveSensor(2,4);
CapacitiveSensor LR_5_2 = CapacitiveSensor(2,5);
CapacitiveSensor Ce_6_2 = CapacitiveSensor(2,6);
CapacitiveSensor LL_7_2 = CapacitiveSensor(2,7);
CapacitiveSensor HL_8_2 = CapacitiveSensor(2,8);


RGB_Led  ledRGB(RED_PIN, BLUE_PIN, GREEN_PIN);


//int numTones = 10;
//int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};  //mid C C# D D# E F F# G G# A
int numTones = 5;
int tones[] = {261, 294, 330, 392, 440};  //mid C C# D D# E F F# G G# A

void setup() {
  Serial.begin(9600);
  //pinMode(SPK_PIN, OUTPUT);

  for (int i = 0; i < numTones; i++)
  {
    tone(SPK_PIN, tones[i]);
    delay(500);
  }

//  for (int i = 0; i < numTones; i++)
//  {
//    tone(SPK_PIN, tones[numTones - 1 - i]);
//    delay(500);
//  }
  noTone(SPK_PIN);
}

void loop() {
  long HR_value =  HR_4_2.capacitiveSensor(30);
  long LR_value =  LR_5_2.capacitiveSensor(30);
  long Ce_value =  Ce_6_2.capacitiveSensor(30);
  long LL_value =  LL_7_2.capacitiveSensor(30);
  long HL_value =  HL_8_2.capacitiveSensor(30);
  int pitch;

  //Serial.print(HR_value);
  //Serial.print("  ");
  //Serial.print(LR_value);
  //Serial.print("  ");
  //Serial.print(Ce_value);
  //Serial.print("  ");
  //Serial.print(LL_value);
  //Serial.print("  ");
  //Serial.println(HL_value);

  pitch = 0;
  if (HR_value > SOFT_BTN_THRESHOLD)
  {
   ledRGB.voting(true, false, false);
   pitch = tones[0];   //C
  }

  if (LR_value > SOFT_BTN_THRESHOLD)
  {
   ledRGB.voting(false, true, true);
   pitch = tones[3];   //G
  }

  if (LL_value > SOFT_BTN_THRESHOLD)
  {
    ledRGB.voting(true, false, true);
    pitch = tones[4];   //A
  }

  if (HL_value > SOFT_BTN_THRESHOLD)
  {
    ledRGB.voting(false, false, true);  
    pitch = tones[1];   //D
  }

  if (Ce_value > SOFT_BTN_THRESHOLD)
  {
      ledRGB.voting(false, true, false);  
      pitch = tones[2];   //E  
  }

  boolean isLedOn = ledRGB.update_values();

  Serial.println(isLedOn);
  if (pitch)
     tone(SPK_PIN, pitch);
  else
     noTone(SPK_PIN);
  
  delay(50);

}
