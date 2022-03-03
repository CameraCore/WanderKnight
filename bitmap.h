//This file contains bitmap handling
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

//An exception class for displaying specific messages
class Exception
{
	private:
		string message; //Error message
	public:
		string getMessage() const {return(message);} //Function to return a message

		//Constructor	
		Exception(const string& message) : message(message){};
		//Destructor
		~Exception(){};
		//Note: these are inline to avoid having to add them to the other cpp files.	
};

class Bitmap
{
	private:
	    //Overloaded i/o operators for taking in and writing out map data
	    friend istream& operator>>(istream& in, Bitmap& b);
	    friend ostream& operator<<(ostream& out, const Bitmap& b);
	    //UA START
	    //These are the bitmap header's fields

	    //First Header
	    //Holds the first two characters to confirm that BM is there 
	    //NOTE: using character arrays here instead of vectors because these are set amounts that don't need to grow
	    //Putting these fields into a vector would take more lines of code
	    vector<char> identifier; //Should be BM
	    uint32_t size;
	    vector<char> garbage;
	    uint32_t offset;

	    //Second Header
	    uint32_t secondSize;
	    int width;
	    int height;
	    uint16_t colorPlanes; //Should always be 1
	    uint16_t colorDepth; //Can either be 24(RGB) or 32(RGBA)
	    uint32_t compressionMethod; //Should always be 0 or 3
	    uint32_t sizeRaw;
	    uint32_t horiRes; //These resolutions will always be 2835
	    uint32_t vertRes; 
	    uint32_t paletteColors; //These following two aren't used since palettes arent used for this project
	    uint32_t importantColors;

	    //Masks
	    //Determines which RGBA values a pixel has
	    uint32_t mask1; //Always the red mask
	    uint32_t mask2; //Always the green mask
	    uint32_t mask3; //Always the blue mask
	    uint32_t mask4;
	    uint32_t maskOrder; //The order of the masks
	    vector<char> colorSpace; //Unused in this project 

	    //Pixel Data
	    vector<uint32_t> pixelVector;

	public:
	    Bitmap(); //This is the constructor
	    ~Bitmap(); //This is the destructor

	    void cellShade(); //Rounds the pixel's color to the nearest value of 0 or 255
		uint32_t checkClosest(uint32_t & component);	//Checks which color the pixel component is closest too, then return the rounded value
	    void update(vector<uint32_t> & toSave);    //Updates the pixel vector using a new vector
	    //Takes in a mask value and returns how much to shift that value
	    int shiftDetermine (uint32_t mask) 
	    {
		//Each digit is 4 bytes, so return 4*n where n is the digit place
		if(mask == 0xFF000000)
			return 24;
		else if(mask == 0x00FF0000)
			return 16;
		else if(mask == 0x0000FF00)
			return 8;
		else if(mask == 0x000000FF)
			return 0;
	    }
	    //Returns the value in it's pixel array
	    uint32_t getColor(int index) {return pixelVector.at(index);};
	    //Returns the size of the pixel vector
	    int getSize() {return pixelVector.size();};
	    int getWidth() {return width;}
	    int getHeight() {return height;}


};
void cellShade(Bitmap& b);		 //Convert the Bitmap into a worldmap

void update(Bitmap& b, vector<uint32_t>& toSave);    //Updates the pixel vector using a new vector
