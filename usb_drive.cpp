#include "usb_drive.h"

#include "hal.h"

constexpr size_t MAX_FILE_SIZE = 1024;

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

void UsbDrive::write_file(const char* filename, const char* data, unsigned num_chars) {
  #ifndef HOST_BUILD
 log_print("UsbDrive: Writing to file %s\n", filename);
  FsFile file = usb_file_system.mscfs.open("file1.txt", O_WRITE | O_CREAT);
  unsigned int len = file.fileSize();
  if (len > 0) {
    // reduce the file to zero if it already had data
    file.truncate();
  }
  if (file.preAllocate(num_chars)) {
    log_print("UsbDrive:   Allocated %i bytes for %s\n", num_chars, filename);
    unsigned i = 0;
    while (data[i] != '\0' && i < num_chars) {
      file.write((uint8_t)data[i]);
      i = i + 1;
    }
    log_print("UsbDrive:   Written %i bytes to file %s\n", i, filename);
  } else {
   log_print("UsbDrive:   Unable to preallocate this file");
  }
  file.close();
  #else
  log_print("UsbDrive: Writing to file %s\n", filename);
  log_print("  Data:\n%s\n=============================\n", data);
  #endif
}

void UsbDrive::read_file(const char* filename, char* data, unsigned max_size) {
  #ifndef HOST_BUILD
  log_print("UsbDrive: Reading file %s\n", filename);
  File file = usb_file_system.open("file1.txt");
  if (file) {
    char mybuffer[MAX_FILE_SIZE];
    int index = 0;
    while (file.available()) {
      char c = file.read();
      mybuffer[index] = c;
      index = index + 1;
      if (index == MAX_FILE_SIZE) break; // buffer full
    }
    mybuffer[index] = 0;
    log_print("UsbDrive: Read:\n");
    log_print(mybuffer);
    log_print("\n=============================\n");
  } else {
    log_print("UsbDrive: Unable to open %s\n");
  }
  file.close();
  #else
  log_print("UsbDrive::Reading file %s\n", filename);
  strncpy(data, "synth_notes:   {1, 2, 3, 4, 1, 2, 3, 4}\n"
                "bass_notes:    {0, 0, 0, 0, 0, 0, 0, 0}\n"
                "drum_notes[0]: {1, 0, 1, 0, 1, 0, 1, 0}\n"
                "drum_notes[1]: {0, 0, 0, 0, 0, 0, 0, 0}\n"
                "drum_notes[2]: {0, 0, 0, 0, 0, 0, 0, 0}\n\0",
                MAX_FILE_SIZE);
  #endif
}
