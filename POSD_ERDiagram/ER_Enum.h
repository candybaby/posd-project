#pragma once
#ifndef _ER_ENUM_ 
#define _ER_ENUM_

enum ComponentType
{
	Attribute,
	Entity,
	Relationship,
	Connection,
	SIZE_OF_ComponentType
};
static const char* ComponentTypeNames[SIZE_OF_ComponentType] = { "A", "E", "R", "C"};

enum MenuCommand
{
	Option_1,
	Option_2,
	Option_3,
	Option_4,
	Option_5,
	Option_6,
	SIZE_OF_MenuCommand 
};
static const char* MenuCommandNames[SIZE_OF_MenuCommand] = { "1", "2", "3", "4", "5", "6" };

enum Option1Type
{
	Option1_A,
	Option1_E,
	Option1_R,
	Option1_Attribute,
	Option1_Entity,
	Option1_Relation,
	SIZE_OF_Option1Type 
};
static const char* Option1TypeNames[SIZE_OF_Option1Type] = { "A", "E", "R", "Attribute", "Entity", "Relation"};

enum ConnectionCardinality
{
	one,
	n,
	SIZE_OF_Cardinality 
};
static const char* ConnectionCardinalityNames[SIZE_OF_Cardinality] = {"1", "N"};

#endif
