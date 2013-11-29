#include "ERD_Component.h"

ERD_Component::ERD_Component(void)
{
	id = 0;
	type = Attribute;
	posX = 0;
	posY = 0;
}

// clone建構子
ERD_Component::ERD_Component(ERD_Component* componentClone)
{
	// virtual method
	this->id = componentClone->getId();
	this->type = componentClone->getType();
	this->text = componentClone->getText();
	this->connections = componentClone->getConnections();
	this->posX = componentClone->getPosX();
	this->posY = componentClone->getPosY();
}

ERD_Component::~ERD_Component(void)
{
}

void ERD_Component::setId(int value)
{
	this->id = value;
}

// 取得id
int ERD_Component::getId()
{
	return id;
}

// 型態轉換
const char* ERD_Component::componentTypeNames[SizeOfComponentType] = { "A", "E", "R", "C"};

// 取得型態
ERD_Component::ComponentType ERD_Component::getType()
{
	return type;
}

// 取得text  (name)
string ERD_Component::getText()
{
	return text;
}

// 設定text  (name)
void ERD_Component::setText(string text)
{
	this->text = text;
}

// 連線
void ERD_Component::connectTo(ERD_Component* component)
{
	// virtual method
	connections.push_back(component);
}

// 判斷是否可以連線
bool ERD_Component::canConnectTo(ERD_Component* component)
{
	// virtual method
	return false;
}

// 取得連線Vector
vector<ERD_Component*> ERD_Component::getConnections()
{
	return connections;
}

// 克隆
ERD_Component* ERD_Component::clone()
{
	return new ERD_Component(*this);
}

// 設定座標
void ERD_Component::setPos(int x, int y)
{
	this->posX = x;
	this->posY = y;
}

// 取得座標x part
int ERD_Component::getPosX()
{
	return posX;
}

// 取得座標y part
int ERD_Component::getPosY()
{
	return posY;
}