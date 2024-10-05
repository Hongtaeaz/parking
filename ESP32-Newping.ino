#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define TRIG_PIN1  2  // Pin trig ของเซนเซอร์อัลตราโซนิกตัวที่ 1
#define ECHO_PIN1  15  // Pin echo ของเซนเซอร์อัลตราโซนิกตัวที่ 1
#define TRIG_PIN2  4  // Pin trig ของเซนเซอร์อัลตราโซนิกตัวที่ 2
#define ECHO_PIN2  16  // Pin echo ของเซนเซอร์อัลตราโซนิกตัวที่ 2
#define TRIG_PIN3  17  // Pin trig ของเซนเซอร์อัลตราโซนิกตัวที่ 3
#define ECHO_PIN3  5  // Pin echo ของเซนเซอร์อัลตราโซนิกตัวที่ 3

#define MAX_DISTANCE 200  // ระยะสูงสุดที่เซนเซอร์อัลตราโซนิกสามารถตรวจจับได้ (200 ซม.)

NewPing sonar1(TRIG_PIN1, ECHO_PIN1, MAX_DISTANCE);  // เซนเซอร์อัลตราโซนิกตัวที่ 1
NewPing sonar2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE);  // เซนเซอร์อัลตราโซนิกตัวที่ 2
NewPing sonar3(TRIG_PIN3, ECHO_PIN3, MAX_DISTANCE);  // เซนเซอร์อัลตราโซนิกตัวที่ 3

LiquidCrystal_I2C lcd(0x27, 16, 2);  // ตั้งค่าจอ LCD I2C ที่ address 0x27, ขนาด 16x2

void setup() {
  Serial.begin(115200);  // เปิดการใช้งาน Serial Monitor ที่บอดเรต 115200
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  delay(2000);
}

void loop() {
  int distance1 = sonar1.ping_cm();  // อ่านค่าระยะทางจากเซนเซอร์ตัวที่ 1
  int distance2 = sonar2.ping_cm();  // อ่านค่าระยะทางจากเซนเซอร์ตัวที่ 2
  int distance3 = sonar3.ping_cm();  // อ่านค่าระยะทางจากเซนเซอร์ตัวที่ 3

  int freeSpaces = 3;  // สมมติว่ามีช่องจอด 3 ช่อง

  // ตรวจสอบว่ามีรถจอดในแต่ละช่องหรือไม่
  if (distance1 > 0 && distance1 < 30) freeSpaces--;  // ถ้าระยะน้อยกว่า 30 ซม. แสดงว่ามีรถจอดอยู่
  if (distance2 > 0 && distance2 < 30) freeSpaces--;
  if (distance3 > 0 && distance3 < 30) freeSpaces--;

  // แสดงข้อมูลใน LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Free spaces:");
  lcd.setCursor(0, 1);
  lcd.print(freeSpaces);

  // แสดงข้อมูลใน Serial Monitor
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  Serial.print("Distance 3: ");
  Serial.print(distance3);
  Serial.println(" cm");

  Serial.print("Free spaces: ");
  Serial.println(freeSpaces);

  delay(1000);  // อัพเดตทุกๆ 1 วินาที
}
