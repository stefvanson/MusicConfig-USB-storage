#include "usb_drive.h"

#include <string.h>

#include "hal.h"

#ifndef HOST_BUILD
#include <USBHost_t36.h>

static USBHost usb_host;
static USBDrive usb_drive(usb_host);
static USBFilesystem usb_file_system(usb_host);
#endif

UsbDrive::UsbDrive() {
#ifndef HOST_BUILD
  usb_host.begin();
  log_print("UsbDrive: USB Host started\n");
#endif
}

bool UsbDrive::try_to_connect() {
  bool connected = false;
#ifndef HOST_BUILD
  // usb_host.Task();
  log_print("UsbDrive: Try to connect to USB Drive...\n");
  usb_host.Task();

  if (usb_file_system) {
    log_print("UsbDrive: Connected\n");
    connected = true;
  } else {
    log_print("UsbDrive: Connecting failed\n");
    connected = false;
  }
  return connected;
#else
  return true;
#endif
}

bool UsbDrive::write_file(const char* filename, const char* data, unsigned num_chars) {
  bool successful = false;
#ifndef HOST_BUILD
  log_print("UsbDrive::write_file(): Writing to %s\n", filename);
  FsFile file = usb_file_system.mscfs.open(filename, O_WRITE | O_CREAT);
  unsigned int len = file.fileSize();
  if (len > 0) {
    file.truncate();  // Reduce the file to zero if it already had data
  }
  if (file.preAllocate(num_chars)) {
    log_print("UsbDrive::write_file(): Allocated %i bytes\n", num_chars);
    unsigned i = 0;
    while (data[i] != '\0' && i < num_chars) {
      file.write((uint8_t)data[i++]);
    }
    log_print("UsbDrive::write_file(): Written %i bytes to file %s\n", i, filename);
    successful = true;
  } else {
    log_print("UsbDrive::write_file(): Unable to preallocate this file");
  }
  file.close();
#else
  log_print("UsbDrive::write_file(): Writing:>>>%s<<<\n", data);
  successful = true;
#endif
  return successful;
}

bool UsbDrive::read_file(const char* filename, char* data, unsigned max_size) {
  bool successful = false;
#ifndef HOST_BUILD
  log_print("UsbDrive::read_file(): Reading %s\n", filename);
  File file = usb_file_system.open(filename);
  if (file) {
    int index = 0;
    while (file.available()) {
      char c = file.read();
      data[index++] = c;
      if (index == USB_DRIVE_MAX_FILE_SIZE - 1) {
        log_print("UsbDrive::read_file(): Error: buffer full!\n");
        break;
      }
    }
    if (!file.available()) {
      successful = true;
      data[index++] = '\0';
      log_print("UsbDrive: Read:>>>%s<<<\n");
    }
  } else {
    log_print("UsbDrive: Unable to open %s\n");
  }
  file.close();
#else
  log_print("UsbDrive::Reading file %s\n", filename);
  strncpy(data,
          "synth_notes:   {1, 2, 3, 4, 0, 0, 0, 0}\n"
          "bass_notes:    {1, 3, 0, 0, 1, 2, 0, 0}\n"
          "drum_notes[0]: {1, 1, 1, 1, 1, 1, 1, 1}\n"
          "drum_notes[1]: {0, 0, 1, 0, 0, 0, 1, 0}\n"
          "drum_notes[2]: {1, 0, 0, 0, 1, 0, 0, 0}\n",
          USB_DRIVE_MAX_FILE_SIZE);
  successful = true;
#endif
  return successful;
}
