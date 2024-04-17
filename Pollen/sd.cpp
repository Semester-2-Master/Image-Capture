#include <Arduino.h>
#include "FS.h"
#include "SD_MMC.h"

#define MAXFILES 20

void init_sd() {
  if(!SD_MMC.begin()) {
    return;
  }
  
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    return;
  }
}

void write_file(char *filename, uint8_t *buf, int len) {
  fs::FS &fs = SD_MMC;
  File file = fs.open(filename, FILE_WRITE);

  if(!file) {
    return;
  }

  file.write(buf, len);
  file.close();
}

void print_card(char ***file_list, int *count) {
  Serial.println("print_card");
  *file_list = (char **)malloc(MAXFILES * sizeof(char *));

  fs::FS &fs = SD_MMC;
  File dir = fs.open("/");
  dir.rewindDirectory();
  int i = 0;
  for (; i < MAXFILES; ++i) {
    File entry = dir.openNextFile();
    if (!entry) {
      break;
    }
    (*file_list)[i] = (char*)entry.path();
    // Serial.println(entry.path());
    // Serial.println(file_list[cnt]);
    entry.close();
    Serial.print("file #");
    Serial.print(i);
    Serial.println((*file_list)[i]);
  }
  dir.close();

  *count = i;
  Serial.println("print_card done");
}
