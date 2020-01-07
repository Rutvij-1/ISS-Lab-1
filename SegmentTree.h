class ST
{
private:
	int sz;
	int *st,*arr,*lp;

	void init(int rt,int l,int r)
	{
		if(l == (r-1))
			st[rt] = arr[l];
		else
		{
			lp[rt] = 0;
			int lc = (rt * 2) + 1,rc = (rt * 2) + 2;
			int mid = (l+r)/2;
			init(lc,l,mid);
			init(rc,mid,r);
			st[rt] = st[lc] + st[rc];
		}
	}

	void iupdt(int rt,int l,int r,int ul,int ur,int val)
	{
		if(l == (r-1))
		{
			st[rt] += val;
			arr[l] += val;
		}
		else if(l == ul and r == ur)
		{
			st[rt] += (r - l) * val;
			lp[rt] += val;
		}
		else
		{
			int lc = (rt * 2) + 1,rc = (rt * 2) + 2;
			int mid = (l+r)/2;
			if(ur<=mid)
				iupdt(lc,l,mid,ul,ur,val);
			else if(ul >= mid)
				iupdt(rc,mid,r,ul,ur,val);
			else
			{
				iupdt(lc,l,mid,ul,mid,val);
				iupdt(rc,mid,r,mid,ur,val);
			}
			st[rt] = st[lc] + st[rc];
		}
	}

	int iqry(int rt,int l,int r,int ql,int qr)
	{
		if(l == (r-1))
			return st[rt];
		else if(l == ql and r == qr)
			return st[rt];
		else
		{
			int lc = (rt * 2) + 1,rc = (rt * 2) + 2;
			int mid = (l+r)/2;
			lp[lc] += lp[rt];
			st[lc] += lp[rt] * (mid-l);
			lp[rc] += lp[rt];
			st[rc] += lp[rt] * (r-mid);
			lp[rt] = 0;
			if(qr<=mid)
				return iqry(lc,l,mid,ql,qr);
			else if(ql >= mid)
				return iqry(rc,mid,r,ql,qr);
			else
				return (iqry(lc,l,mid,ql,mid) + iqry(rc,mid,r,mid,qr));
		}
	}

public:
	ST(int a[],int n) // Constructor with parameters : O(nlogn)
	{
		sz = n;
		arr = new int[sz];
		st = new int[sz * 4];
		lp = new int[sz * 4];
		for(int i=0;i<sz;++i)
			arr[i] = a[i];
		init(0,0,n);
	}

	ST() // Constructor without any parameters : O(1)
	{
		sz = 0;
		arr = NULL;
		st = NULL;
		lp = NULL;
	}

	void initialize(int a[],int n) // Initialization of ST apart from constructor : O(nlogn)
	{
		sz = n;
		arr = new int[sz];
		st = new int[sz * 4];
		lp = new int[sz * 4];
		for(int i=0;i<sz;++i)
			arr[i] = a[i];
		init(0,0,n);
	}

	void update(int pos,int val) // Point update to set value at pos to val : O(logn)
	{
		iupdt(0,0,sz,pos,(pos+1),(val-arr[l]));
	}

	void update(int l,int r,int val) // Range update to increment values of [l,r] by val : O(logn)
	{
		r++;
		iupdt(0,0,sz,l,r,x);
	}

	int query(int l,int r) // Range query of sumation of [l,r] : O(logn)
	{
		r++;
		return iqry(0,0,sz,l,r);
	}

	int query(int pos) // Point query of pos : O(1)
	{
		return arr[pos];
	}

	int* getArray() // get the updated array : O(nlogn)
	{
		for(int i=0;i<sz;++i)
			iupdt(0,0,sz,i,i+1,0);
		return arr;
	}

	~ST() // Destructor : O(n)
	{
		sz = 0;
		delete[] arr;
		delete[] st;
		delete[] lp;
	}
};