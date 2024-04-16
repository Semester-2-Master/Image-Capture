#include "FS.h"
#include "SD_MMC.h"

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
