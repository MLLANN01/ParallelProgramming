#include "hpc_helpers.hpp"  // timers
#include "binary_IO.hpp"    // load images

#include <limits>   // numerical limits of data types
#include <vector>   // std::vector
#include <cmath>    // std::max
#include <algorithm>
#include<opencv2/opencv.hpp>


template <
	typename value_t,
	typename index_t>
	void softmax_regression(
		value_t* input,
		value_t* output,
		value_t* weights,
		value_t* bias,
		index_t   n_input,
		index_t   n_output) {

	for (index_t j = 0; j < n_output; j++) {
		value_t accum = value_t(0);
		for (index_t k = 0; k < n_input; k++)
			accum += weights[j * n_input + k] * input[k];
		output[j] = accum + bias[j];

	}

	value_t norm = value_t(0);
	value_t mu = std::numeric_limits<value_t>::lowest();


	// compute mu = max(z_j)
	for (index_t index = 0; index < n_output; index++)
		mu = std::max(mu, output[index]);

	// compute y_j = exp(z_j-mu)
	for (index_t j = 0; j < n_output; j++)
		output[j] = std::exp(output[j] - mu);

	// compute Z = sum_j z_j
	for (index_t j = 0; j < n_output; j++)
		norm += output[j];

	// compute z_j/Z
	for (index_t j = 0; j < n_output; j++)
		output[j] /= norm;

}

template <
	typename value_t,
	typename index_t>
	index_t argmax(
		value_t * neurons,
		index_t   n_units) {

	index_t arg = 0;
	value_t max = std::numeric_limits<value_t>::lowest();

	for (index_t j = 0; j < n_units; j++) {
		const value_t val = neurons[j];
		if (val > max) {
			arg = j;
			max = val;
		}
	}

	std::cout << "Guess: " << arg << std::endl;

	return arg;
}

template <
	typename value_t,
	typename index_t>
	float accuracy(
		value_t * input,
		value_t * label,
		value_t * weights,
		value_t * bias,
		index_t   num_entries,
		index_t   num_features,
		index_t   num_classes) {

	index_t counter = index_t(0);

	# pragma omp parallel for reduction(+: counter)
	for (index_t i = 0; i < num_entries; i++) {

		value_t output[10];
		const int64_t input_off = i * num_features;
		const int64_t label_off = i * num_classes;

		softmax_regression<float, int64_t>(input + input_off, output, weights,
			bias, num_features, num_classes);

		counter += argmax<float, int64_t>(output, num_classes) ==
			argmax(label + label_off, num_classes);

	}

	return value_t(counter) / value_t(num_entries);
}

void softmax() {

	const int64_t num_features = 28 * 28;
	const int64_t num_classes = 10;
	const int64_t num_entries = 100;
	const int64_t num_acc = 100;

	std::vector<float> input(num_entries * num_features);
	std::vector<float> label(num_entries * num_classes);

	std::vector<float> weights(num_classes * num_features);
	std::vector<float> bias(num_classes);

//	load_binary(input.data(), input.size(), "C:/Users/marsh/Documents/GitHub/ParallelProgramming/Homework4/Homework4/Homework4/Homework4/data/X.bin");
//	load_binary(label.data(), label.size(), "C:/Users/marsh/Documents/GitHub/ParallelProgramming/Homework4/Homework4/Homework4/Homework4/data/Y.bin");
//	load_binary(weights.data(), weights.size(), "C:/Users/marsh/Documents/GitHub/ParallelProgramming/Homework4/Homework4/Homework4/Homework4/data/A.bin");


	load_binary(input.data(), input.size(), "C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/ImageData/exports/X.bin");
	load_binary(label.data(), label.size(), "C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/ImageData/exports/Y.bin");
    load_binary(weights.data(), weights.size(), "C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/ImageData/exports/W.bin");


	load_binary(bias.data(), bias.size(), "C:/Users/marsh/Documents/GitHub/ParallelProgramming/Homework4/Homework4/Homework4/Homework4/data/b.bin");;

	std::cout << "Input Data: " << std::endl;

	for (int i = 0; i <= input.size(); i++)
	{
		if ((i) % 28 == 0 && i != 0)
			std::cout << std::endl;

		if (input[i] != 0)
			std::cout << "1 ";
		else
			std::cout << input[i] << " ";
	}

	std::cout << "\nLabel Data: " << std::endl;

	for (int i = 0; i <= label.size(); i++)
	{
		if ((i) % 10 == 0 && i != 0)
			std::cout << std::endl;

		std::cout << label[i] << " ";
	}

	while (true) {

		TIMERSTART(accuracy)
			auto acc = accuracy(input.data(),
				label.data(),
				weights.data(),
				bias.data(),
				num_acc,
				num_features,
				num_classes);
		TIMERSTOP(accuracy)

			std::cout << "\naccuracy_test: " << std::setprecision(10) << acc << std::endl;

			
	}

	
}
