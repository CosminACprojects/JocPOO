#include"TestColiziune.h"
#include"ComponentColiziune.h"

bool TestColiziune::TestColiziuniInFunctieDePozitie(const SDL_Rect& A, const SDL_Rect& B)
{
	if (
		A.x + A.w >= B.x + 15 &&
		B.x + B.w >= A.x + 15 &&
		A.y + A.h >= B.y + 15 &&
		B.y + B.h >= A.y + 15
		)
	{
		return true;
	}

	return false;
}

bool TestColiziune::TestColiziuniInFunctieDePozitie(const ComponentColiziune& colA, const ComponentColiziune& colB)
{
	if (TestColiziuniInFunctieDePozitie(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}