char *scanfx(){
	int a = 0; 
	char c,  *p = malloc(1*sizeof(char));
	__fpurge(stdin);
	do{
		c = getchar(); 
		if(c!=10){
			p[a]=c;
			a++;
			p=realloc(p,(a+1)*sizeof(char));
		}
		else{
			p[a]='\0';
		}
	}while(c!=10);

	return p;
}