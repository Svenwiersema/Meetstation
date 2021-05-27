// include librarys
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// define the dht data pin
#define dhtpin 2
#define dhttype DHT11
// name of wifi
#define ssid "WeerStation"
// password for wifi
#define password "P@$$w0rd"

// port number
ESP8266WebServer server(80);

// store http request
String header;

// dht object
DHT dht(dhtpin, dhttype);

// temp and hum var
float temp;
float hum;

// Current time
unsigned long currentTime;
// Previous time
unsigned long previousTime;
// Define timeout time in milliseconds
#define timeoutTime 2000

// Function to handle the root of the site
void handleRoot() {
  // Send a string to the server
  server.send(200,"text/html", sendHTML());
}

void setup() {
  // Begin the serial and DHT
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);

  // print ip
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP adress: ");
  Serial.print(WiFi.softAPIP());

  // This will check if someone tries to connect to the root site
  server.on("/", handleRoot);

  // start server
  server.begin();
}

void loop() {
  // This will handle the client
  server.handleClient();
}

// Construct the HTML for the webserver
String sendHTML() {

  // Read the temperature and humidity
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  // This is the HTML for the site
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Weer Station</title>\n";
  ptr += "<style>\n";
  ptr += "body {";
  ptr += "Text-align: center;";
  ptr += "}";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Weerstation</h1>\n";
  ptr += "<h3>Temperature</h3>\n";
  ptr += "<p>";
  ptr += String(temp);
  ptr += " *C</p>\n";
  ptr += "<h3>Humidity</h3>\n";
  ptr += "<p>";
  ptr += String(hum);
  ptr += "%</p>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";

  return ptr;
}
