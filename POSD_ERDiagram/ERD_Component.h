#pragma once
#ifndef _ERD_COMPONENT_ 
#define _ERD_COMPONENT_
#include <string>
#include <vector>

using namespace std;

class ERD_Component
{
public:
	enum ComponentType
	{
		Attribute,
		Entity,
		Relationship,
		Connection,
		SizeOfComponentType
	};
	static const char* componentTypeNames[SizeOfComponentType];
	ERD_Component(void);
	ERD_Component(ERD_Component*);
	virtual ~ERD_Component(void);
	void setId(int);
	int getId();
	ComponentType getType();
	string getText();
	virtual void setText(string);
	virtual void connectTo(ERD_Component*);
	virtual bool canConnectTo(ERD_Component*);
	vector<ERD_Component*> getConnections();
	void setPos(int, int);
	int getPosX();
	int getPosY();
	virtual ERD_Component* clone();
	
protected:
	vector<ERD_Component*> connections;
	int id;
	ComponentType type;
	string text;
	int posX;
	int posY;
};
#endif
