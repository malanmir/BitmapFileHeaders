#include<fstream>
#include<iostream>
#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace std;

caveofprogramming::Bitmap::Bitmap(int width, int height) : m_width(width), m_heigth(height), m_pPixels(new uint8_t[width * height * 3]{})
{
}

caveofprogramming::Bitmap::~Bitmap()
{
}

bool caveofprogramming::Bitmap::write(std::string filename)
{
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width * m_heigth * 3;
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
	
	infoHeader.width = m_width;
	infoHeader.height = m_heigth;

	ofstream file;
	file.open(filename, ios::out | ios::binary);
	
	if (!file)
		return false;
	
	file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
	file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
	file.write(reinterpret_cast<char*>(m_pPixels.get()), m_width * m_heigth * 3);
	
	file.close();
	if (!file)
		return false;
	return true;
}

void caveofprogramming::Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t *pPixel = m_pPixels.get();
	pPixel += (y * 3) * m_width + (x * 3);

	pPixel[0] = blue;
	pPixel[1] = green;
	pPixel[2] = red;
	
}
