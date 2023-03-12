#include <Arduino.h>

// Librairies Serveur Web
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// Librairies MQTT
#include <PubSubClient.h>

// Camera libraries
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"

#include <configCamera.h>
camera_fb_t  * fb;
const uint8_t PIN_LED = 4;

// Maison
//const char *SSID = "Livebox-A250";
//const char *PWD= "yezvypYswaeUhtGGTL";

// Partage Wifi GSM
const char *SSID = "AndroidAP1550";
const char *PWD= "973b6716f3fb";

// Paramétrage MQTT
const char * ROBOT_NUM = "01";
const char * HOSTNAME = "LES BRICOLOS";
const char * mqtt_server = "192.168.43.14";
const char * mqtt_user = "nao974";
const char * mqtt_passwd = "az$er";
WiFiClient espClientWifi;
PubSubClient mqtt(espClientWifi);
char mqttTopic[64]; // array pour le nom du topic à envoyer
char mqttMsg[16]; // array pour les données des messages à envoyer
uint8_t mqttInitRobot = 1;
#include <mqtt.h>

// Paramétrage serveur Web
AsyncWebServer server(80);
#include <webHandle.h>

void setup() {
// Initialisation de la liaison série
    Serial.begin(115200);
    delay(1000);
    Serial.println("\nDémarrage");

// LED Flash
    pinMode(PIN_LED, OUTPUT);

// Initialisation du gestionnaire de fichier SPIFFS
    Serial.println("\nInit SPIFFS");
    if ( !SPIFFS.begin() ) {
        Serial.println("   Erreur SPIFFS...");
        return;
    }
    Serial.println("   Fin Init SPIFFS OK!");
    
// Connexion au WIFI
    Serial.println("\nInit Wifi"); 
    WiFi.begin(SSID, PWD);
	Serial.print("   Tentative de connexion...");
	
	while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
		delay(100);
	}
	Serial.println("");
	Serial.println("   Connexion etablie!");
	Serial.print("   Adresse IP: ");
	Serial.println(WiFi.localIP());

// Configuration du Broker MQTT
    mqtt.setServer(mqtt_server, 1883);
    mqtt.setCallback(callback);

// Initialisation de la camera
    Serial.println("\nInitialisation du module Camera");
    configESPCamera();
    Serial.println("   Camera OK!");  

// Démarrage du serveur Web 
    server.begin();
    Serial.println("\nServeur Web actif!");
    initHandleWeb();
}


void loop() {

// sommes nous connectés au serveur MQTT ?
    if (!mqtt.connected() )
        reconnect();

// gestion MQTT
    mqtt.loop();

// Déclaration initiale du robot sur le serveur MQTT     
    if (mqtt.connected() && mqttInitRobot == 1) {
        sprintf(mqttTopic, "ROBOTS/%s/Nom_Equipe", ROBOT_NUM);    
        mqtt.publish(mqttTopic, HOSTNAME);
        sprintf(mqttTopic, "ROBOTS/%s/TimeStamp_Depart", ROBOT_NUM);    
        sprintf(mqttMsg, "%d", millis());
        mqtt.publish(mqttTopic, mqttMsg);
        sprintf(mqttTopic, "ROBOTS/%s/IP", ROBOT_NUM);
        sprintf(mqttMsg, "%s", "192.168.43.58"); //WiFi.localIP());    
        mqtt.publish(mqttTopic, mqttMsg);
        mqttInitRobot = 0;
    }
}

