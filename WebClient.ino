
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char APIserver[] = "192.168.0.147";    // name address for Google (using DNS)
IPAddress ip(192, 168, 0, 177);


EthernetClient sclient;
EthernetServer sserver(80);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
  
  delay(1000);
  sendDataToServer();
}

void loop() {
  //jalankan fungsi get data setelah send data
  printDataFromServer();
  responseToClient();

  
}



//send data to server
void sendDataToServer(){
    Serial.println("connecting...");
    if (sclient.connect(APIserver, 80)) {
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

//get data after send data
void printDataFromServer(){
    if (sclient.available()) {
      char c = sclient.read();
      Serial.print(c);
    }
  }  


//fungsi arduino sebagai server
void responseToClient(){
    EthernetClient client = sserver.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  }

