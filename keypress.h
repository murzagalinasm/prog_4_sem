#pragma once
class Keypressable
{
public:
	virtual void onkey(int)=0;
	Keypressable() {}
	virtual ~Keypressable() {}

};
