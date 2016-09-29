#ifndef HEADER
#define HEADER

struct Track {
  int pin;
  const uint16_t *freqs;
  const uint32_t *durs;
  int arraySize;
};

#endif
