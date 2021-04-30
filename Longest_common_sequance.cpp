#include<iostream>
#include<bits/stdc++.h>
#include<string>
using namespace std;

int max(int a, int b)
{
	return (a > b)? a : b;
}

int lcs( string &X, string &Y, int m, int n )
{
	int L[m + 1][n + 1];

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
		if (i == 0 || j == 0)
			L[i][j] = 0;

		else if (X[i - 1] == Y[j - 1])
			L[i][j] = L[i - 1][j - 1] + 1;

		else
			L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}
	//printing LCS
	string tmp;
	int i = m,j = n;
	while(i!=0&&j!=0){
		if(L[i][j]==L[i][j-1])
		    j--;
		else if(L[i][j]==L[i-1][j])
		    i--;
		else{
		    tmp+=Y[j-1];
		    i--;
		    j--;
			}
	}
	reverse(tmp.begin(),tmp.end());
	cout<<"\n\nLCS is : "<<tmp<<"\n\n";

	return L[m][n];
}
