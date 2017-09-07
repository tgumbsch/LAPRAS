
class LAPRAS {
    std::vector<int> S;
    std::vector<int> best_index;
    double best_obj;
    int new_k;
    std::vector<std::vector<double>> Distances;
    bool dist;


public:
    void Init(std::vector<int> &Initial);
    void Fit(std::vector<int> &Node, int k);
};

void LAPRAS::Init(std::vector<std::vector<double>> &Dist){
    S.resize(Dist.size());
    std::iota(S.begin(), S.end(),1);
    Distances = Dist;
    best_index = S;
    best_obj = 0;
    for(int i = 0; i< S.size()-1;i++){
        best_obj += Dist[i][i+1];
    }
}

void LAPRAS::Fit(std::vector<int> &Node, int k, double val){
    for(int tilde_k = 0; tilde_k < Node.size()-k; tilde_k++){
        new_k = tilde_k + k;
        int save = Node[new_k];
        double obj = val; //compute update for new node if there are enough values!!
        Node.erase(Node.begin()+new_k);
        if (Node.size()>0){
                Fit(Node,new_k, obj);
        }
        Node.insert(Node.begin()+new_k,save);


    }

}
