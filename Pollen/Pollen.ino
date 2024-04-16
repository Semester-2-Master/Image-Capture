#include "sd.h"

void test_sd() {
  char *filename = "/test2.txt";
  uint8_t *content = (uint8_t *)"hello world";
  int content_len = 11;
  write_file(filename, content, content_len);
}

void setup() {
  init_sd();

  // test SD card access
  test_sd();
}

void loop() {
  // put your main code here, to run repeatedly:

}
