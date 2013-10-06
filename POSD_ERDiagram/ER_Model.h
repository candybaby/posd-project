#pragma once
#ifndef _ER_MODEL_ 
#define _ER_MODEL_
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "ERD_Component.h"
#include "ER_ComponentFactory.h"
#include "Tool_Function.h"
#include "ER_FileManager.h"


using namespace std;
class ER_Model
{
public:
	enum ComponentTypeMap
	{
		Attribute,
		Entity,
		Relationship,
		Connection,
		SIZE_OF_ComponentTypeMap
	};
	struct ComponentSorter
	{
		bool ComponentSorter::operator ()(ERD_Component* lhs, ERD_Component* rhs) {
			return lhs->getId() > rhs->getId();
		}
	};
	static const char* componentTypeMapNames[SIZE_OF_ComponentTypeMap];
	ER_Model(void);
	~ER_Model(void);
	void clearCurrentComponents();
	void sortComponents();
	vector<ERD_Component*> getComponents();
	int addNode(ERD_Component::ComponentType, string);
	void addNode(string, string);
	void addNode(ERD_Component::ComponentType, string, int);
	ERD_Component* setAttributeTypeConnected(ERD_Component*);
	string addConnection(int, int);
	string addConnection(int, int, ERD_Connection::ConnectionCardinality);
	void addConnection(int, int, int);
	void addConnection(int, int, int, string);
	void addConnection(int, int, int, ERD_Connection::ConnectionCardinality);
	int getCurrentId();
	int getIdByIndex(int);
	int getConnectionNodeById(int, int);
	string getNameById(int);
	ERD_Component::ComponentType getTypeById(int);
	ERD_Component* findComponentById(int);
	bool isAlreadyConnect(ERD_Component*, ERD_Component*);
	void setIsPrimaryKey(int, bool);
	bool getIsPrimaryKey(int);
	void setRelatedIdVector(int, int, ERD_Component::ComponentType, vector<int> &);
	vector<int> findNodes();
	vector<int> findComponents();
	vector<int> findComponentsByType(ERD_Component::ComponentType);
	vector<int> findIdWithTypeByTargetId(ERD_Component::ComponentType, int);
	vector<int> findIdWithTypeByTargetIdWithCardinality(ERD_Component::ComponentType, int);
	vector<int> findPrimaryKeyByEntityId(int);
	vector<vector<int>> findForeignKeyByEntityId(int);
	vector<int> findOneByOneRelationEntityId(int);
	string loadComponents(string);
	string storeComponents(string);
	bool isExistComponentId(string);
	string checkEntitySelectedValid(string);
	bool deleteComponent(int);
	vector<int> findRelatedConnectionById(int);
	void addComponent(ERD_Component*);

private:
	vector<ERD_Component *> components;
	int currentId;
	ER_ComponentFactory factory;
};

#endif