/*

   Copyright (c) 2015. Mario Mikočević <mozgy>

   MIT Licence

*/

#include <Wire.h>
#include <TM1650.h>

TM1650 Disp4Seg;

// I2C pins
#define SDA_pin 4
#define SCL_pin 5

void setup() {

  Serial.begin(115200);
  Serial.println( "TM1650 4 segment display example" );

  Wire.begin( SDA_pin, SCL_pin );
  Wire.setClock( 400000 );

  Disp4Seg.Init();
  delay(1000);

}

void loop() {

  Disp4Seg.WriteNum( 0000 );
  Serial.println( "TM1650 Display text '0000'" );

  for (byte i = 1; i < 8; i++) {
    Disp4Seg.SetBrightness( i );
    Serial.println( "TM1650 Display Brightness = " + String (i) );
    delay(500);
  }

  Disp4Seg.SetBrightness( 0 );
  Serial.println( "TM1650 Display Brightness = 0");
  delay(500);

  Disp4Seg.ClearDisplay();

  for (int i = 1; i < 0x100; i = i << 1) {
    Disp4Seg.SendDigit(i, 0);
    Serial.println( "TM1650 Display text = " + String(i, HEX) + " " + String(i, BIN));
    delay(300);
  }




  for (byte j = 0; j < 4; j++) {
    Disp4Seg.ClearDisplay();
    for (int i = 0; i < 15; i++) {
      Disp4Seg.WriteNum(i, j);
      Serial.println( "TM1650 Display text = " + String(i));
      delay(200);
    }
  }

  Disp4Seg.ClearDisplay();

  for (int i = 1; i < 11; i++) {
    Disp4Seg.ColonON();
    delay(250);
    Disp4Seg.ColonOFF();
    delay(250);
  }

  /*
    for ( uint16_t i = 0; i < 10000; i++ ) {
      Disp4Seg.WriteNum( i );
      //( i & 0x10 ) ? Disp4Seg.ColonON() : Disp4Seg.ColonOFF();
      Disp4Seg.SetDot( 1, ( i & 0x10 ) ? true : false );
      delay(5);
    }
    Disp4Seg.ColonOFF();


    Disp4Seg.ClearDisplay();

    for ( uint8_t k = 0; k < 3; k++ ) {
    for ( uint8_t i = 0; i < 4; i++ ) {
      for ( uint8_t j = 1; j < 0x40; j = j << 1 ) {
        Disp4Seg.SendDigit( j, i );
        delay(50);
      }
      Disp4Seg.SendDigit( 0, i );
    }
    }


    Disp4Seg.WriteNum( 8888 );
    Disp4Seg.SetDot( 0, true );
    Disp4Seg.SetDot( 1, true );
    Disp4Seg.SetDot( 2, true );
    Disp4Seg.SetDot( 3, true );
    delay(4000);

    for ( uint8_t i = 0; i < 3; i++ ) {
    Disp4Seg.DisplayOFF();
    delay(400);
    Disp4Seg.DisplayON();
    delay(400);
    }
  */

  Disp4Seg.ClearDisplay();

  int8_t datastring[] = {_E, _S, _P, _8, _2, _6, _6};
  scrolltext(datastring, 7, 500);

}

void scrolltext(int8_t DispData[], byte amount, int delayMs) {
  byte bright = 0;
  uint8_t segData[amount + 8];    // оставляем место для 4х пустых слотов в начале и в конце
  for (byte i = 0; i < 4; i++) {  // делаем первые 4 символа пустыми
    segData[i] = 0x00;
  }
  for (byte i = 0; i < amount; i++) {  // далее забиваем тем что на входе (сам текст строки)
    segData[i + 4] = DispData[i];
  }
  for (byte i = amount + 4; i < amount + 8; i++) {  // и последние 4 тоже забиваем пустыми символами
    segData[i] = 0x00;
  }
  for (byte i = 0; i <= amount + 4; i++) {   // выводим
    Disp4Seg.SetBrightness( bright++ );
    Disp4Seg.SendDigit(segData[i] , 3);
    Disp4Seg.SendDigit(segData[i + 1] , 2);
    Disp4Seg.SendDigit(segData[i + 2] , 1);
    Disp4Seg.SendDigit(segData[i + 3] , 0);
    //    displayByte(segData[i], segData[i + 1], segData[i + 2], segData[i + 3]);
    delay(delayMs);
    Disp4Seg.SetBrightness( bright + i );
  }
}

//void scrolldate(int8_t DispData[], byte amount, int delayMs) {
