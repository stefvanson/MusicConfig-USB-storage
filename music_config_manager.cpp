#include "music_config_manager.h"

#include <string.h>

#include "hal.h"

static constexpr char config_filename[] = "config.txt";

static const char FORMAT[] =
    "synth_notes:   {%d, %d, %d, %d, %d, %d, %d, %d}\n"
    "bass_notes:    {%d, %d, %d, %d, %d, %d, %d, %d}\n"
    "drum_notes[0]: {%d, %d, %d, %d, %d, %d, %d, %d}\n"
    "drum_notes[1]: {%d, %d, %d, %d, %d, %d, %d, %d}\n"
    "drum_notes[2]: {%d, %d, %d, %d, %d, %d, %d, %d}\n";

bool MusicConfigManager::load(MusicConfig& config) {
  bool successful = false;
  log_print("MusicConfigManager: Loading config...\n");
  if (usb_drive.try_to_connect()) {
    char data[USB_DRIVE_MAX_FILE_SIZE] = {0};
    if (usb_drive.read_file(config_filename, data, USB_DRIVE_MAX_FILE_SIZE)) {
      successful = parse_config(data, config);
    } else {
      log_print("MusicConfigManager: Unable to read config file\n");
    }
  }
  return successful;
}

bool MusicConfigManager::save(const MusicConfig& config) {
  bool successful = false;
  log_print("MusicConfigManager: Saving config...\n");
  if (usb_drive.try_to_connect()) {
    char data[USB_DRIVE_MAX_FILE_SIZE];
    snprintf(data, USB_DRIVE_MAX_FILE_SIZE, FORMAT, config.synth_notes[0],
             config.synth_notes[1], config.synth_notes[2], config.synth_notes[3],
             config.synth_notes[4], config.synth_notes[5], config.synth_notes[6],
             config.synth_notes[7], config.bass_notes[0], config.bass_notes[1],
             config.bass_notes[2], config.bass_notes[3], config.bass_notes[4],
             config.bass_notes[5], config.bass_notes[6], config.bass_notes[7],
             config.drum_notes[0][0], config.drum_notes[0][1], config.drum_notes[0][2],
             config.drum_notes[0][3], config.drum_notes[0][4], config.drum_notes[0][5],
             config.drum_notes[0][6], config.drum_notes[0][7], config.drum_notes[1][0],
             config.drum_notes[1][1], config.drum_notes[1][2], config.drum_notes[1][3],
             config.drum_notes[1][4], config.drum_notes[1][5], config.drum_notes[1][6],
             config.drum_notes[1][7], config.drum_notes[2][0], config.drum_notes[2][1],
             config.drum_notes[2][2], config.drum_notes[2][3], config.drum_notes[2][4],
             config.drum_notes[2][5], config.drum_notes[2][6], config.drum_notes[2][7]);
    usb_drive.write_file(config_filename, data, strlen(data));
    successful = true;
  }
  return successful;
}

bool MusicConfigManager::parse_config(const char* data, MusicConfig& config) {
  bool successful = false;
  int num_results =
      sscanf(data, FORMAT, &config.synth_notes[0], &config.synth_notes[1],
             &config.synth_notes[2], &config.synth_notes[3], &config.synth_notes[4],
             &config.synth_notes[5], &config.synth_notes[6], &config.synth_notes[7],
             &config.bass_notes[0], &config.bass_notes[1], &config.bass_notes[2],
             &config.bass_notes[3], &config.bass_notes[4], &config.bass_notes[5],
             &config.bass_notes[6], &config.bass_notes[7], &config.drum_notes[0][0],
             &config.drum_notes[0][1], &config.drum_notes[0][2], &config.drum_notes[0][3],
             &config.drum_notes[0][4], &config.drum_notes[0][5], &config.drum_notes[0][6],
             &config.drum_notes[0][7], &config.drum_notes[1][0], &config.drum_notes[1][1],
             &config.drum_notes[1][2], &config.drum_notes[1][3], &config.drum_notes[1][4],
             &config.drum_notes[1][5], &config.drum_notes[1][6], &config.drum_notes[1][7],
             &config.drum_notes[2][0], &config.drum_notes[2][1], &config.drum_notes[2][2],
             &config.drum_notes[2][3], &config.drum_notes[2][4], &config.drum_notes[2][5],
             &config.drum_notes[2][6], &config.drum_notes[2][7]);
  log_print("MusicConfigManager::parse_config(): num_results = %i\n", num_results);
  if (num_results == 40) {
    successful = true;
  } else {
    log_print("MusicConfigManager::parse_config(): Failed, data: >>>%s<<<\n", data);
  }
  return successful;
}
