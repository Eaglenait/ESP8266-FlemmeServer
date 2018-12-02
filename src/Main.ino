#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Fs.h>
#include <rest.h>
#include <Timer.h>

#include <string.h>

Timer t;

const int RELAY = 14;
const int RED = 15;
const int BLUE = 13;
const int GREEN = 12;
const int BUTTON = 4;
const int LED1 = 2;
const int LED2 = 5;
const int LED3 = 0; //blinds
const int LDR = A0; //Brightness sensor

WiFiClient wclient;
ESP8266WebServer server(80);
Rapi rest;

//handles the website icon requests
void handleico() {
	server.send(404);
}

void handleNotFound() {
	if (!rest.handleRest()) { //we call rest when the webserver doesn't recognize the entered URI
		File notfound = SPIFFS.open("/notfound.html", "r");
		size_t sent = server.streamFile(notfound, "text/html");
		notfound.close();
	}
	else {
		server.send(200);
	}
}

void handleData() {
	File data = SPIFFS.open("/data.html", "r");
	size_t sent = server.streamFile(data, "text/html");
	data.close();
	server.send(200);
}


void setup() {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(RELAY, OUTPUT);
	pinMode(BUTTON, INPUT);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LDR, INPUT);

	//set rgb led to nothing
	analogWrite(RED, 0);
	analogWrite(BLUE, 0);
	analogWrite(GREEN, 0);

	if (!SPIFFS.begin()) {
		Serial.println("Error beginning SPIFFS");
	}

	server.on("/", handleNotFound);
	server.on("/favicon.ico", handleico);
	server.on("/data.html", handleData);
	//REST trigger
	server.onNotFound(handleNotFound);

	//HTTP server
	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
	//Timer update
	t.update();

	//Wifi reconnection loop
	if (WiFi.status() != WL_CONNECTED) {
		Serial.print(F("Connecting to "));
		Serial.print(ssid);
		Serial.println(F("..."));
		WiFi.begin(ssid, password);

		if (WiFi.waitForConnectResult() != WL_CONNECTED) return;
		Serial.println(F("WiFi connected"));
		Serial.println(WiFi.localIP());
	}
	server.handleClient();
}
