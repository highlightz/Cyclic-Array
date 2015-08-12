// To run this example, 
// Bumblebee2-Stereo-Camera-Driver-Class-for-Windows 
// is needed, which can be found at https://github.com/highlightz/Bumblebee2-Stereo-Camera-Driver-Class-for-Windows

#include <iostream>
#include <sstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

#include "DataCache.h"

#include <opencv2/opencv.hpp>

#include "bb2_wrapper.h"
bb2_wrapper m_camera(640,480);
IplImage* pfL;
IplImage* pfR;
IplImage* pframeL;
IplImage* pframeR;
IplImage* disp8;

int main( )
{
	pfL = cvCreateImage(cvSize(640,480),8,3);
	pfR = cvCreateImage(cvSize(640,480),8,3);
	disp8 = cvCreateImage(cvSize(640,480),8,1);

	DataCache< cv::Mat > dcL, dcR;

	if( !m_camera.StartCamera() )
	{
		cout<<"StartCamera failed!"<<endl;
		return -1;
	}
	else
	{
		//m_camera.showCameraInfo( );
		m_camera.EnableStereoMatch( );
		while (1)
		{
			if(m_camera.AcquireFrame()&&m_camera.StereoMatch())
			{
				pframeL = m_camera.GetRetfImgL();
				pframeR = m_camera.GetRetfImgR();
				m_camera.Four2Three(pframeL,pfL);
				m_camera.Four2Three(pframeR,pfR);

				/*
				disp8 = m_camera.getStereo( );
				cv::Mat disparity( disp8 );
				cv::imshow( "disp8", disparity );
				*/

				cv::Mat left( pfL, true );
				cv::Mat right( pfR, true );
				dcL.writeData( left );
				dcR.writeData( right );
				//cout << "The current number of datas in cache is: " << dc.getLastDatas( ).numDatas << endl;

				DataInfo< cv::Mat > diL, diR;
				diL = dcL.getLastDatas( );
				diR = dcR.getLastDatas( );
				if ( diL.numDatas > 1 )
				{
					for ( int i = 0; i < diL.numDatas; i++ )
					{
						stringstream ss;
						ss << i + 1;
						string windowName;
						ss >> windowName;
						windowName = "frameL " + windowName;
						cv::imshow( windowName, diL.datas[i] );
					}
				}
				if ( diR.numDatas > 1 )
				{
					for ( int i = 0; i < diR.numDatas; i++ )
					{
						stringstream ss;
						ss << i + 1;
						string windowName;
						ss >> windowName;
						windowName = "frameR " + windowName;
						cv::imshow( windowName, diR.datas[i] );
					}
				}

				cvWaitKey( 33 );
			}
		}	
	}
	
	m_camera.StopCamera();
	cvDestroyWindow("Left");
	cvDestroyWindow("Right");
	return 0;
}
