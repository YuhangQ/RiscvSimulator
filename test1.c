//n numbers, m orders
//at first, all bits are 0 
//1 l r : flipped the bits in [l,r]
//2 x: print the bit at x
#include<stdio.h>
int s[1023];
int n,m;
void rev(int x)
{
	for (;x<=n;x+=x&(-x))
	    s[x]^=1;
}
int sub(int x)
{
	int ans=0;
	for (;x;x-=x&(-x))
	    ans^=s[x];
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	while (m--)
	{
		int opt,l,r; 
		scanf("%d%d",&opt,&l);
		if (opt==1) scanf("%d",&r),rev(l),rev(r+1);
		else printf("%d\n",sub(l));
	}
}
