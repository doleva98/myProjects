#include <stdio.h>
#include "calculator.h"
#include "stack.h"
#include "string.h"
typedef const char *(*parsing_func)(const char *);
typedef double (*exec_func)(double, double);

Stack_t *operators;
Stack_t *numbers;
int *presedence;

static const char *HandleWhiteSpace(const char *str);
static double Add(double d1, double d2);
static double Sub(double d1, double d2);
static double Mul(double d1, double d2);
static double Div(double d1, double d2);
static const char *HandleOperator(const char *str);
static const char *HandleNumber(const char *str);
static const char *HandleOpenParentheseas(const char *str);
static const char *HandleCloseParentheseas(const char *str);
static void HandleAllOperators(const char *str);

exec_func exec_lut[6] = {Mul, Add, NULL, Sub, NULL, Div};

double Calculate(const char *str)
{
	double result = 0;
	parsing_func parsing_lut[128];
	size_t i;
	operators = StackCreate(128);
	numbers = StackCreate(128);

	presedence = (int *)malloc(128 * sizeof(int));
	if (!presedence)
	{
		return -1;
	}
	presedence['~'] = 1;
	presedence['('] = 2;
	presedence[')'] = 3;
	presedence['+'] = 4;
	presedence['-'] = 4;
	presedence['*'] = 5;
	presedence['/'] = 5;

	for (i = 0; i < 10; ++i)
	{
		parsing_lut['0' + i] = HandleNumber;
	}

	parsing_lut[' '] = HandleWhiteSpace;
	parsing_lut[')'] = HandleCloseParentheseas;
	parsing_lut['('] = HandleOpenParentheseas;
	parsing_lut['-'] = HandleOperator;
	parsing_lut['+'] = HandleOperator;
	parsing_lut['*'] = HandleOperator;
	parsing_lut['/'] = HandleOperator;

	while (*str)
	{
		str = parsing_lut[(int)*str](str);
	}

	while (!StackIsEmpty(operators))
	{
		HandleAllOperators("~");
	}

	result = *(double *)StackPeek(numbers);
	free(StackPeek(numbers));
	StackDestroy(numbers);
	StackDestroy(operators);
	free(presedence);
	return result;
}

static const char *HandleNumber(const char *str)
{
	char *end = NULL;
	double *num = NULL;

	num = (double *)malloc(sizeof(double));
	if (!num)
	{
		return NULL;
	}

	*num = strtod(str, &end);
	StackPush(numbers, num);
	return end;
}

static const char *HandleOperator(const char *str)
{
	char *operator= NULL;
	HandleAllOperators(str);

	operator=(char *) malloc(sizeof(char));
	if (!operator)
	{
		return NULL;
	}

	strncpy(operator, str, 1);
	StackPush(operators, operator);
	return str + 1;
}

static const char *HandleCloseParentheseas(const char *str)
{
	HandleAllOperators(str);
	if (!StackIsEmpty(operators))
	{
		free(StackPeek(operators));
		StackPop(operators);
	}
	return str + 1;
}

static void HandleAllOperators(const char *str)
{
	double *num1 = NULL;
	double *num2 = NULL;
	double *res = NULL;
	while (!StackIsEmpty(operators) && presedence[(int)*str] <= presedence[(int)*(char *)StackPeek(operators)])
	{

		res = (double *)malloc(sizeof(double));
		if (!res)
		{
			return;
		}

		num2 = (double *)StackPeek(numbers);
		StackPop(numbers);
		num1 = (double *)StackPeek(numbers);
		StackPop(numbers);
		*res = exec_lut[(int)(*(char *)StackPeek(operators) - '*')](*num1, *num2);
		StackPush(numbers, res);
		free(StackPeek(operators));
		StackPop(operators);
		free(num1);
		free(num2);
	}
}

static const char *HandleWhiteSpace(const char *str)
{
	return str + 1;
}

static const char *HandleOpenParentheseas(const char *str)
{
	char *operator= NULL;

	operator=(char *) malloc(sizeof(char));
	if (!operator)
	{
		return NULL;
	}
	strncpy(operator, str, 1);
	StackPush(operators, operator);
	return str + 1;
}

static double Add(double d1, double d2)
{
	return d1 + d2;
}

static double Sub(double d1, double d2)
{
	return d1 - d2;
}

static double Mul(double d1, double d2)
{
	return d1 * d2;
}

static double Div(double d1, double d2)
{
	return d1 / d2;
}