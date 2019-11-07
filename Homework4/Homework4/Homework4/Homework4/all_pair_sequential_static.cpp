#include <iostream>                   // std::cout
#include <cstdint>                    // int64_t
#include <vector>                     // std::vector
#include <thread>                     // std::thread (not used yet)
#include "hpc_helpers.hpp" // timers, no_init_t
#include "binary_IO.hpp"   // load_binary

template <
	typename index_t,
	typename value_t>
	void sequential_all_pairs_static(
		std::vector<value_t>& mnist,
		std::vector<value_t>& all_pair,
		index_t rows,
		index_t cols) {

	#pragma omp parallel for schedule(static)
	// for all entries below the diagonal (i'=I)
	for (index_t i = 0; i < rows; i++) {
		for (index_t I = 0; I <= i; I++) {
			// compute squared Euclidean distance
			value_t accum = value_t(0);
			for (index_t j = 0; j < cols; j++) {
				value_t residue = mnist[i * cols + j]
					- mnist[I * cols + j];
				accum += residue * residue;
			}

			// write Delta[i,i'] = Delta[i',i] = dist(i, i')
			all_pair[i * rows + I] = all_pair[I * rows + i] = accum;
		}
	}
}

void all_pair_sequential_static() {

	// used data types
	typedef no_init_t<float> value_t;
	typedef int64_t         index_t;

	// number of images and pixels
	const index_t rows = 65000;
	const index_t cols = 28 * 28;

	// load MNIST data from binary file
	TIMERSTART(load_data_from_disk)
		std::vector<value_t> mnist(rows * cols);
	load_binary(mnist.data(), rows * cols,
		"C:/Users/marsh/Documents/GitHub/ParallelProgramming/Homework4/Homework4/Homework4/Homework4/data2/data/mnist_65000_28_28_32.bin");
	TIMERSTOP(load_data_from_disk)

		TIMERSTART(compute_distances)
		std::vector<value_t> all_pair(rows * rows);
	sequential_all_pairs_static(mnist, all_pair, rows, cols);
	TIMERSTOP(compute_distances)


		TIMERSTART(dump_to_disk)
		dump_binary(mnist.data(), rows * rows, "./all_pairs.bin");
	TIMERSTOP(dump_to_disk)

}