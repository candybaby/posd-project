#pragma once
#ifndef _ER_PRESENTATION_MODEL_ 
#define _ER_PRESENTATION_MODEL_
#include "ER_Model.h"
class ER_PresentationModel
{
public:
	enum EntityOptionType
	{
		EntityOption_A,
		EntityOption_E,
		EntityOption_R,
		EntityOption_Attribute,
		EntityOption_Entity,
		EntityOption_Relation,
		SIZE_OF_EntityOptionType 
	};

	static const char* EntityOptionTypeNames[SIZE_OF_EntityOptionType];

	ER_PresentationModel(void);
	ER_PresentationModel(ER_Model*);
	~ER_PresentationModel(void);
	int option1Mapping(string);
	void addNode(ERD_Component::ComponentType, string);
	int getCurrentId();
	int getIdByIndex(int);
	int getConnectionNode1ById(int);
	int getConnectionNode2ById(int);
	string getNameById(int);
	ERD_Component::ComponentType getTypeById(int);
	string addConnection(int ,int);
	string addConnection(int ,int, ERD_Connection::ConnectionCardinality);
	bool isConnectCommandValid(string);
	string checkEntitySelectedValid(string);
	string checkAttributesSelectedValid(string, int);
	bool isAttributeBelongEntity(int, int);
	void setIsPrimaryKey(int, bool);
	bool getIsPrimaryKey(int);
	string getPrimaryKeyString(int);
	vector<int> findNode();
	vector<int> findComponent();
	vector<int> findTypeIdByComponentId(ERD_Component::ComponentType, int);
	vector<int> findComponentType(ERD_Component::ComponentType);
	bool isExistTable();
	string getForeignKeyResult(int);
	string getAttributesForTable(int);
	vector<int> findOneByOneEntity();
	string getTable();
	string loadComponents(string);
	string storeComponents(string);

private:
	ER_Model model;
};

#endif