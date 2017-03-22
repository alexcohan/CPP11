//binary search tree made entirely with unique_ptrs
//"Happiness is a tree of unique_pts" Herb Sutter
#include <iostream>
#include <string>
#include <memory>
#include <ostream>
#include <cstdarg>

template<class T>
class AC_tree {
    public:
    ~AC_tree(){
     deleteTree();   
    }
    AC_tree ()=default;
    AC_tree (T t) {
        root=std::unique_ptr<Node> (new Node(t));
    }

    template<class... Ts>
    AC_tree (T t, Ts... ts):AC_tree(t) {
     //multi-argument constructor
        Add_Ts(ts...); 
    }

    AC_tree (const AC_tree& tree1){
    // copy constructor
    if(!(this==&tree1))*this = tree1;
    }
    AC_tree (AC_tree&& tree1){
    //move constructor
    if(!(this==&tree1))*this = std::move(tree1); 
    }
    
    AC_tree& operator=(const AC_tree& tree1){
     // copy assignment operator
     if(!(this==&tree1)){
     deleteTree();
     root = std::unique_ptr<Node> (new Node());
     *root = *(tree1.root); // use node copy assignment
     }
     return *this;
    }
    
    AC_tree& operator=(AC_tree&& tree1){
    // move assignment operator
    if(!(this==&tree1)){
     deleteTree();
     root = std::move(tree1.root); // use node move assignment
     tree1.deleteTree();
    }
     return *this;
    }
    
    void addval(T t){
     if(root)root->add_val(t);
     else root=std::unique_ptr<Node> (new Node(t));
    }
    
    const T& min() const{
        return root->min();
    }

    const T& max() const{
        return root->max();
    }
    
    const bool& empty() const{
     return(!root);   
    }
    
    bool remove(T ival){
     if(root){
         if(root->getval()==ival){
             
              if(root->left&&root->right){
                *(root->val)=root->right->min();
                return root->rem_node(root->getval());
              } else if(root->left){
                  root=std::move(root->left);
              } else if(root->right){
                  root=std::move(root->right);
              } else root->val.reset();
              return true;
         }
         return root->rem_node(ival);
     }
     return false;
    }
    
    void printTop() const{
     root->printTop();   
    }
    
    void printOrder() const{
     root->printOrder();   
    }
    
    bool find(const T& t) const{
        return root->find(t);
    }
    
    template<class T2>
    friend std::ostream& operator<<(std::ostream&, const AC_tree<T2>& );
    
    private:
        void deleteTree(){
            if(root)root->deleteNode();
            root.reset();
        }
    
        template<class... Ts>
        void Add_Ts (T t , Ts... ts) {
            addval(t);
            Add_Ts(ts...);  
        }
        void Add_Ts (T t){
            addval(t);
        }
        
        class Node{
            public:
            ~Node(){
                deleteNode();
            }
            Node ()=default;
            Node (T t){
               add_val(t);
            }

            Node (const Node& node){
            // copy constructor
            if(!(this==&node))*this = node;
            }
            Node (Node&& node){
            //move constructor
            if(!(this==&node))*this = std::move(node); 
            }
    
            Node& operator=(const Node& node){
             // copy assignment operator
             if(this==&node)return *this;
             deleteNode();
             if(node.val)val = std::unique_ptr<T>(new T(node.getval()));
             if(node.left){
                left = std::unique_ptr<Node>(new Node);
                *left = *(node.left);//recursively set left node
             }
             if(node.right){
                right = std::unique_ptr<Node>(new Node);
                *right = *(node.right);//recursively set right node
             }     
             return *this;
            }
    
            Node& operator=(Node&& node){
            // move assignment operator
             if(this==&node)return *this;
             deleteNode();
             if(node.val)val = std::move(node.val);
             if(node.left){
                left = std::move(node.left);
             }
             if(node.right){
                right = std::move(node.right);
             }     
             node.deleteNode();//redudant clean up
             return *this;    
            }         
                    
            const T& getval() const{
                return *val;
            } 
 
            void add_val(T t){
                if(!val) val = std::unique_ptr<T> ( new T(t));
                else if(t < getval()) {
                    if(left)left->add_val(t);
                    else left = std::unique_ptr<Node> (new Node(t));
                }
                else {
                    if(right)right->add_val(t);
                    else right = std::unique_ptr<Node> (new Node(t));
                }
            }
               
            void printTop() const{
                int mx = getMaxDepth();
                for (int i=1;i<=mx;++i){
                  printRow(i);
                  std::cout<<std::endl;
                }
            }
    
            void printOrder() const{
                if(left)left->printOrder();
                if(val)std::cout<<getval()<<" ";
                if(right)right->printOrder();        
            }
            
            bool find(const T& ival) const {
                if(!val)return false;
                if(getval() == ival)return true;
                if(getval() > ival){
                    if(left)return left->find(ival);
                } else
                    if(right)return right->find(ival);
                return false;
            }

            void deleteNode() {
                if(left){
                    left->deleteNode();
                    left.reset();
                }
                if(right){
                    right->deleteNode();
                    right.reset();
                }
                if(val)val.reset();
                } 
            
            void  printer_help (std::ostream& os) const{
              if(left)left->printer_help(os);
              if(val)os<<getval()<<' ';
              if(right)right->printer_help(os);
            }
            
            const T& min() const{
                return (left?left->min():getval());
            }

            const T& max() const{
                return (right?right->max():getval());
            }
            
            bool rem_node(const T& t){
               //looks for t in children
               if(!val)return false;
               if(t<getval()){
                 if(!left)return false;
                 if(left->getval()==t){
                     if(left->left&&left->right){
                         *(left->val)=left->right->min();
                         return left->rem_node(left->getval());
                     }
                     left->val.reset();
                     if(left->left) {
                         left=std::move(left->left);
                     }
                     if(left->right){
                         left=std::move(left->right);
                     }
                     return true;
                 }
                 return left->rem_node(t);
               } else {
                 if(!right)return false;
                 if(right->getval()==t){
                     if(right->left&&right->right){
                         *(right->val)=right->right->min();
                         return right->rem_node(right->getval());
                     }
                     right->val.reset();
                     if(right->left) {
                         right=std::move(right->left);
                     }
                     if(right->right){
                         right=std::move(right->right);
                     }
                     return true;
                 }
                 return right->rem_node(t);
               }
               
            }
            
            int getMaxDepth(int i=1) const {
                if(!left&&!right)return i;
                int n1(0),n2(0);
                if(left)n1=left->getMaxDepth(i+1);
                if(right)n2=right->getMaxDepth(i+1);
                return (n1>n2?n1:n2);
            }
            
            void printRow(int i) const {
             if(i<=1)
             {
                 if(val)std::cout<<getval()<<' ';
             }
             else {
              if(left)left->printRow(i-1);
              if(right)right->printRow(i-1);
             }
            }
            
            std::unique_ptr<T> val;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;
            
        };
        
        std::unique_ptr<Node> root;
        
};

template<class T> 
std::ostream& operator<<(std::ostream& os, const AC_tree<T>& tree1){
 if(tree1.root)tree1.root->printer_help(os);
 return os;   
}
