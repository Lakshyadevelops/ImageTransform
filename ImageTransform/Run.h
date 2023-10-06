#pragma once
#include<NvInfer.h>
#include<opencv2/opencv.hpp>

const enum Models{BWtoCOLOR,RemoveScratches,MNIST};
// INFO:: Whenever adding new models do add their name in the constructor also
const Models ModelsList[] = { BWtoCOLOR,RemoveScratches,MNIST };

class Run
{
	public:
		Run();
		~Run();
		std::string getModelName(int);
		void run(const int&,std::vector<cv::Mat>&,std::unordered_map<std::string,int>&);

	private:
		std::unordered_map<int, std::string> enum_to_model_name;


};

