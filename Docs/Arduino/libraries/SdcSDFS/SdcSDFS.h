/**
	\defgroup	ARDUINO_SDCSDFS
	\ingroup	ARDUINO
	\brief		SDCard FatFs interface for Arduino
	\author		Sungjune Lee
	\date		Wed May 23 10:44:54 EDT 2012

	This program provides a thin and simple wrapper for the FatFs developed by elm-chan
	(http://elm-chan.org/fsw/ff/00index_e.html). This class is especially designed for
	the simplicity but that does not necessarily mean that the capability of the original
	FatFs is limited as such. You can add as many methods as you want for your project.


	\verbatim
	Programming Example
	==============================================================================
	// Define a SdcSDFS object on the heap. You need one and only one SdcSDFS object.
	// This automatically mounts the drive and opens the root directory for 
	// enumeration of files.
	SdcSDFS fs;

	// Initially, the file enumeration filter string is set to "*", which implies
	// that all the files are entitled to be enumerated. So you can open thoese
	// files one by one by invoking
	fs.openNextFile();

	// To open the next file, simply invoking the same method again, while it
	// returns value other than FR_OK.
	while(fs.openNextFile() == FR_OK)
	{
		...
	}

	// To rewind the file list and reopen the first file, you need to open the
	// directory again.
	fs.openDirectory("/");

	// FileFilter is actually a string for matching the file extension. To enumerate
	// the BMP files only, 
	fs.setFileFilter("BMP");

	// After open a file, you can get the name of the file by
	char* fname = fs.getFileName();

	// And read the data by invoking the following method, where nsize denotes the
	// size of the buffer to read and psize returns the actual number of bytes to
	// be read.
	fs.readFile(&buff, nsize, psize);


	Version History
	==============================================================================
	v0.1: (23 May 2012) Initial release.

	\{
 */

/*
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
#ifndef SDCSDFS_h
#define SDCSDFS_h

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <utility/ff.h>
#include <utility/diskio.h>

typedef uint8_t ErrorCode;

class SdcSDFS {
public:
	// constructor
	SdcSDFS();

	// public functions
	ErrorCode openDirectory(const char* dir);
	ErrorCode openNextFile(void);
	ErrorCode readFile(void* buff, unsigned int nsize, unsigned int* psize);
	ErrorCode getLastError(void);
	char* getFileName(void);
	void setFileFilter(const char* fext);

private:
	char		FileExt[4];	// file extention as a filter
	FATFS		FatFS;		// file system
	DIR			Dir;		// directory
	FIL			Fil;		// FIL
	FILINFO		FILinfo;	// FIL info
	ErrorCode	lastError;	// error code
};

#endif	// SDCSDFS_h


/**
	\}
 */

