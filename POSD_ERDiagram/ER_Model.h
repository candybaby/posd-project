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
#include "ER_Subject.h"

using namespace std;

class ER_Model : public ER_Subject
{
public:
	enum ComponentTypeMap
	{
		Attribute,
		Entity,
		Relationship,
		Connection,
		SizeOfComponentTypeMap
	};
	struct ComponentSorter
	{
		bool ComponentSorter::operator ()(ERD_Component* leftComponent, ERD_Component* rightComponent)
		{
			return leftComponent->getId() < rightComponent->getId();
		}
	};
	static const char* componentTypeMapNames[SizeOfComponentTypeMap];
	ER_Model(void);
	~ER_Model(void);
	void clearCurrentComponents();
	void sortComponents();
	vector<ERD_Component*> getComponents();
	int addNode(ERD_Component::ComponentType, string);
	void addNode(string, string);
	void addNode(ERD_Component::ComponentType, string, int);
	void setAttributeConnected(int, bool);
	int checkAddConnection(int, int);
	void plusCurrentId();
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
	bool isAlreadyConnect(int, int);
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
	string readComponentsFile(string);
	void loadFileContent(ER_FileManager &);
	void loadComponents(vector<string>::iterator, map<int, string> &);
	void loadConnections(vector<string>::iterator, map<int, string> &);
	void loadPrinaryKey(vector<string>::iterator);
	string storeComponents(string);
	void storeFileAboutComponents(ER_FileManager &);
	void storeFileAboutConnections(ER_FileManager &);
	void storeFileAboutPrimaryKey(ER_FileManager &);
	bool isExistComponentId(string);
	string checkEntitySelectedValid(string);
	bool deleteComponent(int);
	vector<int> findRelatedConnectionById(int);
	void addComponent(ERD_Component*);
	bool enoughNodesToConnect();
	void setHasModify(bool);
	bool getHasModify();
	string getGuiNodes();
	string getGuiConnections();
	string getComponentInfo(int);
	bool isStoreFileFail;
	void setComponentText(int, string);
	void setComponentPosition(int, int, int);
	

private:
	vector<ERD_Component *> components;
	int currentId;
	ER_ComponentFactory factory;
	bool hasModify;
};
#endif