#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte arduinoMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress arduinoIP(192, 168, 0, 177); // desired IP for Arduino
unsigned int arduinoPort = 8888;      // port of Arduino

IPAddress receiverIP(192, 168, 0, 147); // IP of udp packets receiver
unsigned int receiverPort = 6000;      // port to listen on my PC

EthernetUDP Udp;

void setup() {
  Ethernet.begin(arduinoMac,arduinoIP);
  Udp.begin(arduinoPort);
}

void loop() {
sendMsg();
}

void sendMsg(){
    Udp.beginPacket(receiverIP, receiverPort); //start udp packet
   Udp.print(String(analogRead(A0), DEC)); //write sensor data to udp packet
   Udp.write(",");
   Udp.print(String(analogRead(A1), DEC)); //write sensor data to udp packet
   Udp.endPacket(); // end packet
  
   delay(3000); 
}
