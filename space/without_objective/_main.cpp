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



int main(int argc, const char * argv[]) {

        int length = atoi(argv[1]);
        int type = atoi(argv[2]);
        std::vector<int> seq(length);

        std::iota(seq.begin(), seq.begin() + length,0);




        if(type == 0){
        BottomUp BU;
        BU.Init(seq);
        BU.Fit(seq);
    }
    else if(type == 1){

        LAPRAS LA;
        LA.Init(seq);
        LA.Fit(seq, 0);
    }
else{
    PowerSet(seq);
}


    return 0;
}
