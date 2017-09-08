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

#include <cstdlib>
#include "LAPRAS.cpp"
#include "PowerSet.cpp"
#include <ctime>


int main(int argc, const char * argv[]) {

        int length = atoi(argv[1]);
        int type = atoi(argv[2]);
        std::vector<double> seq(length*length);

        std::iota(seq.begin(), seq.begin() + length*length,0);

        std::vector<double> Column;
        std::vector<std::vector<double>> Dist;
        for(int x = 0; x < length; x++){
            Column = {};
            for(int y = 0; y < length; y++){
                Column.push_back(seq[x*length + y]);
            }
            Dist.push_back(Column);
        }

        std::vector<int> S;


        if(type == 0){
        BottomUp BU;
        S.resize(length);
        std::iota(S.begin(), S.end(),0);
        double obj = BU.Init(S,Dist);
        BU.Fit(S, Dist);
    }
    else if(type == 1){

        LAPRAS LA;
        S.resize(length);
        std::iota(S.begin(), S.end(),0);
        double obj = LA.Init(Dist);
        LA.Fit(S, Dist,0,obj);
    }
else{
    PowerSet(Dist,length);
}


    return 0;
}


