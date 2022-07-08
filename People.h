#pragma once
class People
{
public:
	People();
	People(char* name, int age);

	virtual void test();
	~People();

public:
	char* name;
	int   age;
};

