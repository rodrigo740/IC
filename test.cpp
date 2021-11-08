#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

int main(void)
{
  char *inFileName;
  SNDFILE *inFile;
  SF_INFO inFileInfo;
  int fs;

  inFileName = "noise.wav";

  inFile = sf_open(inFileName, SFM_READ, &inFileInfo);
  sf_close(inFile);

  fs = inFileInfo.samplerate;
  printf("Sample Rate = %d Hz\n", fs);

  return 0;
}