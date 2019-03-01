#include<string>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstdio>
using namespace std;

int if_num(string s1){
  string s = s1;
  for (int i = 0; i < s.length(); i++){
    if (s[i]!='0' && s[i]!='1' && s[i]!='2' && s[i]!='3' && s[i]!='4' &&
        s[i]!='5' && s[i]!='6' && s[i]!='7' && s[i]!='8' && s[i]!='9'){
          return 0;
        }
  }
  if (atol(s.c_str()) > 4294967295 || atol(s.c_str()) < 0){
    return 0;
  }
  return 1;
}

class node{
public:
  string key;
  int value;
  node *next;
  node(string k, int v, node* n){
    key = k;
    value = v;
    next = n;
  }
};

class linklist{
public:
  node* head;

  linklist(){
    head = NULL;
  }

  node*  key_existed(string key){
    node* current = head;
    while (current){
      if (current->key == key){
        return current;
      }
      current = current->next;
    }
    return NULL;
  }

  void push(string key, int* size){
    node* check = key_existed(key);
    if (!check){//not exist
      head = new node(key,1,head);
      *size += 1;
    }else{//exist
      check->value += 1;
    }
  }

  void remove(string key){
    node* current = head;
    node* prev;
    while (current){
      if (head->key == key){
        head = head->next;
        delete current;
        break;
      }else if (current->key == key){
        node *tmp = current;
        prev->next = current->next;
        delete tmp;
        break;
      }
      prev = current;
      current = current->next;
    }
  }

  void print_list(){
    printf("{");
    node* current = head;
    int i = 0;
    while (current){
      if (i > 0){
        printf(",");
      }
      if_num(current->key) == 1 ? printf("\"%s\":", (current->key).c_str()):printf("\"%s\":", (current->key).c_str());
      printf("%d", current->value);
      current = current->next;
      i += 1;
    }
    printf("}");
  }
};

class Hash{
public:
  linklist *hash_tbl;
  int length;
  int load_fac;
  int size;

  Hash(int load, int len){
    hash_tbl = new linklist[len];
    load_fac = load;
    length = len;
    size = 0;
    for (int i = 0; i<length; i++){
      hash_tbl[i].head = NULL;
    }
  }

  int hash_num(string s){
    return atol(s.c_str())%length;
  }

  int hash_str(string s){
    int sum = 0;
    for (int i = 0; i < s.length(); i++){
      int mul = ((int)(unsigned char)(s[i]))%length;
      for (int j = 0; j < s.length()-i-1; j++){
        mul = (mul*256)%length;
      }
      sum += mul;
    }
    return sum%length;
  }

  void do_when_full(){
    //deal with the table
    linklist* newhash_tbl = new linklist[2*length + 1];
    for (int i = 0; i < 2*length+1; i++){
      newhash_tbl[i].head = NULL;
    }
    linklist* oldhash_tbl = hash_tbl;
    hash_tbl = newhash_tbl;
    //deal with the length
    length = 2*length + 1;
    //deal with the size
    size = 0;
    //start moving
    for (int i = 0; i<(length-1)/2; i++){
      node* current = oldhash_tbl[i].head;
      while (current){
        int freq = current->value;
        for (int j = 0; j<freq; j++){
          insert(current->key,0);
        }
        current = current->next;
      }
    }
  }

  void insert(string key, int mode){
    if (mode == 1){
      if (size*100 > load_fac*length){
        do_when_full();
      }
    }

    int index = (if_num(key)==1 ? hash_num(key):hash_str(key));

    hash_tbl[index].push(key, &size);
  }

  void remove(string key){
    int index = ((if_num(key) == 1 ? hash_num(key):hash_str(key)));
    hash_tbl[index].remove(key);
  }

  void print_hash(){
    printf("[\n");
    for (int i = 0; i < length; i++){
      if (!hash_tbl[i].head){
        printf("{}");
      }else{
        hash_tbl[i].print_list();
      }
      if (i == length -1){
        printf("\n");
        break;
      }
      printf(",\n");
    }
    printf("]");
  }
};

int main(){
  int load_fac;
  int length;
  scanf("%d", &load_fac);
  scanf("%d", &length);
  Hash hash(load_fac,length);

  char input[1024];
  while (scanf("%s", input)){
    if (string(input) == "************************"){
      break;
    }
    hash.insert(string(input),1);
  }
  while (scanf("%s", input)){
    if (string(input) == "************************"){
      break;
    }
    hash.remove(string(input));
  }

  hash.print_hash();
  return 0;
}
