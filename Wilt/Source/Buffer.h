/*
  ==============================================================================

    Buffer.h
    Created: 14 Mar 2023 3:39:26pm
    Author:  thoma

  ==============================================================================
*/

#pragma once
#include "Outils.hpp"
#include "Filter.h"
#include <math.h>

//test

namespace noi {
	namespace buffer {
		class RingBuffer {
		private:
			float m_read;
			float m_write;
			float m_buffer_size;
			float m_step;
			float m_time;
			bool m_freeze{ false };
			float m_actual_size;
			std::vector<float> m_buffer;
		public:
			RingBuffer(float max_time) {
				m_buffer_size = noi::Outils::convertMsToSample(max_time);
				size_t buffer_int = static_cast<size_t> (m_buffer_size);
				m_buffer_size -= 1;
				m_buffer.resize(buffer_int);
				m_read = 1.f;
				m_write = m_buffer_size / 2.f;
				m_step = 1.f;
				std::fill(m_buffer.begin(), m_buffer.end(), 0);
			}
			inline float read() {
				m_read += m_step;

				double tmp;
				float fractional;

				fractional = modf(m_read, &tmp);
				int int_read = static_cast<int> (tmp);

				while ((int_read < 0) || (int_read > (m_buffer_size)))
				{

					if (int_read > (m_buffer_size))
					{
						int_read = int_read - (m_buffer_size);
					}

					if (int_read < 1.0)
					{
						int_read = (m_buffer_size ) - m_read;
					}
				}

				float sample1 = m_buffer[int_read];
				if ((int_read + 1) > m_buffer_size) int_read = 1;
				float sample2 = m_buffer[int_read + 1];
				float output = ((sample2 - sample1) * fractional) + sample1;
				return output;
			}
			inline void write(float new_sample) {
				m_write += 1.f;

				int int_write = static_cast<int>(m_write);


				while ((int_write < 0) || (int_write > m_buffer_size))
				{

					if (int_write > m_buffer_size)
					{
						int_write -= m_buffer_size;
					}

					if (int_write < 0)
					{
						int_write = m_buffer_size-int_write;
					}
				}
				m_buffer[int_write] = new_sample;
				//m_buffer[1] = new_sample;
			}
			inline float getSize() {
				float size = m_write - m_read;
				if (m_write < m_read) {
					size = m_write + (m_buffer_size - m_read);
				}
				return size;
			}
			inline void setStep(float step) { m_step = step; }
			inline void setSizeWoRepitch(float size) {
				m_read = 0;
				m_write = noi::Outils::convertMsToSample(size);
			}
			inline void setSize(float new_time) {
				if (m_freeze) {
					m_step = m_time / new_time;
					return;
				}
				m_time = new_time;
				float size_goal = noi::Outils::convertMsToSample(new_time);
				if (size_goal > m_buffer_size - 2.f) size_goal = m_buffer_size - 2.f;
				if (size_goal <0) size_goal = 0.f;
				float actual_size = getSize();
				m_actual_size = actual_size;
				//ralenti si le buffer doit être plus petit
				//accelere si le buffer doit être plus grand
				if (actual_size < (size_goal - 2.f)) {
					m_step = 0.8;
				}
				else if (actual_size < (size_goal - 4800.f)) {
					m_step = 0.5;
				}
				else if (actual_size > (size_goal + 2.f)) {
					m_step = 1.2;
				}
				else if (actual_size > (size_goal + 4800.f)) {
					m_step = 2.f;
				}
				else { m_step = 1.f; }
			}
			inline float getActualSize() {
				return m_actual_size;
			}
			inline void setFreeze(bool statut) {
				m_freeze = statut;
			}
		};
	}
}
