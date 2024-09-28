#include <stdio.h>

int twice(int x){
	return x*2;
}

int triple(int x){
	return x*3;
}

int main(){
	int q;
	scanf("%d",&q);
	int r = twice(q);
	printf("t(%d) = %d\n",q,r);
	r=triple(q);
	printf("t(%d} = %d\n",q,r);
	return 0;
}
