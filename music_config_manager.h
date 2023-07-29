#ifndef MUSIC_CONFIG_MANAGER_H_
#define MUSIC_CONFIG_MANAGER_H_

#include "music_config.h"
#include "usb_drive.h"

/** @brief Class for loading/saving a MusicConfig from/to a USB drive. */
class MusicConfigManager {
 public:
  MusicConfigManager();
  bool load(MusicConfig& config);
  void save(const MusicConfig& config);

 private:
  enum class State {
    IDLE,
    SAVING,
  };
  UsbDrive usb_drive;
};

#endif // MUSIC_CONFIG_MANAGER_H_
