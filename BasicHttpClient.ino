void Line_Notify(String message) ;
#include <ESP8266WiFi.h>
#include <WiFiClientSecureAxTLS.h> // กรณีขึ้น Error ให้เอาบรรทัดนี้ออก
// Config connect WiFi
#define WIFI_SSID "Tangtai"
#define WIFI_PASSWORD "123454321"
// Line config
#define LINE_TOKEN "EZ2SkNIuF2AiogopW5aefNSZsdo6kVsuqeTjh7jGMBo"
#define SW D2
String message = "โดนกด"; // ArduinoIDE เวอร์ชั่นใหม่ ๆ ใส่ภาษาไทยลงไปได้เลย
void setup() {
pinMode(SW, INPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
// connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}
void loop() {
if (digitalRead(14) == HIGH) {
Line_Notify("TESTTEST");
// Serial.println();
  }
delay(1000);
}
void Line_Notify(String message) {
  axTLS::WiFiClientSecure client; // กรณีขึ้น Error ให้ลบ axTLS:: ข้างหน้าทิ้ง
if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
return;   
  }
  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
// Serial.println(req);
  client.print(req);
delay(20);
// Serial.println("-------------");
while(client.connected()) {
    String line = client.readStringUntil('\n');
if (line == "\r") {
break;
    }
//Serial.println(line);
  }
// Serial.println("-------------");
}
