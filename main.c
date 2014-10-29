
/*and the code*/
#include <opencv2/opencv.hpp>
#include <vector>
#include <stdio.h>


using namespace cv;
int i,j;

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat ,int* val);
int get_raw( int s[]);
int reverse(int raw);



int main( int argc, char** argv )
{

  int raw[640*480];
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




void createAlphaMat(Mat &mat ,int* val)
{   int k=0;
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {

        	 Vec4b& rgba = mat.at<Vec4b>(i, j);
        	rgba[0] =val[k]/4;

            rgba[1] =val[k]/4;
            rgba[2] =val[k]/4;
            rgba[3] = 25;
            /*
            rgba[0] = reverse(val[k])/4-1; //(UCHAR_MAX-i)/13;
            rgba[1] = reverse(val[k])/4-1;//(UCHAR_MAX-j)/13;//saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = reverse(val[k])/4-1; //UCHAR_MAX-100;//saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = 255;//saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
            */
            k++;
        }
    }
}






int get_raw( int s[]) {

	uint tmp[20];
    uint data[5];   //when use [int] instead of [uint] , [1111111111]=-1 (!!!not 1023!!!)
    int i,k;
    FILE *fi;

   fi=fopen("00", "rb");

for(k=0;k<(640*480/16);k++){


/*---------init-------------*/

 	for(i=0;i<20;i++)
    tmp[i]=0;


	for (i=0;i<5;i++)
	data[i]=0;

    fread(data,4,5,fi);

    tmp[0]=data[0]>>22;
    tmp[1]=(data[0]<<10)>>22;
    tmp[2]=(data[0]<<20)>>22;
    tmp[3]=(data[0]<<30)>>22;

    tmp[4]=data[1]>>24;
    tmp[5]=(data[1]<<8)>>22;
    tmp[6]=(data[1]<<18)>>22;
    tmp[7]=(data[1]<<28)>>22;

    tmp[8] =data[2]>>26;
    tmp[9] =(data[2]<<6)>>22;
    tmp[10]=(data[2]<<16)>>22;
    tmp[11]=(data[2]<<26)>>22;

    tmp[12]=data[3]>>28;
    tmp[13]=(data[3]<<4)>>22;
    tmp[14]=(data[3]<<14)>>22;
    tmp[15]=(data[3]<<24)>>22;

    tmp[16]=data[4]>>30;
    tmp[17]=(data[4]<<2)>>22;
    tmp[18]=(data[4]<<12)>>22;
    tmp[19]=(data[4]<<22)>>22;


    s[k*16+0]=tmp[0];
    s[k*16+1]=tmp[1];
    s[k*16+2]=tmp[2];
    s[k*16+3]=tmp[3]+tmp[4];
    s[k*16+4]=tmp[5];
    s[k*16+5]=tmp[6];
    s[k*16+6]=tmp[7]+tmp[8];
    s[k*16+7]=tmp[9];
    s[k*16+8]=tmp[10];
    s[k*16+9]=tmp[11]+tmp[12];
    s[k*16+10]=tmp[13];
    s[k*16+11]=tmp[14];
    s[k*16+12]=tmp[15]+tmp[16];
    s[k*16+13]=tmp[17];
    s[k*16+14]=tmp[18];
    s[k*16+15]=tmp[19];



 }

    fclose(fi);

    return 0;
}

/*
short int swap8bits(int) 
*/

int reverse(int raw){
	return raw<<15>>6|raw<<14>>7|raw<<13>>8|raw<<12>>9|raw<<11>>10|raw<<10>>11|raw<<9>>12|raw<<8>>13|raw<<7>>14|raw<<6>>15;
}
