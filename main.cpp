#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue> 
#include <algorithm> // for conversion of username to lower case(transform)
#include <ctime>
#include <sstream>

using namespace std;

// For Posts
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

// For Friends
struct node{
    string name;
    int ind;
    node* next;

    node(string name,int ind){
        this->name=name;
        this->ind=ind;
        next=nullptr;
    }
};

class sorted_ll{
private:
    node* root;
    node* add_helper(string name,int ind){
        if (root==nullptr){
            return new node(name,ind);
        }
        if (root->name>name){
            node* n=new node(name,ind);
            n->next=root;
            return n;
        }
        node* curr=root;
        while(curr!=nullptr){
            if (!curr->next){
                curr->next=new node(name,ind);
                return root;
            }
            else if (curr->name == name){
                return root;
            }
            else if (curr->name<name && curr->next->name>name){
                node* n=new node(name,ind);
                n->next=curr->next;
                curr->next=n;
                return root;
            }
            else{
                curr=curr->next;
            }
        }
        return root;
    }

    node* add_rev_helper(string name,int ind){
        if (root==nullptr){
            return new node(name,ind);
        }
        if (root->ind < ind || (root->ind == ind && root->name > name)){
            node* n=new node(name,ind);
            n->next=root;
            return n;
        }
        node* curr=root;
        while(curr!=nullptr){
            if (!curr->next){
                curr->next=new node(name,ind);
                return root;
            }
            
            else if (curr->name == name){
                return root;
            }
            else if (curr->next->ind==ind){
                if (curr->next->name>name){
                    node* x=curr->next;
                    node* ne=new node(name,ind);
                    curr->next=ne;
                    ne->next=x;
                    return root;
                }
                else{
                    curr=curr->next;
                    continue;
                }
            }
            else if (curr->ind>=ind && curr->next->ind<ind){
                node* n=new node(name,ind);
                n->next=curr->next;
                curr->next=n;
                return root;
            }
            else{
                curr=curr->next;
            }
        }
        return root;
    }

    static void delete_list(node* root){
        node* current = root;
        while (current != nullptr) {
            node* next = current->next;
            delete current;
            current = next;
        }
    }
public:
    sorted_ll(){
        root=nullptr;
    }
    ~sorted_ll(){
        delete_list(root);
    }

    // ADD THESE: Move constructor and move assignment
    sorted_ll(sorted_ll&& other) {
        root=other.root;
        other.root = nullptr;
    }
    
    // sorted_ll& operator=(sorted_ll&& other) {
    //     if (this != &other) {
    //         delete_list(root);
    //         root = other.root;
    //         other.root = nullptr;
    //     }
    //     return *this;
    // }
    
    // DELETE THESE: Prevent copying
    sorted_ll(const sorted_ll&) = delete;
    sorted_ll& operator=(const sorted_ll&) = delete;

    node* get_root(){
        return root;
    }

    void add(string name,int ind){
        root=add_helper(name,ind);
    }

    void add_rev(string name,int ind){
        root=add_rev_helper(name,ind);
    }

    string list(){
        node* curr=root;
        string s="";
        while (curr!=nullptr){
            s+=curr->name;
            s+=" ";
            curr=curr->next;
        }
        return s;
    }
};

class friends{
private:
    vector<sorted_ll> f;
    map<string,int> username_id;
    map<int,string> id_username;

public:
    friends(){}
    ~friends(){}

    void add(string username){
        int ind=f.size();
        username_id[username]=ind;
        id_username[ind]=username;
        f.push_back(sorted_ll());
    }

    void friendship(string username1,string username2){
        if(!username_id.count(username1) || !username_id.count(username2)){
            cout << "Error: User not found!\n";
            return;
        }
        int id1=username_id[username1];
        int id2=username_id[username2];

        node* curr = f[id1].get_root();
        while (curr != nullptr) {
            if (curr->ind == id2) {
                cout << "Friendship already exists!\n";
                return;
            }
            curr = curr->next;
        }
        f[id1].add(username2,id2);
        f[id2].add(username1,id1);
        cout << "Friendship added!" << "\n";
    }

    void list_friends(string username){
        if(!username_id.count(username)){
            cout << "Error: User not found!\n";
            return;
        }
        int id=username_id[username];
        cout << f[id].list();
    }

    int no_of_mutuals(int id1,int id2){
        node* curr1=f[id1].get_root();
        node* curr2=f[id2].get_root();
        int count=0;
        while (curr1 && curr2){
            if (curr1->name==curr2->name){
                count++;
                curr1=curr1->next;
                curr2=curr2->next;
            }
            else if (curr1->name>curr2->name){
                curr2=curr2->next;
            }
            else{
                curr1=curr1->next;
            }
        }
        return count;
    }

    void suggest_friends(string username1,int n){
        if(n == 0) return;
        vector<bool> is_friend(f.size(),false);
        sorted_ll mutual_friend_list; //ind of this will store no. of mutual friends
        int id1=username_id[username1];
        is_friend[id1]=true;
        node* curr1=f[id1].get_root();
        while (curr1!=nullptr){
            is_friend[curr1->ind]=true;
            curr1=curr1->next;
        }
        for (int i=0;i<f.size();i++){
            if (!is_friend[i]){
                int m=no_of_mutuals(id1,i);
                if (m>0){
                    mutual_friend_list.add_rev(id_username[i],m);
                }
            }
        }
        node* final=mutual_friend_list.get_root();
        if (!final){
            return;
        }
        else{
            for (int i=0;i<n;i++){
                if (!final){
                    break;
                }
                cout << final->name << " ";
                final=final->next;
            }
            cout << "\n";
        }
    }

    int degrees_of_separation(string username1, string username2){
        queue<vector<int>> q;
        if(!username_id.count(username1) || !username_id.count(username2)){
            return -1;
        }
        int id1=username_id[username1];
        int id2=username_id[username2];
        
        if (id1==id2){
            return 0;
        }
        q.push({id1,0});
        vector<int> visited(f.size(),0);
        
        while(!q.empty()){
            vector<int> curr=q.front(); //vector of id and distance
            q.pop();
            if(curr[0]==id2){
                return curr[1];
            }
            visited[curr[0]]=1;
            node* n=f[curr[0]].get_root();
            while(n!=nullptr){
                if (visited[n->ind]==0){
                    q.push({n->ind,curr[1]+1});
                    visited[n->ind]=1;
                }
                n=n->next;
            }
        }
        return -1;
    }
};

// Main
void execute_command(map<string,post>& p, friends& friend_list, string line){
    stringstream input(line);
    vector<string> tokens;
    string tok;
    while (input >> tok) tokens.push_back(tok);
    if (tokens.empty()) return;
    string command=tokens[0];  
    if (command=="ADD_USER"){
        if (tokens.size()==1){
            cout << "Error: No username found\n";
            return;
        }
        string name=tokens[1];
        if (name.empty()) {
            cout << "Error: No username found\n";
            return;
        }
        transform(name.begin(),name.end(),name.begin(),::tolower);
        if (p.count(name)){
            cout << "Username already taken!" << "\n";
        }
        else{
            p[name] = post();
            friend_list.add(name);
            cout << "User Successfully Added!" << "\n" ;
        }
    }
    else if (command=="ADD_FRIEND"){
        if (tokens.size()==1 || tokens[1].empty()) {
            cout << "Error: Username 1 not found\n";
            return;
        }
        string name1=tokens[1];
        transform(name1.begin(),name1.end(),name1.begin(),::tolower);
        
        if (tokens.size()==2 || tokens[2].empty()) {
            cout << "Error: Username 2 not found\n";
            return;
        }
        string name2=tokens[2];
        if (tokens.size()>3){
            cout << "Error: Too many usernames\n";
            return;
        }
        transform(name2.begin(),name2.end(),name2.begin(),::tolower);
        if (name1==name2){
            cout << "Error: Both usernames are the same." << "\n";
        }
        else if (p.count(name1) && p.count(name2)){
            friend_list.friendship(name1,name2);
        }
        else{
            cout << "Error: User not found!" << "\n";
        }
    }
    else if (command=="LIST_FRIENDS"){
        if (tokens.size()==1 || tokens[1].empty()) {
            cout << "Error: No username found\n";
            return;
        }
        string name=tokens[1];
        if (tokens.size()>2){
            cout << "Error: Too many usernames\n";
            return;
        }
        transform(name.begin(),name.end(),name.begin(),::tolower);
        if (p.count(name)){
            friend_list.list_friends(name);
            cout << "\n";
        }
        else{
            cout << "Error: User not found!" << "\n";
        }
    }
    else if (command=="SUGGEST_FRIENDS"){
        if (tokens.size()==1 || tokens[1].empty()) {
            cout << "Error: No username found\n";
            return;
        }
        string name=tokens[1];
        transform(name.begin(),name.end(),name.begin(),::tolower);
        if (tokens.size()==2 || tokens[2].empty() || !isdigit(tokens[2][0])){
            cout << "Invalid or missing number!" << "\n";
            return;
        }
        int n=stoi(tokens[2]);
        if (tokens.size()>3){
            cout << "Error: Too many usernames\n";
            return;
        }
        if (p.count(name)){
            friend_list.suggest_friends(name,n);
        }
        else{
            cout << "Error: User not found!" << "\n";
        }
    }
    else if (command=="DEGREES_OF_SEPARATION"){
        if (tokens.size()==1 || tokens[1].empty()) {
            cout << "Error: Username 1 not found\n";
            return;
        }
        string name1=tokens[1];
        transform(name1.begin(),name1.end(),name1.begin(),::tolower);
        
        if (!p.count(name1)){
            cout << "Error: 1st Username not found\n";
            return;
        }

        if (tokens.size()==2 || tokens[2].empty()) {
            cout << "Error: Username 2 not found\n";
            return;
        }
        
        string name2=tokens[2];
        if (tokens.size()>3){
            cout << "Error: Too many usernames\n";
            return;
        }
        transform(name2.begin(),name2.end(),name2.begin(),::tolower);
        
        if (!p.count(name2)){
            cout << "Error: 2nd Username not found\n";
            return;
        }
        int dist=friend_list.degrees_of_separation(name1,name2);
        cout << "Degrees of Separation: " << dist << endl;
    }
    else if (command=="ADD_POST"){
        if (tokens.size()==1 || tokens[1].empty()) {
            cout << "Error: No username found\n";
            return;
        }
        string name=tokens[1];
        transform(name.begin(),name.end(),name.begin(),::tolower);

        if (tokens.size()==2 || tokens[2].empty()) {
            cout << "Error: No content found for post!\n";
            return;
        }
        if (!p.count(name)){
            cout << "Error: User not found!" << "\n";
            return;
        }
        string content = "";
        for(size_t i = 2; i < tokens.size(); i++) {
            content += tokens[i];
            if(i < tokens.size() - 1) {
            content += " ";
            }
        }
        if (content[0]=='"' && content[content.size()-1]=='"'){
            content.erase(0,1);
            content.pop_back();
        }

        if (content==""){
            cout << "Error: No content found for post!\n";
            return;
        }
        p[name].add_post(content, time(0));
        cout << "Post added!" << "\n";
    }
    else if (command=="OUTPUT_POSTS"){
        if (tokens.size()==1 || tokens[1].empty()) {
            cout << "Error: No username found\n";
            return;
        }
        string name=tokens[1];
        transform(name.begin(),name.end(),name.begin(),::tolower);
        if (p.count(name)){
            if (tokens.size()==2 || tokens[2].empty()){
                cout << "Invalid or missing number!" << "\n";
                return;
            }
            if (tokens[2]!="-1" && !isdigit(tokens[2][0])){
                cout << "Invalid or missing number!" << "\n";
                return;
            }
            int n=stoi(tokens[2]);
            int count = 0;
            p[name].list_n_posts(p[name].get_root(), n, count);
        }
        else{
            cout << "Error: User not found!" << "\n";
        }
        
    }
    else{
        cout << "No such command found." << "\n";
    }
}

int main(){
    friends friend_list;
    map<string,post> posts;
    string line;
    cout << "Welcome to SocialNet! Enter you commands, or type 'EXIT' to quit." << endl;
    while (getline(cin, line)) {
        if (line=="EXIT"){
            break;
        }
        execute_command(posts,friend_list,line);
    }
}
