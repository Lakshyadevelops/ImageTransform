#pragma once
#include<NvInfer.h>
#include<opencv2/opencv.hpp>

enum models{BWtoCOLOR,RemoveScratches,MNIST};

class Run
{
	public:
		Run();
		~Run();
		void run(int&,std::vector<cv::Mat>&,std::unordered_map<std::string,int>&);

	private:

};

