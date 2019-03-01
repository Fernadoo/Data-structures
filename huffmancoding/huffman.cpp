#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>
using namespace std;

class huffnode{
public:
  unsigned char value;
  int freq;
  huffnode* lf;
  huffnode* rt;
};

class Minheap{
private:
  int capacity;
  int last;

public:
  huffnode *heap;
  Minheap(int cap){
    capacity = cap;
    last = 0;
    heap = new huffnode[capacity+1];
  }

  bool isempty(){
    return last == 0;
  }

  huffnode top(){
    return heap[1];
  }

  void push(huffnode in){
    last += 1;
    heap[last] = in;
    int cur_ind = last;
    while ((cur_ind >> 1) > 0){
      if (heap[cur_ind >> 1].freq > heap[cur_ind].freq){
        huffnode tmp = heap[cur_ind >> 1];
        heap[cur_ind >> 1] = heap[cur_ind];
        heap[cur_ind] = tmp;
        cur_ind = cur_ind >> 1;
      }else if(heap[cur_ind >> 1].freq == heap[cur_ind].freq){
        if((unsigned char)(heap[cur_ind >> 1].value) > (unsigned char)(heap[cur_ind].value)){
          huffnode tmp = heap[cur_ind >> 1];
          heap[cur_ind >> 1] = heap[cur_ind];
          heap[cur_ind] = tmp;
          cur_ind = cur_ind >> 1;
        }else{
          break;
        }
      }else if(heap[cur_ind >> 1].freq < heap[cur_ind].freq){
        break;
      }
    }
  }

  huffnode* pop_root(){
    int cur_ind = 1;
    int next_ind = 1;
    huffnode* out = new huffnode;
    *out= this->top();
    heap[1] = heap[last];
    last -= 1;
    while (this->isempty() == 0 && (cur_ind<<1) <= last){
      if ((cur_ind<<1)+1 > last){
        next_ind = cur_ind << 1;
      }else{///
        if (heap[cur_ind << 1].freq > heap[(cur_ind << 1)+1].freq){
          next_ind = (cur_ind << 1)+1;
        }else if (heap[cur_ind << 1].freq == heap[(cur_ind << 1)+1].freq){
          if ((unsigned char)(heap[cur_ind << 1].value) > (unsigned char)(heap[(cur_ind << 1)+1].value)){
            next_ind = (cur_ind << 1)+1;
          }else if((unsigned char)(heap[cur_ind << 1].value) < (unsigned char)(heap[(cur_ind << 1)+1].value)){
            next_ind = (cur_ind << 1);
          }
        }else if (heap[cur_ind << 1].freq < heap[(cur_ind << 1)+1].freq){
          next_ind = (cur_ind << 1);
        }
      }
      if (heap[cur_ind].freq > heap[next_ind].freq){
        huffnode tmp = heap[next_ind];
        heap[next_ind] = heap[cur_ind];
        heap[cur_ind] = tmp;
        cur_ind = next_ind;
      }else if (heap[cur_ind].freq == heap[next_ind].freq){
        if ((unsigned char)(heap[cur_ind].value) > (unsigned char)(heap[next_ind].value)){
          huffnode tmp = heap[next_ind];
          heap[next_ind] = heap[cur_ind];
          heap[cur_ind] = tmp;
          cur_ind = next_ind;
        }else{
          break;
        }
      }else if (heap[cur_ind].freq < heap[next_ind].freq){
        break;
      }
    }
    return out;
  }

  int size(){
    return last;
  }
};

Minheap gnrt_heap(int* table){
  // std::cout << "-------heap------" << '\n';
  Minheap minheap(256);
  for(int i = 0; i < 256; i++){
    if(table[i] == 0){
      continue;
    }
    huffnode newhuff;
    newhuff.value = (unsigned char)(i);
    newhuff.freq = table[i];
    newhuff.lf = NULL;
    newhuff.rt = NULL;
    minheap.push(newhuff);
  }
  // std::cout << "heap size: " <<minheap.size() << '\n';
  //print heap----------------
  // for (int j = 1; j <= minheap.size(); j++){
  //   std::cout << "heap element: "<< int(minheap.heap[j].value) << " freq:" << minheap.heap[j].freq << '\n';
  // }
  return minheap;
}

huffnode gnrt_tree(Minheap minheap){
  // std::cout << "------hufftree-----" << '\n';
  while (minheap.size() > 1){
    huffnode newhuff;
    huffnode* first = new huffnode;
    first = minheap.pop_root();
    // std::cout << int(first->value) << '\n';
    huffnode* second = new huffnode;
    second = minheap.pop_root();
    // std::cout << int(second->value) << '\n';
    newhuff.lf = second;
    // std::cout << int(newhuff.lf->value) << '\n';
    newhuff.rt = first;
    // std::cout << int(newhuff.rt->value) << '\n';
    newhuff.freq = first->freq + second->freq;
    if ((unsigned char)(first->value) > (unsigned char)(second->value)){
      newhuff.value = (unsigned char)(second->value);
    }else if ((unsigned char)(first->value) < (unsigned char)(second->value)){
      newhuff.value = (unsigned char)(first->value);
    }
    // cout << "newhuff.value: "<< int(newhuff.value) << "newhuff.freq: "<< newhuff.freq << endl;
    minheap.push(newhuff);
  }
  return minheap.top();
}


void hufftree_to_table(huffnode* hufftree, string path, string* encode_table, int mode){
  // std::cout << (int)hufftree->lf->value << '\n';
  // std::cout << (int)hufftree->rt->value << '\n';
  // std::cout << "---" << '\n';
  if ((!hufftree->lf) && (!hufftree->rt)){
    // std::cout << hufftree->value << '\n';
    if (mode == -1){
      path += '0';
    }else if (mode == 1){
      path += '1';
    }
    encode_table[int((unsigned char)(hufftree->value))] = path;
    //.....................
    // std::cout << "char: " << int(hufftree->value) << "pathcode: "<< path << '\n';
    //.....................
    path = "";
  }else{
    if (mode == 0){
      // std::cout << "mode:" << mode << '\n';
      hufftree_to_table(hufftree->lf, path, encode_table, -1);
      hufftree_to_table(hufftree->rt, path, encode_table, 1);
    }else if(mode == -1){
      // std::cout << "mode:" << mode << '\n';
      path += '0';
      hufftree_to_table(hufftree->lf, path, encode_table, -1);
      hufftree_to_table(hufftree->rt, path, encode_table, 1);
    }else if(mode == 1){
      // std::cout << "mode:" << mode << '\n';
      path += '1';
      hufftree_to_table(hufftree->lf, path, encode_table, -1);
      hufftree_to_table(hufftree->rt, path, encode_table, 1);
    }
  }
}

string d_to_32bin(int d){
  string s = "00000000000000000000000000000000";
  for (int i = 0; i < 32; i++){
    s[31 - i] = (d%2 ? '1':'0');
    d = d >> 1;
  }
  return s;
}

string d_to_8bin(int d){
  string s = "00000000";
  for (int i = 0; i < 8; i++){
    s[7 - i] = (d%2 ? '1':'0');
    d = d >> 1;
  }
  return s;
}

int bin_to_dec(string bin){
  int dec = 0;
  for (int i = 0; i < bin.length(); i++){
    dec += (bin[bin.length()-1-i]=='1' ? 1:0)*pow(2,i);
  }
  return dec;
}

string reverse(string bits){
  string s = "";
  for (int i = 0; i < bits.length(); i++){
    s += bits[bits.length() -1 - i];
  }
  return s;
}

int cal_every_8(string bits){
  int dec = 0;
  for (int i = 0; i < bits.length(); i++){
    dec += (bits[i]=='1' ? 1:0)*pow(2,i);
  }
  return dec;
}

void out_every_8(string encode_txt){
  int is_8 = 0;
  string encode_data = "";
  for (int i = 0; i < encode_txt.length(); i++){
    encode_data += encode_txt[i];
    is_8 += 1;
    if (is_8 % 8 == 0){
      cout.put(cal_every_8(encode_data));
      encode_data = "";
      is_8 = 0;
    }
  }
}

int cal_every_4bytes(int* every_4){
  int out = 0;
  out = out|every_4[0];
  out = out|(every_4[1]<<8);
  out = out|(every_4[2]<<16);
  out = out|(every_4[3]<<24);
  return out;
}

void encode_out(string txt, int* freq_table, string* encode_table) {
  // cout.put('D');
  // cout.put('E');
  // cout.put('C');
  // cout.put('O');
  // cout.put('D');
  // cout.put('E');

  cout.put('H');
  cout.put('U');
  cout.put('F');
  cout.put('F');
  cout.put('M');
  cout.put('A');
  cout.put('N');
  cout.put('\0');
  int i;
  for (i = 0; i < 256; i++){
    int dec = freq_table[i];
    cout.put(0x000000ff & dec);
    cout.put(0x000000ff & (dec>>8));
    cout.put(0x000000ff & (dec>>16));
    cout.put(0x000000ff & (dec>>24));
  }
  string encode_txt = "";
  for (i = 0; i < txt.length(); i++){
    encode_txt += encode_table[int((unsigned char)(txt[i]))];
  }
  int x = 8 - (encode_txt.length() % 8);
  x = (x==8 ? 0:x);
  for (i = 0; i < x; i++){
    encode_txt += '0';
  }
  out_every_8(encode_txt);
}





int main(){
  //already input
  //read first 6 chars
  //read next chars
  // std::cout << d_to_32bin(255) << '\n';
  // std::cout << bin_to_dec(d_to_32bin(255)) << '\n';
  // std::cout << reverse("1234") << '\n';
  // out_every_8("12345678qwertyui");
  // // std::cout << cal_every_8("11110000") << '\n';
  // int s[4]={1,254,255,0};
  // std::cout << d_to_32bin(cal_every_4bytes(s)) << '\n';
  // std::cout << reverse(d_to_8bin(254)) << '\n';
  // std::cout << char(130) << '\n';
  // int a =  sizeof("ö");
  // cout << a << endl;
  int freq_table[256];
  for(int i = 0; i < 256; i++){
    freq_table[i] = 0;
  }
  string txt = "";
  int is_6 = 0;
  string mode = "";
  char input;
  while(cin.get(input)){
    if (is_6 == 6){
      if (mode == "ENCODE"){
        if (int(input) < 0){
          freq_table[int(input)+256] += 1;
        }else{
          freq_table[int(input)] += 1;
        }
        txt += input;
      }else if(mode == "DECODE"){
        // if (int(input) < 0){
        //   freq_table[int(input)+256] += 1;
        // }else{
        //   freq_table[int(input)] += 1;
        // }
        txt += input;
      }
    }else{
      is_6 += 1;
      mode += input;
    }
  }
// --------------------------------------Encode
  if (mode == "ENCODE"){
    Minheap minheap = gnrt_heap(freq_table);
    huffnode hufftree = gnrt_tree(minheap);
    // std::cout << "-----print tree-----" << '\n';
    // std::cout << (int)hufftree.lf->value << '\n';
    // std::cout << (int)hufftree.rt->value << '\n';
    // std::cout << (int)hufftree.lf->lf->value << '\n';
    // std::cout << (int)hufftree.lf->rt->value << '\n';
    string* encode_table = new string[256];
    for(int i = 0; i < 256; i++){
      encode_table[i] = "";
    }
    string path = "";
    // std::cout << "-------encode path----" << '\n';
    hufftree_to_table(&hufftree,path,encode_table,0);
    // for (int j = 0; j < 256; j++){
    //   if (encode_table[j] == ""){
    //     continue;
    //   }
    //   std::cout << char(j) << encode_table[j] << '\n';
    // }
    encode_out(txt, freq_table, encode_table);
//---------------------------------------------------Decode
  }else if (mode == "DECODE"){
    int i;
    string txt_only_freq = txt.substr(8,1024);
    string txt_only_cmpdata = txt.substr(1032);
    int every_4[4] = {0,0,0,0};
    int is_4 = 0;
    for (i = 0; i < txt_only_freq.length(); i++){
      // every_4[i%4] = (int(txt_only_freq[i])<0 ? int(txt_only_freq[i])+256:int(txt_only_freq[i]));
      every_4[i%4] = int((unsigned char)(txt_only_freq[i]));
      is_4 += 1;
      if (is_4 % 4 == 0){
        freq_table[i/4] = cal_every_4bytes(every_4);
        every_4[0]=0;every_4[1]=0;every_4[2]=0;every_4[3]=0;
      }
    }
    int count_of_nonzero_char = 0;
    for (i = 0; i < 256; i++){
      if (freq_table[i] != 0){
        // std::cout << "char: " << i << "freq: " << freq_table[i] << '\n';
        count_of_nonzero_char += freq_table[i];
      }
    }
    Minheap minheap = gnrt_heap(freq_table);
    huffnode hufftree = gnrt_tree(minheap);
    string* encode_table = new string[256];
    for(i = 0; i < 256; i++){
      encode_table[i] = "";
    }
    string path = "";
    hufftree_to_table(&hufftree,path,encode_table,0);

    // for (i = 0; i < 256; i++){
    //   if (encode_table[i] != ""){
    //     std::cout << "char: " << i << " path: " << encode_table[i] << '\n';
    //   }
    // }

    string txt_decmp = "";
    int each_byte;
    for (i = 0; i < txt_only_cmpdata.length(); i++){
      // each_byte = (int(txt_only_cmpdata[i])<0 ? int(txt_only_cmpdata[i])+256:int(txt_only_cmpdata[i]));
      each_byte = int((unsigned char)(txt_only_cmpdata[i]));
      txt_decmp += reverse(d_to_8bin(each_byte));
    }
    // std::cout << txt_decmp << '\n';
    string every_code = "";
    for (i = 0; i < txt_decmp.length(); i++){///count -= 1
      if (count_of_nonzero_char == 0){
        break;
      }
      every_code += txt_decmp[i];
      for (int j = 0; j < 256; j++){
        if (every_code == encode_table[j]){
            cout.put(j);
            every_code = "";
            count_of_nonzero_char -= 1;
            break;
        }
      }
    }
  }


  return 0;
}
