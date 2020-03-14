
#include <SoftwareSerial.h>       
int sensor_pin = A1;                               

volatile int heart_rate;          

volatile int analog_data;              

volatile int time_between_beats = 600;            

volatile boolean pulse_signal = false;    

volatile int beat[10];         //heartbeat values will be sotred in this array    

volatile int peak_value = 512;          

volatile int trough_value = 512;        

volatile int thresh = 525;              

volatile int amplitude = 100;                 

volatile boolean first_heartpulse = true;      

volatile boolean second_heartpulse = false;    

volatile unsigned long samplecounter = 0;   //This counter will tell us the pulse timing

volatile unsigned long lastBeatTime = 0;


int tempPin=A0;
 int val;
char cecg[10],ctem[10],cpulse[10];
int Signal,tem;
float ecg;              
int Threshold = 550;         

SoftwareSerial mySerial(2, 3);  //TX RX
void setup() {
   
   mySerial.begin(9600);
   Serial.begin(115200);    
    pinMode(10,INPUT);
  pinMode(11,INPUT);
interruptSetup();  

}


void loop() {
 
 Serial.print("BPM: ");

 Serial.println(heart_rate);

 delay(200); //  take a break               

val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;
tem=cel;
Serial.print("Temp - "); 
 Serial.print(tem); 
  Serial.print(" C ");     
  delay(1000);
   Serial.println("ECG:");
  if((digitalRead(10)==1)||(digitalRead(11)==1)){
      Serial.println("Gagal");
//      ecg="Gagal";
  }
  else{
    ecg=analogRead(A2);
     Serial.println(ecg);
     
  }
itoa(ecg, cecg, 10);
itoa(heart_rate, cpulse, 10);
itoa(tem, ctem, 10);  
   mySerial.write(cecg);
    mySerial.write("|");
    mySerial.write(cpulse);
    mySerial.write("|");
  mySerial.write(ctem);
  
  
 
delay(2000);

 
}
void interruptSetup()

{    

  TCCR2A = 0x02;  // This will disable the PWM on pin 3 and 11

  OCR2A = 0X7C;   // This will set the top of count to 124 for the 500Hz sample rate

  TCCR2B = 0x06;  // DON'T FORCE COMPARE, 256 PRESCALER

  TIMSK2 = 0x02;  // This will enable interrupt on match between OCR2A and Timer

  sei();          // This will make sure that the global interrupts are enable

}


ISR(TIMER2_COMPA_vect)

{ 

  cli();                                     

  analog_data = analogRead(sensor_pin);            

  samplecounter += 2;                        

  int N = samplecounter - lastBeatTime;      


  if(analog_data < thresh && N > (time_between_beats/5)*3)

    {     

      if (analog_data < trough_value)

      {                       

        trough_value = analog_data;

      }

    }


  if(analog_data > thresh && analog_data > peak_value)

    {        

      peak_value = analog_data;

    }                          



   if (N > 250)

  {                            

    if ( (analog_data > thresh) && (pulse_signal == false) && (N > (time_between_beats/5)*3) )

      {       

        pulse_signal = true;          

        

        time_between_beats = samplecounter - lastBeatTime;

        lastBeatTime = samplecounter;     



       if(second_heartpulse)

        {                        

          second_heartpulse = false;   

          for(int i=0; i<=9; i++)    

          {            

            beat[i] = time_between_beats; //Filling the array with the heart beat values                    

          }

        }


        if(first_heartpulse)

        {                        

          first_heartpulse = false;

          second_heartpulse = true;

          sei();            

          return;           

        }  


      word runningTotal = 0;  


      for(int i=0; i<=8; i++)

        {               

          beat[i] = beat[i+1];

          runningTotal += beat[i];

        }


      beat[9] = time_between_beats;             

      runningTotal += beat[9];   

      runningTotal /= 10;        

      heart_rate = 60000/runningTotal;

    }                      

  }




  if (analog_data < thresh && pulse_signal == true)

    {  

    

      pulse_signal = false;             

      amplitude = peak_value - trough_value;

      thresh = amplitude/2 + trough_value; 

      peak_value = thresh;           

      trough_value = thresh;

    }


  if (N > 2500)

    {                          

      thresh = 512;                     

      peak_value = 512;                 

      trough_value = 512;               

      lastBeatTime = samplecounter;     

      first_heartpulse = true;                 

      second_heartpulse = false;               

    }


  sei();                                

}
