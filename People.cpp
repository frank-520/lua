#include "stdafx.h"
#include "People.h"
#include "stdlib.h"
#include "string.h"

People::People()
{
}

People::People(char* Name,int Age)
{
	//strcpy(name, Name);
	name = Name;
	age = Age;
}

People::~People()
{
}

void People::test() {

}
