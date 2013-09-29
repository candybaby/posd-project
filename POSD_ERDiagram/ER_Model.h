#pragma once
#ifndef _ER_MODEL_ 
#define _ER_MODEL_
#include <string>
#include <vector>
#include "ERD_Component.h"
#include "ER_ComponentFactory.h"
#include "Tool_Function.h"

using namespace std;
class ER_Model
{
public:
	ER_Model(void);
	~ER_Model(void);
	vector<ERD_Component*> getComponents();
	void addNode(ERD_Component::ComponentType,string);
	ERD_Component* setAttributeTypeConnected(ERD_Component*);
	string addConnection(int, int);
	string addConnection(int, int, ERD_Connection::ConnectionCardinality);
	string getTable();
	int getCurrentId();
	int getId(int);
	int getConnectionNode1(int);
	int getConnectionNode2(int);
	string getName(int);
	ERD_Component::ComponentType getType(int);
	ERD_Component* findComponentById(int);
	bool isAlreadyConnect(ERD_Component*, ERD_Component*);
	void setIsPrimaryKey(int, bool);
	bool getIsPrimaryKey(int);
	void setIdVector(int, int, ERD_Component::ComponentType, vector<int> &);
	int findComponentIdWithConnection(vector<ERD_Component*>, int);
	vector<int> findTypeIdByComponentId(ERD_Component::ComponentType, int);
	vector<int> findTypeIdByComponentIdWithCardinality(ERD_Component::ComponentType, int);
	vector<int> findPrimaryKeyByEntityId(int);
	vector<vector<int>> findForeignKeyByEntityId(int);
	vector<int> findOneByOneRelationEntityId(int);

private:
	vector<ERD_Component *> components;
	int currentId;
	ER_ComponentFactory factory;
};

#endif