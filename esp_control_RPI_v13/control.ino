#if defined usePID


#define DEBUG

#ifdef DEBUG
#define db(t,x)     if(t) { Serial.print(x); }
#define dbln(t,x)   if(t) { Serial.println(x); }
#else
#define db(t,x)     // define empty, so macro does nothing
#define dbln(t,x)
#endif 


boolean Diag0 = true;                                                          // loop point reporting
unsigned long D0lasttime = 0;                                                  // last set ON
unsigned long D0endtime = 5000;                                                // timeout to not spam USB

boolean Diags = false;                                                         // loop point PV simulation
float w = 0.0;

boolean Diag1 = false;                                                         // job control diagnostic
boolean Diag2 = false;                                                         // serial diagnostic
boolean Diag3 = false;                                                         // PID diagnostic
unsigned long cmdtimeout= 500;                                                 // millis for one full line
String ERRTXT = "";
int DBI = -1;
long RPI_CP = -1;


// SIM analog points
float PVsim = 0.0;
float SPsim = 0.0;
float OVsim = 0.0;
float MDsim = 2.0;

float PVin = 0.0;                         // for all reading raw value from hardware

// PID1 global
#define PID1_DBI  1                   // unique point number
// data to JSON:
/*
float PID1_PV = 0.0;
float PID1_SP = 0.0;
float PID1_OV = 0.0;
float PID1_MD = 2.0;
*/

float PID1_delta = 0.0;               // setpoint  SP, RSP or CAS  - PV
float PID1_deltamem = 0.0;            // last delta
float PID1_integral = 0.0;            // calc I
float PID1_derivate = 0.0;            // calc D 
int PID1_mode=1;                      // PID_mode   0=safe, 1=MAN, 2=AUTO
int PID1_oldmode=1;                   // memory
boolean PID1_en = false;
int PID1_OUT = 0;
#define PID1_outmax 100.0  
#define PID1_outmin 0.0
boolean needARWU = false;                     // test anti reset windup

float PID1_PVfil0=0.01;                       // times old PV   +
// float PID1_PVfil1=0.99                     // times new input      // PVfil0 + PVfil1 == 1.0

float PID1_PVALL=0.0;                   // PV Alarm LOLO
float PID1_PVALO=0.0;                   // PV Alarm LO
float PID1_PVAHI=100.0;                   // PV Alarm HI
float PID1_PVAHH=100.0;                   // PV Alarm HIHI

float PID1_gain=0.30;                 // P = gain
float PID1_reset=0.20;                // I = reset
float PID1_rate=0.0;                  // D = rate
int PID1_action=-1;                   // -1 reverse / 1 direct action; heater / cooler loop
int PID1_outdir=1;                    // -1 invert / 1 direct ; valve type failure open / close 

#define PID1_epsilon 0.01             // low lim for suppress I action
#define PID1_ARWUh 105.0              // anti reset windup, limit I action
#define PID1_ARWUl -5.0               // anti reset windup, limit I action
boolean PID1_needARWU = false;            // new V405

#define PID1_OUTtrack 1               // enable for switch from 5 ( or4) to 2!
#define PID1_SPtrack 0                // disable
float PID1_Ctimlim= 1000.0;              // = sampletime millisec 
float PID1_OVALO=0.0;                 // OV Alarm LO
float PID1_OVAHI=100.0;               // OV Alarm HI


//____________________________________________________________________________
//float IND1_PV = 0.0;
float IND1_PVfil0=0.01;                   // times old PV   +
float IND1_PVfil1=1.0-IND1_PVfil0;                   // times new input 
// PVfil0 + PVfil1 == 1.0
float IND1_PVALL=0.0;                     // PV Alarm LOLO
float IND1_PVALO=0.0;                     // PV Alarm LO
float IND1_PVAHI=100.0;                   // PV Alarm HI
float IND1_PVAHH=100.0;                   // PV Alarm HIHI

//float IND2_PV = 0.0;
float IND2_PVfil0=0.01;                   // times old PV   +
float IND2_PVfil1=1.0-IND2_PVfil0;        // times new input 
float IND2_PVALL=0.0;                     // PV Alarm LOLO
float IND2_PVALO=0.0;                     // PV Alarm LO
float IND2_PVAHI=100.0;                   // PV Alarm HI
float IND2_PVAHH=100.0;                   // PV Alarm HIHI


//float IND3_PV = 0.0;
float IND3_PVfil0=0.01;                   // times old PV   +
float IND3_PVfil1=1.0-IND3_PVfil0;        // times new input 
float IND3_PVALL=0.0;                     // PV Alarm LOLO
float IND3_PVALO=0.0;                     // PV Alarm LO
float IND3_PVAHI=100.0;                   // PV Alarm HI
float IND3_PVAHH=100.0;                   // PV Alarm HIHI


//float IND4_PV = 0.0;
float IND4_PVfil0=0.01;                   // times old PV   +
float IND4_PVfil1=1.0-IND4_PVfil0;        // times new input 
float IND4_PVALL=0.0;                     // PV Alarm LOLO
float IND4_PVALO=0.0;                     // PV Alarm LO
float IND4_PVAHI=100.0;                   // PV Alarm HI
float IND4_PVAHH=100.0;                   // PV Alarm HIHI


float DCD1_PV = 0.0;
float DCD1_SP = 0.0;
float DCD1_OV = 0.0;
float DCD1_MD = 0.0;



//_____________________________________________________________________serial print tools JSON (NOT USED HERE)

void PID1_detail() {
  db(true,"{'PID1':{'PV':"); db(true,PID1_PV); 
            db(true,",'SP':"); db(true,PID1_SP); 
            db(true,",'OV':"); db(true,PID1_OV); 
            db(true,",'MD':"); db(true,PID1_MD);
            db(true,",'tPV':"); db(true,PID1_PVfil0);
            db(true,",'tPI':"); db(true,PID1_gain);
            db(true,",'tII':"); db(true,PID1_reset);
            db(true,",'tDI':"); db(true,PID1_rate);
            db(true,",'tAI':"); db(true,PID1_action);
            db(true,",'tOI':"); db(true,PID1_outdir);
            db(true,",'tTI':"); db(true,PID1_Ctimlim);
// alarm limits
            db(true,",'ALL':"); db(true,PID1_PVALL);
            db(true,",'ALO':"); db(true,PID1_PVALO);
            db(true,",'AHI':"); db(true,PID1_PVAHI);
            db(true,",'AHH':"); db(true,PID1_PVAHH);
            db(true,",'LOV':"); db(true,PID1_OVALO);
            db(true,",'HOV':"); db(true,PID1_OVAHI);
// output limits  clamps
            db(true,",'OLH':"); db(true,PID1_outmax);
            db(true,",'OLL':"); db(true,PID1_outmin);

            dbln(true,"}}");                     
}

void IND1_detail() {
  db(true,"{'IND1':{'PV':"); db(true,IND1_PV); 
            db(true,",'tPV':"); db(true,IND1_PVfil0);             
            db(true,",'ALL':"); db(true,IND1_PVALL);
            db(true,",'ALO':"); db(true,IND1_PVALO);
            db(true,",'AHI':"); db(true,IND1_PVAHI);
            db(true,",'AHH':"); db(true,IND1_PVAHH);
            dbln(true,"}}");                   
  
}
void IND2_detail() {
  db(true,"{'IND2':{'PV':"); db(true,IND2_PV); 
            db(true,",'tPV':"); db(true,IND2_PVfil0);
            db(true,",'ALL':"); db(true,IND2_PVALL);
            db(true,",'ALO':"); db(true,IND2_PVALO);
            db(true,",'AHI':"); db(true,IND2_PVAHI);
            db(true,",'AHH':"); db(true,IND2_PVAHH);
            dbln(true,"}}");  
}
void IND3_detail() {
  db(true,"{'IND3':{'PV':"); db(true,IND3_PV); 
            db(true,",'tPV':"); db(true,IND3_PVfil0);             
            db(true,",'ALL':"); db(true,IND3_PVALL);
            db(true,",'ALO':"); db(true,IND3_PVALO);
            db(true,",'AHI':"); db(true,IND3_PVAHI);
            db(true,",'AHH':"); db(true,IND3_PVAHH);
            dbln(true,"}}");  
  
}
void IND4_detail() {
  db(true,"{'IND4':{'PV':"); db(true,IND4_PV); 
            db(true,",'tPV':"); db(true,IND4_PVfil0);             
            db(true,",'ALL':"); db(true,IND4_PVALL);
            db(true,",'ALO':"); db(true,IND4_PVALO);
            db(true,",'AHI':"); db(true,IND4_PVAHI);
            db(true,",'AHH':"); db(true,IND4_PVAHH);
            dbln(true,"}}");  
  
}
void DCD1_detail() {
  db(true,"{'DCD1':{'PV':"); db(true,DCD1_PV); 
            db(true,",'SP':"); db(true,DCD1_SP);
            db(true,",'OV':"); db(true,DCD1_OV);
            db(true,",'MD':"); db(true,DCD1_MD);
            dbln(true,"}}");  
  
}

void setPID1_OV(float PIDval) {  if ( PIDval >= 0.0 || PIDval <= 100.0 ) { PID1_OV = PIDval; dbln(Diag2," > OVset");} }
void setPID1_SP(float PIDval) {  if ( PIDval >= 0.0 || PIDval <= 100.0 ) { PID1_SP = PIDval; dbln(Diag2," > SPset");} }
void setPID1_MD(float PIDval) {  if ( PIDval == 0.0 || PIDval == 1.0 || PIDval == 2.0 ) { PID1_MD = PIDval; dbln(Diag2," > MDset"); } }

//_____________________________________________________________________PID1
void PID1() {
  dbln(Diag1," PID: 1");
  if ( Diags ) {
    w = w + 0.0174533;                                      //    2*3.14159/360
    if ( w >= 6.28318 ) { w = 0.0;}
    PVsim = 50.0 + 20.0*sin(w);
    SPsim = 50.0;
    OVsim = 30.0 - (PVsim - SPsim);
    MDsim = 2.0;

    
    PID1_PV = PVsim;
    PID1_SP = SPsim;
    PID1_OV = OVsim;
    PID1_MD = MDsim;
            } else {

#if defined useESP32                                                                      // here wire your I/O
    PVin = analogRead(PID1_inpin);
#else
// ESP8266 need A0 or linked sensors
#endif
    PVin = map(PVin,0,Ainres,0,10000)/100.0;
    PID1_PV = PID1_PV * PID1_PVfil0 + ( 1.0 - PID1_PVfil0) * PVin;    // apply numeric filter
    PID1_RPV = PID1_LOR + ( PID1_HIR - PID1_LOR )* PID1_PV / 100.0;
    PID1_RSP = PID1_LOR + ( PID1_HIR - PID1_LOR )* PID1_SP / 100.0;
                                                                      // PID loop 
    PID1_mode = int(PID1_MD);
    
    switch (PID1_mode) {                                             // 
    case 0:
      PID1_en = false;
      PID1_OV = PID1_outmin;                                       // not safe mode, limit used 
    break;    
    case 1:                                                        // MAN
      PID1_en = false;    
      PID1_OV = PID1_OV;                                           // drive same OUTPUT      
    break;
    case 2:                                                        // AUTO
      PID1_en = true;
      PID1_delta = PID1_SP - PID1_PV;
      
      if ( abs(PID1_delta) > PID1_epsilon ) {                                // only integrate if not too small error  
        if (!needARWU) { 
          PID1_integral = PID1_integral + PID1_delta * PID1_Ctimlim/1000;  
          }            
      }
      PID1_derivate = ( PID1_delta - PID1_deltamem )*1000/PID1_Ctimlim;

      PID1_OV= PID1_action * ( PID1_gain * PID1_delta + PID1_reset * PID1_integral + PID1_rate * PID1_derivate );       // THATS THE PID CALC LINE 
      if ((PID1_OV > PID1_ARWUh) || (PID1_OV < PID1_ARWUl) ) { needARWU = true;  dbln(Diag3,"needARWU"); } else { needARWU = false; } 
      PID1_deltamem=PID1_delta; 
      db(Diag3,"delta "); db(Diag3,PID1_delta); db(Diag3," integral "); db(Diag3,PID1_integral); db(Diag3," derivat "); db(Diag3,PID1_derivate); db(Diag3," out "); db(Diag3,PID1_OV); dbln(Diag3," PID1 ")
    break;
    default:
      PID1_en = false;
      PID1_OV = 0.0;                                               // safe mode, no limit used
    }// end switch mode
    // process output
    if (PID1_OV > PID1_outmax ) { PID1_OV = PID1_outmax; }        // use limit
    if (PID1_OV < PID1_outmin ) { PID1_OV = PID1_outmin; }       
    // drive output to digital hardware
    if (PID1_outdir < 0 ) {
      PID1_OUT = map(int(100.0*PID1_OV),0,10000,255,0);              // output invers / increase to close PWM      
    }else {
      PID1_OUT = map(int(100.0*PID1_OV),0,10000,0,255);              // PWM      
    }
//    analogWrite(PID1_outpin,PID1_OUT);   change to ESP DAC2

#if defined useESP32
    dacWrite(PID1_outpin,PID1_OUT);
#else

#endif

    db(Diag3,"pwm "); db(Diag3,PID1_OUT); db(Diag3," D_"); db(Diag3,PID1_outpin); db(Diag3," MD "); db(Diag3,PID1_mode); dbln(Diag3," PID1 ")
                   }
                   
// output JSON PID string
    db(Diag0,"{'PID1':{'PV':"); db(Diag0,PID1_PV); 
            db(Diag0,",'SP':"); db(Diag0,PID1_SP); 
            db(Diag0,",'OV':"); db(Diag0,PID1_OV); 
            db(Diag0,",'MD':"); db(Diag0,PID1_MD); 
            dbln(Diag0,"}}");                   
  PID1_ALM = 0;
  if ( PID1_OV <= PID1_OVALO ) { PID1_ALM = 5; }
  if ( PID1_OV >= PID1_OVAHI ) { PID1_ALM = 6; }
  if ( PID1_PV <= PID1_PVALO ) { PID1_ALM = 2; }
  if ( PID1_PV <= PID1_PVALL ) { PID1_ALM = 1; }
  if ( PID1_PV >= PID1_PVAHI ) { PID1_ALM = 3; }
  if ( PID1_PV >= PID1_PVAHH ) { PID1_ALM = 4; }
}

//_____________________________________________________________________IND1
void IND1() {
  dbln(Diag1," IND: 1");
  if ( Diags ) {
    w = w + 0.0174533;                                      //    2*3.14159/360
    if ( w >= 6.28318 ) { w = 0.0;}
    PVsim = 10.0 + 5.0*sin(w);
    IND1_PV = PVsim;
              } else {
  // here wire your I/O
#if defined useESP32                                                                      // here wire your I/O
    PVin = analogRead(IND1_inpin);
#else
// ESP8266 need linked sensors
#endif
    PVin = map(PVin,0,Ainres,0,10000)/100.0;
    IND1_PV = IND1_PV * IND1_PVfil0 + ( 1.0 - IND1_PVfil0) * PVin;    // apply numeric filter
    
                      }
    db(Diag0,"{'IND1':{'PV':");db(Diag0,IND1_PV); dbln(Diag0,"}}");

  IND1_ALM = 0;
  if ( IND1_PV <= IND1_PVALO ) { IND1_ALM = 2; }
  if ( IND1_PV <= IND1_PVALL ) { IND1_ALM = 1; }
  if ( IND1_PV >= IND1_PVAHI ) { IND1_ALM = 3; }
  if ( IND1_PV >= IND1_PVAHH ) { IND1_ALM = 4; }

}

//_____________________________________________________________________IND2
void IND2() {
  dbln(Diag1," IND: 2");
  if ( Diags ) {
    w = w + 0.0174533;                                      //    2*3.14159/360
    if ( w >= 6.28318 ) { w = 0.0;}
    PVsim = 20.0 + 5.0*sin(w);
    IND2_PV = PVsim;
              } else {
  // here wire your I/O
#if defined useESP32                                                                      // here wire your I/O
    PVin = analogRead(IND2_inpin);
#else
// ESP8266 need linked sensors
#endif
    PVin = map(PVin,0,Ainres,0,10000)/100.0;
    IND2_PV = IND2_PV * IND2_PVfil0 + ( 1.0 - IND2_PVfil0) * PVin;    // apply numeric filter
    
                      }
    db(Diag0,"{'IND2':{'PV':");db(Diag0,IND2_PV); dbln(Diag0,"}}");

  IND2_ALM = 0;
  if ( IND2_PV <= IND2_PVALO ) { IND2_ALM = 2; }
  if ( IND2_PV <= IND2_PVALL ) { IND2_ALM = 1; }
  if ( IND2_PV >= IND2_PVAHI ) { IND2_ALM = 3; }
  if ( IND2_PV >= IND2_PVAHH ) { IND2_ALM = 4; }
}

//_____________________________________________________________________IND3
void IND3() {
  dbln(Diag1," IND: 3");
  if ( Diags ) {
    w = w + 0.0174533;                                      //    2*3.14159/360
    if ( w >= 6.28318 ) { w = 0.0;}
    PVsim = 30.0 + 5.0*sin(w);
    IND3_PV = PVsim;
              } else {
  // here wire your I/O
#if defined useESP32                                                                      // here wire your I/O
    PVin = analogRead(IND3_inpin);
#else
// ESP8266 need linked sensors
#endif
    PVin = map(PVin,0,Ainres,0,10000)/100.0;
    IND3_PV = IND3_PV * IND3_PVfil0 + ( 1.0 - IND3_PVfil0) * PVin;    // apply numeric filter
    
                      }
    db(Diag0,"{'IND3':{'PV':");db(Diag0,IND3_PV); dbln(Diag0,"}}");

  IND3_ALM = 0;
  if ( IND3_PV <= IND3_PVALO ) { IND3_ALM = 2; }
  if ( IND3_PV <= IND3_PVALL ) { IND3_ALM = 1; }
  if ( IND3_PV >= IND3_PVAHI ) { IND3_ALM = 3; }
  if ( IND3_PV >= IND3_PVAHH ) { IND3_ALM = 4; }
}

//_____________________________________________________________________IND4
void IND4() {
  dbln(Diag1," IND: 4");
  if ( Diags ) {
    w = w + 0.0174533;                                      //    2*3.14159/360
    if ( w >= 6.28318 ) { w = 0.0;}
    PVsim = 40.0 + 5.0*sin(w);
    IND4_PV = PVsim;
              } else {
  // here wire your I/O
#if defined useESP32                                                                      // here wire your I/O
    PVin = analogRead(IND4_inpin);
#else
// ESP8266 need linked sensors
#endif
    PVin = map(PVin,0,Ainres,0,10000)/100.0;
    IND4_PV = IND4_PV * IND4_PVfil0 + ( 1.0 - IND4_PVfil0) * PVin;    // apply numeric filter
    
                      }
    db(Diag0,"{'IND4':{'PV':");db(Diag0,IND4_PV); dbln(Diag0,"}}");

  IND4_ALM = 0;
  if ( IND4_PV <= IND4_PVALO ) { IND4_ALM = 2; }
  if ( IND4_PV <= IND4_PVALL ) { IND4_ALM = 1; }
  if ( IND4_PV >= IND4_PVAHI ) { IND4_ALM = 3; }
  if ( IND4_PV >= IND4_PVAHH ) { IND4_ALM = 4; }
}

//_______________________________________________________________________________control_point_timer
void control_point_timer() {
  Ccount = Ccount + 1;
  if ( Ccount == Ccount_end ) {
    Ccount = 0;
    Ctime = millis();
    if (( Ctime - Ctime_old ) >= Ctime_delta ) {
      Ctime_old = Ctime;
      job = job + 1;
      if (job >= maxjob ) { job = 0; }
      run_control(job);     }  }  }
      
//_______________________________________________________________________________run_control
void run_control(int myjob) {
  db(Diag1,"job: "); db(Diag1,myjob);
  if(myjob == 0){ PID1(); }
  if(myjob == 1){ IND1(); }
  if(myjob == 2){ PID1(); }
  if(myjob == 3){ IND2(); }
  if(myjob == 4){ PID1(); }
  if(myjob == 5){ IND3(); }
  if(myjob == 6){ PID1(); }
  if(myjob == 7){ IND4(); }   }

#endif
