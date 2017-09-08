#include <math.h>

std::vector<int> PowerSet(std::vector<std::vector<double>> &Dist, int length)
{
    std::vector<int> Set;
    Set.resize(length);
    std::iota(Set.begin(), Set.end(),0);

    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    int set_size = length;
    double best_obj = 0;
    double obj = 0;
    std::vector<int> best_index;
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j,k;
    std::vector<int> Processing(set_size);


    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
       k=0;
      for(j = 0; j < set_size; j++)
       {
          /* Check if jth bit in the counter is set
             If set then print jth element from set */
          if(counter & (1<<j)){
            Processing[k] = Set[j];
            //std::cout << Set[j];
            k++;
        }

       }
       //std::cout << std::endl;
       Processing.resize(k);

       obj = 0;
       for(int i = 0; i < k-1;i++){
            obj += Dist[Processing[i]][Processing[i+1]];
       }
       if(obj > best_obj){
            best_obj = obj;
            best_index = Processing;
       }

    }
    //std::cout << best_obj << std::endl;
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

