#include "music_config_manager.h"

#include "hal.h"
//#include <USBHost_t36.h>
#include <utility>

MusicConfigManager::MusicConfigManager() {

}

bool MusicConfigManager::load(MusicConfig& config) {
 log_print("MusicConfigManager: Loading config...\n");
  if (usb_drive.try_to_connect()) {
    char data[1024] = {0};
    usb_drive.read_file("file1.txt", data, 1024);
    config.synth_notes[0] = 1;
    config.synth_notes[1] = 2;
    config.synth_notes[2] = 3;
    config.synth_notes[3] = 4;
    config.synth_notes[4] = 1;
    config.synth_notes[5] = 2;
    config.synth_notes[6] = 3;
    config.synth_notes[7] = 4;
    config.drum_notes[0][0] = true;
    config.drum_notes[0][2] = true;
    config.drum_notes[0][4] = true;
    config.drum_notes[0][6] = true;
    return true;
  } else {
    return false;
  }
}

void MusicConfigManager::save(const MusicConfig& config) {
  log_print("MusicConfigManager: Saving config...\n");
  if (usb_drive.try_to_connect()) {
    char data[1024];
    strncpy(data, "hi1234\nblabla\0", 1024);
    size_t num_chars = strlen(data);
    usb_drive.write_file("file1.txt", data, num_chars);
  }
}
