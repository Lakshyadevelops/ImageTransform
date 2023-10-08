#include "Run.h"

Run::Run()
{
	enum_to_model_name[BWtoCOLOR] = "BW to Color";
	enum_to_model_name[RemoveScratches] = "Remove Scratches";
	enum_to_model_name[MNIST] = "MNIST";


}

Run::~Run()
{

}

std::string Run::getModelName(int model)
{
	return enum_to_model_name[model];
}

void Run::run(const int& model_selected, std::vector<cv::Mat>& image_list,std::unordered_map<std::string, int>& hyper_parameters)
{

}
