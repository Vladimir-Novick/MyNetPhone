////////////////////////////////////////////////////////////////////////////
//
//
//    Project     : VideoNet Ver. 1.0.
//    Description : Video Conferencing over the LAN.
//	  Author      :	Vladiimir Novick ( v_novick@yahoo.com )
//    Date        : 17/12/2005
//
//
//    File description : 
//    Name    : convert.h
//    Details : Conversion routine from RGB24 to YUV420 & YUV420 to RGB24.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined _CONVERT_H
#define _CONVERT_H

#include<stdio.h>

// Conversion from RGB24 to YUV420
void InitLookupTable();
int  ConvertRGB2YUV(int w,int h,unsigned char *rgbdata,unsigned int *yuv);


// Conversion from YUV420 to RGB24
void InitConvertTable();
void ConvertYUV2RGB(unsigned char *src0,unsigned char *src1,unsigned char *src2,unsigned char *dst_ori,
								 int width,int height);


#endif