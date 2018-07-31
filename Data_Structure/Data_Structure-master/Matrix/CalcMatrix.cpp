#include "LwyMatrix.h"

int main()
{
	CLwyMatrix a, b, c;

	a.Read();
	b.Read();
	c.Add( a, b );
	a.Print( " A " );
	b.Print( " B " );
	c.Print( "A+B" );
	
	getchar();
	getchar();
	
	return 0;
}