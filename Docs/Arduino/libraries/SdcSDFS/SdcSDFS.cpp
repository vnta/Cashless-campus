/**
	\addtogroup	ARDUINO_SDCSDFS

	\{
 */

/*
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include "SdcSDFS.h"
#include "utility/diskio.h"

// constructor
SdcSDFS::SdcSDFS()
{
	// initialize the disk
	lastError = disk_initialize(0);

	if(lastError == 0x00)
	{
		// mount the file system
		lastError = f_mount(0, &FatFS);

		if(lastError == FR_OK)
		{
			// open the root dir
			lastError = f_opendir(&Dir, "/");
		}
	}

	// initialize the file search filter
	FileExt[0] = '*';
	FileExt[1] = 0x00;

	// initialize the other varibles
	Fil.fs = 0x00;
	FILinfo.fname[0] = 0x00;
}

ErrorCode SdcSDFS::getLastError(void)
{
	return lastError;
}

void SdcSDFS::setFileFilter(const char* fext)
{
	uint8_t i;

	for(i = 0; i < 3; i++)
	{
		FileExt[i] = *(fext + i);
		if(*(fext + i) == 0x00) break;
	}
	FileExt[3] = 0x00;
}

ErrorCode SdcSDFS::openNextFile(void)
{
	ErrorCode ec;
	uint8_t i, j;

	if(Dir.fs == 0x00) return FR_NO_FILESYSTEM;

	while(1)
	{
		ec = f_readdir(&Dir, &FILinfo);

		// end of the file list
		if((ec != FR_OK) || (FILinfo.fname[0] == 0))
			return FR_NO_FILE;

		// skip dir
		if((FILinfo.fattrib & AM_DIR)) 
			continue;
		
		if(FileExt[0] != '*')
		{

			// scan the file name string for the extension
			i = 0;
			while((FILinfo.fname[i] != '.') && 
				(FILinfo.fname[i] != 0x00) && (i < 12))
			{
				i++;
			}
			if(FILinfo.fname[i] != '.') continue;
			i++;

			j = 0;
			while((FILinfo.fname[i+j] == FileExt[j]) && 
				(FileExt[j] != 0x00) && (j < 3))
			{
				j++;
			}
		
			if(FileExt[j] != 0x00) continue;
		}

		// close the previous file if any
		if(Fil.fs) f_close(&Fil);
		// open the next file for read
		f_open(&Fil, FILinfo.fname, FA_READ);

		return FR_OK;
	}
}

char* SdcSDFS::getFileName(void)
{
	if(FILinfo.fname[0] != 0x00)
		return FILinfo.fname;
	else
		return 0x00;
}

ErrorCode SdcSDFS::openDirectory(const char* dir)
{
	return f_opendir(&Dir, dir);	
}

ErrorCode SdcSDFS::readFile(void* buff, unsigned int nsize, unsigned int* psize)
{
	return f_read(&Fil, buff, nsize, psize);	
}
/**
	\}
 */

