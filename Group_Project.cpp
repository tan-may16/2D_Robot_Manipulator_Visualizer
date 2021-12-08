#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "link.h"
#include "start.h"

int main() 
{
	ArmIK inv;
	Start S;
	int M, A;

	FsOpenWindow(0, 0, 1000.0, 700.0, 1);
	int start = S.startInterface(A, M);
	if (start == 0)
	{
		return 0;
	}

	inv.Automatic(A , M);
	return 0;
}