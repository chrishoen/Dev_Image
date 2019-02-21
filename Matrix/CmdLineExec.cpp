
#include "stdafx.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override. Execute a command line command. It calls one of
// the following specific command execution functions. This is called by
// the owner of this object to pass command line commands to it. 

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO21"))      executeGo21(aCmd);
   if (aCmd->isCmd("GO22"))      executeGo22(aCmd);
   if (aCmd->isCmd("GO23"))      executeGo23(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))       executeGo5(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GO1  ******************************");

   cv::Mat tX1;
   cv::Mat tX2;

   tX1 = cv::imread("C:\\Alpha\\TestImage\\Image1920_0.png", CV_8UC1);
   tX2 = tX1;

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");

   tX1 = cv::imread("C:\\Alpha\\TestImage\\Image1920_1.png", CV_8UC1);

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GO21 ******************************");

   cv::Mat tX1;
   cv::Mat tX2;

   tX1 = cv::Mat(1080, 1920, CV_8UC1, 11);
   tX2 = tX1;

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");

   tX1 = cv::Mat::zeros(1080, 1920, CV_8UC1);

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GO22 ******************************");

   cv::Mat tX1;
   cv::Mat tX2;

   tX1 = cv::Mat(1080, 1920, CV_8UC1, 11);
   tX2 = tX1;

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");

   tX1 = cv::Mat();
   tX1 = cv::Mat::zeros(1080, 1920, CV_8UC1);

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo23(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GO23 ******************************");

   cv::Mat tX1;
   cv::Mat tX2;

   tX1 = cv::Mat(1080, 1920, CV_8UC1, 11);
   tX2 = tX1;

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");

   tX1 = cv::Mat(cv::Mat::zeros(1080, 1920, CV_8UC1));

   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GO3  ******************************");

   cv::Mat tX1;
   cv::Mat tX2;

   tX1 = cv::Mat(1080, 1920, CV_8UC1, 11);
   tX2 = tX1;
   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");

   tX1 = cv::Mat(1080, 1920, CV_8UC1,cv::Scalar(0));
   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   cv::Mat tX1;
   cv::Mat tX2;

   tX1 = cv::Mat(1080, 1920, CV_8UC1, 11);
   tX2 = tX1;
   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");

   tX1 = cv::Mat(1080, 1920, CV_8UC1, cv::Scalar(0));
   Prn::print(0, "X1 %4d %8x", tX1.at<uchar>(0, 0), tX1.data);
   Prn::print(0, "X2 %4d %8x", tX2.at<uchar>(0, 0), tX2.data);
   Prn::print(0, "");

   size_t tX1Size = tX1.total() * tX1.elemSize();
   size_t tX2Size = tX2.total() * tX2.elemSize();
   Prn::print(0, "S1 %4d", tX1Size);
   Prn::print(0, "S2 %4d", tX2Size);
}

