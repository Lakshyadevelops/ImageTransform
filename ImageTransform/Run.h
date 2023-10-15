#pragma once
#include <NvInfer.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "Engine.h"

const enum class Models{BWtoCOLOR,RemoveScratches,MNIST};
// INFO:: Whenever adding new models do add their name in the constructor also
const Models ModelsList[] = { Models::BWtoCOLOR,Models::RemoveScratches,Models::MNIST };

class Run
{
	public:
		Run();
		~Run();
		std::string getModelName(Models);
		void run(const int&,std::vector<cv::Mat>&,std::unordered_map<std::string,int>&);

	private:
		Engine* engine;
		std::unordered_map<Models, std::string> enum_to_model_name;
		std::unordered_map<Models, std::string> enum_to_model_path;




};

