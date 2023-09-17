/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esp-rfid.ino                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdelo <ababdelo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:30:48 by ababdelo          #+#    #+#             */
/*   Updated: 2023/09/16 23:13:59 by ababdelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif

#include <SPI.h>
#include <MFRC522.h>

// Replace with your network credentials
const char *ssid = "1337-guest";
const char *password = "wifi@1337++@";

// REPLACE with your Domain name and URL path or IP address with path
const char *serverName = "http://10.32.129.186/ESP-RFID/src/post.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /post.php also needs to have the same key
char *apiKeyValue = "483f2f4bc98c7dbb9adb6bf693881c0e";

char *uname[6] = {"ababdelo", "ted-dafi", "hnaama", "msouiyeh", "elel-yaak", "malloui"};
char *uid[6] = {"0x63V92W6D", "0x11SI1HPZ", "0xT4IKQXTE", "0xP1FTPH3A", "0xA9C2X2NW", "0xW79B5NXS"};
char *role[3] = {"Member", "Staff", "Admin"};
char *action[2] = {"Entered to the club", "Exited from the Club"};
char *unuid[3] = {"0xURJYRLU1", "0xPPG7Q5EO", "0xBNDGYQOK"};

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
	int x = (int)random(0, 5);
	int y = (int)random(0, 2);
	int z = (int)random(0, 1);

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
		String httpRequestData = "api_key=" + String(apiKeyValue) + "&username=" + String(uname[x]) + "&uid=" + String(uid[x]) + "&role=" + String(role[y]) + "&action=" + String(action[x]);
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
