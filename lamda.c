#include <stdint.h>

void	*TRUE(void *x, void *y)
{
	(void)y;
	return (x);
}

void	*FALSE(int *x, void *y)
{
	(void)x;
	return (y);
}

void	*AND(void *p, void *q)
{
	return (((void *(*)(void *, void *))p)(q, FALSE));
}

void	*OR(void *p, void *q)
{
	return (((void *(*)(void *, void *))p)(TRUE, q));
}

void	*NOT(void *p)
{
	return ((void *(*)(void *, void *))p)(FALSE, TRUE);
}

static int	toBOOL(void *b)
{
	return ((int)(uintptr_t)((void *(*)(void *, void *))b)((void *)1, (void *)0));
}

void	*ZERO(void *f, void *x)
{
	(void)f;
	return (x);
}

void	*ONE(void *f, void *x)
{
	return (((void *(*)(void *))f)(x));
}

void	*TWO(void *f, void *x)
{
	return (((void *(*)(void *))f)(((void *(*)(void *))f)(x)));
}

void	*THREE(void *f, void *x)
{
	return (((void *(*)(void *))f)(((void *(*)(void *))f)(((void *(*)(void *))f)(x))));
}

void	*SUCC(void *n, void *f, void *x)
{
	return (((void *(*)(void *))f)(((void *(*)(void *, void *))n)(f, x)));
}

void	*PLUS(void *m, void *n, void *f, void *x)
{
	return (((void *(*)(void *, void *))m)(((void *(*)(void *))f), ((void *(*)(void *, void *))n)(f, x)));
}

static void	*increment(void *x)
{
	void	*val;

	val = (void *)x;
	return ((void *)(val + 1));
}

static int	toINT(void *n)
{
	return ((int)(uintptr_t)(((void *(*)(void *, void *))n)(increment, (void *)0)));
}

#include <stdio.h>
int	main(void)
{
	printf("AND TRUE FALSE: %d\n", toBOOL(AND(TRUE, FALSE)));
	printf("AND TRUE TRUE: %d\n", toBOOL(AND(TRUE, TRUE)));
	printf("AND TRUE (NOT FALSE): %d\n", toBOOL(AND(TRUE, NOT(FALSE))));
	printf("OR FALSE (NOT AND(TRUE, FALSE)): %d\n", toBOOL(OR(FALSE, NOT(AND(TRUE, FALSE)))));
	printf("toInt ZERO: %d\n", toINT(ZERO));
	printf("toInt ONE: %d\n", toINT(ONE));
	printf("toInt TWO: %d\n", toINT(TWO));
	printf("toInt TWO: %d\n", toINT(THREE));
	printf("toInt (SUCC ONE): %d\n", (int)(uintptr_t)SUCC(ONE, increment, (void *)0));
	printf("PLUS ONE TWO: %d\n", (int)(uintptr_t)PLUS(ONE, TWO, increment, (void *)0));
	return (0);
}
