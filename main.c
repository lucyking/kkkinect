#include <opencv2/opencv.hpp>
#include <vector>
#include <stdio.h>
#define SIZE 384000

using namespace cv;
int i,j;

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat ,unsigned int* val);
int get_raw(unsigned int raw[]);
unsigned short reverse(unsigned short int src);
unsigned short get_bit(unsigned short src,int index);



int main( int argc, char** argv )
{

  unsigned int raw[640*480];
  get_raw(raw);
  Mat mat(480, 640, CV_8UC4);
  createAlphaMat(mat,raw);

  vector<int> compression_params;
  compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(10);
  imwrite("00.png", mat, compression_params);
/* test raw data;but it seems right
  for(i=0;i<640*480;i++)
          printf("%d\n",raw[i]);
*/
  /*
  namedWindow( "Display Image", WINDOW_AUTOSIZE );
  imshow( "Display Image",mat);

  waitKey(0);
*/

  return 0;
}




void createAlphaMat(Mat &mat ,unsigned int* val)
{ int k=0;
    unsigned int pixel;
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
             //printf("%d\n",val[k]);

                pixel=val[k]/4;


                 Vec4b& rgba = mat.at<Vec4b>(i, j);
                 rgba[0] = pixel;
                 rgba[1] = pixel;
                 rgba[2] = pixel;
                 rgba[3] = 255;

                         /*
                rgba[0] = reverse(val[k])/4;
            rgba[1] =reverse(val[k])/4;
            rgba[2] =reverse(val[k])/4;
            rgba[3] = 255;
            */
            /*
            rgba[0] = reverse(val[k])/4-1; //(UCHAR_MAX-i)/13;
            rgba[1] = reverse(val[k])/4-1;//(UCHAR_MAX-j)/13;//saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = reverse(val[k])/4-1; //UCHAR_MAX-100;//saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = 255;//saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
            */
            k++;
        }
    }



/*
    k=0;
    for (int i = 0; i < mat.rows; i++) {
            for (int j = 0; j < mat.cols; j++) {
                 //printf("%d\n",val[k]);
                    pixel=reverse(val[k])/4;
                     Vec4b& rgba = mat.at<Vec4b>(i, j);
                     if(abs(pixel-nearst)<=10){
                     rgba[0] = 0;
                     rgba[1] = 0;
                     rgba[2] = 255;
                     rgba[3] = 255;
                     }


                k++;
            }
        }

*/




}






int get_raw(unsigned int raw[]) {

    FILE *fi;

    int k,index;
    unsigned char tmp[SIZE];



    fi=fopen("00", "rb");
    fread(tmp,sizeof(tmp[0]),SIZE,fi);
        fclose(fi);

        index=0;

        k=0;
for (k=0;k<384000;k=k+5){


        raw[index+0]=tmp[k+0]<<2;
        raw[index+0]=raw[index+0]|(tmp[k+1]>>6);
        //printf("%d\n",raw[0] );


        raw[index+1]=(tmp[k+1]&0b00111111)<<4;
        raw[index+1]=raw[index+1]|(tmp[k+2]>>4);
        //printf("%d\n",raw[1] );


        raw[index+2]=(tmp[k+2]&0b00001111)<<6;
        raw[index+2]=raw[index+2]|(tmp[k+3]>>2);
        //printf("%d\n",raw[2] );

        raw[index+3]=(tmp[k+3]&0b00000011)<<8;
        raw[index+3]=raw[index+3]|tmp[k+4];
        //printf("%d\n",raw[3] );

        index=index+4;

}



    return 0;
}

/*
short int swap8bits(int)
*/

unsigned short reverse(unsigned short src){
        int tmp[17],i;
        tmp[0]=get_bit(src,0)*32768;
        tmp[1]=get_bit(src,1)*16384;
        tmp[2]=get_bit(src,2)*8192;
        tmp[3]=get_bit(src,3)*4096;
        tmp[4]=get_bit(src,4)*2048;
        tmp[5]=get_bit(src,5)*1024;
        tmp[6]=get_bit(src,6)*512;
        tmp[7]=get_bit(src,7)*256;
        tmp[8]=get_bit(src,8)*128;
        tmp[9]=get_bit(src,9)*64;
        tmp[10]=get_bit(src,10)*32;
        tmp[11]=get_bit(src,11)*16;
        tmp[12]=get_bit(src,12)*8;
        tmp[13]=get_bit(src,13)*4;
        tmp[14]=get_bit(src,14)*2;
        tmp[15]=get_bit(src,15);
        tmp[16]=0;
        for (i = 0; i < 16; ++i)
        tmp[16]=tmp[16]+tmp[i];
        return tmp[16];
        //return raw>>3<<12|0x8;
        //return (raw<<15)|((raw>>1)<<14)|((raw>>2)<<13)|((raw>>3)<<12)|((raw>>4)<<11)|((raw>>5)<<10)|((raw>>6)<<9)|((raw>>7)<<8)|((raw>>8)<<7)|((raw>>9)<<6)|((raw>>10)<<5)|((raw>>11)<<4)|((raw>>12)<<3)|((raw>>13)<<2)|((raw>>14)<<1)|(raw>>15);
}



unsigned short get_bit(unsigned short src,int index){


        return ((src>>index<<15)&0xffff)>>15;

}
