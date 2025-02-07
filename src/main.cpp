#include <WiFi.h>
#include <WebSocketsClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPIFFS.h>

// WiFi credentials
using namespace std;

const char *ssid = "Wifi name";
const char *password = "wifipassword";

// Socket.IO Client
WebSocketsClient webSocket;

// OLED screen setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define USE_SERIAL Serial

const char *host = "IP here";
const uint16_t port = 8080; //port here
const char *url = "/ws";
const char *protocol = "arduino";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        USE_SERIAL.printf("Oh no :( Disconnected!\n");
        break;
    case WStype_CONNECTED:
        if (payload != NULL && length > 0)
        {
            USE_SERIAL.printf("Connected to %s\n", payload);
        }
        break;
    case WStype_TEXT:
        if (payload != NULL && length > 0)
        {
            USE_SERIAL.printf("Got text:  %s\n", payload);
            display.clearDisplay();
            display.setCursor(0, 10);
            display.setTextSize(2);
            display.println((char *)payload);
            display.display();
        }
        break;
    default:
        USE_SERIAL.printf("Unsopported WebSocket event \n");
    }
}

void setup()
{
    // Start Serial Monitor
    Serial.begin(115200);

    // Start the I2C communication
    Wire.begin(21, 22); // SDA = 21, SCL = 22

    Serial.printf("Scren connecting..\n");

    // Initialize the OLED display with I2C address ----> 0x3C <----
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println(F("Wsup bro.."));
    display.display(); // Update the screen

    // Connect to WiFi
    display.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    display.display();

    // Wait for WiFi connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        display.print(".");
        display.display();
    }
    delay(10000);
    display.clearDisplay();
    display.printf("WiFi connected!\n");
    display.printf("IP Address: \n");
    display.println(WiFi.localIP());
    display.display();

    // Setup the Socket.IO connection (connect to the correct IP and port of your server)
    webSocket.begin(host, port, url, protocol);
    webSocket.onEvent(webSocketEvent);
}

void loop()
{
    webSocket.loop(); // Keep socket alive, allowing communication with the server
}
