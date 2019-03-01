#include<cstdio>
#include<string>
#include<iostream>
#include<cstdlib>
using namespace std;

char up_low(char in){
  if (int(in) < 91){
    return char(int(in)+32);
  }else{
    return in;
  }
}

struct queue {
  int head;
  int tail;
  char result[26];
};
void push(queue* q, char in){
  q->result[q->tail] = in;
  q->tail += 1;
}
char pop(queue* q){
  char out = q->result[q->head];
  q->head += 1;
  return out;
}
int isempty(queue q){
  return q.head==q.tail;
}

int output(queue* outq, queue q, int* indeg_tbl, string* next_tbl){
  int visit_num = 0;
  int count = 0;
  while (visit_num < 26){
    count ++;
    if(count > 50){
      return 1;
    }
    if (visit_num == 0){
      for (int i = 0; i < 26; i++){
        if (indeg_tbl[i] == 0){
          push(&q, char(i+97));
          indeg_tbl[i] = -1;
          visit_num += 1;
          break;
        }
      }
    }
    while (isempty(q) != 1){
      char out = pop(&q);
      for (int j = 0; j < next_tbl[int(out)-97].length(); j++){
        indeg_tbl[int(next_tbl[int(out)-97][j])-97] -= 1;
      }
      next_tbl[int(out)-97] = "";
      push(outq,out);
      for (int i = 0; i < 26; i++){
        if (indeg_tbl[i] == 0){
          push(&q, char(i+97));
          indeg_tbl[i] = -1;
          visit_num += 1;
          break;
        }
      }
    }
  }
  return 0;
}

int main(){
  int num;
  scanf("%d\n", &num);
  string namelist[num];
  char input;
  int ind = 0;
  while ((input = getchar()) != EOF){
    if (input == '\n'){
      ind += 1;
    }else if (input == ' '){
      continue;
    }else{
      namelist[ind] += up_low(input);
    }
  }
  // for (int i = 0; i< num; i++){
  //   std::cout << namelist[i] << '\n';
  // }
  int indeg_tbl[26];
  for (int i = 0; i < 26; i++){
    indeg_tbl[i] = 0;
  }
  string next_tbl[26];
  // for (int i = 0; i < 26; i++){
  //   std::cout << next_tbl[i] << endl;
  // }
  for (int i = 0; i < num-1; i++){
    string tmp1 = namelist[i];
    string tmp2 = namelist[i+1];
    for (int j = 0; j < tmp1.length(); j++){
      if (j >= tmp2.length()){
        std::cout << "另请高明吧" << '\n';
        return 0;
      }
      if (tmp1[j] != tmp2[j]){
        indeg_tbl[int(tmp2[j])-97] += 1;
        next_tbl[int(tmp1[j])-97] += tmp2[j];
        break;
      }
    }
  }
  // for (int i = 0; i < 26; i++){
  //   std::cout << char(i+97) << ' ' << indeg_tbl[i] << '\n';
  // }
  // for (int i = 0; i < 26; i++){
  //   std::cout << char(i+97) << ' ' << next_tbl[i] << endl;
  // }
  struct queue q;
  q.tail = 0;
  q.head = 0;
  struct queue outq;
  outq.tail = 0;
  outq.head = 0;
  // push(&q,'a');
  // push(&q,'b');
  // std::cout << pop(&q) << '\n';
  // std::cout << pop(&q) << '\n';
  int no_source = output(&outq,q, indeg_tbl, next_tbl);
  if (no_source == 1){
    std::cout << "另请高明吧" << '\n';
  }else{
    for (int i = 0; i < 26; i++){
      std::cout << outq.result[i];
    }
    std::cout << '\n';
  }
  return 0;
}
