#include <math.h>

void PowerSet(std::vector<int> Set, int set_size)
{
    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
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
             If set then pront jth element from set */
          if(counter & (1<<j)){
            Processing[k] = Set[j];
            //std::cout << Set[j];
            k++;
        }

       }
       //std::cout << std::endl;
       Processing.resize(k);
    }
}

class BottomUp{
public:
    std::vector<int> Set;
    std::vector<int> Config;
    std::vector<std::vector<int>> Powerset;
    int i,size;
    int loc;

    void Init(std::vector<int> &X);
    void Fit(std::vector<int> &Node);


};


void BottomUp::Init(std::vector<int> &X){
    Set = X;
    std::vector<int> Empty = {};
    loc = 0;
    Powerset.resize(pow(2,X.size()+1));
    Powerset[loc] = Empty;
    loc++;
}

void BottomUp::Fit(std::vector<int> &Node){
    std::vector<int> Branch = Node;
    int x = Branch.back();
    Branch.pop_back();

    if (Branch.size()>0){
        Fit(Branch);
    }
    std::vector<std::vector<int>> add;
    i=0;
    size=Powerset.size();
    while(i<size){
        Config = Powerset[i];
        Config.push_back(x);
        Powerset[loc] = Config;
        loc++;
        i++;
    }

}
