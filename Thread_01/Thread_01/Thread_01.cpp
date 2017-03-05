// Thread_01.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

//const values
#define MAX_COUNT		10000
#define MAX_THREAD		10

//global variables
std::mutex g_mutex;
int g_counter = 0;

#pragma region Mutex
void IncreaseFunc()
{
	/*if (g_mutex.try_lock() == false)
		return;*/
	
	g_mutex.lock();

	if (MAX_COUNT > g_counter)
	{
		++g_counter;
		std::cout << g_counter << std::endl;
	}

	g_mutex.unlock();
}

void ThreadFunc()
{
	while (g_counter < MAX_COUNT)
	{
		IncreaseFunc();
	}
}
#pragma endregion

#pragma region Unique lock
void IncreaseFunc2()
{
	std::unique_lock<std::mutex> lock(g_mutex);
	if (MAX_COUNT > g_counter)
	{
		++g_counter;
		std::cout << g_counter << std::endl;
	}
}

void ThreadFunc2()
{
	while (g_counter < MAX_COUNT)
	{
		IncreaseFunc2();
	}
}
#pragma endregion

int main()
{
	std::vector<std::thread> threads;
	for (unsigned int idx = 0; idx < MAX_THREAD; ++idx)
	{
		threads.push_back(std::thread(ThreadFunc));
	}

	for (unsigned int idx = 0; idx < threads.size(); ++idx)
	{
		threads[idx].join();
	}

	std::getchar();

	return 0;
}

