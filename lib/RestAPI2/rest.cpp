#include "rest.h"

Rapi::Rapi() {}

restAction Rapi::handleRest() {
	restAction ra;
	ra.Pin = [1, 2];
	ra.Value = 127;
	return ra;
}