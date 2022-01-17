#pragma once
#include <SDL.h>

class ComponentColiziune;

class TestColiziune
{
public:
	static bool TestColiziuniInFunctieDePozitie(const SDL_Rect& A, const SDL_Rect& B);
	static bool TestColiziuniInFunctieDePozitie(const ComponentColiziune& colA, const ComponentColiziune& colB);
};
