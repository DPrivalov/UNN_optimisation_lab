#include <thread>
#include <iostream>
using namespace std;

#define CACHE_LINE_ALIGNED

#define THREAD_1_CORE 0
#define THREAD_2_CORE 2
#define THREAD_3_CORE 4

#define CACHE_LINE_SIZE 64
#define ITERATION 30000

#pragma pack(push, 1)
struct dummy
{
#ifdef CACHE_LINE_ALIGNED
	alignas(CACHE_LINE_SIZE)uint32_t d1;
	alignas(CACHE_LINE_SIZE)uint32_t d2;
	alignas(CACHE_LINE_SIZE)uint32_t d3;
#else
	uint32_t d1;
	uint32_t d2;
	uint32_t d3;
#endif
};
#pragma pack(pop)

static  dummy  my_data[20];
static  dummy  other_data;

void thread1()
{
	for (int i(0); i<ITERATION; i++)
	{
		for (int j(0); j<ITERATION; j++)
		{
			for (size_t i = 0; i < 20; i++)
			{
				my_data[i].d1++;
				other_data.d1 += my_data[i].d1 * (my_data[i].d1 + 1);
			}
		}
	}
}

void thread2()
{
	for (int i(0); i<ITERATION; i++)
	{
		for (int j(0); j<ITERATION; j++)
		{
			for (size_t i = 0; i < 20; i++)
			{
				my_data[i].d2++;
				other_data.d2 += my_data[i].d2 * (my_data[i].d2 + 1);
			}
		}
	}
}

void thread3()
{
	for (int i(0); i<ITERATION; i++)
	{
		for (int j(0); j<ITERATION; j++)
		{
			for (size_t i = 0; i < 20; i++)
			{
				my_data[i].d3++;
				other_data.d3 += my_data[i].d3 * (my_data[i].d3 + 1);
			}
		}
	}
}

int main(int argc, char** argv)
{

	auto start = std::chrono::system_clock::now();
	
	std::thread first(thread1);
	std::thread second(thread2);
	std::thread third(thread3);

	first.join();
	second.join();
	third.join();

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time " << diff.count() << " s\n";
	for (size_t i = 0; i < 20; i++)
	{
		std::cout << my_data[i].d1 << ", " << my_data[i].d2 << ", "
			<< my_data[i].d3 << "\n";
	}
	std::cout << other_data.d1 << ", " << other_data.d2 << ", "
		<< other_data.d3;
	
	//cin >> other_data.d3;
	//cin.ignore();

	return 0;
}