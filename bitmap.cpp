#include <iostream>
#include "bitmap.h"


void cellShade(Bitmap& b) {

	cout << "Building the world..." << endl;
	//Call helper function
	b.cellShade();	

}
uint32_t Bitmap::checkClosest(uint32_t & component){

	//Set the pixel's color component to a value depending on how close it is to 0, 128, or 255
	if(component < 0x80)
		component = 0x0;

	else if(component >= 0x80)
		component = 0xFF;

	//Return the value after rounding it
	return component;
		

}
void Bitmap::cellShade(){

	//These are variables to hold the pixel's color components once isolated
        uint32_t red;
        uint32_t green;
        uint32_t blue;
	for(int i = 0; i < pixelVector.size() ; i++)
	{
		//IGNORE the alpha pixel
		
		//Bitshift (Push) the isolated component to the rightmost bits, for reading into the rounding function
		//The masks protect the value being isolated from turning into 0
		red = (pixelVector.at(i) & mask1) >> shiftDetermine(mask1);
		green = (pixelVector.at(i) & mask2) >> shiftDetermine(mask2);
		blue = (pixelVector.at(i) & mask3) >> shiftDetermine(mask3);

		//Make sure to bitshift it back to the appropriate place, you can then just add the values up like 100 + 10 + 1
		pixelVector.at(i) = (checkClosest(red) << shiftDetermine(mask1)) + 
				    (checkClosest(green) << shiftDetermine(mask2)) + 
				    (checkClosest(blue) << shiftDetermine(mask3));
	}
}
void update(Bitmap& b, vector<uint32_t>& toSave)
{
	b.update(toSave);
}
void Bitmap::update(vector<uint32_t>& toSave){
	pixelVector = toSave;
}
istream& operator>>(istream& in, Bitmap& b) {
	
	//Header 1	
	uint32_t temp;

	//Read in the first two characters
	for(int i = 0; i < 2 ; ++i){

		in.read((char*)&temp, 1);
		b.identifier.push_back(temp);
	}
	//Check if the first two characters are indeed BM
	if(b.identifier.at(0) != 'B' || b.identifier.at(1) != 'M')
	{
		throw (Exception(" Invalid Bitmap file: Expected BM")); //If tag isn't BM, throw an exception
	}

	in.read((char*)&b.size, 4);
	//Read in garbage
	for(int i = 0; i < 4 ; ++i){

		in.read((char*)&temp, 1);
		b.garbage.push_back(temp);
	}
	in.read((char*)&b.offset,4);

	//Header 2
	in.read((char*)&b.secondSize, 4);
	in.read((char*)&b.width, 4);
	in.read((char*)&b.height, 4);
	in.read((char*)&b.colorPlanes, 2);
	if(b.colorPlanes != 1){
		throw (Exception(" Invalid Bitmap file: Color Planes is not 1"));} //Color Plane amount should alwaus be 1
	in.read((char*)&b.colorDepth, 2);
	in.read((char*)&b.compressionMethod, 4);
	if(b.compressionMethod != 3){
		throw (Exception(" Invalid Bitmap file: Expected Compression Method to be 3"));} //Compression method should only be 3
	in.read((char*)&b.sizeRaw, 4);
	in.read((char*)&b.horiRes, 4);
	in.read((char*)&b.vertRes, 4);
 	in.read((char*)&b.paletteColors, 4);
	in.read((char*)&b.importantColors, 4);

	//Masks
	//NOTE: These would only be included if compression method is 3!
	if(b.compressionMethod == 3){
		in.read((char*)&b.mask1, 4);
		in.read((char*)&b.mask2, 4);
		in.read((char*)&b.mask3, 4);
		in.read((char*)&b.mask4, 4);
		in.read((char*)&b.maskOrder, 4);
		//Read in colorSpace
		for(int i = 0; i < 64 ; ++i){
			in.read((char*)&temp, 1);
			b.colorSpace.push_back(temp);
		}

	}

	//Reading in the pixel data
	//Set the vector's size to height x width of the image, because that's how many pixels there are
	for(int i = 0; i < (b.height * b.width) ; ++i){

		//32-bit
		in.read((char*)&temp, 4);
		b.pixelVector.push_back(temp);
		
	}

	return in;
}

ostream& operator<<(ostream& out, const Bitmap& b) {

	//Header 1
	//Only output two characters, which should be BM
	for(int i = 0; i < 2; ++i)
	{
		out.write((char*)&b.identifier.at(i), 1);
	}
	out.write((char*)&b.size, 4);
	for(int i = 0; i < 4; ++i)
	{
		out.write((char*)&b.garbage.at(i), 1);
	}
        out.write((char*)&b.offset, 4);

	//Header 2
       	out.write((char*)&b.secondSize, 4);
       	out.write((char*)&b.width, 4);
       	out.write((char*)&b.height, 4);
	out.write((char*)&b.colorPlanes, 2);
	out.write((char*)&b.colorDepth, 2);
	out.write((char*)&b.compressionMethod, 4);
       	out.write((char*)&b.sizeRaw, 4);
       	out.write((char*)&b.horiRes, 4);
	out.write((char*)&b.vertRes, 4);
       	out.write((char*)&b.paletteColors, 4);
       	out.write((char*)&b.importantColors, 4);

	//Masks
	//NOTE: These would only be included if compression method is 3!
	if(b.compressionMethod == 3)
	{
		out.write((char*)&b.mask1, 4);
		out.write((char*)&b.mask2, 4);
		out.write((char*)&b.mask3, 4);
		out.write((char*)&b.mask4, 4);
		out.write((char*)&b.maskOrder, 4);
		for(int i = 0; i < 64; ++i)
		{
			out.write((char*)&b.colorSpace.at(i), 1);
		}
	}

	//Pixel Data
	for(int i = 0; i < (b.width * b.height) ; ++i)
	{

		out.write((char*)&b.pixelVector.at(i), 4);
	}

	return out;
} 


//This is the contructor
Bitmap::Bitmap() {
/* unimplemented */
}
Bitmap::~Bitmap() {
}
