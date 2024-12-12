#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <RTClib.h>
#include <SFE_BMP180.h> 

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C LCD(0x27, 16, 2); 
RTC_DS1307 rtc;
SFE_BMP180 bmp;

void setup() {
	LCD.init();
	LCD.backlight();
	dht.begin(); 

	if(!rtc.begin()) {
		LCD.setCursor(0, 0);
		LCD.print("RTC Error!");
		while(1); 
	}

	if(!bmp.begin()) {
		LCD.setCursor(0, 0);
		LCD.print("BMP180 Error!");
		while(1); 
	}
}

void loop() {
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	char status;
	double pressure = 0.0;
	status = bmp.startPressure(3); 
	if(status != 0) {
		delay(status);
		bmp.getPressure(pressure);
	}

	DateTime now = rtc.now();
	LCD.clear();
	LCD.setCursor(0, 0);
	if(now.hour() < 10) LCD.print('0'); 
	LCD.print(now.hour());
	LCD.print(':');
	if(now.minute() < 10) LCD.print('0');
	LCD.print(now.minute());
	LCD.print(' ');
	LCD.print(t, 1); 
	LCD.print((char)223); 
	LCD.print("C");
	LCD.setCursor(0, 1);
	LCD.print(pressure / 100.0, 1); 
	LCD.print("Pa ");
	LCD.print(h, 1); 
	LCD.print("%");

	delay(2000); 
}