#include <vector>
#include <iostream>
#include <numeric>
#include "LAPRAS.cpp"
#include "PowerSet.cpp"
#include <ctime>

int main(){
    std::clock_t start;
    std::clock_t stop;
    int it = 1;

    for(int i = 20; i<21; i++){

        std::vector<int> Set(i);
        std::iota(Set.begin(), Set.end(),0);

        start = std::clock();
        for(int j = 0; j< it;j++){
        LAPRAS LP;
        LP.Init(Set);
        LP.Fit(Set,0);
        }
        stop = std::clock();
        std::cout << i << " Suffix: " << ( stop - start ) / (double) CLOCKS_PER_SEC << std::endl;

        Set.resize(i);
        std::iota(Set.begin(), Set.end(),0);


        start = std::clock();
        BottomUp BU;
        BU.Init(Set);
        BU.Fit(Set);
        stop = std::clock();
        std::cout << i << " Bottom Up: " << ( stop - start ) / (double) CLOCKS_PER_SEC << std::endl;


        Set.resize(i);
        std::iota(Set.begin(), Set.end(),0);

        start = std::clock();
        for(int j = 0; j< it;j++){
        PowerSet(Set);
        }
        stop = std::clock();
        std::cout << i << " Binary: " << ( stop - start ) / (double) CLOCKS_PER_SEC << std::endl;
    }
}


