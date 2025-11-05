#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct Node{
    string data;
    time_t time;
    Node* left;
    Node* right;
    int height;
    Node(string d,time_t t){
        this->data=d;
        this->time=t;
        this->left=nullptr;
        this->right=nullptr;
        this->height=1;
    }
};

class post{
private:
    Node* root;
    int size;
    Node* right_rotate(Node* y){
        Node* x=y->left;
        Node* z=x->right;
        x->right=y;
        y->left=z;

        x->height=1+ max(get_height(x->left),get_height(x->right));
        y->height=1+ max(get_height(y->left),get_height(y->right));
        return x;
    }
    Node* left_rotate(Node* y){
        Node* x=y->right;
        Node* z=x->left;
        x->left=y;
        y->right=z;

        x->height=1+ max(get_height(x->left),get_height(x->right));
        y->height=1+ max(get_height(y->left),get_height(y->right));
        return x;
    }
    Node* insert(string p,time_t t,Node* root){
        if (root==nullptr){
            size++;
            return new Node(p,t);
        }
        if (t<root->time){
            root->left=insert(p,t,root->left);
        }
        else{
            root->right=insert(p,t,root->right);
        }

        root->height=1+max(get_height(root->left),get_height(root->right));

        int b=balance_factor(root);

        //rotate
        if (b>1 && t<root->left->time){
            return right_rotate(root);
        }
        else if (b<-1 && t>root->right->time){
            return left_rotate(root);
        }
        else if (b>1 && t>root->left->time){
            root->left=left_rotate(root->left);
            return right_rotate(root);
        }
        else if (b<-1 && t<root->right->time){
            root->right=right_rotate(root->right);
            return left_rotate(root);
        }
        else{
            return root;
        }
    }
    void deleteTree(Node* root) {
        if (root == nullptr) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
public:
    post(){
        root=nullptr;
        size=0;
    }
    ~post(){
        deleteTree(root);
    }    

    post(post&& other) {
        root=other.root;
        size=other.size;
        other.root = nullptr;
        other.size = 0;
    }
    
    post& operator=(post&& other) noexcept {
        if (this != &other) {
            deleteTree(root);
            root = other.root;
            size = other.size;
            other.root = nullptr;
            other.size = 0;
        }
        return *this;
    }

    post(const post&) = delete;
    post& operator=(const post&) = delete;

    Node* get_root(){
        return root;
    }
    int get_height(Node* root){
        if (root==nullptr){
            return 0;
        }
        else{
            return root->height;
        }
    }
    int balance_factor(Node* p){
        return get_height(p->left)-get_height(p->right);
    }
    void add_post(string content, time_t t){
        root = insert(content, t, root);
    }
    void list_n_posts(Node* root, int& n,int& count){
        //find right most node
        if (!root || count==n){
            return;
        }
        if (n==-1){
            n=size;
        }
        list_n_posts(root->right,n,count);
        if (count<n){
            cout << root->data << endl;
            count++;
        }
        else{
            return;
        }
        list_n_posts(root->left,n,count);
    }
};
