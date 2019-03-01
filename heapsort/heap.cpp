#include<string>
#include<iostream>
#include<istream>
#include<ostream>
#include<sstream>
#include<cmath>
using namespace std;

class Maxheap{
private:
  int capacity;
  int last;
  string *heap;
public:
  Maxheap(int cap){
    capacity = cap;
    last = 0;
    heap = new string[capacity+1];
  }

  // ~Maxheap();

  bool isempty(){
    return last == 0;
  }

  bool isfull(){
    return last == capacity-1;
  }

  string top(){
    return heap[1];
  }

  void push(string in){
    // cout << "inserting "   <<in << endl;
    if (this->isfull() == 1){
      //extend and copy into
    }
    last += 1;
    // cout<< "size: " <<last << endl;
    heap[last] = in;
    int cur_ind = last;
    // cout << (cur_ind >> 1) << endl;
    while ((cur_ind >> 1) > 0 && atof(heap[cur_ind >> 1].c_str()) < atof(heap[cur_ind].c_str())){
      // cout << "*****" << endl;
      string tmp = heap[cur_ind >> 1];
      heap[cur_ind >> 1] = heap[cur_ind];
      heap[cur_ind] = tmp;
      cur_ind = cur_ind >> 1;
    }
    // cout << "current index: "<< cur_ind << endl;
  }

  string pop_root(){//maxheap
    int cur_ind = 1;
    int next_ind = 1;
    string out = this->top();
    heap[1] = heap[last];
    last -= 1;
    while (this->isempty() == 0 && (cur_ind<<1) <= last){
      if ((cur_ind<<1)+1 > last){
        next_ind = cur_ind << 1;
      }else{
        if (atof(heap[cur_ind << 1].c_str()) < atof(heap[(cur_ind << 1)+1].c_str())){
          next_ind = (cur_ind << 1)+1;
        }else{
          next_ind = cur_ind << 1;
        }
      }//////////////
      if (atof(heap[cur_ind].c_str()) < atof(heap[next_ind].c_str())){
        string tmp = heap[next_ind];
        heap[next_ind] = heap[cur_ind];
        heap[cur_ind] = tmp;
        cur_ind = next_ind;
      }else{
        break;
      }
    }
    return out;
  }

  int size(){
    return last;
  }

  void printheap(){
    int level = 1;
    int count = 1;
    while (count <= last){
      int i = 1;
      for (; i<pow(2,level-1); i++){
        if (count<=last){
          printf("%d ", atoi(heap[count].c_str()));
        }else if(count>last){
          printf("S ");
        }
        count += 1;
      }
      //print the last element
      if (count<=last){
        printf("%d\n", atoi(heap[count].c_str()));
      }else if(count>last){
        printf("S\n");
      }
      count += 1;
      //update the level
      level += 1;
    }
  }

};

class Minheap{
private:
  int capacity;
  int last;
  string *heap;
public:
  Minheap(int cap){
    capacity = cap;
    last = 0;
    heap = new string[capacity+1];
  }

  // ~Minheap();

  bool isempty(){
    return last == 0;
  }

  bool isfull(){
    return last == capacity-1;
  }

  string top(){
    return heap[1];
  }

  void push(string in){
    // cout << "inserting " <<in << endl;
    if (this->isfull() == 1){
      //extend and copy into
    }
    last += 1;
    // cout<< "size: " <<last << endl;
    heap[last] = in;
    int cur_ind = last;
    // cout << (cur_ind >> 1) << endl;
    while ((cur_ind >> 1) > 0 && atof(heap[cur_ind >> 1].c_str()) > atof(heap[cur_ind].c_str())){
      // cout << "*****" << endl;
      string tmp = heap[cur_ind >> 1];
      heap[cur_ind >> 1] = heap[cur_ind];
      heap[cur_ind] = tmp;
      cur_ind = cur_ind >> 1;
    }
    // cout << "current index: "<< cur_ind << endl;
  }

  string pop_root(){//minheap
    int cur_ind = 1;
    int next_ind = 1;
    string out = this->top();
    heap[1] = heap[last];
    last -= 1;
    while (this->isempty() == 0 && (cur_ind<<1) <= last){
      if ((cur_ind<<1)+1 > last){
        next_ind = cur_ind << 1;
      }else{
        if (atof(heap[cur_ind << 1].c_str()) > atof(heap[(cur_ind << 1)+1].c_str())){
          next_ind = (cur_ind << 1)+1;
        }else{
          next_ind = cur_ind << 1;
        }
      }//////////////
      if (atof(heap[cur_ind].c_str()) > atof(heap[next_ind].c_str())){
        string tmp = heap[next_ind];
        heap[next_ind] = heap[cur_ind];
        heap[cur_ind] = tmp;
        cur_ind = next_ind;
      }else{
        break;
      }
    }
    return out;
  }

  int size(){
    return last;
  }

  void printheap(){
    int level = 1;
    int count = 1;
    while (count <= last){
      int i = 1;
      for (; i<pow(2,level-1); i++){
        if (count<=last){
          printf("%d ", atoi(heap[count].c_str()));
        }else if(count>last){
          printf("S ");
        }
        count += 1;
      }
      //print the last element
      if (count<=last){
        printf("%d\n", atoi(heap[count].c_str()));
      }else if(count>last){
        printf("S\n");
      }
      count += 1;
      //update the level
      level += 1;
    }
  }

};

int main() {
  //------------main body---

  Maxheap maxheap(100000);
  Minheap minheap(100000);
  string a,b;
  cin >> a >> b ;
  // cout << "reading:" << a << b << endl;
  if (atoi(a.c_str()) < atoi(b.c_str())){
    maxheap.push(a);
    minheap.push(b);
    if ((atoi(a.c_str())+atoi(b.c_str()))%2 == 1){
      double median = atof(a.c_str())+atof(b.c_str());
      printf("%.1f\n",median/2);
    }else{
      int median = (atoi(a.c_str())+atoi(b.c_str()));
      printf("%d\n", median/2);
    }
    minheap.printheap();
    maxheap.printheap();
  }
  if (atoi(a.c_str()) > atoi(b.c_str())){
    maxheap.push(b);
    minheap.push(a);
    if ((atoi(a.c_str())+atoi(b.c_str()))%2 == 1){
      double median = (atof(a.c_str())+atof(b.c_str()));
      printf("%.1f\n",median/2);
    }else{
      int median = (atoi(a.c_str())+atoi(b.c_str()));
      printf("%d\n", median/2);
    }
    minheap.printheap();
    maxheap.printheap();
  }

  string input;
  while (cin >> input){
    //inputing
    // cout << "reading: "<< input<< endl;
    if (atoi(input.c_str()) < atoi(maxheap.top().c_str())){
      maxheap.push(input);
    }
    else{
      minheap.push(input);
    }
    //balancing
    if (minheap.size() - maxheap.size() > 1){
      string root = minheap.pop_root();
      maxheap.push(root);
    }else if (maxheap.size() - minheap.size() > 1){
      string root = maxheap.pop_root();
      minheap.push(root);
    }
    //outputing
    if (minheap.size() == maxheap.size()){
      if ((atoi(minheap.top().c_str())+atoi(maxheap.top().c_str()))%2 == 1){
        double median = atof(minheap.top().c_str())+atof(maxheap.top().c_str());
        printf("%.1f\n",median/2);
      }else{
        int median = atoi(minheap.top().c_str())+atoi(maxheap.top().c_str());
        printf("%d\n",median/2 );
      }
    }else if (minheap.size() > maxheap.size()){
      int median = atoi(minheap.top().c_str());
      printf("%d\n",median);
    }else if (maxheap.size() > minheap.size()){
      int median = atoi(maxheap.top().c_str());
      printf("%d\n",median);
    }
    minheap.printheap();
    maxheap.printheap();
  }
  return 0;
}
