//Min Heap using std::vector
#include <vector>

template<class T>
class minHeap {
 std::vector<T> dat;
 
 public:
 
 minHeap(const T& t){
  add(t);   
 }

 minHeap()=default;
 
 template<class... Ts>
 minHeap(const Ts& ...ts){
  add(ts...);   
 }
 
 //template<class T, class... Ts>
 template<class... Ts>
 void add(const T& t, const Ts& ...ts){
    add(t);
    add(ts...);
 }
 
 
 std::size_t getLeftChildIndex(const std::size_t& ind) const {return 2*ind+1;}
 std::size_t getRightChildIndex(const std::size_t& ind) const {return 2*ind+2;}
 std::size_t getParentIndex(const std::size_t& ind) const {return (ind-1)/2;}
 
 bool hasLeftChild(const std::size_t& ind) const { return getLeftChildIndex(ind)<dat.size();}
 bool hasRightChild(const std::size_t& ind) const { return getRightChildIndex(ind)<dat.size();}
 bool hasParent(const std::size_t& ind) const { return getParentIndex(ind)>=0;}
 
 T leftChild(const std::size_t& ind) const {return dat[getLeftChildIndex(ind)];}
 T rightChild(const std::size_t& ind) const {return dat[getRightChildIndex(ind)];}
 T parent(const std::size_t& ind) const {return dat[getParentIndex(ind)];}
 
 void swap (const std::size_t& ind1,const std::size_t& ind2){
  std::swap(dat[ind1],dat[ind2]);
 }
 
 T& peek() const{return dat[0];} // take a peek at first element
 
 bool empty() const {return dat.empty();}
 
 T poll(){
     //removes min element
  if(!empty()){
   T t(dat.front());
   dat[0]=dat.back();
   dat.pop_back();
   heapifyDown();
   return t;
  }
 }
 
  bool del(const T& t){
     //removes element t
  if(!empty()){
    //for (auto& it:dat){
    for(std::size_t ind=0;ind<dat.size();++ind){ 
        if(dat[ind]==t){
         dat[ind] = dat.back();
         dat.pop_back();
         heapifyDown(ind);
         //heapifyDown();
         return true;
        }
    }
  }
  return false;
 }
 
 void add(const T& t){
  dat.push_back(t);
  heapifyUp();
 }

 void print() const{
  for(auto& it:dat){
  std::cout<<it<<'\n';   
  }
 }
 
 bool find(const T& t) const{
  for(auto& it:dat){
    if(it==t)return true;   
    }
  return false;
 }
 
 private:
 
 void heapifyUp(){
 if(!empty()){
  std::size_t ind = dat.size()-1;   
  while (hasParent(ind)&& parent(ind)>dat[ind]){
   swap(getParentIndex(ind),ind);
   ind = getParentIndex(ind);
  }
 }
 }
 
 void heapifyDown(std::size_t ind = 0){
     if(!empty()){
        std::size_t sind;   
        while (hasLeftChild(ind)){
          sind =  getLeftChildIndex(ind);
          if(hasRightChild(ind)&&rightChild(ind)<leftChild(ind)){
            sind = getRightChildIndex(ind);   
          }
          if(dat[ind]<dat[sind]){
            break;   
          } else{
            swap(ind,sind);   
          }
          ind=sind;
        }
      } 
 }
 
};
