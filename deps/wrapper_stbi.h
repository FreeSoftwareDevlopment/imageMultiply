#pragma once
#ifndef dynlink
#define frontw
#else
#ifdef EXPORTSNOWstb_d
#define frontw __declspec( dllexport )
#else
#define frontw __declspec( dllimport )
#endif
#endif // !dynlink

namespace stb_image {
	frontw void stbiw_set_flip_vertically_on_load(int n);
	frontw unsigned char* stbiw_load(const char* filename, int* x, int* y, int* bpp, int desired_channels);
	frontw void stbiw_image_free(void* tounload);
}
