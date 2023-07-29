#include "music_config.h"
#include "music_config_manager.h"

#include "hal.h"

#ifdef HOST_BUILD

int main() {
  MusicConfigManager manager;
  MusicConfig config;
  if (manager.load(config)) {
    config.dump();
    manager.save(config);
  }

  return 0;
}

#endif
