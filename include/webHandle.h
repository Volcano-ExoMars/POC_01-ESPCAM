#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

/* Initialisation des différentes page
-------------------------------------------------------------------*/
void initHandleWeb() {
// Page par défaut à la racine
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/index.html", "text/html");
    });

// Chemin pour le css
    server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/w3.css", "text/css");
    });

// Chemin pour le JS
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

// Chemin pour la map
    server.on("/sol_martien.jpg", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/sol_martien.jpg", "image/jpg");
    });

// Chemin pour le sprite du rover
    server.on("/rover.png", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/rover.png", "image/png");
    });

// Chemin pour la photo
    server.on("/photo.jpg", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/photo.jpg", "image/jpg");
    });

// MAJ Temperature
    server.on("/retourtemperature", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        float valeur = 23+random(0,5);
        String valeurString = String( valeur );
        char mqttTopic[64]; // array pour le nom du topic à envoyer
        char mqttMsg[16]; // array pour les données des messages à envoyer
        sprintf(mqttTopic, "ROBOTS/%s/Temperature", ROBOT_NUM);
        sprintf(mqttMsg, "%2f", valeur);            
        mqtt.publish(mqttTopic, mqttMsg);

        request->send(200, "text/plain", valeurString);
    });

// MAJ Humidité
    server.on("/retourhumidity", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        float valeur = 43+random(0,30);
        String valeurString = String( valeur );
        char mqttTopic[64]; // array pour le nom du topic à envoyer
        char mqttMsg[16]; // array pour les données des messages à envoyer
        sprintf(mqttTopic, "ROBOTS/%s/Humidity", ROBOT_NUM);
        sprintf(mqttMsg, "%2f", valeur);            
        mqtt.publish(mqttTopic, mqttMsg);

        request->send(200, "text/plain", valeurString);
    });

// MAJ Gaz
    server.on("/retourgaz", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        uint16_t valeur = 500+random(0,50);
        String valeurString = String( valeur );
        char mqttTopic[64]; // array pour le nom du topic à envoyer
        char mqttMsg[16]; // array pour les données des messages à envoyer
        sprintf(mqttTopic, "ROBOTS/%s/Gaz", ROBOT_NUM);
        sprintf(mqttMsg, "%d", valeur);            
        mqtt.publish(mqttTopic, mqttMsg);

        request->send(200, "text/plain", valeurString);
    });

// MAJ Pression
    server.on("/retourpression", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        uint16_t valeur = 1000+random(0,100);
        String valeurString = String( valeur );
        char mqttTopic[64]; // array pour le nom du topic à envoyer
        char mqttMsg[16]; // array pour les données des messages à envoyer
        sprintf(mqttTopic, "ROBOTS/%s/Pression", ROBOT_NUM);
        sprintf(mqttMsg, "%d", valeur);            
        mqtt.publish(mqttTopic, mqttMsg);

        request->send(200, "text/plain", valeurString);
    });

// MAJ Photo
    server.on("/retourphoto", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        char mqttTopic[64]; // array pour le nom du topic à envoyer

        Serial.println("ESP32-CAMP capturing photo: ");

        fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Failed");
            sprintf(mqttTopic, "ROBOTS/%s/Photo", ROBOT_NUM); 
            mqtt.publish(mqttTopic, "KOOOO!" );
        }
        else {
            File file = SPIFFS.open("/photo.jpg", FILE_WRITE);
            if (!file) {
                Serial.println("Failed to open file in writing mode");
            }
            else {
                digitalWrite(PIN_LED, HIGH);
                file.write(fb->buf, fb->len); 
                Serial.print("The picture has been saved");
                Serial.print(" - Size: ");
                Serial.print(file.size());
                Serial.println(" bytes");
            }
            file.close();
            esp_camera_fb_return(fb);
                        
            sprintf(mqttTopic, "ROBOTS/%s/Photo", ROBOT_NUM); 
            mqtt.publish(mqttTopic, "OK" );

            digitalWrite(PIN_LED, LOW);
        }
        request->send(200, "text/plain", "");
    });    

/*
// Allumage de la LED
    server.on("/ledon", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        digitalWrite(PINLED, HIGH);
        request->send(200);
    });

// Extinction de la LED
    server.on("/ledoff", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        digitalWrite(PINLED, LOW);
        request->send(200);
    });
*/
}