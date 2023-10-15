#include "Run.h"
#include <NvOnnxParser.h>
//#include "Engine.h"


Run::Run()
{
	enum_to_model_name[Models::BWtoCOLOR] = "BW to Color";
	enum_to_model_name[Models::RemoveScratches] = "Remove Scratches";
	enum_to_model_name[Models::MNIST] = "MNIST";

	enum_to_model_path[Models::MNIST] = "..\\Models\\mnist.onnx";

	/*
	TO DO
	enum_to_model_name[BWtoCOLOR] = "";
	enum_to_model_name[RemoveScratches] = "";
	*/


}

Run::~Run()
{

}

std::string Run::getModelName(Models model)
{
	return enum_to_model_name[model];
}

void Run::run(const int& model_selected, std::vector<cv::Mat>& image_list,std::unordered_map<std::string, int>& hyper_parameters)
{
	//Create the builder
	//auto builder = nvinfer1::createInferBuilder(gLogger);
	//assert(builder != nullptr);
	//
	////Parse the ONNX Model to create a TensorRT network
	//const auto explicit_batch = 1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
	//auto network = builder->createNetworkV2(explicit_batch);

	//auto parser = nvonnxparser::createParser(*network, gLogger);
	//assert(parser != nullptr);

	//const std::string model_path = enum_to_model_path[model_selected];
	//if (!parser->parseFromFile(model_path.c_str(), static_cast<int>(nvinfer1::ILogger::Severity::kWARNING))) {
	//	gLogger.CustomLog("ERROR: Failed to parse the ONNX File.");
	//	return;
	//}

	//auto input = network->getInput(0);
	//assert(input != nullptr);
	//input->setDimensions(nvinfer1::Dims4{ 1,1,28,28 });

	//builder->setMaxBatchSize(1);
	//auto config = builder->createBuilderConfig();
	//config->setMaxWorkspaceSize(256 * (1 << 20)); // 256 MiB

	//auto engine = builder->buildEngineWithConfig(*network, *config);
	//assert(engine != nullptr);

	///*
	//TO DO inference
	//*/

	//engine->destroy();
	//network->destroy();
	//parser->destroy();
	//config->destroy();
	//builder->destroy();




}
