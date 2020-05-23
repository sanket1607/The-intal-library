#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"intal.h"

int intal_compare(const char* intal1, const char* intal2){
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	int ans=0;
	if(len1!=len2)
		ans=(len1>len2)?1:-1;
	else{
		int i=0;
		int first=0;
		int second=0;
		while(i<len1)
		{
			first=intal1[i]-'0';
			second=intal2[i]-'0';
			if(first>second)
			{
				ans=1;
				break;
			}
			else if(first<second)
			{
				ans=-1;
				break;
			}
			else
			{
				i++;
			}
		}
	}
	return ans;
}

int intal_max(char **arr, int n){
	int max_offset=0;
	for(int i=1;i<n;i++)
	{
		if(intal_compare(arr[max_offset],arr[i])==-1)
		{
			max_offset=i;
		}
	}
	return max_offset;

}

int intal_min(char **arr, int n){
	int min_offset=0;
	for(int i=1;i<n;i++)
	{
		if(intal_compare(arr[min_offset],arr[i])==1)
		{
			min_offset=i;
		}
	}
	return min_offset;
}

int intal_search(char **arr, int n, const char* key){
	int ans=-1;
	for(int i=0;i<n;i++)
	{
		if(intal_compare(key,arr[i])==0)
		{
			ans=i;
			break;
		}
	}
	return ans;
}


//helper function for sorting
static void Merge(char** arr,int m,int n){
	char **temp = (char**) malloc(n * sizeof(char*));
	for(int i = 0; i < n; i++) {
		temp[i] = (char*) malloc(1001 * sizeof(char));
	}
	// int* B=(int*)malloc(n*sizeof(int));
	int i=0,j=m,k=0,p=0;
	while(i < m && j < n)
	{
		if(intal_compare(arr[i],arr[j])==-1 || intal_compare(arr[i],arr[j])==0)
		{
			temp[k]=arr[i];
			i++;
		}
		else
		{
			temp[k]=arr[j];
			j++;
		}
		k++;
	}
	if(j == n)
	{
		while(i<m)
		{
			temp[k]=arr[i];
			k++;i++;
		}
	}
	else
	{
		while(j<n)
		{
			temp[k]=arr[j];
			k++;j++;
		}
	}
	for(p=0;p<n;p++)
		arr[p]=temp[p];
	free(temp);
}

void intal_sort(char **arr, int n){
	if(n<=1) return;
	
	int m=n/2;
	
	intal_sort(arr,m);
	intal_sort(arr+m,n-m);
	Merge(arr,m,n);
}


int intal_binsearch(char **arr, int n, const char* key){
	int left=0;
	int right=n-1;
	int ans=-1;
	while (left <= right) { 
        int middle = left + (right - left) / 2; 
  		// printf("%d\n",middle);
        if (intal_compare(arr[middle],key) == 0)
        {
        	ans=middle;
        	right=middle-1;
        }  
  
        if (intal_compare(arr[middle],key) == -1) 
            left = middle + 1; 
   
        else
            right = middle - 1; 
    } 
  
    return ans; 
}

char* intal_add(const char* intal1, const char* intal2){
	// printf("initial numbers-->%s %s\n",intal1,intal2);
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	int carry=0;
	const char *num1=intal1;
	const char *num2=intal2;
	if(len2>len1)
	{
		num1=intal2;
		num2=intal1;
		len1=strlen(num1);
		len2=strlen(num2);
	}
	char *ans=(char*)malloc(sizeof(char)*(1001));
	int m=len1-1;
	int n=len2-1;
	int sum=0;
	int ansindex=0;
	while(m>=0 && n>=0)
	{
		sum=(num1[m]-'0')+(num2[n]-'0')+carry;
		// printf("inb sum---->%d\n",sum);
		ans[ansindex]=(sum%10+'0');
		// printf("between---->%s\n",ans);
		carry=sum/10;
		m--;
		n--;
		ansindex++;
	}

	while(m>=0)
	{
		sum=(num1[m]-'0')+carry;
		ans[ansindex]=(sum%10+'0');
		carry=sum/10;
		m--;
		ansindex++;
	}
	if(carry)
	{
		ans[ansindex]=carry+'0';
		ans[ansindex+1]='\0';
	}
	else
		ans[ansindex]='\0';

	// printf("add---->%s\n",ans);
	char *finalans=(char*)malloc(sizeof(char)*1001);
	int finallen=strlen(ans);
	int i;
	for(i=0;i<finallen;i++)
	{
		finalans[i]=ans[finallen-i-1];
	}
	free(ans);
	finalans[i]='\0';
	// printf("add---->%s\n",finalans);
	return finalans;
}

char* intal_diff(const char* intal1, const char* intal2){
	// printf("diff->%s %s\n",intal1,intal2);
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	int carry=0;
	const char *num1=intal1;
	const char *num2=intal2;
	if(len2>len1 || (intal_compare(intal1,intal2)==-1))
	{
		num1=intal2;
		num2=intal1;
		len1=strlen(num1);
		len2=strlen(num2);
	}
	char *ans=(char*)malloc(sizeof(char)*(len1+1));
	int m=len1-1;
	int n=len2-1;
	int sub=0;
	int toend=0;
	while(m>=0 && n>=0)
	{
		sub=(num1[m]-'0')-(num2[n]-'0')-carry;
		if(sub<0)
		{
			sub+=10;
			carry=1;
		}
		else
			carry=0;

		ans[m]=(sub+'0');
		toend++;
		m--;
		n--;
	}

	while(m>=0)
	{
		sub=(num1[m]-'0')-carry;
		if(sub<0)
		{
			sub+=10;
			carry=1;
		}
		else
			carry=0;

		ans[m]=(sub+'0');
		toend++;
		m--;
	}
	ans[toend]='\0';
	// printf("between1---->%s\n",ans);
	int leading=0;
	while(1)
	{
		// printf("len-->%d\n %s",strlen(ans),ans);
		if((strlen(ans)-leading)==1)
			break;
		if((ans[leading]-'0')==0)
			leading++;
		else
			break;
	}
	char *finalans=(char*)malloc(sizeof(char)*(len1+1-leading));
	int j=0;
	for(int i=leading;i<len1;i++)
	{
		finalans[j]=ans[i];
		j++;
	}
	free(ans);
	finalans[j]='\0';
	// printf("finaldiff---->%s\n",finalans);
	return finalans;
}

char* intal_fibonacci(unsigned int n){

	if(n==0)
	{
		char *ans=(char*)malloc(sizeof(char)*2);
		strcpy(ans, "0");
		return ans;
	}
	else if(n==1)
	{
		char *ans=(char*)malloc(sizeof(char)*2);
		strcpy(ans, "1");
		return ans;

	}
	else
	{
		char *num1=(char*)malloc(sizeof(char)*1001);
		char *num2=(char*)malloc(sizeof(char)*1001);
		char *ans;
		strcpy(num1, "0");
		strcpy(num2, "1");
		for(int i=2;i<=n;i++)
		{
			ans=intal_add(num1,num2);
			strcpy(num1,num2);
			strcpy(num2,ans);
			// printf("fib--->%s\n",ans);
		}
	free(num1);
	free(num2);
	return ans;
	}
}

static char* reverse(const char* intal){
	// printf("%s\n",intal);
	char *rev=(char*)malloc(sizeof(char)*1001);
	int len=strlen(intal);
	int m=0;
	len--;
	while(len>=0)
	{
		rev[m]=intal[len];
		m++;
		len--;
	}
	rev[m]='\0';
	// printf("%s\n",rev);
	return rev;
}

char* intal_multiply(const char* intal1, const char* intal2){
	// printf("from multiply--->%s %s\n",intal1,intal2);
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	const char *num1=intal1;
	const char *num2=intal2;
	// printf("%d %d\n\n",len1,len2);
	if(len2>len1 || (intal_compare(intal1,intal2)==-1))
	{
		num1=intal2;
		num2=intal1;
		len1=strlen(num1);
		len2=strlen(num2);
	}
	// printf("%d %d %s %s\n\n",len1,len2,num1,num2);
	if(strcmp(num2,"0")==0)
	{
		char *ans=(char*)malloc(sizeof(char)*2);
		strcpy(ans,"0");
		return ans;
	}
	else if(strcmp(num2,"1")==0)
	{
		char *ans=(char*)malloc(sizeof(char)*1001);
		strcpy(ans,num1);
		return ans;
	}
	else
	{
		char *ans=(char*)malloc(sizeof(char)*1001);
		for(int k=0;k<1000;k++)
			ans[k]='0';
		ans[1000]='\0';
		// printf("%s %s\n",num1,num2);
		num1=reverse(num1);
		num2=reverse(num2);
		// printf("%s %s\n",num1,num2);
		int carry=0;
		int product=0;
		int start=0;
		int end=0;
		int i,j;
		int maxend=0;
		// printf("%s %s\n",num1,num2);
		for(j=0;j<len2;j++)
		{
			carry=0;
			end=start;
			for(i=0;i<len1;i++)
			{
				product=(num1[i]-'0')*(num2[j]-'0')+(ans[end]-'0')+carry;
				ans[end]=(product%10)+'0';
				carry=product/10;
				end++;
				// printf("%c %c %d\n\n",num1[i],num2[j],product);
			}
			if(carry)
			{
				ans[end]=carry+'0';
				end++;
			}
			if(end>maxend)
				maxend=end;
			start++;
			// printf("%c\n\n",ans[end]);
		}
		// printf("%s\n\n",ans);
		ans[maxend]='\0';
		// printf("%s\n\n",ans);
		char *finalans=reverse(ans);
		free(ans);
		return finalans;
	}
}

char* intal_factorial(unsigned int n){
	if(n==0 || n==1)
	{
		char *ans=(char*)malloc(sizeof(char)*2);
		strcpy(ans,"1");
		return ans;
	}
	else
	{
		char *num1=(char*)malloc(sizeof(char)*1001);
		sprintf(num1,"%u",n);
		// printf("%s\n",num1);
		char *ans;
		// printf("%s\n\n",intal_multiply(num1,intal_factorial(n-1)));
		ans=intal_multiply(num1,intal_factorial(n-1));	
		free(num1);
		// printf("%s\n\n",ans);
		return ans;
	}
}

char* intal_pow(const char* intal1, unsigned int n){
	if(intal_compare(intal1,"0")==0)
	{
		char *ans=(char*)malloc(sizeof(char)*2);
		strcpy(ans,"0");
		return ans;
	}
	char *ans=(char*)malloc(sizeof(char)*1001);
	char *num1=(char*)malloc(sizeof(char)*1001);
	strcpy(num1,intal1);
	strcpy(ans,"1");
	while(n>0)
	{
		// printf("%d\n",n);
		if(n%2!=0)
		{
			ans=intal_multiply(ans,num1);
			// strcpy(ans,temp);
			// free(temp);
		}

		// printf("%s\n",num1);
		n/=2;
		if(n>0)
		{
		num1=intal_multiply(num1,num1);
		// strcpy(num1,temp);
		// printf("%d\n\n",n);
		// free(temp);
		}

	}
	// free(num1);
	return ans;
}

char* intal_mod(const char* intal1, const char* intal2) {
    if(intal_compare(intal1, intal2)==0) {
        char *result = (char*) malloc(sizeof(char)*2);
        strcpy(result, "0");
        return result;
    }

    else if(intal_compare(intal1, "0")==0) {
        char *result = (char*) malloc(sizeof(char)*2);
        strcpy(result, "0");
        return result;
    }

    char *num1 = (char*) malloc(1001 * sizeof(char));
    char *num2 = (char*) malloc(1001 * sizeof(char));
    char *result = (char*) malloc(1001 * sizeof(char));
    char *intermediate = (char*) malloc(1001 * sizeof(char));
    strcpy(num1, intal1);
    strcpy(num2, intal2);
    strcpy(result, intal1);
    int check = 0;

    while(intal_compare(result, num2)!= -1) {
        strcpy(intermediate, num2);
        while(intal_compare(intermediate, result)==-1) {
            char *temp = intal_multiply(intermediate, "2");
            char *temp2=intermediate;
            intermediate=temp;
            free(temp2);
        }

        result = intal_diff(intermediate, result);
        check = (check + 1) % 2;
    }

    if(intal_compare(result, "0")==0) {
        char *result2 = (char*) malloc(sizeof(char)*2);
        strcpy(result2, "0");
        free(num1);
        free(num2);
        free(intermediate);
        free(result);
        return result2;
    }

    if(check) 
    {
    	char *result2=(char*)malloc(sizeof(char)*1001);
    	strcpy(result2,intal_diff(result,num2));
    	free(num1);
    	free(num2);
    	free(intermediate);
    	return result2;
    }	

    free(num1);
    free(num2);
    free(intermediate);
    return result;
}


char* intal_gcd(const char* intal1, const char* intal2){
	// printf("gcd-->%s %s\n",intal1,intal2);
	if(intal_compare(intal1,"0")==0 && intal_compare(intal2,"0")==0)
	{
		char *result=(char*)malloc(sizeof(char)*2);
    	strcpy(result,"0");
    	return result;
	}
	else if(intal_compare(intal1,"0")==0)
	{
		char *result=(char*)malloc(sizeof(char)*1001);
    	strcpy(result,intal2);
    	return result;
	} 
    return intal_gcd(intal_mod(intal2,intal1),intal1);
}

static int minimum(int a,int b){
	return (a>b)?b:a;
}
char* intal_bincoeff(unsigned int n, unsigned int k){
	char **dptable=(char**)malloc(sizeof(char*)*(k+1));
	for(int i=0;i<=k;i++){
		dptable[i]=(char*)malloc(sizeof(char)*1001);
		strcpy(dptable[i],"0");
	}



	strcpy(dptable[0],"1");
	char *add;
	for(int i=1;i<=n;i++)
	{
		for(int j=minimum(i,k);j>0;j--)
		{
			add = intal_add(dptable[j],dptable[j-1]);
            strcpy(dptable[j],add);
            // free(addition);
		}

	}
	char *ans=(char*)malloc(sizeof(char)*1001);
	strcpy(ans,dptable[k]);
	free(dptable);
	return ans;
}

char* coin_row_problem(char **arr, int n){
	char *first=(char*)malloc(sizeof(char)*1001);
	char *second=(char*)malloc(sizeof(char)*1001);
	char *current=(char*)malloc(sizeof(char)*1001);
	char *add;
	strcpy(first,"0");
	strcpy(second,arr[0]);

	for(int i=1;i<n;i++)
	{
		add=intal_add(arr[i],first);
		if((intal_compare(add,second)==-1))
		{
			strcpy(current,second);
		}
		else
		{
			strcpy(current,add);
		}
		strcpy(first,second);
		strcpy(second,current);
	}	

	char *result=(char*)malloc(sizeof(char)*1001);
	strcpy(result,current);
	free(first);
	free(second);
	free(current);
	return result;
}
