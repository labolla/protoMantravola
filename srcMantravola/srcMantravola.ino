#include <CapacitiveSensor.h>

int RED_PIN = 9;
int GREEN_PIN = 10;
int BLUE_PIN = 11;

#define VALUE_MAX  0
#define VALUE_OFF  255
#define VALUE_STEP   5

#define R_IDX 0
#define G_IDX 1
#define B_IDX 2

#define  SOFT_BTN_THRESHOLD   400

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
  
  void update_values()
  {
    for (int i = R_IDX ; i <= B_IDX; i++)
    {
      Serial.print(vote[i]);
      Serial.print("\t");
      if (vote[i])
      {
        if (value[i] != VALUE_MAX)    value[i] = value[i] - VALUE_STEP;

        vote[i] = 0;
      }
      else
      {
        if (value[i] != VALUE_OFF)    value[i] = value[i] + VALUE_STEP;
      }

      Serial.print(value[i]);
      Serial.print("\t");
      analogWrite(pin[i], value[i]);
    }
    Serial.println();
  }
};

CapacitiveSensor HR_4_2 = CapacitiveSensor(2,4);
CapacitiveSensor LR_5_2 = CapacitiveSensor(2,5);
CapacitiveSensor Ce_6_2 = CapacitiveSensor(2,6);
CapacitiveSensor LL_7_2 = CapacitiveSensor(2,7);
CapacitiveSensor HL_8_2 = CapacitiveSensor(2,8);


RGB_Led  ledRGB(RED_PIN, BLUE_PIN, GREEN_PIN);


void setup() {
  Serial.begin(9600);
}

void loop() {
  long HR_value =  HR_4_2.capacitiveSensor(30);
  long LR_value =  LR_5_2.capacitiveSensor(30);
  long Ce_value =  Ce_6_2.capacitiveSensor(30);
  long LL_value =  LL_7_2.capacitiveSensor(30);
  long HL_value =  HL_8_2.capacitiveSensor(30);

  if (HR_value > SOFT_BTN_THRESHOLD)
  {
   ledRGB.voting(true, false, false);     
  }

  if (LR_value > SOFT_BTN_THRESHOLD)
  {
   ledRGB.voting(false, true, true);
  }

  if (LL_value > SOFT_BTN_THRESHOLD)
  {
    ledRGB.voting(true, false, true);    
  }

  if (HL_value > SOFT_BTN_THRESHOLD)
  {
    ledRGB.voting(false, false, true);  
  }

  if (Ce_value > SOFT_BTN_THRESHOLD)
  {
      ledRGB.voting(false, true, false);  
  }

  ledRGB.update_values();
  
  delay(10);

}
