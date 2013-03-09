// Script.cpp: implementation of the CScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Script.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////
//Script ��������ṹ, ����ʾ�ű����, ���Ϊ��������
SCRIPTS CScript::Script[MAX_SCRIPT] =
{
	//NULL
	{
		SI_NULL,
		{//��
			{SC_NULL, 0, 0, 0},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//SceneScript
	{
		SI_SCENE,
		{//����
			{SC_NULL, 0, 0, 0},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//Role Script
	{
		SI_ROLE,
		{//��ɫ
			{SC_NULL,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//Wall
	{
		SI_WALL,
		{//ǽ
			{SC_NULL,0,0,0},
			{0,0,0,0},
		},
	},
	//Entry
	{
		SI_ENTRY,
		{//���
			{SC_SCENEFORWARD, 0, 0, 0},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//Exit
	{
		SI_EXIT,
		{//����
			{SC_SCENEBACKWARD, 0, 0, 0},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//npc
	{
		SI_NPC,
		{//NPC
			{SC_NPC, 0, 0, 0},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//FIGHT
	{
		SI_MONSTER,
		{//ս��
			{SC_FIGHT, 0, 0, 0},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//Celestial
	{
		SI_CELESTIAL,
		{//����
			{SC_TALK, 0, 50, 100},
			{SC_SETNPCPOS,0,4,8},
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//Shop
	{
		SI_SHOP,
		{//�̵�
			{0,0,0,0},
			{0,0,0,0},
		},
	},
	//Secret
	{
		SI_SECRET,
		{//����
			{0,0,0,0},
			{0,0,0,0},
		},
	},
};

void CScript::InitScript()
{

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScript::CScript()
{
	m_nCommandIndex = 0;
}

CScript::~CScript()
{

}

void CScript::LoadScript(IDSCRIPT idScript)
{
	m_nScriptIndex = 0;
	int i;
	for(i = 0; i < MAX_SCRIPT; i++)
	{
		if(Script[i].idScript == idScript)
		{
			m_nScriptIndex = i;
		}
	}
	m_nCommandIndex = 0;
	memcpy(&m_Script, &Script[m_nScriptIndex].Script[m_nCommandIndex], sizeof(m_Script));
}

void CScript::LoadNextScript()
{
	m_nCommandIndex++;
	memcpy(&m_Script, &Script[m_nScriptIndex].Script[m_nCommandIndex], sizeof(m_Script));
}

SCRIPT CScript::GetScriptInfo()
{
	return m_Script;
}
