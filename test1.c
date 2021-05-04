#define lowbit(x) ((x)&(-x))
int tree[500010],a[500010],n;
void update(int x,int k) {
	while(x<=n) {
		tree[x]+=k;
		x+=lowbit(x);
	}
}
void build() {
	for(int i=1; i<=n; i++) update(i,a[i]);
}

int query(int x) {
	int sum=0;
	while(x) {
		sum+=tree[x];
		x-=lowbit(x);
	}
	return sum;
}
int main() {
	int m,mode,left,right;
	n = 10;
	for(int i=1; i<=n; i++) a[i] = 1;
	build();
	
	update(1, 3);
	update(2, 4);
	update(3, 5);
	update(6, -5);

	int ans = query(10);

	return 0;
}