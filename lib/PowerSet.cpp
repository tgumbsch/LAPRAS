#include <math.h>


void Binary(std::vector<int> Set)
{
    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    int set_size = Set.size();
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
    }
}



void FastBinary(std::vector<int> Set)
{

    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    int set_size = Set.size();
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
            //if(affected>1){
            //    obj -= D[Processing[affected-1]][Processing[affected]];
            //}
            Processing.erase(Processing.begin()); //what are the armortized costs of this?
            k--;
            counter &= ~mask;
            mask <<= 1;
            affected++;
        }
        counter |= mask;
        Processing.insert(Processing.begin(),Set[affected]);
        k++;

        //if(k>1){
        //    obj += D[Processing[k-2]][Processing[k-1]];
        //}
       // Process the list of indices here!!
       //if(obj > best_obj){
       //     best_obj = obj;
       //     best_index = Processing;
       //}
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

