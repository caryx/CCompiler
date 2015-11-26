
int Add(int x, int y)
{
	return x+	y;
}

double Multi(double x, double y)
{
	return x*y;
}

double Div(double x, double y)
{
	return x/y;
}

int main()
{
	int a;
	double b;
	long c;
	a = 1;
	b = 234.5;
	c = a + b;
	b = Add(a, c);
	return a+c;
}