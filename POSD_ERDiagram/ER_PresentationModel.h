#pragma once
#ifndef _ER_PRESENTATION_MODEL_ 
#define _ER_PRESENTATION_MODEL_
#include "ER_Model.h"
#include "ER_CommandManager.h"
#include "ER_AddCommand.h"
#include "ER_ConnectCommand.h"
#include "ER_DeleteCommand.h"
#include "ER_MultipleDeleteCommand.h"
#include "ER_EditTextCommand.h"
#include "ER_MoveCommand.h"
#include "ER_SetPrimaryKeyCommand.h"
#include "ER_PasteCommand.h"
#include "ER_Observer.h"

class ER_PresentationModel
{
public:
	enum EntityOptionType
	{
		EntityOptionA,
		EntityOptionE,
		EntityOptionR,
		EntityOptionAttribute,
		EntityOptionEntity,
		EntityOptionRelation,
		SizeOfEntityOptionType 
	};
	static const char* entityOptionTypeNames[SizeOfEntityOptionType];
	ER_PresentationModel(void);
	ER_PresentationModel(ER_Model*);
	~ER_PresentationModel(void);
	int addNodeOptionMapping(string);
	string addNode(ERD_Component::ComponentType, string, int, int);
	int getCurrentId();
	int getIdByIndex(int);
	int getConnectionNodeById(int, int);
	string getNameById(int);
	ERD_Component::ComponentType getTypeById(int);
	string getAddConnectionMessage(int ,int);
	string getCannotConnectMessage(string, string);
	string getSameNodeMessage(string);
	string getAskCardinaryStateMessage();
	string getAlreadyConnectedMessage(string, string);
	string getNodeConnectedMessage(string, string);
	string addConnection(int ,int, ERD_Connection::ConnectionCardinality);
	bool isExistComponentId(string);
	string checkEntitySelectedValid(string);
	string checkAttributesSelectedValid(string, int);
	bool isAttributeBelongEntity(int, int);
	void setIsPrimaryKey(int);
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
	string makePrimaryKeyString(int, string);
	string makeResultString(int, string, string);
	vector<int> findOneByOneEntity();
	string getTable();
	string readComponentsFile(string);
	string storeComponents(string);
	string storeComponentsAsXml(string);
	string getConnectionsTable();
	string getNodesTable();
	string getComponentsTable();
	string getEntitiesTable();
	string getAttributesTableById(int);
	string redo();
	string undo();
	string deleteComponent(int);
	string deleteComponents(vector<int>);
	bool enoughNodesToConnect();
	bool getHasModify();
	string getGuiNodes();
	string getGuiConnections();
	void setComponentPos(int, int ,int);
	int getComponentPosXById(int);
	int getComponentPosYById(int);
	void setComponentText(int, string);
	void registerModelObserver(ER_Observer*);
	void moveComponent(string, int, int);
	void cutComponents(vector<int>);
	void copyComponents(vector<int>);
	void pasteComponents();
	string getTableHtml();
	string getAttributeForTableHtml(int);
	string getForeignKeyHtmlResult(int);

private:
	ER_Model model;
	ER_CommandManager* cmdManager;
};
#endif