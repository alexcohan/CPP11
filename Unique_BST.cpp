//binary search tree made with unique_ptrs
//"Happiness is a tree of unique_pts" Herb Sutter
#include <iostream>
#include <string>
#include <memory>

template <typename T> 
class Tree { 
    struct Node { 
        T key; 
        std::unique_ptr<Node> left; 
        std::unique_ptr<Node> right; 
        Node():key(), left(), right(){} 
        Node(T x):key(x),left(), right(){} 
        
            const T& min() const{
                return (left?left->min():key);
            }
        
            bool rem_node(const T& t){
               //looks for t in children, assume t is not in parent node
               if(t<key){
                 if(!left)return false;
                 if(left->key==t){
                     if(left->left&&left->right){
                         left->key=left->right->min();
                         return left->rem_node(left->key);
                     } else if(left->left) {
                         left=std::move(left->left);
                     } else if(left->right){
                         left=std::move(left->right);
                     } else left.reset();
                     return true;
                 }
                 return left->rem_node(t);
               } else {
                 if(!right)return false;
                 if(right->key==t){
                     if(right->left&&right->right){
                         right->key=right->right->min();
                         return right->rem_node(right->key);
                     } else if(right->left) {
                         right=std::move(right->left);
                     } else if(right->right){
                         right=std::move(right->right);
                     } else right.reset();
                     return true;
                 }
                 return right->rem_node(t);
               }
               
            }
        }; 
        std::unique_ptr<Node> root; 

// private methods
       void inorder_impl(std::ostream& os, Node* nptr) const {
           if(nptr){
               inorder_impl(os, nptr->left.get());
               os<<nptr->key<<' ';
               inorder_impl(os, nptr->right.get());
           }
       }   
       
       bool find_impl(const T& t, Node* nptr) const{
        if (!nptr) return false;
        if (nptr->key==t) return true;
        if (t< nptr->key) return (nptr->left?find_impl(t,nptr->left.get()):false);
        return (nptr->right?find_impl(t,nptr->right.get()):false);
       }

       public: 
       Tree() = default;
       ~Tree() = default; 
       Tree(Tree&&) = default; 
       Tree& operator =(Tree&&) = default; 
       Tree(const Tree&); 
       Tree& operator =(const Tree&); 
       void push(const T& t){
           if(!root){
               root = std::make_unique<Node> ();
               root->key=t;
           } else {
               Node* nptr = root.get();
               while (true){
                   if( t > nptr->key) {
                       if (nptr->right) nptr = nptr->right.get();
                       else {
                           nptr->right = std::make_unique<Node> (t);
                           return;
                       }
                   } else{
                       if (nptr->left) nptr = nptr->left.get();
                       else {
                           nptr->left = std::make_unique<Node> (t);
                           return;
                       }                       
                   }
               }
           }
           return;
       }
       std::ostream& inorder(std::ostream& os) const {
           inorder_impl(os, root.get());
           os<<'\n';
           return os;
       }

    bool remove(const T& ival){
     if(root){
         if(root->key==ival){
             
              if(root->left&&root->right){
                root->key=root->right->min();
                return root->rem_node(root->key);
              } else if(root->left){
                  root=std::move(root->left);
              } else if(root->right){
                  root=std::move(root->right);
              } else root.reset();
              return true;
         }
         return root->rem_node(ival);
     }
     return false;
    }       
       
       bool find(const T& x) const { return find_impl(x, root.get()); } 
    };

template<class T> 
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree1){
 tree1.inorder(os);
 return os;   
}
