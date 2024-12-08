#include <iostream>
#include <fstream>
#include <stdint.h>

#include <stdlib.h>		// srand, rand
#include <time.h>

struct ImageHeader
{
	char signature[4]; //first 4 bytes
	uint16_t width; // 2 bytes 
	uint16_t height; // 2 bytes
	unsigned short mode; // 2 bytes
};

struct Image
{
	ImageHeader header;
	char* data;
};

bool WriteImage(Image* img, const char* filename)
{
	std::ofstream os(filename, std::ifstream::binary);
	if (!os)
		return false;

	// write header first
	os.write((char*)&img->header, sizeof(ImageHeader));

	// calculate image size
	uint16_t imgsize = img->header.width * img->header.height;

	// write image content
	os.write(img->data, imgsize);

	return true;
}

int getFileSize(const char* filename) {
	std::ifstream file(filename, std::ifstream::binary | std::ifstream::ate); //ate makes it open the file from the end
	if (!file) {
		return 0;
	}
	return file.tellg();
}

Image *ReadImage(const char* filename)
{
	std::ifstream is(filename, std::ifstream::binary);
	if (!is)
		return nullptr;

	Image* img = new Image();

	// read header first
	is.read((char*)&img->header, sizeof(ImageHeader));

	// calculate image size
	uint16_t imgsize = img->header.width * img->header.height;


	//check file size
	int expectedSize = sizeof(ImageHeader) + imgsize;
	int fileSize = getFileSize(filename);
	std::cout << "size: " << fileSize << std::endl;
	std::cout << "expected size: " << expectedSize << std::endl;
	if (fileSize != expectedSize) {
		std::cout << "file is not the expected size" << std::endl;
		return img;
	}

	img->data = new char[imgsize];
	// read image content
	char* tmpbuff = new char[img->header.width];
	for (int i = 0; i < img->header.height; i++)
	{
		is.read(tmpbuff, img->header.width);
		memcpy(img->data + (i * img->header.width), tmpbuff, img->header.width);
	}
	return img;
}

void FreeImage(Image* img)
{
	delete img;
}

Image *GenerateDummyImage(uint16_t width, uint16_t height)
{
	Image* img = new Image();

	// create image header
	memcpy(img->header.signature, "MAGI", 4);
	img->header.width = width;
	img->header.height = height;
	img->header.mode = 1;

	// calculate image size
	uint16_t imgsize = img->header.width * img->header.height;
	img->data = new char[imgsize];

	// generate dummy content
	srand((unsigned int)time(0));
	char* pos = img->data;
	for (int i = 0; i < imgsize; i++)
		*pos++ = rand() % 255;

	return img;
}


int main()
{
	Image *im = ReadImage("img2.magi");
	FreeImage(im);

	//second pic defines width as ABAA in hex, that is 43707
	//and the height as  3
	//that means the size of the file is not consistent with the size specified in the headers

	return 0;
}
