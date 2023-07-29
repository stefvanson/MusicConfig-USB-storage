#include "music_config.h"
#include "music_config_manager.h"

MusicConfigManager manager;
MusicConfig config;

static inline char get_next_user_command() {
  Serial.print("Send a command to load (l) or save (s) a configuration...\n");
  char next_char = '\n';
  while ((Serial.available() == 0) || next_char == '\n') {
    next_char = Serial.read();
  }
  return next_char;
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
}

void loop() {
  auto command = get_next_user_command();
  switch (command) {
    case 'l':
      Serial.print("Loading configuration...\n");
      if (manager.load(config)) {
        config.dump();
      }
      break;
    case 's':
      Serial.print("Saving configuration...\n");
      manager.save(config);
      break;
    default:
      Serial.printf("Unknown command %c\n", command);
      break;
  }
}
