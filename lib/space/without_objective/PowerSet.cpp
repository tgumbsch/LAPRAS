#include <math.h>
#include <bitset>

void PowerSet(std::vector<int> Set)
{
    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    int set_size = Set.size();
    unsigned int pow_set_size = pow(2, set_size);
    int counter, mask, affected, j,k;
    std::vector<int> ToBeRemoved(Set.size());
    std::vector<int> Processing(set_size);

    /*Run from counter 000..0 to 111..1*/
    counter = 0;
    while(counter < pow_set_size)
    {
       k=0;

       // Bitwise increment of counter
        mask = 1;
        affected = 0;
        // This loop has armortized factor of O(1)
        while (counter & mask)
        {
            Processing.erase(Processing.begin()); //what are the armortized costs of this?
            counter &= ~mask;
            mask <<= 1;
            affected++;
        }
        counter |= mask;
        Processing.insert(Processing.begin(),Set[affected]);
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
    i=0;
    size = loc;
    while(i<size){
        Config = Powerset[i];
        Config.push_back(x);
        Powerset[loc] = Config;
        loc++;
        i++;
    }

}

