#include <iostream>
#include <vector>
#include "lodepng.h"

using namespace std;

void decodeOneStep(double** pic, const char* filename);

int main()
{
    cout << "This is an encoder for PNG files." << endl
         << "Thanks lodepng project for making it possible!" << endl;

    size_t width = 28, height = 28;
    double** pic = new double* [width];
    for (size_t i = 0; i < 28; i++)
    {
        pic[i] = new double[height];
    }

    decodeOneStep(pic, "000000-num5.png");

    for (size_t i = 0; i < 28; i++)
    {
        for (size_t j = 0; j < 28; j++)
        {
            cout << pic[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

//Decode from disk to raw pixels with a single function call
void decodeOneStep(double** pic, const char* filename)
{
    vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    //decode
    unsigned error = lodepng::decode(image, width, height, filename);

    //if there's an error, display it
    if (error)
    {
        cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
    }

    size_t sup = 0, supPicLines = 0, supPicColumns = 0;
    bool flag = false;
    for (size_t i = 0; i < image.size(); i++)
    {
        sup++;
        if (sup == 4)
        {
            sup = 0;
            pic[supPicLines][supPicColumns] = (flag ? 1 : 0);
            if (++supPicColumns == 28)
            {
                supPicLines++;
                supPicColumns = 0;
            }
            flag = false;
        }
        else if ((int)image[i] != 0)
        {
            flag = true;
        }
    }
}