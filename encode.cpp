#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::cout << argv << std::endl;
    std::string algo;
    std::cin >> algo;
    std::cout << "algo: " << algo << std::endl;
    std::string quickSort = "quick";

    if (algo.compare(quickSort) == 0){
        std::cout << "Running quicksort";
    }
    else
    {
        std::cout << "Running insertion sort" << std::endl;
    }

    int txt = std::cin.get();
    std::cout << txt << std::endl;
    

    return 0;
}