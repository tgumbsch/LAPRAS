
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
        new_k = tilde_k + k;
        int save = Node[new_k];
        Node.erase(Node.begin()+new_k);
        if (Node.size()>0){
                    Fit(Node,new_k);
        }
        Node.insert(Node.begin()+new_k,save);


    }

}
