#ifndef USB_DRIVE_H_
#define USB_DRIVE_H_

class UsbDrive {
 public:
  UsbDrive();

  bool try_to_connect();
  void write_file(const char* filename, const char* data, unsigned num_chars);
  void read_file(const char* filename, char* data, unsigned max_size);
 private:
  bool connected = false;
};

#endif // USB_DRIVER_H_
