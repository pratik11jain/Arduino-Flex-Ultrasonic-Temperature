#include<LiquidCrystal.h> // includes the LiquidCrystal Library

    const int trigPin = 9;
    const int echoPin = 10;
    long duration;
    int distanceCm, distanceInch;
    int tempPin = 0;
    int lightPin = 1;
    const int flexPin = A1; //pin A1 to read analog input
    int valueChanged = 0;
    //Variables:
    int value; //save analog value
    int ctm;

    LiquidCrystal lcd(12,11,5,4,3,2); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

    void setup() {
        ctm = 0;
        lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
        Serial.begin(9600);       //Begin serial communication
    }

    void loop() {

        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distanceCm = duration * 0.034 / 2;
        distanceInch = duration * 0.0133 / 2;
        value = analogRead(flexPin);         //Read and save analog value from potentiometer
        if (value < 940 && valueChanged == 0) {
            if (ctm == 0) {
                ctm = 1;
                valueChanged = 1;
                Serial.println("Changed to C");
            } else {
                ctm = 0;
                valueChanged = 1;
                Serial.println("Changed to F");
            }

            //delay(500);
        }

        if (value > 970) {
            valueChanged = 0;
        }
        Serial.print(value);
        Serial.println(ctm);
        if (distanceCm < 20) {

            lcd.display();
            int tempReading = analogRead(tempPin);
            float tempVolts = tempReading * 5.0 / 1024.0;
            float tempC = (tempVolts - 0.5) * 100.0;
            float tempF = tempC * 9.0 / 5.0 + 32.0;
            //         ----------------
            if (ctm == 0) {
                lcd.setCursor(0, 0);
                lcd.print("Temp         C  ");
                lcd.setCursor(6, 0);
                lcd.print(tempC);
                Serial.print("C");
            } else {
                lcd.setCursor(0, 0);
                lcd.print("Temp         F  ");
                lcd.setCursor(6, 0);
                lcd.print(tempF);
                Serial.print("F");
            }
            delay(500);
        } else {
            lcd.noDisplay();
            delay(500);
        }

    }
