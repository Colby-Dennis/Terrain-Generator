// Following M Muiz Hassan's tutorial on dev.to
// https://dev.to/muiz6/c-how-to-write-a-bitmap-image-from-scratch-1k6m

#include <cstdint> // for specific size integers
#include <fstream> // for file handling
using namespace std;

int w = 512;
int h = 512;

struct BmpHeader {
	char bitmapSignatureBytes[2] = {'B','M'};
	uint32_t sizeOfBitmapFile = (14+40) + (w*h*3); // total size of bitmap file
	uint32_t reservedBytes = 0;
	uint32_t pixelDataOffset = 54;
};

BmpHeader bmpHeader;

struct BmpInfoHeader {
	uint32_t sizeOfThisHeader = 40;
	int32_t width = w; // in pixels
	int32_t height = h; // in pixels
	uint16_t numberOfColorPlanes = 1; // must be 1
	uint16_t colorDepth = 24;
	uint32_t compressionMethod = 0;
	uint32_t rawBitmapDataSize = 0; // generally ignored
	int32_t horizontalResolution = 0; // in pixel per meter
	int32_t verticalResolution = 0; // in pixel per meter
	uint32_t colorTableEntries = 0;
	uint32_t importantColors = 0;
};

BmpInfoHeader bmpInfoHeader;

struct Pixel {
	uint8_t blue = 250;
	uint8_t green = 250;
	uint8_t red = 0;
};

Pixel pixel;

int main(int argc, char **argv) {
	ofstream out("output.bmp", ios::binary);

	out.write((char *) &bmpHeader, 14);
	out.write((char *) &bmpInfoHeader, 40);

	// writing pixel data
	size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
	for (int i = 0; i < numberOfPixels; i++) {
		out.write((char *) &pixel, 3);
	}
	out.close();

	return 0;
}