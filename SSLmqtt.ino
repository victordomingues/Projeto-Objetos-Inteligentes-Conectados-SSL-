# include <ESP8266WiFi.h>
# include <PubSubClient.h>

# define ID_MQTT "SSL_mqtt"
# define TOPICO_PUBLISH_PIR_SENSOR "topico_pir_sensor"

const char * BROKER = "test.mosquitto.org";
int PORTA = 1883;

const int Pin_Alarm = D1;
const int PIR_Sensor = D0;

char * SSID = "#####";
char * PASSWORD = "#####";

WiFiClient espClient;
PubSubClient MQTT(espClient);

char * msg = "";
int Waiting_Time = 5000; 

void ReconectMQTT(void) {
  if (!MQTT.connected()){
    while (!MQTT.connected()) {
      Serial.print("* Conectando-se ao MQTT: ");
      Serial.println(BROKER);
      if (MQTT.connect(ID_MQTT)) {
        Serial.println("Conectado com sucesso");
      } else {
        Serial1.println("Falha ao se conectar.");
        Serial.println("Reiniciando em 2s");
        delay(2000);
      }
    }
  }
}

void StartMQTT(void) {
  MQTT.setServer(BROKER, PORTA);
}

void ReconectWIFI(void) {
  if (WiFi.status() == WL_CONNECTED)
    return;
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Conectado na rede ");
}

void ConsultaConexoes(void) {
  ReconectWIFI(); 
  ReconectMQTT(); 
}

void setup() {
  pinMode(PIR_Sensor, INPUT);             
  pinMode(Pin_Alarm, OUTPUT);            
  digitalWrite(Pin_Alarm, LOW); 

  StartMQTT();
}

void loop(){
  ConsultaConexoes();
  int state = digitalRead(PIR_Sensor);                              
  Serial.println(state);
  
  if(state == HIGH){                
    digitalWrite (Pin_Alarm, HIGH);        
    msg = "0";                                      
  }
  else {
    digitalWrite (Pin_Alarm, LOW); 
    msg = "1";     
  }


  Serial.println("Valor da mensagem enviada");
  Serial.println(msg);

  MQTT.publish(TOPICO_PUBLISH_PIR_SENSOR, msg);
  MQTT.loop();
  delay(10000);
  
}
