
class LAPRAS {
    std::vector<int> best_index;
    double best_obj;
    int new_k;
    bool dist;


public:
    double Init(std::vector<std::vector<double>> &Dist);
    void Fit(std::vector<int> &Node, std::vector<std::vector<double>> &Dist, int k, double &val);
    std::vector<int> return_index();
    double return_objective();
};


std::vector<int> LAPRAS::return_index(){
    return best_index;
}

double LAPRAS::return_objective(){
    return best_obj;
}

double LAPRAS::Init(std::vector<std::vector<double>> &Dist){
    best_obj = 0;
    for(int i = 0; i< Dist.size()-1;i++){
        best_obj += Dist[i][i+1];
    }
    return best_obj;
}

void LAPRAS::Fit(std::vector<int> &Node, std::vector<std::vector<double>> &Dist, int k, double &val){
    for(int tilde_k = 0; tilde_k < Node.size()-k; tilde_k++){

        // K index for the location in Node
        new_k = tilde_k + k;
        // The node which is to be removed at this point
        int save = Node[new_k];


        //Recursive update for objective
        double obj = 0;
        if(Node.size()>new_k+1 && new_k>0){
            obj = val-Dist[Node[new_k-1]][save]-Dist[save][Node[new_k+1]]+Dist[Node[new_k-1]][Node[new_k+1]];
        }
        else if(new_k ==0 && Node.size() > 1){
            obj = val - Dist[save][Node[1]];
        }
        else if(new_k == Node.size() && Node.size() > 1){
            obj = val - Dist[Node[new_k-1]][save];
        }

        //Non-recursive update
        /*
        double obj = 0;
        for(int i = 0; i < Node.size()-1; i++){
            obj += Dist[Node[i],Nodew[i+1]];
        }
        */

        //Save node if objective is better
        if(obj > best_obj){
            best_obj = obj;
            best_index = Node;
        }


        Node.erase(Node.begin()+new_k);
        if (Node.size()>0){
            Fit(Node,Dist,new_k, obj);
        }
        Node.insert(Node.begin()+new_k,save);

    }

}
