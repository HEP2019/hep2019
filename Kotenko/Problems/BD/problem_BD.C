#include <iostream>
#include <cmath>

template <typename T>
class FuncTable
{
public:
	int columns, rows;
	T *data;

	FuncTable(int c, int r): columns(c), rows(r)
	{
		data = new T[columns*rows];
		FillFalse();
		FillInitial();
	}
	~FuncTable()
	{
		delete []data;
	}

public:
	T& GetElement(int xpos, int ypos)
	{
		return data[rows*ypos+xpos];
	}
	void SetElement(int xpos, int ypos, T val)
	{
		data[rows*ypos+xpos] = val;
	}
	void FillFalse()
	{
		for(int i=0;i<columns*rows;i++)
		{
			data[i]= (T)(-1);
		}
	}
	void FillInitial()
	{
		SetElement(0,0,T(0));
		SetElement(0,1,T(0));
		SetElement(1,1,T(1));
		SetElement(2,1,T(0));
		for(int i=2;i<rows;i++) 
		{
			SetElement(0,i,T(1));
			SetElement(1,i,T(1));
			SetElement(2,i,T(1));
			SetElement(3,i,T(2));
			SetElement(4,i,T(2));
		}
		SetElement(1,0,T(0));
		SetElement(3,0,T(0));
		SetElement(3,1,T(0));
		SetElement(3,2,T(1));
		SetElement(4,2,T(0));
		SetElement(4,3,T(1));
		SetElement(4,4,T(2));

	}
	// void Print()
	// {
	// 	for(int i=0;i<rows;i++)
	// 	{
	// 		for(int j=0;j<rows;j++)
	// 		{
	// 			if(data[rows*j+i]!=-1)
	// 			{

	// 			std::cout<<"table["<<i<<"]["<<j<<"] = "<<data[rows*j+i]<<"\t";
	// 			}
	// 		}
	// 		std::cout<<"\n";
	// 	}
	// }
};

int minh(int);
long long int numcomb(int);
long long int secondarycomb(int,int,FuncTable<long long int> &);

int minh(int n)
{
	return int( (sqrt(1+8*n)-1)/2 );
}

long long int numcomb(int n)
{
	int minheight = minh( n);
	long long int sol =0;

	FuncTable<long long int> func_table = FuncTable<long long int>(n+1,n+1);

	for(int i=1;i<=(n-minheight);i++)
	{
		sol+=secondarycomb(i,n-i-1,func_table);
	}
	// func_table.Print();
	return sol;
}

long long int secondarycomb(int number, int maxlen, FuncTable<long long int> & func_table)
{
	if( func_table.GetElement(number,maxlen) !=-1 )
	{
		return func_table.GetElement(number,maxlen);
	}
	int minheight = minh(number);
	long long int sol =0;
	if( (maxlen>0) && (maxlen>=minheight) )
	{
		for( int cur_col = minheight; cur_col<=maxlen; cur_col++)
		{
			if( (cur_col*(cur_col-1)/2)<(number-cur_col) || (number<cur_col) ) continue;
			sol+=secondarycomb(number-cur_col,cur_col-1,func_table);
		}
		func_table.SetElement(number,maxlen,sol);
		return sol;
	}
	else
	{
		func_table.SetElement(number,maxlen,0);
		return 0;
	}
}

int main()
{
	int i;
	std::cin>>i;
	std::cout<<numcomb(i);
	return 0;
}