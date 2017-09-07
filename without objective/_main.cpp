#include <vector>
#include <iostream>
#include <numeric>

struct Itemset{
    std::vector<int>  locations = {}; //indices
    double time =1.; //runtime
};


#include "LAPRAS.cpp"
#include "PowerSet.cpp"
#include <ctime>



extern "C" {
    // Changepoint detection on the vector v
    double powerset(std::vector<int>* v,const char* TEST, int *arr, int length){
        // It is possible to change the testing function here, K-S test or Mann-Whitney, for instance
        std::vector<int> seq(arr, arr + length);

        std::clock_t start;
        std::clock_t stop;

        start = std::clock();

        Itemset Result;
        Result.locations = seq;

        if (strcmp(TEST,"LAPRAS")==0 ){
            LAPRAS LP;
            LP.Init(seq);
            LP.Fit(seq,0);
        }
        else if(strcmp(TEST,"BU")==0 ){
            BottomUp BU;
            BU.Init(seq);
            BU.Fit(seq);
        }
        else if(strcmp(TEST,"Binary")==0 ){
            PowerSet(seq);
        }
        else {
            std::cout<< "Unrecognized function" << std::endl;
        }

        stop = std::clock();
        Result.time = ( stop - start ) / (double) CLOCKS_PER_SEC;

        v->push_back(Result.locations.size()); // v[v.size()] = size of itemset
        for (auto const& loc : Result.locations){ // v[v.size()+1,v.size()+v[v.size()]] = items
            v->push_back(loc);
        }
        return Result.time;

    }

    // Helper fucntions to build the vector containing the time series
    std::vector<int>* new_vector(){
        return new std::vector<int>;
    }
    void delete_vector(std::vector<int>* v){
        // std::cout << "destructor called in C++ for " << v << std::endl;
        delete v;
    }
    int vector_size(std::vector<int>* v){
        return v->size();
    }
    double vector_get(std::vector<int>* v, int i){
        return v->at(i);
    }
    void vector_push_back(std::vector<int>* v, int i){
        v->push_back(i);
    }
}


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


