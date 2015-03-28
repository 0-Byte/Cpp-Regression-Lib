#include <cmath>

/*
Order of calculations:

1) The means must be calulated first.
2) B must be calculated before A is calculated.
*/

class LinearRegression
{
public:
	LinearRegression();
	int init_values(long double *x_list, long double *y_list, size_t arrSize);
	void calculate_means();
	long double calculate_a();
	long double calculate_b();
	long double calculate_r();
	void clean();

private:
	long double *x_list;
	long double *y_list;
	long double x_mean;
	long double y_mean;

	int n;
	long double b;
	long double a;
	long double r;
};

/*
Set the pointers to nullptr.
*/
LinearRegression::LinearRegression()
{
	this->x_list = nullptr;
	this->y_list = nullptr;
}

/*
Add the x and y values.
*/
int LinearRegression::init_values(long double *x_list, long double *y_list, size_t arrSize)
{
	this->n = arrSize;

	// Allocate memory for the x values.
	this->x_list = new long double[arrSize];
	if (this->x_list == nullptr)
		return -1;

	// Allocate memory for the y values.
	this->y_list = new long double[arrSize];
	if (this->y_list == nullptr)
		return -1;

	// Write the x and y values to their pointers.
	for (int arrIt = 0; arrIt < arrSize; arrIt++)
	{
		this->x_list[arrIt] = x_list[arrIt];
		this->y_list[arrIt] = y_list[arrIt];
	}

	return 0;
}

/*
Calculate the x and y mean.
*/
void LinearRegression::calculate_means()
{
	long double xsum = 0, ysum = 0;

	// Get the sumation of the x and y values.
	for (int arrIt = 0; arrIt < this->n; arrIt++)
	{
		xsum += this->x_list[arrIt];
		ysum += this->y_list[arrIt];
	}

	// Set the means.
	this->x_mean = xsum / this->n;
	this->y_mean = ysum / this->n;
}

/*
Calculate the b value.
*/
long double LinearRegression::calculate_b()
{
	long double b;
	long double numerator = 0;
	long double denominator = 0;

	// Calculate the numerator.
	for (int arrIt = 0; arrIt < this->n; arrIt++)
	{
		numerator += (this->x_list[arrIt] - this->x_mean) * (this->y_list[arrIt] - this->y_mean);
	}

	// Calculate the denominator.
	for (int arrIt = 0; arrIt < this->n; arrIt++)
	{
		denominator += pow((this->x_list[arrIt] - this->x_mean), 2);
	}

	b = numerator / denominator;
	this->b = b;

	return b;
}

/*
Calculate the a value.
*/
long double LinearRegression::calculate_a()
{
	long double a;

	a = this->y_mean - (this->x_mean * this->b);
	this->a = a;

	return a;
}

/*
Calculate the the r value.
*/
long double LinearRegression::calculate_r()
{
	long double r;
	long double sumxy = 0;
	long double sumx = 0;
	long double sumy = 0;
	long double numerator;
	long double denominator;

	long double sumx2 = 0;
	long double sumxto2 = 0;
	long double sumy2 = 0;
	long double sumyto2 = 0;
	long double sqrt1 = 0;
	long double sqrt2 = 0;

	int arrIt;

	// Calcualte the sumation of x, y and x * y.
	for (arrIt = 0; arrIt < this->n; arrIt++)
	{
		sumxy += this->x_list[arrIt] * this->y_list[arrIt];
		sumx += this->x_list[arrIt];
		sumy += this->y_list[arrIt];
	}

	numerator = this->n * sumxy - sumx * sumy;

	for (arrIt = 0; arrIt < this->n; arrIt++)
	{
		sumx2 += pow(this->x_list[arrIt], 2);
		sumy2 += pow(this->y_list[arrIt], 2);
	}

	sumxto2 = pow(sumx, 2);
	sumyto2 = pow(sumy, 2);

	sqrt1 = sqrt(this->n * sumx2 - sumxto2);
	sqrt2 = sqrt(this->n * sumy2 - sumyto2);

	denominator = sqrt1 * sqrt2;

	r = numerator / denominator;

	this->r = r;

	return r;
}

/*
Free up the used memory.
*/
void LinearRegression::clean()
{
	delete[] this->x_list;
	delete[] this->y_list;
}
