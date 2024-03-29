#ifndef CVEYETRACKER_COLOUR_CONV
#define CVEYETRACKER_COLOUR_CONV

#define YUV2RGB(y, u, v, r, g, b)\
  r = y + ((v*1436) >> 10);\
  g = y - ((u*352 + v*731) >> 10);\
  b = y + ((u*1814) >> 10);\
  r = r < 0 ? 0 : r;\
  g = g < 0 ? 0 : g;\
  b = b < 0 ? 0 : b;\
  r = r > 255 ? 255 : r;\
  g = g > 255 ? 255 : g;\
  b = b > 255 ? 255 : b

//----------------------- uyyvyy (i.e. YUV411) to rgb24 -----------------------//
void uyyvyy2rgb (unsigned char *src, unsigned char *dest, unsigned long long int NumPixels);
#endif
