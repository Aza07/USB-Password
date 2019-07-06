#include <SPI.h>
#include <MFRC522.h>

#include "Keyboard.h"
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // membuat MFRC522 instance.

//int RXLED = 17;
//int TXLED = 30;

void setup() 
{
  Serial.begin(115200);   // Memulai Serial Communication Baud Rate 115200
  
  SPI.begin();      // Memulai SPI Serial Protokol Antara Arduino Micro dan MFRC522
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  Keyboard.begin();

  pinMode(17, OUTPUT);  // RXLED
  pinMode(30, OUTPUT);  // TXLED
  
  Serial.println("Dekatkan Kartu Ke Reader...");
  Serial.println();

  lampu(200,10,30);

}
void loop() 
{
  // Lihat jika ada Card baru terdeteksi
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Baca Isi Card Tersebut
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Tampilan User ID ke Serial Monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();
  if (content.substring(1) == "89 7B 97 55") //Ini adalah UID di Kartu
  {
    lampu(200,3,17);
    Serial.println("Authorized access");
    Serial.println();
    Keyboard.print("490@Ff1$T$xmk6XuqRQlnC63");
    delay(200);
    Keyboard.print("GbFu4#OD0!Dj5@IsZ!$DkWivyW");
    
    delay(1000);
  }
  
  else if (content.substring(1) == "56 F6 CE F7") //Ini adalah UID di gantungan kunci
  {
    lampu(200,3,17);
    Serial.println("Authorized access");
    Serial.println();
    Keyboard.print("6%BnXkDYraph^0sAttN7%rb%Bh");
    delay(200);
    Keyboard.print("*xunZ!o@^joVXLIQ3z4&0Rt9");

    delay(1000);
  }
 
 else   {
    lampu(1000,1,17);
    Serial.println(" Access denied");
    delay(1000);
  }
} 

void lampu(int delay_, int jumlah, int pin){
    for(int i = 1 ; i <= jumlah ; i++){
          digitalWrite(pin, HIGH);
          delay(delay_);
          digitalWrite(pin, LOW);
          delay(delay_);
    }
}
