/*
This is ESP32 code for a web server accessible at http://192.168.4.1
 when connected to a "RMCE" Wi-Fi 
 with a password "MADIRANO"
 */
 
#include <WiFi.h>

//Wi-Fi connection credentials
const char *ssid =     "RMCE";
const char *password = "MADIRANO";

//assign port 80 to the server
WiFiServer server(80);

WiFiClient client;

bool sw;
bool condition;

void setup() {

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  server.begin();

  Serial.begin(9600);

  //assign a false value to the switch boolean
  sw = false;
  //assign a false value to the condition boolean
  condition = false;
}

void sendHttpResponse() {

      //homepage
      client.println("HTTP/ 1.1 200 OK");
      client.println("Content-Type:text/html");
      client.println("");
      client.println("<!DOCTYPE html>");
      client.println("<html>");
      
      client.println("<head>");
      
      client.println("<title>home</title>");
      
      client.println("<style>");
      client.println("body { background-color: #ffffff; font-family: Verdana, sans-serif; }");          
      client.println(".container { display: flex; flex-direction: column; align-items: center; gap: 20px; }");
      client.println(".button-container { display: flex; gap: 20px; }");
      client.println(".circular-button { color: #ffffff; width: 80px; height: 80px; border-radius: 50%;  border-width: 1px; border-color: #cccccc; border-style: ridge; cursor: pointer; font-size: 16px; }");      
      client.println(".button-on { background-color: #008000;}");
      client.println(".button-off { background-color: #ff0000}");
      client.println("</style>");
      
      client.println("</head>");

      client.println("<body>");
      client.println("<h1 style='color: #cccccc; text-align: center;'>Welcome to Remote Monitoring and Control Environment!</h1>"); 
      client.println("<div class = \"container\">");
      client.println("<p>Click the interactive switch buttons.</p>");
      client.println("<div class \"button-container\">");
      client.println("<button class = 'circular-button button-on' onclick='window.location.href=\"/ON\"'>On</button>"); 
      client.println("<button class = 'circular-button button-off' onclick='window.location.href=\"/OFF\"'>Off</button>");
      client.println("</div>");
      client.println("</div>");
      client.println("</body>");
      
      client.println("</html>");
      
}

void handleButtonPress(bool condition) {
  if (condition) {
    
    //switch on page
    client.println("HTTP/ 1.1 200 OK");
    client.println("Content-Type:text/html");
    client.println("");
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    
    client.println("<head>");

    client.println("<title>on</title>");
    
    client.println("<style>");
    client.println("body { background-color: #32cd32; color: #ffffff; margin: 0; padding: 0; overflow: hidden; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; font-family: Helvetica, sans-serif; }");
    client.println("</style>");
    
    client.println("</head>");
    
    client.println("<body>");
    client.println("<h1>Switch on was successful !</h1>");
    client.println("<p>Click return home or exit the app.</p>");
    client.println("</body>");
    
    client.println("</html>");

  } else {
 
    //switch off page
    client.println("HTTP/ 1.1 200 OK");
    client.println("Content-Type:text/html");
    client.println("");
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    
    client.println("<head>");

    client.println("<title>off</title>");
    
    client.println("<style>");
    client.println("body { background-color: #ff6600; color: #ffffff; margin: 0; padding: 0; overflow: hidden; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; font-family: Helvetica, sans-serif; }");
    client.println("</style>");
    
    client.println("</head>");
    
    client.println("<body>");
    client.println("<h1>Switch off was successful !</h1>");
    client.println("<p>Click return home or exit the app.</p>");
    client.println("</body>");
    
    client.println("</html>");

  }
}

void loop() {
  
  client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    
    if (request.indexOf("/ON") != -1) {
      sw = true;
      handleButtonPress(true);
    }else if (request.indexOf("/OFF") != -1) {
      sw = false;
      handleButtonPress(false);
    }else{
      sendHttpResponse();
    }
    //closing the connection with the client
    client.stop();
  }
  
  Serial.println(sw);
}
