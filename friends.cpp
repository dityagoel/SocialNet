#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue> 

using namespace std;
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
