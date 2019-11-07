#include <iostream>

using namespace std;

void NearestNeighbor();
void all_pair_sequential_static();
void all_pair_sequential_dynamic();
void all_pair_sequential_guide();
void all_pair_dynamic();
void vector_add();
void softmax();

int main()
{

	int n = 0;

	cout << "\n\n--------------------------\n\n";
//	cout << "all_pair_sequential_static Output\n";
//	cout << "all_pair_sequential_dynamic Output\n";
//	cout << "all_pair_dynamic Output\n";
//	cout << "all_pair_sequential_guide Output\n";
//	cout << "vector_add Output\n";
 	cout << "Nearest Neighbor Output\n";
//	cout << "Softmax Output\n";

//	all_pair_sequential_static();

//	all_pair_sequential_dynamic();

//  all_pair_sequential_guide();

//	all_pair_dynamic();

//	vector_add();

//	NearestNeighbor();

	softmax();

	cout << "\n\n--------------------------\n\n";

	std::cin >> n;

}