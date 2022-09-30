#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>

std::vector<int> sweetdeg_status;

class node {
public:

    int sweetdeg;
    int left_index;
    int right_index;
    int bigger_number;
    int stacking_number;

public:

    node() = default;
    node(int sweetdeg_) {
        sweetdeg = sweetdeg_;
    }

};

int put(std::vector<node>& candy, int new_sweetdeg, int root, int count, int& total_num) {
    
    if (candy[root].sweetdeg == -1) {
        
        // the leaf node
        candy[root].sweetdeg = new_sweetdeg;

        // refresh the infomation of child node
        candy[root].left_index = 2 * total_num + 1;
        candy[root].right_index = 2 * total_num + 2;
        candy[root].bigger_number = 1;
        candy[root].stacking_number = 0;
        total_num++;
        candy.push_back(node(-1));
        candy.push_back(node(-1));
        return count;

    }
    
    else if (new_sweetdeg < candy[root].sweetdeg) {

        count += candy[root].bigger_number;
        return put(candy, new_sweetdeg, candy[root].left_index, count, total_num);
    
    }

    else if (new_sweetdeg > candy[root].sweetdeg) {

        candy[root].bigger_number++;
        // for new_sweetdeg the same as the previous sweetdeg
        if (std::find(sweetdeg_status.begin(), sweetdeg_status.end(), new_sweetdeg) != sweetdeg_status.end()) {
            candy[root].stacking_number++;
        }
        return put(candy, new_sweetdeg, candy[root].right_index, count, total_num);
    
    }

    else {
        
        // the equal node
        // refresh the infomation of child node
        candy[root].bigger_number++;
        total_num++;
        candy[root].stacking_number++;
        if (std::find(sweetdeg_status.begin(), sweetdeg_status.end(), new_sweetdeg) == sweetdeg_status.end()) {
            sweetdeg_status.push_back(new_sweetdeg);
        }
        return count;
    
    }

}

int search(std::vector<node>& candy, int k, int root) {

    if (candy[root].bigger_number >= k) {
        if (candy[root].bigger_number - candy[root].stacking_number + 1 == k) return candy[root].sweetdeg;
        else return search(candy, k, candy[root].right_index);
    }
    else {
        return search(candy, k, candy[root].left_index);
    }

}




int main() {

    // total number of operation
    int total_op;
    
    // the operation in once
    int op[2];

    // 0-4: 
    // the sweet deg., the left index, 
    // the right index, the node# in bigger-side child tree
    // the stacking number
    std::vector<node> candy; 
    int total_num = 0;
    scanf("%d", &total_op);
    candy.push_back(node(-1));
    // memset(candy, -1, sizeof(candy));    
    for (int i = 0; i < total_op; i++) {
        scanf("%d %d", &op[0], &op[1]);
        /*Growth*/
        if (op[0] == 1) {
            printf("%d\n", put(candy, op[1], 0, 0, total_num));
        }
        /*The k-sweetest*/
        if (op[0] == 2) printf("%d\n", search(candy, op[1], 0));
        
    }
}