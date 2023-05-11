/*
  ==============================================================================

    Buffer.h
    Created: 11 May 2023 5:54:58pm
    Author:  thoma

  ==============================================================================
*/

#pragma once
#include <vector>
Class Buffer(
  public:
void Buffer(size);
void setSize();
void processSample(float);
void write();
void read();
float interpolate();
private:
std::Vector <float> m_buffer;
float read_pos, write_pos;



);
