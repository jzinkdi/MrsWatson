//
// SampleSourcePcm.h - MrsWatson
// Created by Nik Reiman on 1/2/12.
// Copyright (c) 2012 Teragon Audio. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef MrsWatson_InputSourcePcm_h
#define MrsWatson_InputSourcePcm_h

#include <stdio.h>

#include "io/SampleSource.h"

typedef struct {
  boolByte isStream;
  boolByte isLittleEndian;
  FILE* fileHandle;
  size_t dataBufferNumItems;
  union {
    short* shorts;
    int* ints;
  } interlacedPcmBuffer;

  unsigned short bitDepth;
  unsigned short numChannels;
  unsigned int sampleRate;
} SampleSourcePcmDataMembers;
typedef SampleSourcePcmDataMembers *SampleSourcePcmData;

// TODO: Make private
SampleSource newSampleSourcePcm(const CharString sampleSourceName);

/**
 * Check if a given bit depth is supported for use with raw PCM sample sources
 * @param bitDepth Bit depth
 * @return True if valid, false otherwise
 */
boolByte isValidBitDepth(unsigned short bitDepth);

/**
 * Read raw PCM data to a floating-point sample buffer
 * @param self
 * @param sampleBuffer
 * @return Number of samples read
 */
size_t sampleSourcePcmRead(SampleSourcePcmData self, SampleBuffer sampleBuffer);

/**
 * Writes data from a sample buffer to a PCM output
 * @param self
 * @param sampleBuffer
 * @return Number of samples written
 */
size_t sampleSourcePcmWrite(SampleSourcePcmData self, const SampleBuffer sampleBuffer);

/**
 * Set the bit depth to be used for reading raw PCM files. When writing raw PCM
 * data, a bit depth of 16 is assumed. When reading WAVE or AIFF files, the
 * provided bit depth from the file container is used instead of this value.
 * @param sampleSourcePtr
 * @param bitDepth Bit depth (valid values: 8, 16, 24, and 32)
 */
void sampleSourcePcmSetBitDepth(void* sampleSourcePtr, unsigned short bitDepth);

/**
 * Set the number of channels to be used for raw PCM file operations. Like the
 * sample, this is most relevant when writing a WAVE or a AIFF file.
 * @param sampleSourcePtr
 * @param numChannels Number of channels
 */
void sampleSourcePcmSetNumChannels(void* sampleSourcePtr, unsigned short numChannels);

/**
 * Set the sample rate to be used for raw PCM file operations. This is most
 * relevant when writing a WAVE or a AIFF file, as the sample rate must be given
 * in the file header.
 * @param sampleSourcePtr
 * @param sampleRate Sample rate, in Hertz
 */
void sampleSourcePcmSetSampleRate(void* sampleSourcePtr, double sampleRate);

// TODO: Make private
void freeSampleSourceDataPcm(void* sampleSourceDataPtr);

#endif
