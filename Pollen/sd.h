#include <FS.h>
#include <SD_MMC.h>

void init_sd();
void write_file(char *filename, uint8_t *buf, int len);
void readFile(fs::FS &fs, const char *path, File *filePointer) ; 
void print_card(char ***file_list, int *i);
