/*
 * Protocol.cpp - HAPX serial protocol processing
 *
 * Copyright (c) 2010 András Veres-Szentkirályi
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "Protocol.h"

Protocol::Protocol(const int fd, AppState *as) {
	m_fd = fd;
	m_as = as;
}

void Protocol::sendChannelName(unsigned int ch) {
	char *desc = m_as->channel(ch)->desc();
	unsigned char len = strlen(desc) & 0x3F;
	unsigned char fb = len | ((ch & 0x01) << 6);
	
	write(m_fd, &fb, 1);
	write(m_fd, desc, len);
}

void Protocol::recv() {
	unsigned char c1;

	read(m_fd, &c1, 1);
	switch (c1 & 0xc0) {
		case 0x00: // volume change
			unsigned char c2;
			read(m_fd, &c2, 1);
			setVolume(c1 >> 2, ((c1 & 0x03) << 8) | c2);
			break;
		case 0x40: // mute
			setMute((c1 & 0x02) >> 1, (c1 & 0x01) == 0x01);
			break;
		case 0x80: // channel change
			changeChannel(c1 & 0x01);
			break;
	}
}

void Protocol::setVolume(unsigned int ch, unsigned int vol) {
	printf("Set volume on channel %u to %u\n", ch, vol); // TODO
}

void Protocol::setMute(unsigned int ch, bool mute) {
	printf("Turn mute on channel %d %s\n", ch, mute ? "on" : "off"); // TODO
}

void Protocol::changeChannel(unsigned int ch) {
	printf("Change channel %d\n", ch); // TODO
}

void Protocol::sendSignalLevels() {
	unsigned char c, level1, level2, levelM;

	// TODO get actual levels mapped into 0..15 domain
	level1 = 1;
	level2 = 2;
	levelM = 3;

	// first byte: 1000AAAA
	c = 0x40 | level1;
	write(m_fd, &c, 1);

	// second byte: BBBBCCCC
	c = (level2 << 4) | levelM;
	write(m_fd, &c, 1);
}
