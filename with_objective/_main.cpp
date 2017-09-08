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
    double powerset(std::vector<double>* v,const char* TEST, double *arr, int length){
        // It is possible to change the testing function here, K-S test or Mann-Whitney, for instance
        std::vector<double> seq(arr, arr + length);

        std::vector<std::vector<double>> Dist;
        std::vector<double> Column;
        for(int x = 0; x < length; x++){
            Column = {};
            for(int y = 0; y < length; y++){
                Column.push_back(seq[x*length + y]);
            }
            Dist.push_back(Column);
        }

        std::clock_t start;
        std::clock_t stop;

        start = std::clock();

        Itemset Result;
        Result.locations = {};

        if (strcmp(TEST,"LAPRAS")==0 ){
            LAPRAS LP;
            std::vector<int> S;
            S.resize(Dist.size());
            std::iota(S.begin(), S.end(),1);
            double obj = LP.Init(Dist);
            LP.Fit(S,0,obj);
            Result.locations = LP.return_index();
        }
        else if(strcmp(TEST,"BU")==0 ){
            BottomUp BU;
            BU.Init(Dist);
            std::vector<int> S;
            S.resize(Dist.size());
            std::iota(S.begin(), S.end(),1);
            double obj = BU.Init(Dist);
            BU.Fit(Dist);
            Result.locations = BU.return_index());
        }
        else if(strcmp(TEST,"Binary")==0 ){
            Result.locations = PowerSet(Dist);
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
        return new std::vector<double>;
    }
    void delete_vector(std::vector<double>* v){
        // std::cout << "destructor called in C++ for " << v << std::endl;
        delete v;
    }
    int vector_size(std::vector<double>* v){
        return v->size();
    }
    double vector_get(std::vector<double>* v, int i){
        return v->at(i);
    }
    void vector_push_back(std::vector<double>* v, int i){
        v->push_back(i);
    }
}


int main(){
    return 0;
}


