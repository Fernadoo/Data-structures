
import random
def rand_int(a,b):
	return int(a+random.random()*(b-a))

num_cities = rand_int(19375,20000)
num_roads = rand_int(18000,19000)
threshold = rand_int(150,1100)
# num_cities = rand_int(50,60)
# num_roads = rand_int(20,40)
# threshold = rand_int(20,40)
a = set()
while(len(a)!=num_roads):
	start = rand_int(0,num_cities)
	end = rand_int(0,num_cities)
	if start!=end:
		new_road = (start,end)
	a.add(new_road)


print(num_cities)
print(num_roads)
print(threshold)
all_edge = []
for i in a:
	print(i[0],i[1],rand_int(0,1000))
