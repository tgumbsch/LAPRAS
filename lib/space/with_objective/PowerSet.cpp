#include <math.h>


std::vector<int> PowerSet(std::vector<std::vector<double>> &Dist, int length)
{

    std::vector<int> Set;
    Set.resize(length);
    std::iota(Set.begin(), Set.end(),0);

    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    int set_size = length;
    unsigned int pow_set_size = pow(2, set_size);
    int counter, mask, affected, j,k;
    std::vector<int> ToBeRemoved(Set.size());
    std::vector<int> Processing(set_size);
    double obj, best_obj;
    std::vector<int> best_index;

    /*Run from counter 000..0 to 111..1*/
    counter = 0;
    k=0;
    obj = 0;
    while(counter < pow_set_size)
    {

       // Bitwise increment of counter
        mask = 1;
        affected = 0;
        // This loop has armortized factor of O(1)
        while (counter & mask)
        {
            if(affected>1){
                obj -= Dist[Processing[affected-1]][Processing[affected]];
            }
            Processing.erase(Processing.begin()); //what are the armortized costs of this?
            k--;
            counter &= ~mask;
            mask <<= 1;
            affected++;
        }
        counter |= mask;
        Processing.insert(Processing.begin(),Set[affected]);
        k++;

        if(k>1){
            obj += Dist[Processing[k-2]][Processing[k-1]];
        }

       if(obj > best_obj){
            best_obj = obj;
            best_index = Processing;
       }
    }

return best_index;

}



class BottomUp{
public:
    std::vector<int> Set;
    std::vector<int> Config;
    std::vector<int> best_index;
    double best_obj;
    double obj;
    std::vector<std::vector<int>> Powerset;
    int i,size;
    int loc;

    double Init(std::vector<int> &X,std::vector<std::vector<double>> &Dist);
    void Fit(std::vector<int> &Node, std::vector<std::vector<double>> &Dist);
    std::vector<int> return_index();


};

std::vector<int> BottomUp::return_index(){
    //std::cout << best_obj << std::endl;
    return best_index;
}


double BottomUp::Init(std::vector<int> &X,std::vector<std::vector<double>> &Dist){
    Set = X;
    std::vector<int> Empty = {};
    loc = 0;
    Powerset.resize(pow(2,X.size()+1));
    Powerset[loc] = Empty;
    loc++;

    best_obj = 0;
    for(int i = 0; i< X.size()-1;i++){
        best_obj += Dist[i][i+1];
    }

    return best_obj;
}

void BottomUp::Fit(std::vector<int> &Node, std::vector<std::vector<double>> &Dist){
    std::vector<int> Branch = Node;
    int x = Branch.back();
    Branch.pop_back();

    if (Branch.size()>1){
        Fit(Branch,Dist);
    }

    i=0;
    size = loc;
    while(i<size){
        Config = Powerset[i];
        Config.push_back(x);
        Powerset[loc] = Config;
        loc++;
        i++;


       obj = 0;
       for(int i = 0; i < Config.size()-1;i++){
            obj += Dist[Config[i]][Config[i+1]];
       }
       if(obj > best_obj){
            best_obj = obj;
            best_index = Config;
       }


    }

}

