#include "ERD_Relationship.h"
#include "ER_ComponentVisitor.h"

ERD_Relationship::ERD_Relationship(void)
	: ERD_Node()
{
	this->type = Relationship;
}

// clone�غc�l
ERD_Relationship::ERD_Relationship(ERD_Relationship* relationshipClone)
	: ERD_Node(relationshipClone)
{
}

ERD_Relationship::ERD_Relationship(string name, int id)
{
	this->type = Relationship;
	this->text = name;
	this->id = id;
}

ERD_Relationship::~ERD_Relationship(void)
{
}

// �P�_�O�_�i�H�s��
bool ERD_Relationship::canConnectTo(ERD_Component* entity)
{
	if (entity->getType() == Entity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �J��
ERD_Component* ERD_Relationship::clone()
{
	return new ERD_Relationship(*this);
}

void ERD_Relationship::accept(ER_ComponentVisitor* componentVisitor)
{
	componentVisitor->visit(this);
}