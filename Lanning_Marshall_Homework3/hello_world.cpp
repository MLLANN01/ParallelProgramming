#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>

template <typename index_t>
void say_hello_template(index_t id) {
	std::cout << "Hello from thread: " << id << std::endl;
}

void say_hello(uint64_t id) {
	std::cout << "Hello from thread: " << id << std::endl;
}

void hello_world() {

	const uint64_t num_threads = 6;

	std::vector<std::thread> threads;

	for (uint64_t id = 0; id < num_threads; id++)
		threads.emplace_back(
			std::thread(
				say_hello, id
			)
		);

	for (auto& thread : threads)
		thread.join();
}