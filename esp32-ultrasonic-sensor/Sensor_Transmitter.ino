#include <NewPing.h>
#include "WiFi.h"
#include <esp_wifi.h>
#include <esp_now.h>

#define MAX_DISTANCE 50
#define TRIGGER_DISTANCE 12
// PINS
#define TRIGGER_BIN_1 33
#define ECHO_BIN_1 32
#define TRIGGER_BIN_2 12
#define ECHO_BIN_2 14
#define TRIGGER_BIN_3 15
#define ECHO_BIN_3 2

// ULTRASONIC DEVICE INITIALIZATION  
NewPing sonar1(TRIGGER_BIN_1, ECHO_BIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_BIN_2, ECHO_BIN_2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_BIN_3, ECHO_BIN_3, MAX_DISTANCE);

// distances reported from ultrasonic sensors of each bin
int distance_trash = 0;
int distance_waste = 0;
int distance_recycle = 0;

// Data structure of data to send to responder
// typedef struct Message
// {
//   char message[64];
//   int trash_data;
//   int waste_data;
//   int recycle_data;
// } Message;

typedef struct Message
{
  bool start;
} Message;

Message data;
esp_now_peer_info_t peerInfo;

// Callback function for data sent
void DataSent(const uint8_t* MAC_ADDRESS, esp_now_send_status_t status)
{
  if (status == ESP_NOW_SEND_SUCCESS)
  {
    Serial.println("Data was sent successfully!");
  }
  else
  {
    Serial.println("Error in sending data.");
  }
}

// MAC Address of responder
//uint8_t broadcastAddress[] = {0xA0, 0xB7, 0x65, 0xFE, 0x72, 0xD4};
uint8_t broadcastAddress[] = {0xA0, 0xB7, 0x65, 0xFE, 0xDB, 0x5C};

// Insert your SSID
constexpr char WIFI_SSID[] = "Angel’s iPhone";

int32_t getWiFiChannel(const char *ssid) {
  if (int32_t n = WiFi.scanNetworks()) {
      for (uint8_t i=0; i<n; i++) {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}

void setup() 
{
  Serial.begin(9600);

  // Set device as a Wi-Fi Station and set channel
  WiFi.mode(WIFI_STA);

  int32_t channel = getWiFiChannel(WIFI_SSID);

  WiFi.printDiag(Serial); // Uncomment to verify channel number before
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  WiFi.printDiag(Serial); // Uncomment to verify channel change after

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  Serial.print("MAC ADDRESS: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error during initialization.");
    return;
  }

  esp_now_register_send_cb(DataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer.");
    return;
  }
}

void loop() 
{
  distance_trash = sonar1.ping_in(); // Send ping, get distance in inches (0 = outside set distance range)
  distance_waste = sonar2.ping_in(); // Send ping, get distance in inches (0 = outside set distance range)
  distance_recycle = sonar3.ping_in(); // Send ping, get distance in inches (0 = outside set distance range)

  // strcpy(data.message, "Reported Distances Listed in Order: {trash, waste, recycle}:");
  data.start = true;
  // data.trash_data = distance_trash;
  // data.waste_data = distance_waste;
  // data.recycle_data = distance_recycle;

  // Send message via EP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*) &data, sizeof(data));
  if (result == ESP_OK)
  {
    Serial.println("Message was sent successfully!");
  }
}