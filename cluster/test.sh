python3 generate_test.py >testrand.txt
g++ -std=c++11 cluster.cpp -o cluster.out
./clustering <testrand.txt >stdout.txt
./cluster.out <testrand.txt >myout.txt
diff myout.txt stdout.txt
