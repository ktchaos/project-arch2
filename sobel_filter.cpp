#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//CKingimageDoc* pDoc = GetDocument();  /* TODO: definir file */

int iBitPerPixel = pDoc->_bmp->bitsperpixel;
int iWidth = pDoc->_bmp->width;
int iHeight = pDoc->_bmp->height;
BYTE *pImg = pDoc->_bmp->point;
const int area = iWidth * iHeight;
BYTE *pImg2 = new BYTE[area];

int main() {
    if (iBitPerPixel == 8)
    {
        int pixel_x;
        int pixel_y;

        float sobel_x[3][3] =
        { { -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 } };

        float sobel_y[3][3] =
        { { -1, -2, -1 },
        { 0,  0,  0 },
        { 1,  2,  1 } };

        for (int x=1; x < iWidth-1; x++)
        {
            for (int y=1; y < iHeight-1; y++)
            {

                pixel_x = (sobel_x[0][0] * pImg[iWidth * (y-1) + (x-1)])
                        + (sobel_x[0][1] * pImg[iWidth * (y-1) +  x   ])
                        + (sobel_x[0][2] * pImg[iWidth * (y-1) + (x+1)])
                        + (sobel_x[1][0] * pImg[iWidth *  y    + (x-1)])
                        + (sobel_x[1][1] * pImg[iWidth *  y    +  x   ])
                        + (sobel_x[1][2] * pImg[iWidth *  y    + (x+1)])
                        + (sobel_x[2][0] * pImg[iWidth * (y+1) + (x-1)])
                        + (sobel_x[2][1] * pImg[iWidth * (y+1) +  x   ])
                        + (sobel_x[2][2] * pImg[iWidth * (y+1) + (x+1)]);

                pixel_y = (sobel_y[0][0] * pImg[iWidth * (y-1) + (x-1)])
                        + (sobel_y[0][1] * pImg[iWidth * (y-1) +  x   ])
                        + (sobel_y[0][2] * pImg[iWidth * (y-1) + (x+1)])
                        + (sobel_y[1][0] * pImg[iWidth *  y    + (x-1)])
                        + (sobel_y[1][1] * pImg[iWidth *  y    +  x   ])
                        + (sobel_y[1][2] * pImg[iWidth *  y    + (x+1)])
                        + (sobel_y[2][0] * pImg[iWidth * (y+1) + (x-1)])
                        + (sobel_y[2][1] * pImg[iWidth * (y+1) +  x   ])
                        + (sobel_y[2][2] * pImg[iWidth * (y+1) + (x+1)]);

                int val = (int)sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y));

                if(val < 0) val = 0;
                if(val > 255) val = 255;

                pImg2[iHeight * y + x] = val;
            }
        }
    }
}