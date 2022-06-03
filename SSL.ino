#define Pin_Alarm D1                      
#define PIR_Sensor D0

int Waiting_Time = 5000;                 

void setup() {
  pinMode(PIR_Sensor, INPUT);             
  pinMode(Pin_Alarm, OUTPUT);            
  digitalWrite(Pin_Alarm, LOW);           
}

void loop(){
  int state = digitalRead(PIR_Sensor);    
  delay(500);                             
  
    if(state == HIGH){                
      digitalWrite (Pin_Alarm, HIGH);     
      delay(Waiting_Time);                                         
    }
    else {
      digitalWrite (Pin_Alarm, LOW);      
   }
}
