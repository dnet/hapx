#ifndef _SINKINPUT_H_
#define _SINKINPUT_H_

#include <pulse/pulseaudio.h>
#include <stdio.h>
#define STRDESCLEN 64

class SinkInput {
protected:
	const pa_sink_input_info *m_i;
public:
	SinkInput(const pa_sink_input_info* i);
	char* desc();
};

#endif
