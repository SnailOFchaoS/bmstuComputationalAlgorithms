#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUCCESS 0

int input_fun(float *array_x, float *array_y, float *x, int *n, int *col)
{
	int tmp = 0;
	FILE *f;
	f = fopen("data.txt", "r");
	for(int i = 0; ; i++)
	{
		if(fscanf(f, "%f %f", &array_x[i], &array_y[i]) == 2)
			tmp++;
		else 
			break;
	}
	*col = tmp;
	fclose(f);
	f = fopen("parametrs.txt", "r");
	fscanf(f,"%d %f", n, x);
	fclose(f);
	return SUCCESS;
}

float interpolation_fun(float *array_x, float *array_y, int n, float x, int col)
{
	float tmp_matrix[n][n];
	int n1 = n + 1;
	for(int i = 0; i < n1; i++)
	{
		for(int j = 0; j < n1; j++)
		{
			tmp_matrix[i][j] = -1;
		}
	}
	int stop;
	for(int i = 0; i < col; i++)
	{
		if(array_x[i] >= x)
		{
			stop = i;
			break;
		}
	}
	int first, last;
	first = stop - (n1 + 1) / 2;
	last = stop + (n1 + 1) / 2 - 1;
	if(n % 2 == 0)
		last ++;
	
	if(last > col - 1)
	{
		first = first - (last - col + 1);
		last = col - 1;
	}
	if(first < 0)
	{
		last = last - first;
		first = 0;
	}
	
	int j = 0;
	for(int i = first; i <= last; i++)
	{
		tmp_matrix[j][0] = array_y[i];
		j++;
	}
	for(int j = 1; j < n1; j++)
	{
		for(int i = 0; i < n1 - j; i++)
		{
			tmp_matrix[i][j] = (tmp_matrix[i][j - 1] - tmp_matrix[i + 1][j - 1])/(array_x[first] - array_x[first + j]);
		}
	}
	float res = tmp_matrix[0][0];
	float tmp_x = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = first; j < first + i ; j++)
		{
			tmp_x = tmp_x * (x - array_x[j]);
		}
		res = res + tmp_x*tmp_matrix[0][i];
		tmp_x = 1;
	}
	
	return res;
}

float half_division_fun(float *array_x, float *array_y, int col, int n)
{
	float e = 0.0000001, c;
	float a = array_x[0], b = array_x[col - 1];
	while (abs(interpolation_fun(array_x, array_y, n, a, col) - interpolation_fun(array_x, array_y, n, b, col)) >= e)//поставить здесь отностительную погрешность
	{
		c = (a + b)/2;
		if(interpolation_fun(array_x, array_y, n, c, col) * interpolation_fun(array_x, array_y, c, a, col) < 0)
		{
			b = c;
		}
		else
		{
			a = c;
		}
	}
	return c;
}

int main()
{
	float array_x[128], array_y[128];
	float x;
	int n, col = 0;
	float result;
	input_fun(array_x, array_y, &x, &n, &col);
	result = interpolation_fun(array_x, array_y, n, x, col);
	printf("y(%f) = %f\n", x, result);
	result = half_division_fun(array_x, array_y, col, n);
	printf("x = 0 when y = %f (half ivision)\n",result);
	result = interpolation_fun(array_y, array_x, 1, 0, col);
	printf("x(0) = %f\n",result);
	return SUCCESS;
}