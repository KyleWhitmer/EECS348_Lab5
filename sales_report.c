#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#define MONTHS 12

void read_file (double sales[], const char *file_name);
void print_report (const double sales[]);
void get_stats (const double sales[], double *min, double *max,
				double *average);
void moving_avg (const double sales[], double moving_avg[]);
void sort_sales (double sales[], int months[], double sorted_sales[]);
void swap (double *xp, double *yp);
void swap_int (int *xp, int *yp);

int
main ()
{
  double sales[12], sorted_sales[12], moving_avg_data[7];
  double min, max, avg;
  int months[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

  read_file (sales, "sales.txt");
  get_stats (sales, &min, &max, &avg);
  moving_avg (sales, moving_avg_data);
  memcpy (sorted_sales, sales, sizeof (sales));
  sort_sales (sorted_sales, months, sorted_sales);

  print_report (sales);
  printf ("\n Sales summary:\n");
  printf ("Minimum sales: $%.2f\n", min);
  printf ("Maximum sales: $%.2f\n", max);
  printf ("Average sales: $%.2f\n", avg);
  printf ("\n Six-Month Moving Average Report:\n");
  for (int i = 0; i < MONTHS - 5; i++)
	{
	  printf ("Months %d-%d: $%.2f\n", months[i] + 1, months[i + 5] + 1, moving_avg_data[i]);
	}
  printf ("\nSales Report (Highest to Lowest):\n");
  const char *month_names[MONTHS] =
	{ "January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
  };
  for (int i = 0; i < MONTHS; i++)
	{
	  printf ("%s: $%.2f\n", month_names[i], sorted_sales[i]);
	}

  return 0;
}


// Print formatted sales report
void
print_report (const double sales[])
{
  printf ("Monthly sales report for 2022:\n");
  printf ("Month\t\tSales\n");
  const char *months[MONTHS] =
	{ "January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
  };
  for (int i = 0; i < MONTHS; i++)
	{
	  printf ("%-9s\t$%.2f\n", months[i], sales[i]);
	}
}

// Read sales data from input file
void
read_file (double sales[], const char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (!file)
	{
	  perror ("Failed to open file");
	  exit (EXIT_FAILURE);
	}
  for (int i = 0; i < MONTHS; i++)
	{
	  if (fscanf (file, "%lf", &sales[i]) != 1)
		{
		  fprintf (stderr, "Error reading sales data for month %d\n", i + 1);
		  fclose (file);
		  exit (EXIT_FAILURE);
		}
	}
  fclose (file);
}


// Calculate statistics of sales data
void
get_stats (const double sales[], double *min, double *max, double *average)
{
  *min = sales[0];
  *max = sales[0];
  double sum = 0.0;

  // Calculate sum of all sales
  for (int i = 0; i < MONTHS; i++)
	{
	  sum += sales[i];
	}

  // Calculate average sales
  *average = sum / MONTHS;

  // Find min and max monthly sales 
  for (int i = 0; i < MONTHS; i++)
	{
	  if (sales[i] < *min)
		{
		  *min = sales[i];
		}
	  if (sales[i] > *max)
		{
		  *max = sales[i];
		}
	}
}

// Get moving average data over months of given sales numbers
void
moving_avg (const double sales[], double movingAvg[])
{
  for (int i = 0; i <= MONTHS - 6; i++)
	{
	  double sum = 0.0;
	  for (int j = i; j < i + 6; j++)
		{
		  sum += sales[j];
		}
	  movingAvg[i] = sum / 6;
	}
}

// Get sorted array of sales data
void
sort_sales (double sales[], int months[], double sorted_sales[])
{
  int n = MONTHS;
  for (int i = 0; i < n - 1; i++)
	{
	  for (int j = 0; j < n - i - 1; j++)
		{
		  if (sorted_sales[j] < sorted_sales[j + 1])
			{
			  swap (&sorted_sales[j], &sorted_sales[j + 1]);
			  swap_int (&months[j], &months[j + 1]);
			}
		}
	}
}

void
swap (double *xp, double *yp)
{
  double temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void
swap_int (int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}
