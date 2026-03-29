#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ustawienie adresu 0x27 dla LCD 16x2 (najczęstszy adres)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int buttons[] = {2, 3, 4, 5}; 
const int buzzerPin = 6; 
const int freqs[] = {500, 1000, 1500, 2000}; 
const char* labels[] = {"Moc: 25%", "Moc: 50%", "Moc: 75%", "Moc: 100%"};

void updateDisplay(const char* text) {
    lcd.clear();
    lcd.setCursor(0, 0); // Ustaw kursor na początku 1. linii
    lcd.print("sila dzwieku:");
    lcd.setCursor(0, 1); // Ustaw kursor na początku 2. linii
    lcd.print(text);
}

void setup() {
    Serial.begin(115200);
    
    // Inicjalizacja LCD
    lcd.init();
    lcd.backlight(); // Włącz podświetlenie
    
    for(int i = 0; i < 4; i++) {
        pinMode(buttons[i], INPUT_PULLUP);
    }
    pinMode(buzzerPin, OUTPUT);
    
    updateDisplay("Czekam...");
}

void loop() {
    for(int i = 0; i < 4; i++) {
        if(digitalRead(buttons[i]) == LOW) { 
            updateDisplay(labels[i]);
            tone(buzzerPin, freqs[i], 200); 
            delay(300); 
        }
    }
}
