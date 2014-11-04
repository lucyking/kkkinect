#include <opencv2/opencv.hpp>
#include <vector>
#include <stdio.h>


using namespace cv;
int i,j;

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat ,unsigned short int* val);
int get_raw(unsigned short int s[]);
unsigned short reverse(unsigned short int src);
unsigned short get_bit(unsigned short src,int index);



int main( int argc, char** argv )
{

  unsigned short int raw[640*480];
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
