//TRIES Tree of chars using map of shared_pointers
#include <iostream>
#include <string>
#include <map>
#include <memory>

struct Node {
  std::map<char, std::shared_ptr<Node>> children;
};

class Trie {
  public:

    Trie()=default;
    Trie(const std::string words[], const int &length);
    void insert(const std::string &word);
    bool search(const std::string &word) const;

    void print_tree(const std::map<char, std::shared_ptr<Node>> &tree) const;
    void print() const;

  protected:
    Node head;
};



Trie::Trie(const std::string words[], const int &length) {
  for (int i=0; i<length; ++i) {
    insert(words[i]);
  }
}

void Trie::insert(const std::string &word) {
  auto* current_tree = &(head.children);

  for(auto& ch:word){
    auto it = current_tree->find(ch);

    if (it != current_tree->end()) {
      current_tree = &(it->second->children);

    } else {
// add new node of char ch
      auto new_node = std::make_shared<Node>();
      (*current_tree)[ch] = new_node;
      current_tree = &new_node->children;
      
    }
  }
}

bool Trie::search(const std::string& word) const {
  auto* current_tree = &(head.children);

  for(auto& ch:word){
    auto it = current_tree->find(ch);
    if (it == current_tree->end()) {
      return false;
    }
    current_tree = &(it->second->children);
  }
  return true;
}

void Trie::print_tree(const std::map<char, std::shared_ptr<Node>>& tree) const {
  if (tree.empty()) {
    return;
  }

  for (auto it=tree.begin(); it!=tree.end(); ++it) {
    std::cout << it->first << '\n';
    print_tree(it->second->children);
  }
}

void Trie::print() const {
  print_tree(head.children);
}
