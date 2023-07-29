#ifndef USB_DRIVE_H_
#define USB_DRIVE_H_

constexpr int USB_DRIVE_MAX_FILE_SIZE = 1024;

class UsbDrive {
 public:
  UsbDrive();

  bool try_to_connect();
  bool write_file(const char* filename, const char* data, unsigned num_chars);
  bool read_file(const char* filename, char* data, unsigned max_size);

 private:
  bool connected = false;
};

#endif // USB_DRIVER_H_
