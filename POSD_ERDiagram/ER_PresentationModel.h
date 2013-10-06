#pragma once
#ifndef _ER_PRESENTATION_MODEL_ 
#define _ER_PRESENTATION_MODEL_
#include "ER_Model.h"
#include "ER_CommandManager.h"
#include "ER_AddCommand.h"
#include "ER_ConnectCommand.h"
#include "ER_DeleteCommand.h"

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

	static const char* entityOptionTypeNames[SIZE_OF_EntityOptionType];

	ER_PresentationModel(void);
	ER_PresentationModel(ER_Model*);
	~ER_PresentationModel(void);
	int addNodeOptionMapping(string);
	string addNode(ERD_Component::ComponentType, string);
	int getCurrentId();
	int getIdByIndex(int);
	int getConnectionNodeById(int, int);
	string getNameById(int);
	ERD_Component::ComponentType getTypeById(int);
	string checkAddConnection(int ,int);
	string addConnection(int ,int, ERD_Connection::ConnectionCardinality);
	bool isExistComponentId(string);
	string checkEntitySelectedValid(string);
	string checkAttributesSelectedValid(string, int);
	bool isAttributeBelongEntity(int, int);
	void setIsPrimaryKey(int, bool);
	bool getIsPrimaryKey(int);
	string getPrimaryKeyString(int);
	vector<int> findNodes();
	vector<int> findComponents();
	vector<int> findIdWithTypeByTargetId(ERD_Component::ComponentType, int);
	vector<int> findComponentsByType(ERD_Component::ComponentType);
	bool isExistTable();
	string getForeignKeyResult(int);
	string getAttributesForTable(int);
	vector<int> findOneByOneEntity();
	string getTable();
	string loadComponents(string);
	string storeComponents(string);
	string getConnectionsTable();
	string getNodesTable();
	string getComponentsTable();
	string getEntitiesTable();
	string getAttributesTableById(int);
	string redo();
	string undo();
	string deleteComponent(int);


private:
	ER_Model model;
	ER_CommandManager cmdManager;
};

#endif