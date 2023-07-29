#include "music_config.h"
#include "music_config_manager.h"

static inline void wait_for_any_serial_input() {
  while(Serial.available() == 0){}
  while(Serial.available() != 0){
    Serial.read();
  }
}

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for Arduino Serial Monitor to connect.
  }

  MusicConfigManager manager;
  MusicConfig config;

  while (true) {
    Serial.print("Send some serial message to load/read\n");
    wait_for_any_serial_input();
    if (manager.load(config)) {
      config.dump();
    }
    
    Serial.print("Send some serial message to save/write\n");
    wait_for_any_serial_input();
    manager.save(config);
  }

  // // After the MSC drive is initialized, you can access it using the ordinary
  // // SD library functions, regardless of whether it was initialized by
  // // SD library SD.begin() or SdFat library SD.sdfs.begin() or MSC auto
  // // initialization. MSC access to SdFat is achieved as in this example:
  // // "partition1.mscfs.ls()".
  // Serial.println("Print directory using SD functions");
  // File root = partition1.open("/");
  // while (true) {
  //   File entry = root.openNextFile();
  //   if (!entry) break; // no more files
  //   Serial.print(entry.name());
  //   if (entry.isDirectory()) {
  //     Serial.println("/");
  //   } else {
  //     printSpaces(40 - strlen(entry.name()));
  //     Serial.print("  ");
  //     Serial.println(entry.size(), DEC);
  //   }
  //   entry.close();
  // }
}

void loop()
{
  // nothing happens after setup finishes.
}


void printSpaces(int num) {
  for (int i = 0; i < num; i++) {
    Serial.print(" ");
  }
}
