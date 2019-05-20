// ColorLight.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
  GetColor �������Կ���״̬�����жϡ�
    �����ʱ����ɫ����Ϊ��ɫ�����red��
	�����ʱ���󲿷���ɫ�����ǳ�ɫ�����orange��
	�̵���ʱ����hsv��ֵ���жϣ����green_on��
	�̵���ʱ�����green_out;
*/
void GetColor(Mat frame)
{
	int arr[4][2][3] = { { { 156, 43,  46 },{ 180, 255, 255 } },  //red
						 { { 11, 43,  46 },{ 25, 255, 255 } },  //orange
						 { { 35, 43, 127 },{ 77, 255, 255 } },  //green_on  �̵���
						 { { 35, 43,  46 },{ 77, 255,  80 } }   //green_out �̵ư�
					   };
	Mat hsv, mask, binary, binary2;	
	printf("recognizing the status...");
	cvtColor(frame, hsv, COLOR_BGR2HSV);
	int maxsum = -100, color_num;
	string color[4] = {"red", "orange", "green_on", "green_out"};
	int i, lower[3], upper[3];
	for (i = 0; i < 4; i++) 
	{
		//ͼ����������ֵ��Χ�ڵ�ͼ���������������ɶ�ֵͼ
		inRange(hsv, Scalar(arr[i][0][0], arr[i][0][1], arr[i][0][2]), 
			Scalar(arr[i][1][0], arr[i][1][1], arr[i][1][2]), mask);
		threshold(mask, binary, 127, 255, THRESH_BINARY);
		dilate(binary, binary2, Mat(), Point(-1,-1), 2);

		int sum = 0;
		int height = binary2.rows;
		int width = binary2.cols;
		int a, b;
		for (a = 0;a < height;a++)
		{
			for (b = 0;b < width;b++)
			{
				if (binary2.at<uchar>(a, b) == 255)
				{
					sum += 1;
				}
			}
		}
		if (sum > maxsum)
		{
			maxsum = sum;
			color_num = i;
		}

	}
	cout << color[color_num];
}

/*
  GetColorRG�������ж�һ��ͼƬ(�ŶϷ�)��Ҫ��ɫ�Ǻ�ɫ������ɫ��
    ��ɫ�����red��
    ��ɫ�����green��
*/
void GetColorRG(Mat frame)
{
	int arr[2][2][3] = { { { 156, 43,  46 },{ 180, 255, 255 } }, //red
							{ { 35, 43,  46 },{ 77, 255, 255 } }  //green
						  };
	Mat hsv, mask, binary, binary2;
	printf("recognizing the status...");
	cvtColor(frame, hsv, COLOR_BGR2HSV);
	int maxsum = -100, color_num;
	string color[2] = { "red", "green"};
	int i;
	for (i = 0; i < 2; i++)
	{
		//ͼ����������ֵ��Χ�ڵ�ͼ���������������ɶ�ֵͼ
		inRange(hsv, Scalar(arr[i][0][0], arr[i][0][1], arr[i][0][2]),
			Scalar(arr[i][1][0], arr[i][1][1], arr[i][1][2]), mask);
		threshold(mask, binary, 127, 255, THRESH_BINARY);
		dilate(binary, binary2, Mat(), Point(-1, -1), 2);

		int sum = 0;
		int height = binary2.rows;
		int width = binary2.cols;
		int a, b;
		for (a = 0;a < height;a++)
		{
			for (b = 0;b < width;b++)
			{
				if (binary2.at<uchar>(a, b) == 255)
				{
					sum += 1;
				}
			}
		}
		if (sum > maxsum)
		{
			maxsum = sum;
			color_num = i;
		}

	}
	cout << color[color_num];
}

int main()
{
	
	
	Mat src = imread("H:/green.jpg");  //��ȡͼƬ
	//GetColor(src);
	//GetColorRG(src);
	return 0;
}