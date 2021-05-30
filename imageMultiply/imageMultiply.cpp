#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <wrapper_stbi.h>
#include "stbi_img_write.hpp"

#define s 4
#define path std::filesystem::path
#define exists std::filesystem::exists

int main(int argc, char* argv[])
{
	if (argc > 3) {
		int width[2], height[2], BPP[2];
		memset(width, 0x00, sizeof(width));
		memset(height, 0x00, sizeof(height));
		memset(BPP, 0x00, sizeof(BPP));
		if (!(exists(path(argv[1])) && exists(path(argv[2])))) {
			puts("You should give me a File Path that Work!\n");
			return -1;
		}
		unsigned char* buf1 = stb_image::stbiw_load(argv[1], &width[0], &height[0], &BPP[0], s);
		unsigned char* buf2 = stb_image::stbiw_load(argv[2], &width[1], &height[1], &BPP[1], s);
		printf("IN 1:\n\tHEIGHT: %i\n\tWIDTH: %i\n\tBPP: %i\n\n"
			"IN 2:\n\tHEIGHT: %i\n\tWIDTH: %i\n\tBPP: %i\n",
			height[0], width[0], BPP[0],
			height[1], width[1], BPP[1]);

		if (height[0] != height[1] || width[0] != width[1] || BPP[0] != BPP[1]) {
			puts("\nThe Image Format or Size is not ==\n");
			return 1;
		}
		int aSize{ width[0] * height[0] * BPP[0] };
		if (aSize <= 0)
			return 2;

		for (int xr{ 0 }; xr < aSize; xr++) {
			buf1[xr] = (unsigned char)(((float)buf1[xr] / 0xff) * ((float)buf2[xr] / 0xff) * 0xff);
		}

		path p(argv[3]);
		{
			bool xt{ true };
			std::string ext = p.extension().string();
			if (ext.length() == 4)
				xt = ext != std::string(".png");
			if (!p.has_extension() || xt)
				p.replace_extension(".png"); 
		}

		stbi_write_png(p.string().c_str(), width[0], height[0], s, buf1, width[0] * s);

		printf("\nOUT:\n\tHEIGHT: %i\n\tWIDTH: %i\n",
			height[0], width[0]);

		if (buf1 != nullptr)
			stb_image::stbiw_image_free(buf1);
		if (buf2 != nullptr)
			stb_image::stbiw_image_free(buf2);
	}
	else {
		printf("imgMultiply\n<c> Sharkbyteprojects\nUsage: %s <in1> <in2> <out>\n", argv[0]);
		return -1;
	}
	return 0;
}
