#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int num_city = 0;
int num_road = 0;
int thresh_rig = 0;
int num_regions = 0;
int real_road = 0;

//----implement disjoint-set------
int find_tag(int* dj_set, int search_city){
  int child = search_city;
  int parent = dj_set[search_city];
  while (parent != child){
    child = parent;
    parent = dj_set[parent];
  }
  return parent;
}
void set_union(int* dj_set, int city1, int city2){
  dj_set[find_tag(dj_set,city1)] = dj_set[city2];
}
void ptor(int* dj_set){
  for (int i = 0; i < num_city; i++){
    dj_set[i] = find_tag(dj_set,i);
  }
}
//--------------------------------

//------implement road------------
struct road{
  int start;
  int end;
  int dis;
};
int min(int a, int b){
  return a < b ? a : b;
}
int max(int a, int b){
  return a > b ? a : b;
}
int cmp_road(road r1, road r2){
  if (r1.dis < r2 .dis){
    return -1;
  }else if (r1.dis == r2.dis){
    if (min(r1.start,r1.end) < min(r2.start,r2.end)){
      return -1;
    }else if (min(r1.start,r1.end) == min(r2.start,r2.end)){
      if (max(r1.start,r1.end) < max(r2.start,r2.end)){
        return -1;
      }
    }else{
      return 0;
    }
  }else if (r1.dis > r2.dis){
    return 1;
  }
}
//--------------------------------

//------implement region----------
struct region{
  int minvalue;
  int tag;
  int num_of_city_in_region;
  // string output;
};
int* root_to_region(int* dj_set){
  int exist = 0;
  int* tag_of_region = new int[num_regions];
  for (int i = 0; i < num_regions; i++){
    tag_of_region[i] = -1;
  }
  int i = 0; int t = 0;
  for (i = 0,t = 0; /*i < num_city, */t < num_regions; i++){
    exist = 0;
    for (int j = 0; j < num_regions; j++){
      if (tag_of_region[j] == dj_set[i]){
        exist = 1;
        break;
      }
    }
    if (exist == 0){
      tag_of_region[t] = dj_set[i];
      t += 1 ;
    }
  }
  return tag_of_region;
}
region* get_region(region* Regions,int tag){
  for (int i = 0; i < num_regions; i++){
    if (Regions[i].tag == tag){
      return Regions + i;
    }
  }
  return NULL;
}
int cmp_region(region r1, region r2){
  if(r1.num_of_city_in_region > r2.num_of_city_in_region){
    return -1;
  }else if (r1.num_of_city_in_region == r2.num_of_city_in_region){
    if (r1.minvalue > r2.minvalue){
      return -1;
    }
    return 0;
  }else if (r1.num_of_city_in_region < r2.num_of_city_in_region){
    return 1;
  }
}
//--------------------------------

//------implement minheap---------
class Minheap{
private:
  int capacity;
  int last;
  road *heap;
public:
  Minheap(int cap){
    capacity = cap;
    last = 0;
    heap = new road[capacity+1];
  }
  bool isempty(){
    return last == 0;
  }
  bool isfull(){
    return last == capacity-1;
  }
  road top(){
    return heap[1];
  }
  void push(road in){
    if (this->isfull() == 1){;}
    last += 1;
    heap[last] = in;
    int cur_ind = last;
    while ((cur_ind >> 1) > 0 && cmp_road(heap[cur_ind], heap[cur_ind >> 1]) < 0){
      road tmp = heap[cur_ind >> 1];
      heap[cur_ind >> 1] = heap[cur_ind];
      heap[cur_ind] = tmp;
      cur_ind = cur_ind >> 1;
    }
  }
  road pop_root(){
    int cur_ind = 1;
    int next_ind = 1;
    road out = this->top();
    heap[1] = heap[last];
    last -= 1;
    while (this->isempty() == 0 && (cur_ind<<1) <= last){
      if ((cur_ind<<1)+1 > last){
        next_ind = cur_ind << 1;
      }else{
        if (cmp_road(heap[(cur_ind << 1)+1], heap[cur_ind << 1]) < 0){
          next_ind = (cur_ind << 1)+1;
        }else{
          next_ind = cur_ind << 1;
        }
      }
      if (cmp_road(heap[next_ind], heap[cur_ind]) < 0){
        road tmp = heap[next_ind];
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
};
//--------------------------------

//-----generate mst---------------
road* mst(Minheap minheap, int* dj_set){
  int road_max = num_city - thresh_rig;
  int MAX_SIZE = road_max;
  road* result = new road[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++){
    result[i].start = 2147483647; result[i].end = 2147483647; result[i].dis = 2147483647;
  }
  int i = 0; int r = 0;
  for (i = 0, r = 0; i < num_road/*i < road_max */&& r < road_max; i++){ // pay attention to the condition
    if (i >= num_road){
      continue;
    }
    road tmp = minheap.pop_root();
    if (find_tag(dj_set,tmp.start) != find_tag(dj_set,tmp.end)){
      result[r] = tmp;
      r += 1;
      set_union(dj_set,tmp.start,tmp.end);
    }else{
      continue;
    }
  }
  return result;
}
//--------------------------------

//-----sort result----------------
road* sort_city_in_road(road* result){
  int road_max = num_city - thresh_rig;
  for (int i = 0; i < road_max; i++){
    road tmp = result[i];
    int mn = min(tmp.start,tmp.end);
    int mx = max(tmp.start,tmp.end);
    result[i].start = mn;
    result[i].end = mx;
  }
  return result;
}
//--------------------------------

//----designate the road in the result into regions--
region* road_to_region(road* result, int* dj_set){
  int* tag_of_region = root_to_region(dj_set);
  region* Regions = new region[num_regions];
  for (int i = 0; i < num_regions; i++){
    Regions[i].tag = tag_of_region[i];
    Regions[i].minvalue = -1;
    Regions[i].num_of_city_in_region = 0;
    // Regions[i].output = "";
  }
  for (int i = 0; i < real_road; i++){
    region* found = get_region(Regions, dj_set[result[i].start]);
    int mn = min(result[i].start, result[i].end);
    if (found->minvalue == -1){
      found->minvalue = mn;
    }else if(mn < found->minvalue){
      found->minvalue = mn;
    }
    found->num_of_city_in_region += 1;
    // if (found->num_of_city_in_region == 1){
    //   found->output = "["+to_string(result[i].start)+","+to_string(result[i].end)+","+to_string(result[i].dis)+"]\n"+found->output;
    // }else{
    //   found->output = "["+to_string(result[i].start)+","+to_string(result[i].end)+","+to_string(result[i].dis)+"],\n" + found->output;
    // }
  }
  return Regions;
}
//--------------------------------

//---------quickSort--------------
void quickSort(region* A,int first,int last){        //数组A,first是第一个元素下标，last是最后一个元素下标
    // for (int i = 0; i < 3; i++){
    //   std::cout << A[i].output<< '\n';
    // }
    if(last<=first)                           //到了长度小于1这种情况已经是有序列了
        return;
    region pivot=A[first];
    int left=first+1;                         //left等于第二个元素
    int right=last;
    region temp;
    while(left<=right){
        while(cmp_region(pivot,A[right])<0&&right>=left){
          right--;//找到一个比first小的,但必须保证left值小于等于right值
          if (right < left){//////////////
            break;
          }
        }
        while(cmp_region(A[left],pivot)<0&&left<=right){
          left++;//找到一个比first大的,但得保证left值小于等于right值
          if (left > right){
            break;
          }
        }
         if(left>=right){
          break;//说明已经是相对有序序列，无需交换
        }
        temp=A[left];    //交换位置
        A[left]=A[right];
        A[right]=temp;
        left++,right--; //相应的进一位
    }
    A[first]=A[right]; //因为right一定是停在从右到左第一个小于first的数上，交换之后，
                       //依然能保证first值左边的比first小，右边的比first大
    A[right]=pivot;
    quickSort(A,first,right-1);               //左半部分
    quickSort(A,left,last);                   //右半部分
}
//---------------------------------

//---print out--------------------
// void printout(region* Regions){
//   printf("[\n");
//   for (int i = 0; i < num_regions; i++){
//     printf("[\n");
//     printf("%s", Regions[i].output.c_str());
//     i == num_regions-1 ? printf("]\n") : printf("],\n");
//   }
//   printf("]\n");
// }
//


int main(){
  int is_3 = 0;
  road r_tmp;
  Minheap minheap(100000);
  string input;
    cin >> input; num_city = atoi(input.c_str());
    cin >> input; num_road = atoi(input.c_str());
    cin >> input; thresh_rig = atoi(input.c_str());
  int dj_set[num_city];
  while (cin >> input){
    is_3 += 1;
    if (is_3 == 1){
      r_tmp.start = atoi(input.c_str());
    }else if (is_3 == 2){
      r_tmp.end = atoi(input.c_str());
    }else if (is_3 == 3){
      r_tmp.dis = atoi(input.c_str());
      minheap.push(r_tmp);
      is_3 = 0;
    }
  }
  for (int i = 0; i < num_city; i++){
    dj_set[i] = i;
  }
  if (num_city <= thresh_rig){
    std::cout << "[" << '\n';
    for (int i = 0; i < num_city; i++){
      std::cout << "[" << '\n';
      i == num_city - 1 ? std::cout << "]" << '\n' : std::cout << "]," << '\n';
    }
    std::cout << "]" << '\n';
    return 0;
  }
  road* result = mst(minheap,dj_set);
  result = sort_city_in_road(result);
  ptor(dj_set);
  for (int i = 0; i < num_city - thresh_rig; i++){
    if (result[i].start != 2147483647){ //or -1
      real_road += 1;
    }
  }
  num_regions = num_city - real_road;
  region* Regions = road_to_region(result,dj_set);
  quickSort(Regions,0,num_regions - 1);
  // printout(Regions);
  // std::cout << "-----the selected road-----" << '\n';
  // for (int i = 0; i < num_city - thresh_rig; i++){
  //   std::cout<<result[i].start<<' '<< result[i].end<<' '<<result[i].dis<<'\n';
  // }
  // std::cout << "-----dj_set-----" << '\n';
  // for (int i = 0; i < num_city; i++){
  //   std::cout << i <<' '<<dj_set[i] << '\n';
  // }
  // std::cout << "-----the sorted region-----" << '\n';
  // for (int i = 0; i < num_regions; i++){
  //   std::cout << i << ' '<<Regions[i].tag<<' '<<Regions[i].num_of_city_in_region<< '\n';
  // }
  // std::cout << "-----the output-----" << '\n';
  return 0;
  printf("[\n");
  for (int i = 0; i < num_regions; i++){
    printf("[\n");
    int tmp = Regions[i].tag;
    for (int j = real_road-1; j>=0; j--){
      if (dj_set[result[j].start] == tmp){
        if (Regions[i].num_of_city_in_region == 1){
          // printf("[%d,%d,%d]\n",result[j].start,result[j].end,result[j].dis);
          printf("[");printf("%d,",result[j].start);printf("%d,",result[j].end);printf("%d",result[j].dis);printf("]\n");
          break;
        }else{
          // printf("[%d,%d,%d],\n",result[j].start,result[j].end,result[j].dis);
          printf("[");printf("%d,",result[j].start);printf("%d,",result[j].end);printf("%d",result[j].dis);printf("],\n");
        }
        Regions[i].num_of_city_in_region -= 1;
      }

    }
    if (i == num_regions - 1){
      printf("]\n");
    }else{
      printf("],\n");
    }
  }
  printf("]\n");
  return 0;
}
