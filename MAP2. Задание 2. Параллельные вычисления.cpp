#include <thread>
#include <iostream>
#include <chrono>
#include<vector>
#include<algorithm>
#include<array>
using namespace std::chrono_literals;

std::vector<int> create_vec(size_t size)
{
    std::vector<int> a(size);

    for (int i = 0; i < size; i++)
    {
        a[i] = i + 1;
        return a;
    }
}

void sumVec(std::vector<int>& a1, std::vector<int>& a2, std::vector<int>& result, int begin, int end)
{
    for (int i = begin; i < end; i++)
    {
        result[i] = a1[i] + a2[i];
    }
}


void sum(int num, std::vector<int>& a1, std::vector<int>& a2, std::vector<int>& result, int size)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> t;
   
    for (int j = 0; j < num; j++)
    {
        int begin = (size / num) * j;
        int end = (size / num) * (j + 1);

        t.push_back(std::thread(sumVec, std::ref(a1), std::ref(a2), std::ref(result), begin, end));
    }
    for (auto& t : t)
    {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << time.count() << "\t";
}



int main()
{
    setlocale(LC_ALL, "Rus");

    std::array<int, 4> size{ 1000, 10000, 100000, 1000000 };
    std::array <int, 5> num{ 1, 2, 4, 8, 16 };

    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl;

    for (const auto& i : size)std::cout << "         " << i <<"\t";
    std::cout << std::endl;
    for (const auto& j : num)
    {
        std::cout << j << " потоков ";

        for (const auto& i : size)
        {
            std::vector<int> a1 = create_vec(i);
            std::vector<int> a2 = create_vec(i);
            std::vector<int> result(i);

            sum(j, a1, a2, result, i);
        }
        std::cout << std::endl;
    }


}

