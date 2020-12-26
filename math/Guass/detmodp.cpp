int det(){
	s=1;
	for(int i=1;i<n;++i){
		for(p=i;p<n;++p)if(f[p][i])break;
		if(!f[p][i])return 0;
		if(p!=i){
			for(int j=i;j<n;++j)t=f[i][j],f[i][j]=f[p][j],f[p][j]=t;
			s=(M-s)%M;
		}
		t=Pow(f[i][i],M-2),s=(ll)s*f[i][i]%M;
		for(int j=i;j<n;++j)f[i][j]=(ll)f[i][j]*t%M;
		for(int j=i+1;j<n;++j)for(int k=n-1;k>=i;--k)f[j][k]=(f[j][k]-(ll)f[j][i]*f[i][k]%M+M)%M;
	}
	return s;
}
