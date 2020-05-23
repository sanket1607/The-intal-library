
static char* dividebytwo(char *number, int divisor) 
{ 
	// As result can be very large store it in string 
	// printf("tillhere-->");
	// printf("dividebytwo-->%s %d\n",number,divisor );
	// printf("tillhere-->");
	char *ans=(char*)malloc(sizeof(char)*1001);
	
	// Find prefix of number that is larger 
	// than divisor. 
	int idx = 0; 
	// printf("tillhere-->");
	int temp = number[idx] - '0'; 
	// printf("tillhere-->");
	while (temp < divisor) 
		temp = temp * 10 + (number[++idx] - '0'); 
	
	// Repeatedly divide divisor with temp. After 
	// every division, update temp to include one 
	// more digit. 	
	int length=strlen(number);
	int push=0;
	// printf("tillhere-->");
	while (length > idx) 
	{ 
		// printf("%d\n",idx);
		// Store result in answer i.e. temp / divisor 
		ans[push]=(temp / divisor) + '0'; 
		push++;
		// printf("%s\n",ans);
		
		// Take next digit of number 
		if(length>idx)
			temp = (temp % divisor) * 10 + (number[++idx] - '0'); 
	} 
	ans[push]='\0';
	// printf("%s",ans);
	// If divisor is greater than number 
	if (strlen(ans) == 0)
	{
		strcpy(ans,"0");
		return ans; 
	} 
	
	// else return ans 
	// printf("%s",ans);
	return ans; 
} 

static char* intaldiv(const char* num1,const char* num2)
{
	// printf("first-->%s second-->%s\n",num1,num2 );
	char *start=(char*)malloc(sizeof(char)*1001);
	strcpy(start,"0");
	char *end=(char*)malloc(sizeof(char)*1001);
	strcpy(end,num1);
	char *mid=(char*)malloc(sizeof(char)*1001);
	char *intermediate1;
	char *intermediate2;
	char *intermediate3;
	char *max=(char*)malloc(sizeof(char)*1001);
	strcpy(max,"0");
	int check;
	while(1)
	{
		if(intal_compare(start,end)<=0)
		{
			intermediate1=intal_add(start,end);
			intermediate3=dividebytwo(intermediate1,2);
			strcpy(mid,intermediate3);
			free(intermediate3);
			// printf("mid-->%s\n",mid);
			if((strlen(num2)+strlen(mid))>1000)
			{
				intermediate3=intal_diff(mid,"1");
				strcpy(end,intermediate3);
				free(intermediate3);
				continue;
			}
			intermediate2=intal_multiply(num2,mid);
			// printf("shit------------------------->");
			check=intal_compare(num1,intermediate2);
			// printf("intermediate,check-->%s %d\n",intermediate2,check);
			if(check==0)
			{
				strcpy(max,mid);
				break;
			}
			else if(check<0)
			{
				intermediate3=intal_diff(mid,"1");
				strcpy(end,intermediate3);
				free(intermediate3);
			}
			else
			{
				// if(intal_compare(mid,max)>0)
				strcpy(max,mid);
				intermediate3=intal_add(mid,"1");
				strcpy(start,intermediate3);
				free(intermediate3);
			}
		}
		else
			break;
	}
	printf("final-->%s\n",max);
	return max;

}

char* intal_mod(const char* intal1, const char* intal2){
	char *quotient=(char*)malloc(sizeof(char)*1001);
	char *temp=intaldiv(intal1,intal2);
	strcpy(quotient,temp);
	char* intermediate1=intal_multiply(intal2,quotient);
	char* intermediate2=intal_diff(intal1,intermediate1);
	return intermediate2;
}