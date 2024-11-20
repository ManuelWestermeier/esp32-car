#include <Arduino.h>
#include <WiFi.h>

#include "./motor.hpp"

// Define motors
Motor m1{12, 13, 26};
Motor m2{14, 27, 25};

// Wi-Fi credentials
const char *ssid = "ESP32-Car";
const char *password = "12345678";

// Create server
WiFiServer server(80);

#include "./web-page.hpp"

void setup()
{
  Serial.begin(115200);

  // Initialize motors
  m1.init();
  m2.init();

  // Setup Wi-Fi access point
  WiFi.softAP(ssid, password);
  Serial.println("Wi-Fi started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Start the server
  server.begin();
}

void handleClient(WiFiClient client)
{
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Serve the webpage
  if (request.indexOf("GET / ") >= 0)
  {
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print(webpage);
    return;
  }

  // Process motor control
  if (request.indexOf("GET /?motor=") >= 0)
  {
    int motorIndex = request.indexOf("motor=") + 6;
    int speedIndex = request.indexOf("speed=") + 6;
    String motor = request.substring(motorIndex, request.indexOf('&', motorIndex));
    int speed = request.substring(speedIndex, request.indexOf(' ', speedIndex)).toInt();

    bool forwardOrBackward = speed > 0;
    speed = abs(speed);
    // if(speed != 0) speed = constrain(speed, 180, 1023);

    if (motor == "left")
    {
      m1.spin(forwardOrBackward, speed);
    }
    else if (motor == "right")
    {
      m2.spin(forwardOrBackward, speed);
    }

    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSpeed updated");
    return;
  }

  client.print("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found");
}

void loop()
{
  WiFiClient client = server.available(); // Check for incoming client
  if (client)
  {
    while (client.connected() && client.available())
    {
      handleClient(client);
    }
    client.stop(); // Close the connection
  }
}