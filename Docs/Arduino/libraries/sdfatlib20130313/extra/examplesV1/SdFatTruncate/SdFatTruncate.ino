/*
 * Truncate Example
 *
 * This sketch shows how to use truncate() to remove the last 
 * half of the file created by the SdFatAppend.pde example.
 */
#include <SdFat.h>
#include <SdFatUtil.h> // use functions to print strings from flash memory

const uint8_t SD_CHIP_SELECT = SS;

SdFat sd;

SdFile file;

// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))

void setup(void) {
  Serial.begin(9600);
  while (!Serial) {}  // wait for Leonardo
  PgmPrintln("Type any character to start");
  while (Serial.read() <= 0) {}
  delay(200);  // Catch Due reset problem
  
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
  if (!sd.begin(SD_CHIP_SELECT, SPI_HALF_SPEED)) sd.initErrorHalt();
  
  char name[] = "APPEND.TXT";
  // open for read and write
  if (!file.open(name, O_RDWR)) {
    PgmPrint("Can't open "); 
    Serial.println(name);
    PgmPrintln("Run the append example to create the file.");
    error("file.open failed");
  }
  // seek to middle of file
  if (!file.seekSet(file.fileSize()/2)) error("file.seekSet failed");
  // find end of line
  int16_t c;
  while ((c = file.read()) > 0 && c != '\n');
  if (c < 0) error("file.read failed");
  // truncate at current position
  if (!file.truncate(file.curPosition())) error("file.truncate failed");
  Serial.print(name);
  PgmPrintln(" truncated.");
}

void loop(void) {}
