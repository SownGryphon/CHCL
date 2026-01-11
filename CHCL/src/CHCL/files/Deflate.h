#pragma once

#include "CHCL/dataStorage/Buffer.h"

namespace chcl
{
	Buffer DeflateDecomp(const void *data, size_t predictedSize = 0);
	inline Buffer DeflateDecomp(const Buffer &compressed) { return DeflateDecomp(compressed.data()); }
}