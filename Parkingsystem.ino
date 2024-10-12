#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <TridentTD_LineNotify.h>  // Import TridentTD Line Notify

#define TRIG_PIN1  2   // Pin trig for ultrasonic sensor 1
#define ECHO_PIN1  15  // Pin echo for ultrasonic sensor 1
#define TRIG_PIN2  4   // Pin trig for ultrasonic sensor 2
#define ECHO_PIN2  16  // Pin echo for ultrasonic sensor 2
#define TRIG_PIN3  17  // Pin trig for ultrasonic sensor 3
#define ECHO_PIN3  5   // Pin echo for ultrasonic sensor 3

#define MAX_DISTANCE 200  // Maximum distance for ultrasonic sensor (200 cm)

// Initialize ultrasonic sensors
NewPing sonar1(TRIG_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIG_PIN3, ECHO_PIN3, MAX_DISTANCE);

// Initialize 20x4 I2C LCD display
LiquidCrystal_I2C lcd(0x27, 20, 4);

const String LINE_TOKEN = "YOUR_LINE_NOTIFY_TOKEN";  // Insert your LINE Notify Token here

void setup() {
  Serial.begin(115200);  // Start Serial Monitor at 115200 baud rate
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  delay(2000);

  // Initialize LINE Notify
  LINE.setToken(LINE_TOKEN);  // Set LINE Notify Token
}

void loop() {
  int distance1 = sonar1.ping_cm();  // Read distance from sensor 1
  int distance2 = sonar2.ping_cm();  // Read distance from sensor 2
  int distance3 = sonar3.ping_cm();  // Read distance from sensor 3

  // Determine parking space status based on sensor readings
  String space1 = (distance1 > 0 && distance1 < 30) ? "Occupied" : "Free";
  String space2 = (distance2 > 0 && distance2 < 30) ? "Occupied" : "Free";
  String space3 = (distance3 > 0 && distance3 < 30) ? "Occupied" : "Free";

  // Display the status on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  lcd.setCursor(0, 1);
  lcd.print("Space 1: ");
  lcd.print(space1);
  lcd.setCursor(0, 2);
  lcd.print("Space 2: ");
  lcd.print(space2);
  lcd.setCursor(0, 3);
  lcd.print("Space 3: ");
  lcd.print(space3);

  // Notify via LINE if any parking space is occupied
  if (space1 == "Occupied" || space2 == "Occupied" || space3 == "Occupied") {
    String message = "Parking Alert! Spaces Occupied:\n";
    if (space1 == "Occupied") message += "Space 1\n";
    if (space2 == "Occupied") message += "Space 2\n";
    if (space3 == "Occupied") message += "Space 3\n";
    
    // Send LINE Notify message
    LINE.notify(message);
    delay(60000);  // Prevent multiple notifications within 1 minute
  }

  // Display the status on the Serial Monitor
  Serial.println("Parking Space Status:");
  Serial.print("Space 1: ");
  Serial.println(space1);
  Serial.print("Space 2: ");
  Serial.println(space2);
  Serial.print("Space 3: ");
  Serial.println(space3);

  delay(1000);  // Update every 1 second
}
