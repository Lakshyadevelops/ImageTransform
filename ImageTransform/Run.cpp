#include "Run.h"
#include <NvOnnxParser.h>
#include<onnxruntime_cxx_api.h>
#include"Logger.h"
#include<atlbase.h>
#include<atlconv.h>

//#include "Engine.h"


Run::Run()
{
	enum_to_model_name[Models::BWtoCOLOR] = "BW to Color";
	enum_to_model_name[Models::RemoveScratches] = "Remove Scratches";
	enum_to_model_name[Models::MNIST] = "MNIST";

	enum_to_model_path[Models::BWtoCOLOR] = "..\\Models\\colorize_input_channel_3.onnx";

	/*
	TO DO
	enum_to_model_path[Models::MNIST] = "..\\Models\\mnist.onnx";
	enum_to_model_path[RemoveScratches] = "";
	*/


}

Run::~Run()
{

}

std::string Run::getModelName(Models model)
{
	return enum_to_model_name[model];
}

//static std::vector<float> loadImage(const std::string& filename, int sizeX = 224, int sizeY = 224)
//{
//	cv::Mat image = cv::imread(filename);
//	if (image.empty()) {
//		std::cout << "No image found.";
//	}
//
//	// convert from BGR to RGB
//	cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
//
//	// resize
//	cv::resize(image, image, cv::Size(sizeX, sizeY));
//
//	// reshape to 1D
//	image = image.reshape(1, 1);
//
//	// uint_8, [0, 255] -> float, [0, 1]
//	// Normalize number to between 0 and 1
//	// Convert to vector<float> from cv::Mat.
//	std::vector<float> vec;
//	image.convertTo(vec, CV_32FC1, 1. / 255);
//
//	// Transpose (Height, Width, Channel)(224,224,3) to (Chanel, Height, Width)(3,224,224)
//	std::vector<float> output;
//	for (size_t ch = 0; ch < 3; ++ch) {
//		for (size_t i = ch; i < vec.size(); i += 3) {
//			output.emplace_back(vec[i]);
//		}
//	}
//	return output;
//}
//
//static std::vector<std::string> loadLabels(const std::string& filename)
//{
//	std::vector<std::string> output;
//
//	std::ifstream file(filename);
//	if (file) {
//		std::string s;
//		while (getline(file, s)) {
//			output.emplace_back(s);
//		}
//		file.close();
//	}
//
//	return output;
//}


void Run::run(int model_selected, std::vector<cv::Mat>& image_list,std::unordered_map<std::string, int>& hyper_parameters,bool img_BW)
{
	Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ModelRunner");

	// Initialize session options
	Ort::SessionOptions session_options;
	Ort::ThrowOnError(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));

	// Load model
	std::string model_path = enum_to_model_path[static_cast<Models>(model_selected)];
	CA2W modelPathWstr(model_path.c_str());
	Ort::Session session(env, modelPathWstr, session_options);

	// Load image

	cv::Mat img = image_list[0];

	// Convert image to 3D tensor
	img.convertTo(img, CV_32F);

	// Create input tensor object from data values
	std::array<int64_t, 3> input_shape = { img.channels(), img.rows, img.cols };
	auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
	auto input_tensor = Ort::Value::CreateTensor<float>(memory_info, (float*)img.data, img.total(), input_shape.data(), input_shape.size());

	// Run model
	Ort::AllocatorWithDefaultOptions allocator;
	std::vector<const char*> input_names = { session.GetInputNameAllocated(0, allocator) };
	std::vector<const char*> output_names = { session.GetOutputNameAllocated(0, allocator) };
	auto output_tensors = session.Run(Ort::RunOptions{ nullptr }, input_names.data(), &input_tensor, 1, output_names.data(), 1);

	// Get output tensor
	float* floatarr = output_tensors.front().GetTensorMutableData<float>();

	// Convert output tensor to cv::Mat
	cv::Mat output_img(img.rows, img.cols, CV_32FC3, floatarr);
	output_img.convertTo(output_img, CV_8UC3);

	// Save output image
	cv::imwrite("output_image.jpg", output_img);

	return;



	////Testing onnxrun time	
	//Ort::Env env;
	//Ort::RunOptions runOptions;
	//cv::Mat img = image_list[0];
	////Ort::Session session(nullptr);
	//constexpr int64_t numChannels = 3;
	//const int64_t width = img.cols;
	//const int64_t height = img.rows;
	////constexpr int64_t numClasses = 1000;
	//const int64_t numInputElements = numChannels * height * width;

	//const std::string imageFile = "..\\TestExamples\\dog.png";
	//const std::string labelFile = "..\\TestExamples\\imagenet_classes.txt";
	////std::string modelPath = "..\\Models\\resnet50v2.onnx";
	//
	//std::string modelPath = enum_to_model_path[static_cast<Models>(model_selected)];
	//CA2W modelPathWstr(modelPath.c_str());
	// 

	////load labels
	////std::vector<std::string> labels = loadLabels(labelFile);
	////if (labels.empty()) {
	////	std::cout << "Failed to load labels: " << labelFile << std::endl;
	////	return;
	////}

	////// load image
	////const std::vector<float> imageVec = loadImage(imageFile);
	////if (imageVec.empty()) {
	////	std::cout << "Failed to load image: " << imageFile << std::endl;
	////	return;
	////}

	////if (imageVec.size() != numInputElements) {
	////	std::cout << imageVec.size();
	////	std::cout << "Invalid image format. Must be 224x224 RGB image." << std::endl;
	////	return;
	////}


	//// Use CUDA GPU
	//Ort::SessionOptions ort_session_options(nullptr);

	//OrtCUDAProviderOptions options;
	//options.device_id = 0;
	//options.arena_extend_strategy = 0;
	//options.gpu_mem_limit = 2 * 1024 * 1024 * 1024;
	//options.cudnn_conv_algo_search = OrtCudnnConvAlgoSearchExhaustive;
	//options.do_copy_in_default_stream = 1;

	//OrtSessionOptionsAppendExecutionProvider_CUDA(ort_session_options, options.device_id);

	//// create session
	//Ort::Session session(env,modelPathWstr, ort_session_options);

	//// Use CPU
	////session = Ort::Session(env, modelPath, Ort::SessionOptions{ nullptr });

	//// define shape
	//const std::array<int64_t, 4> inputShape = { 1, numChannels, height, width };
	//const std::array<int64_t, 4> outputShape = { 1, numChannels, height, width };

	//// define array
	//std::array<float, numInputElements> input;
	//std::array<float, numInputElements> results;
	//

	//// define Tensor
	//auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
	//auto inputTensor = Ort::Value::CreateTensor<float>(memory_info, input.data(), input.size(), inputShape.data(), inputShape.size());
	//auto outputTensor = Ort::Value::CreateTensor<float>(memory_info, results.data(), results.size(), outputShape.data(), outputShape.size());

	//// copy image data to input array
	//std::copy(imageVec.begin(), imageVec.end(), input.begin());



	//// define names
	//Ort::AllocatorWithDefaultOptions ort_alloc;
	//Ort::AllocatedStringPtr inputName = session.GetInputNameAllocated(0, ort_alloc);
	//Ort::AllocatedStringPtr outputName = session.GetOutputNameAllocated(0, ort_alloc);
	//const std::array<const char*, 1> inputNames = { inputName.get() };
	//const std::array<const char*, 1> outputNames = { outputName.get() };
	//inputName.release();
	//outputName.release();


	//// run inference
	//try {
	//	session.Run(runOptions, inputNames.data(), &inputTensor, 1, outputNames.data(), &outputTensor, 1);
	//}
	//catch (Ort::Exception& e) {
	//	std::cout << e.what() << std::endl;
	//	return;
	//}

	//// sort results
	//std::vector<std::pair<size_t, float>> indexValuePairs;
	//for (size_t i = 0; i < results.size(); ++i) {
	//	indexValuePairs.emplace_back(i, results[i]);
	//}
	//std::sort(indexValuePairs.begin(), indexValuePairs.end(), [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

	//// show Top5
	//for (size_t i = 0; i < 5; ++i) {
	//	const auto& result = indexValuePairs[i];
	//	std::cout << i + 1 << ": " << labels[result.first] << " " << result.second << std::endl;
	//}

	




	//Create the builder

	//auto builder = nvinfer1::createInferBuilder(gLogger);
	//assert(builder != nullptr);
	//
	////Parse the ONNX Model to create a TensorRT network
	//const auto explicit_batch = 1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
	//auto network = builder->createNetworkV2(explicit_batch);

	//auto parser = nvonnxparser::createParser(*network, gLogger);
	//assert(parser != nullptr);

	//const std::string model_path = enum_to_model_path[static_cast<Models>(model_selected)];
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
	//// Assuming you have a vector of cv::Mat images
	//for (auto& image : image_list) {
	//	// Create a buffer to hold inputs and outputs
	//	std::vector<void*> buffers(2);
	//	image.convertTo(image, CV_32F, 1.0 / 255, 0);

	//	// Allocate GPU memory for inputs and outputs
	//	cudaMalloc(&buffers[0], 1 * 1 * 28 * 28 * sizeof(float));
	//	cudaMalloc(&buffers[1], 1 * 10 * sizeof(float));

	//	// Copy the image to the input buffer
	//	cudaMemcpy(buffers[0], image.data, 1 * 1 * 28 * 28 * sizeof(float), cudaMemcpyHostToDevice);

	//	// Create an execution context
	//	auto context = engine->createExecutionContext();
	//	assert(context != nullptr);

	//	// Run inference
	//	context->executeV2(buffers.data());

	//	// Allocate memory for the output on the host
	//	std::vector<float> output(10);

	//	// Copy the output from the GPU to the host
	//	cudaMemcpy(&output[0], buffers[1], 10 * sizeof(float), cudaMemcpyDeviceToHost);

	//	// Print the output
	//	for (int i = 0; i < 10; ++i) {
	//		gLogger.CustomLog(std::to_string(i)+" " +std::to_string(output[i]));
	//		//std::cout << "Output " << i << ": " << output[i] << std::endl;
	//	}

	//	// Free GPU memory
	//	cudaFree(buffers[0]);
	//	cudaFree(buffers[1]);

	//	// Destroy the execution context
	//	context->destroy();
	//}


	//engine->destroy();
	//network->destroy();
	//parser->destroy();
	//config->destroy();
	//builder->destroy();




}


