#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"intal.h"

void* multiply(void* intal1,int i);
char* compute_multiplier(char* r,void* intal,int* c);
long max(long x, long y);

void* intal_create(const char* str)
{
    int i=0;
    char *t=(char*)malloc(sizeof(char));//temporary string to process it to required format
    if(strcmp(str,"0")==0 || !str)//if string is null
    {
        strcpy(t,"0");
    }
    else
    {
        while(str[i]=='0')//to remove trailing zeros
                i++;
        int l=strlen(str);
	l=l-i;
        t=(char*)malloc(sizeof(char)*l);
   
        for(int j=0;j<l;j++)
        {
            if(isdigit(str[i+j]))
                t[j]=str[i+j];
        }

        if(!strcmp(t,"\0"))//if there is some special character just copy 0
            strcpy(t,"0");
    }
    return t;
}


void intal_destroy(void* intal)
{
	free(intal);
}

char* intal2str(void* intal)
{
  if(intal==NULL)
   {
     char *nan=(char *)malloc(sizeof(char)*4);
     nan[0]='N';
     nan[1]='a';
     nan[2]='N';
     nan[3]='\0';
     return nan;
   }

  return (char*)intal_create((char*)intal);
}

void* intal_increment(void* intal)
{
	char *inc=(char*)malloc(sizeof(char));
	inc[0] = '1';
	return intal_add(intal,inc);
}

void* intal_decrement(void* intal){
	
	long l=0;
	char *t,*dec;
	l = strlen(intal);
	t = (char*)malloc(sizeof(char)*(l));
	t = intal;
	dec= (char*)malloc(sizeof(char));
	dec[0] = '1';
	
	if(l == 1 && t[0] == '0'){
		return t;
	}
	t = intal_diff(t , dec);
	return intal_create(t); 
}

void* intal_add(void* intal1, void* intal2)
{
	
	if(intal1==NULL && intal2==NULL)
		return NULL;
	if(intal1==NULL)
		return intal2;
	if(intal2==NULL)
		return intal1;
		
	long l1=0,l2=0,l3=0;
	long i=0;
	char *t1,*t2,*t3;
	int carry = 0,sum = 0;
	l1 = strlen(intal1);
	l2 = strlen(intal2);
	l3 = max(l1,l2);
	t1 = (char*)malloc(sizeof(char)*(l1));
	t2 = (char*)malloc(sizeof(char)*(l2));
	t3 = (char*)malloc(sizeof(char)*(l3 + 1));
	t1 = intal1;
	t2 = intal2;
	l1--;l2--;
	
	while(l1 != -1 && l2 != -1)
	{
		sum = (t1[l1] - '0') + (t2[l2] - '0') + carry;
		carry = sum/10;
		t3[l3] = (sum % 10) + '0';
		l1--;l2--;l3--;
	}
	if(l1 == -1)
	{
		while(l2 != -1)
		{
			sum = (t2[l2] - '0') + carry;
			carry = sum/10;
			t3[l3] = (sum % 10) + '0';
			l2--;l3--;		
		}
		t3[0] = carry +'0';
	}
	if(l2 == -1)
	{
		while(l1 != -1)
		{
			sum = (t1[l1] - '0') + carry;
			carry = sum/10;
			t3[l3] = (sum % 10) + '0';
			l1--;l3--;		
		}
		t3[0] = carry +'0';
	}
	
	return intal_create(t3);
}

void* intal_diff(void* intal1, void* intal2)
{
	
	if(intal1==NULL && intal2==NULL)
		return NULL;
	if(intal1==NULL)
		return intal2;
	if(intal2==NULL)
		return intal1;
		
	long l1=0,l2=0,l3=0;
	char *t1,*t2,*t3;
	int carry = 0,diff = 0;
	l1 = strlen(intal1);
	l2 = strlen(intal2);
	l3 = max(l1,l2);
	t1 = (char*)malloc(sizeof(char)*(l1));
	t2 = (char*)malloc(sizeof(char)*(l2));
	t3 = (char*)malloc(sizeof(char)*(l3));
	t1 = intal1;
	t2 = intal2;
	l1--;l2--;l3--;
	
	if(intal_compare(intal1 , intal2) == 1)
	{
		while(l2 != -1)
		{
			if((t1[l1] - carry) > t2[l2])
			{
				diff = (t1[l1] - '0') - (t2[l2] - '0') - carry;
				carry = 0;
			}
			if((t1[l1] - carry) < t2[l2])
			{
				diff = (t1[l1] - '0') - (t2[l2] - '0') + 10 - carry;
				carry = 1;
			}
			if((t1[l1] - carry) == t2[l2])
			{
				diff = 0;
				carry = 0;
			}
			t3[l3] = diff + '0';
			l1--;l2--;l3--;
		}
		if(l1 != -1)
		{
			while(l1 != -1 && t1[l1] == '0' && carry == 1)
			{
				t3[l3] = '9';
				l1--;l3--;
			}
			t3[l3--] = t1[l1--] - carry;
			while(l1 != -1)
			{
				t3[l3--] = t1[l1--];
			}
		}
					
	}
	else if(intal_compare(intal1 , intal2) == -1)
	{
		while(l1 != -1)
		{
			if((t2[l2] - carry) > t1[l1])
			{
				diff = (t2[l2] - '0') - (t1[l1] - '0') - carry;
				carry = 0;
			}
			if((t2[l2] - carry) < t1[l1])
			{
				diff = (t2[l2] - '0') - (t1[l1] - '0') + 10;
				carry = 1;
			}
			if((t2[l2] - carry) == t1[l1])
			{
				diff = 0;
				carry = 0;
			}
			t3[l3] = diff + '0';
			l1--;l2--;l3--;
		}
		if(l2 != -1)
		{
			while(l2 != -1 && t2[l2] == '0' && carry == 1)
			{
				t3[l3--] = '9';
				l2--;
			}
			t3[l3--] = t2[l2--] - carry;
			while(l2 != -1)
			{
				t3[l3--] = t2[l2--];
			}
		}
	}
	else if(intal_compare(intal1 , intal2) == 0)
	{
		t3[0] = '0';
	}	
	
	return intal_create(t3);
}
	
int intal_compare(void* intal1, void* intal2)
{

	long l1=0,l2=0;
	char *t1,*t2;
	
	l1 = strlen(intal1);
	l2 = strlen(intal2);
	t1 = (char*)malloc(sizeof(char)*(l1));
	t2 = (char*)malloc(sizeof(char)*(l2));
	t1 = intal1;
	t2 = intal2;
	
	if(l1 > l2)
		return 1;
	else if(l2 > l1)
		return -1;
	for(int i=0;i<l1;i++)
	{
		if(t1[i]<t2[i])
			return -1;
		if(t1[i]>t2[i])
			return 1;
	}
	return 0;	
	
}

void* intal_multiply(void* intal1, void* intal2)
{

	if(intal1==NULL || intal2==NULL)
		return NULL;
	
	char *t1,*t2,*tab[10];	
	long l1=0,l2=0;
	
	l1 = strlen(intal1);
	l2 = strlen(intal2);
	if(l1 > l2){
		t1 = (char*)malloc(sizeof(char)*(l1));
		t2 = (char*)malloc(sizeof(char)*(l2));
		t1 = intal1;
		t2 = intal2;
	}
	else{
		t2 = (char*)malloc(sizeof(char)*(l1));
		t1 = (char*)malloc(sizeof(char)*(l2));
		t1 = intal2;
		t2 = intal1;
	}
	
	for(int i=0;i<10;i++){
		tab[i] = (char*)malloc(sizeof(char)*(strlen(t1) +1));
		tab[i] = multiply(t1 , i);
	}
	char *res;
	res = (char*)malloc(sizeof(char)*(l1 + l2));
	int ch=0;
	int i = 0;
	int x =	0;
	while(i < strlen(t2)){
		x = strlen(res);
		res[x] = '0';
		ch = t2[i] - '0';
		res = intal_add(res , tab[ch]);
		i++;
	}
	
	return res;	
}

void* multiply(void* intal , int i)
{
	
	int product=0,carry=0,j=0;
	long l=0,a=0;
	char *t,*partpro,*z;
	l = strlen(intal);
	t = (char*)malloc(sizeof(char)*l);
	t = intal;
	partpro = (char*)malloc(sizeof(char)*(l + 1));
	z = (char*)malloc(sizeof(char));
	z[0] = '0';
	
	if(i == 0){
		return z;
	}
	
	a = l;
	while(a>0){
		j = t[a-1] -'0';
		product = (i*j) + carry;
		carry = product / 10;
		product = product % 10;
		partpro[a] = '0' + product;
		a--;
	}
	partpro[a] = '0' + carry ;
	
	return intal_create(partpro);
}

void* intal_pow(void* intal1, void* intal2)
{

	  if(intal1==NULL || intal2==NULL)
	      return NULL;
	  long l1=0,l2=0,l3=0;
	  char *t1=(char *)intal1;
	  char *t2=(char *)intal2;
	  l1=strlen(t1);
	  l2=strlen(t2);
	  char *t3=(char *)malloc((l2+1)*sizeof(char));
	  strcpy(t3,t2);
	  char *product;
	  if(t1[0]=='0' && t2[0]=='0')
	  {
		   product=(char *)malloc(2*sizeof(char));
		   product[0]='0';
		   product[1]='\0';
	  }
	  else if(t3[0]-'0'==0)
	  {
		    product=(char *)malloc(2*sizeof(char));
		    product[0]='1';
		    product[1]='\0';
	  }
	  else
	  {
		    product=(char *)malloc(2*sizeof(char));
		    product[0]='1';
		    product[1]='\0';
		    while(!(t3[0]=='0' && strlen(t3)==1))
		    {
		      product=(char *)intal_multiply((void *)product,(void *)t1);
		      t3=(char *)intal_decrement((void *)t3);
		    }
	  }
	  return (void *)product;
}

char* compute_multiplier(char* r,void* intal,int* c)
{
    int x=intal_compare((void*)(r),intal);
    *c=0;
    while(x==1)
    {
       (*c)++;
       r=intal_diff((void*)(r),intal);
       x=intal_compare((void*)(r),intal);
    }
    if(x==0)
    {
        (*c)++;
        r=intal_diff((void*)(r),intal);
    }
    return r;
}

void* intal_divide(void* intal1,void* intal2)
{
	if(intal1==NULL || intal2==NULL)
        	return NULL;
        
	if(intal_compare(intal2,intal_create("0")) == 0 )
	{
		return NULL;
     	}
	if(intal_compare(intal1,intal2)==-1)//integer division
        	return intal_create("0");

	char* t1= (intal_create(intal1));   
	char* t2= (intal_create(intal2));   
	int l1=strlen(t1);
	int l2=strlen(t2);
	char* r=(char*)malloc(sizeof(char)*(l2+1));
	char* q=(char*)malloc(sizeof(char)*(l1));
	int i,j=0;
	for(i=0;i<l2;i++)
	{ 
        	r[i]=t1[i];
	}
	int len,c;
	while(i<=l1)
	{
		r=compute_multiplier(r,intal2,&c);
		q[j++]=c+48;
		len=strlen(r);
		r[len]=t1[i++];
		r[len+1]='\0';
	}
	q[j]='\0';
	return intal_create((void*)(q));
}
	          
long max(long x, long y)
{
	if(x > y)
		return x;
	else
		return y;
}

