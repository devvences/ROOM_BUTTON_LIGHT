#define WIFI_SSID "HOME_2.4G"
#define WIFI_PASS "AaBcE81321"
#define MDNS_NAME "room"

#define RELAY_PIN D1
#define BUTTON_PIN D2

#include "OneButton.h"
#include "GenericIOT.h"

OneButton button(BUTTON_PIN, false, false);

void setup() {
  genericSetup();

  pinMode(RELAY_PIN, OUTPUT);

  server.on("/light/on", []() {
    setLight(HIGH);
    server.send(200, "application/json", ""); 
  });

  server.on("/light/off", []() {
    setLight(LOW);
    server.send(200, "application/json", "");
  });

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), checkTicks, CHANGE);
  button.attachClick([] {
    toggleLight();
  });
}

void loop() {
  genericLoop();
  button.tick();
  delay(10);
} 

///////// TOOGLE LIGHT /////////////////

int relayState = LOW;
void toggleLight(){
  relayState = !relayState;
  digitalWrite(RELAY_PIN, relayState);
}

void setLight(int state){
  relayState = state;
  digitalWrite(RELAY_PIN, relayState);
}

///////// INTERRUPT /////////////////

ICACHE_RAM_ATTR void checkTicks() {
  button.tick(); // just call tick() to check the state.
}
