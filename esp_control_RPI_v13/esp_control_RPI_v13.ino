#define useESP32      // or disable with // for ESP8266
//#define useAP         // or disable with // for STA
#define useFIXIP      // or disable with // for IP from router at STA or default 192.168.4.1 at AP
#define usePID        // or disable with // 


#define DEBUG

#ifdef DEBUG
#define db(t,x)     if(t) { Serial.print(x); }
#define dbln(t,x)   if(t) { Serial.println(x); }
#else
#define db(t,x)     // define empty, so macro does nothing
#define dbln(t,x)
#endif 




#if defined useESP32
//  better see https://github.com/esp8266/ESPWebServer / download zip

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

#define PID1_EGU "degC"
#define PID1_TAG "TRC01-54"
#define PID1_DESC "air temperature"
int PID1_ALM = 0;

// compiler warning!!
// char* PID1_tMD[]={"na","MAN","AUTO","CAS","na"}; // 0 .. 3 modes
//                                              ^
// warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]

char* PID1_tALM[]={"ok", "LOLO", "LO", "HI", "HIHI","VOLO", "VOHI"}; // 0 .. 6 alarm
char* PID1_tMD[]={"na","MAN","AUTO","CAS","na"}; // 0 .. 3 modes

float PID1_LOR = 0.0; 
float PID1_HIR = 50.0; 
float PID1_RPV = 0.0;
float PID1_RSP = 0.0;


float PID1_PV = 0.0;
float PID1_SP = 0.0;
float PID1_OV = 0.0;
float PID1_MD = 2.0;

#define PID1_inpin 35                 // ESP32 P35 ADC7         !! 27 ADC17 not work its HIGH
#define PID1_outpin 26                // ESP32 ADC19 DAC2

#define IND1_inpin 39                 // ESP32 ADC3
float IND1_PV = 0.0;
int IND1_ALM = 0;
#define IND2_inpin 32                 // ESP32 ADC4
float IND2_PV = 0.0;
int IND2_ALM = 0;
#define IND3_inpin 33                 // ESP32 ADC5
float IND3_PV = 0.0;
int IND3_ALM = 0;
#define IND4_inpin 34                 // ESP32 ADC6
float IND4_PV = 0.0;
int IND4_ALM = 0;

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

#define STAssid  "kll-wlan"                // "mySSID"
#define STApassword  "WELOVEKOH-SAMUI"     // "password"

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
WiFiClient client = server.available();  // to make "client" global


void setup() {
  pinMode(DoutPin, OUTPUT);
  digitalWrite(DoutPin, LOW);
#if defined useESP32
  dacWrite(AoutPin,dac1v);
#endif
  Serial.begin(serdb);
  delay(7);
  dbln(true,);
  dbln(true,"___________");
  dbln(true," KLL myESP ");
  db(true,"___v1.3____ on ");
  dbln(true,IAM);

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
//  WiFiClient client = server.available();
  client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

// server.on("/submit", handleSubmit);
 
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
  if (request.indexOf("/DETAIL") != -1)  {
    make_detailHTML();                                  // see TAB html
  } else {  
    make_mainHTML();                                    // see TAB html
    }               

  delay(1);
  client.stop();
  Serial.println("Client disonnected");
  Serial.println("");

}  // end loop

