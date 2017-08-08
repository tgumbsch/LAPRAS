
class LAPRAS {
    std::vector<int> S;
    int new_k;


public:
    void Init(std::vector<int> &Initial);
    void Fit(std::vector<int> &Node, int k);
};

void LAPRAS::Init(std::vector<int> &Initial){
    S = Initial;
}

void LAPRAS::Fit(std::vector<int> &Node, int k){
    for(int tilde_k = 0; tilde_k < Node.size()-k; tilde_k++){
        std::vector<int> Branch = Node;
        new_k = tilde_k + k;
        Branch.erase(Branch.begin()+new_k);
        if (Branch.size()>0){
                    Fit(Branch,new_k);
        }


    }

}
