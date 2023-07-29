#ifndef MUSIC_CONFIG_MANAGER_H_
#define MUSIC_CONFIG_MANAGER_H_

#include "music_config.h"
#include "usb_drive.h"

/** @brief Class for loading/saving a MusicConfig from/to a USB drive. */
class MusicConfigManager {
 public:
  bool load(MusicConfig& config);
  bool save(const MusicConfig& config);

 private:
  bool parse_config(const char* data, MusicConfig& config);
  UsbDrive usb_drive;
};

#endif // MUSIC_CONFIG_MANAGER_H_
