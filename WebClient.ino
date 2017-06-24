
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.0.147";    // name address for Google (using DNS)
IPAddress ip(192, 168, 0, 177);


EthernetClient sclient;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
  sendData();
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (sclient.available()) {
    char c = sclient.read();
    Serial.print(c);
  }

  
}

void getResponse(){
  
  }

//send data to server
void sendData(){
    Serial.println("connecting...");
    if (sclient.connect(server, 80)) {
      Serial.println("connected");
      sclient.println("GET /index.php?nama=Adit HTTP/1.1");
      sclient.println("Host: 192.168.0.147");
      sclient.println("Connection: close");
      sclient.println();
    } else {
      Serial.println("connection failed");
    }


    // if the server's disconnected, stop the client:
    if (!sclient.connected()) {
      Serial.println();
      Serial.println("disconnecting.");
      sclient.stop();
  
      // do nothing forevermore:
      while (true);
    }
  }

