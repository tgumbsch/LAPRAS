#include <vector>
#include <iostream>
#include <numeric>

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

struct Itemset{
    std::vector<int>  locations = {}; //indices
    double time =1.; //runtime
};


#include "LAPRAS.cpp"
#include "PowerSet.cpp"
#include <ctime>



extern "C" {
    double powerset(std::vector<double>* v,const char* TEST, double *arr, int length){
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
        std::vector<int> S;
        S.resize(length);
        std::iota(S.begin(), S.end(),0);


        std::clock_t start;
        std::clock_t stop;

        Itemset Result;
        Result.locations = {};

        start = std::clock();


        if (strcmp(TEST,"LAPRAS")==0 ){
            LAPRAS LP;
            LP.Fit(S,0);
            //Result.locations = LP.return_index();
        }
        else if(strcmp(TEST,"BU")==0 ){
            BottomUp BU;
            BU.Init(S);
            BU.Fit(S);
            //Result.locations = BU.return_index();
        }
        else if(strcmp(TEST,"Binary")==0 ){
            FastBinary(S);
        }
        else if(strcmp(TEST,"SlowBinary")==0 ){
            Binary(S);
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
    std::vector<double>* new_vector(){
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

int main(int argc, const char * argv[]) {
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {
        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        printf("free memory: %lld\nused memory: %lld\n", free_memory, used_memory);
    }

        std::vector<double> seq = {1.1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        std::cout << seq[0];
        int length = 10;
        std::vector<double> Column;
        std::vector<std::vector<double>> Dist;
        for(int x = 0; x < length; x++){
            Column = {};
            for(int y = 0; y < length; y++){
                Column.push_back(seq[x*length + y]);
            }
            Dist.push_back(Column);
        }


        BottomUp BU;
        std::vector<int> S;
        S.resize(Dist.size());
        std::iota(S.begin(), S.end(),0);
        //double obj = BU.Init(S);
        BU.Fit(S);

            mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {
        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        printf("free memory: %lld\nused memory: %lld\n", free_memory, used_memory);
    }


    return 0;
}


