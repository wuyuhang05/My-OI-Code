namespace sam{
	const int N=1010000;int go[N][26],len[N],fail[N],tot,last;
	void initsam(){rep(i,1,tot){len[i]=fail[i]=0;rep(j,0,25)go[i][j]=0;}tot=last=1;}
	// Rev(S) 的后缀自动机建出来就是 S 的后缀树
	// 对于结点 x,fail[x] 到 x 的边是 right[x]-len[fail[x]]..right[x]-len[x]+1 ( 倒着的 )
	// 这个板子没有求 right, 需要的话自己写个拓扑排序求
	void add(int c,int pos){
		int p=last;  		//	last:  s[2...n] 的结点
		int np=++tot;		//	np:    s[1...n] 的结点
		len[np]=len[p]+1;
		last=np;
		for(;p&&(!go[p][c]);p=fail[p])go[p][c]=np;
		if(!p){
			fail[np]=1;//lct::newson(1,np,pos);
			return;
		}
		int gt=go[p][c];
		if(len[p]+1==len[gt]){
			fail[np]=gt;//lct::newson(gt,np,pos);
			return;
		}
		int nt=++tot;len[nt]=len[p]+1;fail[nt]=fail[gt];fail[gt]=nt;
		//lct::cut(fail[nt],gt,nt);
		fail[np]=nt;
		//lct::newson(nt,np,pos);
		rep(i,0,25)go[nt][i]=go[gt][i];for(;p&&go[p][c]==gt;p=fail[p])go[p][c]=nt;
	}
};




