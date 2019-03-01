#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int INF = 10000;
char **maze;
int **dis;

struct point{
  int x;
  int y;
};

struct queue {
  int head;
  int tail;
  point result[20000];
};
void push(queue* q, point in){
  q->result[q->tail] = in;
  q->tail += 1;
}
point pop(queue* q){
  point out = q->result[q->head];
  q->head += 1;
  return out;
}
int isempty(queue q){
  return q.head==q.tail;
}



int getpathlen(int row, int col, point start, point end){
  dis[start.x][start.y] = 0;
  int dx[4] = {0,0,1,-1}; int dy[4] = {1,-1,0,0};
  queue q;
  q.head = 0; q.tail = 0;
  push(&q,start);
  while (!isempty(q)){
    point cur = pop(&q);
    if (cur.x == end.x && cur.y == end.y){ break; }
    for (int i = 0; i < 4; i++){
      point next; next.x = cur.x + dx[i]; next.y = cur.y + dy[i];
      if (0<=next.x && next.x<= row && 0<=next.y && next.y<=col &&
          maze[next.x][next.y]!='#' && dis[next.x][next.y]==INF){
            push(&q,next);
            dis[next.x][next.y] = dis[cur.x][cur.y] + 1;
      }
    }
  }
  if (dis[end.x][end.y] == INF){
    return -1;
  }
  return dis[end.x][end.y];
}

void getpath(int row, int col, int pathlen, point end){
  point cur = end;
  int dx[4] = {0,0,1,-1}; int dy[4] = {1,-1,0,0};
  for (int j = pathlen; j>=0; j--){
    maze[cur.x][cur.y] = '.';
    for (int i = 0; i < 4; i++){
      point next; next.x = cur.x + dx[i]; next.y = cur.y + dy[i];
      if(dis[next.x][next.y] == j-1){
        cur = next;
        break;
      }
    }
  }
}




int main(){
  string str_maze = "";
  char input;
  while ((input = getchar()) != EOF){
    str_maze += input;
  }
  // std::cout << str_maze;
  int col = str_maze.find('\n',0);
  int row = (str_maze.length()+1)/(col+1);
  // std::cout << row << ' ' << col << '\n';
  maze = (char **)malloc(sizeof(char *)*row);
  for (int i = 0; i < row; i++){
    maze[i] = (char *)malloc(sizeof(char)*col);
  }
  int row_i = 0;
  int col_j = 0;
  int startx, starty, endx, endy;
  for (int i = 0; i < str_maze.length(); i++){
    if (str_maze[i] == '\n'){
      row_i += 1;
      col_j = 0;
      continue;
    }
    maze[row_i][col_j] = str_maze[i];
    if (str_maze[i] == '*'){
      startx = row_i; starty = col_j;
    }else if (str_maze[i] == '+'){
      endx = row_i; endy = col_j;
    }
    col_j += 1;
  }
  point start; start.x = startx; start.y = starty;
  point end; end.x = endx; end.y = endy;
  // std::cout << "start: " << start.x << ' ' << start.y << '\n';
  // std::cout << "end: " << end.x << ' ' << end.y << '\n';
  // for (int i = 0; i < row; i++){
  //   for (int j = 0; j < col; j++){
  //     std::cout << maze[i][j];
  //   }
  //   std::cout  << '\n';
  // }
  dis = (int **)malloc(sizeof(int *)*row);
  for (int i = 0; i < row; i++){
    dis[i] = (int *)malloc(sizeof(int)*col);
    for (int j = 0; j < col; j++){
      dis[i][j] = INF;
      // std::cout << dis[i][j] << " ";
    }
    // std::cout << '\n';
  }
  int pathlen = getpathlen(row,col,start,end);
  if (pathlen == -1){
    std::cout << "NO SOLUTION" << '\n';
    return 0;
  }
  // std::cout << pathlen << '\n';
  // for(int i = 0; i < row; i++){
  //   for (int j = 0; j < col; j++){
  //     std::cout << dis[i][j] << ' ';
  //   }
  // std::cout << '\n';
  // }
  getpath(row,col,pathlen,end);
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      std::cout << maze[i][j];
    }
    std::cout << '\n';
  }
  std::cout << pathlen << '\n';
  return 0;
}
