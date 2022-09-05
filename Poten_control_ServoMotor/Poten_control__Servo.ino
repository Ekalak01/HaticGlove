#include <M5StickCPlus.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_ADS1X15.h>

#define I2C_SDA 32
#define I2C_SCL 33

Adafruit_ADS1115 ads;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40,Wire);

#define SERVOMIN  150
#define SERVOMAX  620

uint8_t servonum = 0;

void setup() {
  M5.begin();
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
  Serial.println("ADS1115 Test");
  Serial.println("4 channel Servo test!");
  M5.Lcd.setTextSize(3);  // Set font size.  设置字体大小
  M5.Lcd.setRotation(3);  // Rotate the screen. 将屏幕旋转
    // LCD display.  Lcd显示
  M5.Lcd.println("Servo Test");
  M5.Lcd.println("ADS1115 Test");

  pwm.begin();
  pwm.setPWMFreq(60); 

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

}

void loop() {
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  
  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
  Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
  Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");

  //int Vread=0;
  //Vread = analogRead(26);
  //Serial.println(Vread);
  int16_t x1, x2, x3, x4;
  x1 = map(adc0,0,26850,0,180);
  x2 = map(adc1,0,26850,0,180);
  x3 = map(adc2,0,26850,0,180);
  x4 = map(adc3,0,26850,0,180);
  pwm.setPWM(0, 0, angleToPulse(x1));
  pwm.setPWM(1, 0, angleToPulse(x2));
  pwm.setPWM(2, 0, angleToPulse(x3));
  pwm.setPWM(3, 0, angleToPulse(x4));
}

int angleToPulse(int ang){
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  //Serial.print("Angle: ");Serial.print(ang);Serial.print(" pulse: ");Serial.println(pulse);
  return pulse;
}
