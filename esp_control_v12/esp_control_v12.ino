//#define useESP32      // or disable with // for ESP8266
//#define useAP         // or disable with // for STA
#define useFIXIP      // or disable with // for IP from router at STA or default 192.168.4.1 at AP
#define usePID        // or disable with // 

#if defined useESP32
#include <WiFi.h>
const int DoutPin = 5; // P5
const int DinPin = 17; // P17 Digital pin to be read

#define AinPin 36 
#define AoutPin 25
#define IAM "ESP32"

int Ainres = 4095; 
int dac1v = 127;  // 0 .. 255
int dac1d = 5;    // add button


#else
#include <ESP8266WiFi.h>
const int DoutPin = 13; // GPIO13
const int DinPin = 12; // Digital pin to be read
#define IAM "ESP8266"
#define AinPin A0
int Ainres = 1023; 
#endif

int LED_SP = LOW;

#if defined usePID
// button action for PID
int pidOVd = 2;    // add/sub button
int pidSPd = 2;    // add/sub button

float PID1_PV = 0.0;
float PID1_SP = 0.0;
float PID1_OV = 0.0;
float PID1_MD = 2.0;

#define PID1_inpin 35                 // ESP32 P35 ADC7         !! 27 ADC17 not work its HIGH
#define PID1_outpin 26                // ESP32 ADC19 DAC2

#define IND1_inpin 39                 // ESP32 ADC3
float IND1_PV = 0.0;
#define IND2_inpin 32                 // ESP32 ADC4
float IND2_PV = 0.0;
#define IND3_inpin 33                 // ESP32 ADC5
float IND3_PV = 0.0;
#define IND4_inpin 34                 // ESP32 ADC6
float IND4_PV = 0.0;

//_________________________________________________point timer
unsigned long Ccount = 0;                          // loops
const unsigned long Ccount_end = 200;              // every 200 loops check for millis() only
unsigned long Ctime = 0;                           // milliseconds   works for about 50 days
unsigned long Ctime_old = 0;                       // milliseconds memory last scan
unsigned long Ctime_delta  = 500;                  // 500 millis
int job = 0;
const int maxjob = 8;

#endif


#if defined useAP       //setting the addresses                    // AP MODE

#if defined useFIXIP

IPAddress APip(192,168,210,1);
IPAddress APgateway(192, 168, 210, 1);
IPAddress APsubnet(255, 255, 255, 0);

#endif

#define APssid "myESP"                                // set for AP MODE login
#define APpassword "password"

#else                                               // set for STA MODE login

#if defined useFIXIP

IPAddress STAip(192,168,1,210);
IPAddress STAgateway(192, 168, 1, 1);
IPAddress STAsubnet(255, 255, 255, 0);

#endif

#define STAssid "mySSID"
#define STApassword "password"

#endif

// AinPin A0 ( 10bit ADC so read 1024 as 1V MAX )
// ESP32 A0 on P36
// ESP32 AoutPin DAC1 ADC18 P25
// Setting 8bit DAC channel 1 (GPIO 25) voltage to approx 0.78 of VDD_A voltage (VDD * 200 / 255). 
// For VDD_A 3.3V, this is 2.59V:

// for PID on ESP32 use:
// "PV" Ain  P27 ADC17  !HOLD 
// "OUTPUT" Aout P26 DAC2 ADC19



const long serdb = 115200;

WiFiServer server(80);

void setup() {
  pinMode(DoutPin, OUTPUT);
  digitalWrite(DoutPin, LOW);
#if defined useESP32
  dacWrite(AoutPin,dac1v);
#endif
  Serial.begin(serdb);
  delay(7);
  Serial.println();
  Serial.println("___________");
  Serial.println(" KLL myESP ");
  Serial.print("___v1.2____ on ");
  Serial.println(IAM);

#if defined useAP       // AP MODE
  Serial.print("Configuring access point: SSID: ");
  Serial.print(APssid);
  Serial.print(" password: ");  
  Serial.println(APpassword); 
  WiFi.softAP(APssid, APpassword);
  delay(10);  

#if defined useFIXIP
  WiFi.softAPConfig(APip,APgateway,APsubnet);  
#endif

#else                                               // set for STA MODE login

  Serial.print("Connecting to ");
  Serial.println(STAssid); 

  WiFi.begin(STAssid, STApassword);
  
#if defined useFIXIP
  WiFi.config(STAip,STAgateway,STAsubnet);
#endif
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
#endif

  Serial.print("Server started at http://");

  // Start the server
  server.begin();
  
#if defined useAP       // AP MODE
  Serial.print(WiFi.softAPIP());                  // Print the IP address
#else                                               // for STA MODE
  Serial.print(WiFi.localIP());                  // Print the IP address
#endif
 
  Serial.println("/");
}
 
//_______________________________________________________________________________loop
void loop() {
  
#if defined usePID
  control_point_timer();
#endif 

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(DoutPin, HIGH);
    LED_SP = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(DoutPin, LOW);
    LED_SP = LOW;
  }
#if defined useESP32
  if (request.indexOf("/DAC1UP") != -1)  {
    dac1v = dac1v+dac1d;
    if ( dac1v > 255) { dac1v = 255; }
    dacWrite(AoutPin,dac1v);
  }
  if (request.indexOf("/DAC1DN") != -1)  {
    dac1v = dac1v-dac1d;
    if ( dac1v < 0 ) { dac1v = 0; }
    dacWrite(AoutPin,dac1v);
  }
#endif

#if defined usePID

  if (request.indexOf("/DAC2UP") != -1)  {
    PID1_OV += pidOVd;
  }
  if (request.indexOf("/DAC2DN") != -1)  {
    PID1_OV -= pidOVd;
  }
  if (request.indexOf("/PIDMAN") != -1)  {
    PID1_MD = 1;
  }
  if (request.indexOf("/PIDAUTO") != -1)  {
    PID1_MD = 2;
  }
  if (request.indexOf("/SPUP") != -1)  {
    PID1_SP += pidSPd;
    if ( PID1_SP > 100) { PID1_SP = 100; }
  }
  if (request.indexOf("/SPDN") != -1)  {
    PID1_SP -= pidSPd;
    if ( PID1_SP < 0) { PID1_SP = 0; }
  }
  
#endif
 
//_______________________________________________________________________________make_HTML

  // Return the response
  String s = ("HTTP/1.1 200 OK\r\n");
  s += ("Content-Type: text/html\r\n\r\n");
  s += ("<!DOCTYPE HTML>\r\n<html>\r\n");
  s += ("<head> <title>myESP KLL engineering</title> </head>\r\n");
  s += ("<body>\r\n");
  s += ("i am a SoC development board <b>");
  s += (IAM); 
  s += ("</b><br> running as webserver / WIFI remote IO / ");

#if defined useESP32 
//  s += (" <img src=\"http://kll.engineering-news.org/kllfusion01/downloads/ESP32_myPINOUT.jpg\" alt=\"ESP32\" width=\"500\" > ");  
  s += ("<a href=\"http://kll.engineering-news.org/kllfusion01/downloads/ESP32_myPINOUT.jpg\" target=\"_blank\">SHOW pinout</a> / \r\n");
#else
//  s += (" <img src=\"http://kll.engineering-news.org/kllfusion01/downloads/ESP8266_myPINOUT.jpg\" alt=\"ESP8266\" width=\"500\" > ");
  s += ("<a href=\"http://kll.engineering-news.org/kllfusion01/downloads/ESP8266_myPINOUT.jpg\" target=\"_blank\">SHOW pinout</a> / \r\n");
#endif
  s += ("<a href=\"http://kll.engineering-news.org/kllfusion01/articles.php?article_id=132\" target=\"_blank\">Visit KLL engineering</a> <br />\r\n");

  s += ("<br />\r\n <hr><h2>web IO</h2>");
  s += ("______DOUT____________________DoutPin: P");  s += (DoutPin);   s += ("<br>");
  s += ("OV : ");
  if(LED_SP == HIGH) {
  s += ("ON");
  s += (" _<a href=\"/LED=OFF\"\"><button> OFF </button></a>");  
  } else {
  s += ("OFF");
  s += (" _<a href=\"/LED=ON\"\"><button> ON </button></a>");
  }
  s += ("<br>\r\n");  
  s += ("______DIN1____________________DinPin: P");  s += (DinPin);   s += ("<br>");
  s += ("PV: ");
  if(digitalRead(DinPin)) {   s += ("ON");  } else {    s += ("OFF");  }    s += (" <br>\r\n");
  s += ("______AIN1____________________AinPin: ");  s += (AinPin);   s += ("<br>");  
  s += ("PV raw : ");  s += (analogRead(AinPin));  s += (" <br>\r\n");

#if defined useESP32
  s += ("______AOUT____________________AoutPin: ");  s += (AoutPin);   s += ("<br>");  
  s += ("DAC1 : ");  //DAC1 ADC18 P25
  s += (dac1v);
  s += (" _<a href=\"/DAC1UP\"\"><button>  UP </button></a>");  
  s += (" _<a href=\"/DAC1DN\"\"><button> DOWN </button></a>");  
  s += (" <br>\r\n");
#endif

#if defined usePID
  s += ("<hr><h2>uPCS2 for UNO and ESP</h2>");
  s += ("______PID1____________________AinPin: P");  s += (PID1_inpin); s += (" AoutPin: P");  s += (PID1_outpin); s += ("<br>");
  s += ("PV: ");
  s += (PID1_PV);   s += ("%");
  s += (" <br>\r\n");

  s += ("SP: ");
  s += (PID1_SP); s += ("%");
  s += (" _<a href=\"/SPUP\"\"><button> SP UP </button></a>");  
  s += (" _<a href=\"/SPDN\"\"><button> SP DOWN </button></a><br>");  

  s += ("MODE: "); 
  if (PID1_MD == 1) { 
     s += (" MAN ");
     s += (" _<a href=\"/PIDAUTO\"\"><button> AUTO </button></a><br>");  
  }
  if (PID1_MD == 2) { 
     s += (" AUTO ");
     s += (" _<a href=\"/PIDMAN\"\"><button> MAN </button></a><br>");    
  }
  
  s += ("OUT: ");  s += (PID1_OV);  s += ("%");
  if (PID1_MD == 1) {
    s += (" _<a href=\"/DAC2UP\"\"><button> OVP UP </button></a>");  
    s += (" _<a href=\"/DAC2DN\"\"><button> OVP DOWN </button></a>");  
  }
  s += ("<br>\r\n");
  s += ("______IND1____________________AinPin: P");  s += (IND1_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND1_PV);  s += ("%"); s += (" <br>\r\n");  // 
  s += ("______IND2____________________AinPin: P");  s += (IND2_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND2_PV);  s += ("%"); s += (" <br>\r\n");  // 
  s += ("______IND3____________________AinPin: P");  s += (IND3_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND3_PV);  s += ("%"); s += (" <br>\r\n");  // 
  s += ("______IND4____________________AinPin: P");  s += (IND4_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND4_PV);  s += ("%"); s += (" <br>\r\n");  // 

    
#endif
  s += ("<hr>\r\n");
  s += ("\r\n");
  s += ("</body>");
  s += ("</html>");

  client.print(s);

  delay(1);
  client.stop();
  Serial.println("Client disonnected");
  Serial.println("");

}  // end loop

