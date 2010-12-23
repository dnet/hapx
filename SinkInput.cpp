#include "SinkInput.h"

SinkInput::SinkInput(const pa_sink_input_info* i) {
	m_i = i;
}

char* SinkInput::desc() {
	char *retval = (char*)malloc(STRDESCLEN);
	if (!retval) return NULL;

	snprintf(retval, STRDESCLEN, "%s: %s", pa_proplist_gets(
		m_i->proplist, PA_PROP_APPLICATION_NAME), m_i->name);
	return retval;
}
