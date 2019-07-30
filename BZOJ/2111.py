n,m=map(int,input().split())
a = 1;
for i in range(1,n+3):
    a = a*i
for i in range(1,m+1):
    a = a*(n+3-i+1)
b = 1
for i in range(1,n+2):
    b = b*i
for i in range(1,m+1):
    b = b*(n+2-i+1)
b = b*2
print(a-b);

