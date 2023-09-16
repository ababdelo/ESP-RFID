#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif

// Replace with your network credentials
const char *ssid = "your_wifi_ssid";
const char *password = "your_wifi_password";

// REPLACE with your Domain name and URL path or IP address with path
const char *serverName = "http://your_ip_address/ESP-RFID/src/post.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /post.php also needs to have the same key
String apiKeyValue = "483f2f4bc98c7dbb9adb6bf693881c0e";

char *sensorLocation[2] = {"INSIDE", "OUTSIDE"};
String sensorName = "MFRC522";
char *uid[12] = {"0x63V92W6D",
				 "0x11SI1HPZ",
				 "0xT4IKQXTE",
				 "0xP1FTPH3A",
				 "0xA9C2X2NW",
				 "0xW79B5NXS",
				 "0xH56K47HO",
				 "0x3C3UCSRB",
				 "0xYA03L3B7",
				 "0xJHXCTOLT",
				 "0x5FULS85P",
				 "0x4RJYRLU1"};

void setup()
{
	Serial.begin(115200);

	WiFi.begin(ssid, password);
	Serial.println("Connecting");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());
}
void loop()
{
	int x = (int)random(0, 12);
	int z = (int)random(0, 2);

	// Check WiFi connection status
	if (WiFi.status() == WL_CONNECTED)
	{
		HTTPClient http;
		WiFiClient client;
		// Your Domain name with URL path or IP address with path
		http.begin(client, serverName);

		// Specify content-type header
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");

		// Prepare your HTTP POST request data
		String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + String(sensorLocation[z]) + "&value=" + String(uid[x]);
		Serial.print("httpRequestData: ");
		Serial.println(httpRequestData);

		// You can comment the httpRequestData variable above
		// then, use the httpRequestData variable below (for testing purposes without the MFRC522 sensor)
		// String httpRequestData = "api_key=483f2f4bc98c7dbb9adb6bf693881c0e&location=Office&value=0xA9C2X2NW";
		// Send HTTP POST request
		int httpResponseCode = http.POST(httpRequestData);

		// If you need an HTTP request with a content type: text/plain
		// http.addHeader("Content-Type", "text/plain");
		// int httpResponseCode = http.POST("0xA9C2X2NW");

		// If you need an HTTP request with a content type: application/json, use the following:
		// http.addHeader("Content-Type", "application/json");
		// int httpResponseCode = http.POST("{\"value\":\"0xA9C2X2NW\"}");
		if (httpResponseCode > 0)
		{
			Serial.print("HTTP Response code: ");
			Serial.println(httpResponseCode);
		}
		else
		{
			Serial.print("Error code: ");
			Serial.println(httpResponseCode);
		}
		// Free resources
		http.end();
	}
	else
	{
		Serial.println("WiFi Disconnected");
	}
	// Send an HTTP POST request every 15 seconds
	delay(10000);
}
