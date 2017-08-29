//____________________________________________________________________________________make_mainHTML

void make_mainHTML() {

  String s = ("HTTP/1.1 200 OK\r\n");
  s += ("Content-Type: text/html\r\n\r\n");
  s += ("<!DOCTYPE HTML>\r\n<html>\r\n");
  s += ("<head> <title>myESP KLL engineering</title> </head>\r\n");
  s += ("<body>\r\n");
  s += ("i am a SoC development board <b>");
  s += (IAM); 
  s += ("</b><br> running as webserver / WIFI remote IO / (RPI_v1.3) ");

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
  s += (" _<a href=\"/LED=OFF\"><button> OFF </button></a>");  
  } else {
  s += ("OFF");
  s += (" _<a href=\"/LED=ON\"><button> ON </button></a>");
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
  s += (" _<a href=\"/DAC1UP\"><button>  UP </button></a>");  
  s += (" _<a href=\"/DAC1DN\"><button> DOWN </button></a>");  
  s += (" <br>\r\n");
#endif
  client.print(s);

#if defined usePID
  s = ("<hr><h2>uPCS2 for UNO and ESP</h2>");

  s += ("______PID1____________________AinPin: P");  s += (PID1_inpin); s += (" AoutPin: P");  s += (PID1_outpin); s += ("<br>");
  s += ("PV: ");
  s += (PID1_PV);   s += ("%");
  s += (" <br>\r\n");

  s += ("SP: ");
  s += (PID1_SP); s += ("%");
  s += (" _<a href=\"/SPUP\"><button> SP UP </button></a>");  
  s += (" _<a href=\"/SPDN\"><button> SP DOWN </button></a><br>");  

  s += ("MODE: "); 
  if (PID1_MD == 1) { 
     s += (" MAN ");
     s += (" _<a href=\"/PIDAUTO\"><button> AUTO </button></a><br>");  
  }
  if (PID1_MD == 2) { 
     s += (" AUTO ");
     s += (" _<a href=\"/PIDMAN\"><button> MAN </button></a><br>");    
  }
  
  s += ("OUT: ");  s += (PID1_OV);  s += ("%");
  if (PID1_MD == 1) {
    s += (" _<a href=\"/DAC2UP\"><button> OVP UP </button></a>");  
    s += (" _<a href=\"/DAC2DN\"><button> OVP DOWN </button></a>");  
  }
 
  s += ("<br>\r\n");
  s += ("______IND1____________________AinPin: P");  s += (IND1_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND1_PV);  s += ("%"); s += (" <br>\r\n");  // 
  s += ("______IND2____________________AinPin: P");  s += (IND2_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND2_PV);  s += ("%"); s += (" <br>\r\n");  // 
  s += ("______IND3____________________AinPin: P");  s += (IND3_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND3_PV);  s += ("%"); s += (" <br>\r\n");  // 
  s += ("______IND4____________________AinPin: P");  s += (IND4_inpin);   s += ("<br>");
  s += ("PV: "); s += (IND4_PV);  s += ("%"); s += (" <br>\r\n");
  s += ("______________________________<br> see: _<a href=\"/DETAIL\"><button> DETAIL </button></a><br>\r\n");  

  client.print(s);
    
#endif
  s = ("<hr>\r\n");
  s += ("\r\n");
  s += ("</body>");
  s += ("</html>");

  client.print(s);

}

//____________________________________________________________________________________make_detailHTML
void make_detailHTML() {
#if defined usePID

  String s = ("HTTP/1.1 200 OK\r\n");
  s += ("Content-Type: text/html\r\n\r\n");
  s += ("<!DOCTYPE HTML>\r\n<html>\r\n");
  s += ("<head> <title>myESP KLL engineering</title> \r\n");
  s += ("</head><body>\r\n<hr>");

  s += ("<h2>DETAIL</h2>\r\n");
  client.print(s);
// format with html table 
  s = ("<table><tr><td>\r\n");  client.print(s);
  client.print(show_tuninganalogSVG());
  s = ("</td><td width=\"10%\">\r\n");  client.print(s); s="";
  if (PID1_MD == 1) {
    s += (" <a href=\"/DETAIL/DAC2UP\"><button> OV +</button></a><br>");  
    s += (" <a href=\"/DETAIL/DAC2DN\"><button> OV-</button></a><br>");  
  }
  // mode button
  if (PID1_MD == 1) { 
       s += (" <a href=\"/DETAIL/PIDAUTO\"><button> AUTO </button></a>");  
  }
  if (PID1_MD == 2) { 
       s += (" <a href=\"/DETAIL/PIDMAN\"><button> MAN </button></a>");    
  }
  s += ("</td><td>\r\n");  client.print(s);
  client.print(show_PID_FP_SVG());
  s = ("</td><td width=\"10%\">\r\n");  client.print(s); s="";

  s += (" <a href=\"/DETAIL/SPUP\"><button> SP +</button></a><br>");  
  s += (" <a href=\"/DETAIL/SPDN\"><button> SP -</button></a><br>");  
  s += ("</td><td>\r\n");  client.print(s);
  client.print(show_tuningSVG());
  s = ("</td></tr></table>\r\n");
  client.print(s);

  s = ("<br>");
/*  
  s += ("PID1_PV: "); s += (PID1_PV); s += ("<br>");
  s += ("PID1_SP: "); s += (PID1_SP); s += ("<br>");
  s += ("PID1_OV: "); s += (PID1_OV); s += ("<br>");
  s += ("PID1_MD: "); s += (PID1_MD); s += ("<br>");


  s += ("PID1_gain: "); s += (PID1_gain); s += ("<br>");
  s += ("PID1_reset: "); s += (PID1_reset); s += ("<br>");
  s += ("PID1_rate: "); s += (PID1_rate); s += ("<br>");
  s += ("PID1_action: "); s += (PID1_action); s += ("<br>");
  s += ("PID1_outdir: "); s += (PID1_outdir); s += ("<br>");
  s += ("PID1_Ctimlim: "); s += (PID1_Ctimlim); s += ("<br>");


  s += ("PID1_PVALL: "); s += (PID1_PVALL); s += ("<br>");
  s += ("PID1_PVALO: "); s += (PID1_PVALO); s += ("<br>");
  s += ("PID1_PVAHI: "); s += (PID1_PVAHI); s += ("<br>");
  s += ("PID1_PVAHH: "); s += (PID1_PVAHH); s += ("<br>");
  s += ("PID1_PVfil0: "); s += (PID1_PVfil0); s += ("<br>");

  s += ("PID1_OVALO: "); s += (PID1_OVALO); s += ("<br>");
  s += ("PID1_OVAHI: "); s += (PID1_OVAHI); s += ("<br>");
  s += ("PID1_outmax: "); s += (PID1_outmax); s += ("<br>");
  s += ("PID1_outmin: "); s += (PID1_outmin); s += ("<br>");
  
  s += ("<br>");
  s += ("IND1_PV: "); s += (IND1_PV); s += ("<br>");
  s += ("IND1_PVfil0: "); s += (IND1_PVfil0); s += ("<br>");
  s += ("IND1_PVALL: "); s += (IND1_PVALL); s += ("<br>");
  s += ("IND1_PVALO: "); s += (IND1_PVALO); s += ("<br>");
  s += ("IND1_PVAHI: "); s += (IND1_PVAHI); s += ("<br>");
  s += ("IND1_PVAHH: "); s += (IND1_PVAHH); s += ("<br>");
  s += ("<br>");
  s += ("IND2_PV: "); s += (IND2_PV); s += ("<br>");
  s += ("IND2_PVfil0: "); s += (IND2_PVfil0); s += ("<br>");
  s += ("IND2_PVALL: "); s += (IND2_PVALL); s += ("<br>");
  s += ("IND2_PVALO: "); s += (IND2_PVALO); s += ("<br>");
  s += ("IND2_PVAHI: "); s += (IND2_PVAHI); s += ("<br>");
  s += ("IND2_PVAHH: "); s += (IND2_PVAHH); s += ("<br>");
  s += ("<br>");
  s += ("IND3_PV: "); s += (IND3_PV); s += ("<br>");
  s += ("IND3_PVfil0: "); s += (IND3_PVfil0); s += ("<br>");
  s += ("IND3_PVALL: "); s += (IND3_PVALL); s += ("<br>");
  s += ("IND3_PVALO: "); s += (IND3_PVALO); s += ("<br>");
  s += ("IND3_PVAHI: "); s += (IND3_PVAHI); s += ("<br>");
  s += ("IND3_PVAHH: "); s += (IND3_PVAHH); s += ("<br>");
  s += ("<br>");
  s += ("IND4_PV: "); s += (IND4_PV); s += ("<br>");
  s += ("IND4_PVfil0: "); s += (IND4_PVfil0); s += ("<br>");
  s += ("IND4_PVALL: "); s += (IND4_PVALL); s += ("<br>");
  s += ("IND4_PVALO: "); s += (IND4_PVALO); s += ("<br>");
  s += ("IND4_PVAHI: "); s += (IND4_PVAHI); s += ("<br>");
  s += ("IND4_PVAHH: "); s += (IND4_PVAHH); s += ("<br>");

*/
  s += ("<a href=\"/\"><button> HOME </button></a>");  

  s += ("<hr>\r\n");
  s += ("\r\n");
  s += ("</body>");
  s += ("</html>");

  client.print(s);

#endif  

}

