// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Game.h"
#include "Tile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGame::CGame()
{
	//Init All Global Data
	CTile::InitTile();
	CNpc::InitNpc();
	CScript::InitScript();

	//Game Const
	GameState = GS_INIT;
	GameClient.cx = MAX_WIDTH;
	GameClient.cy = MAX_HEIGHT;
	InfoRect.SetRect(32, 50, 32 + 5 * 32, 50 + MAP_HEIGHT * 32);
	MainRect.SetRect(250, 50, 250 + MAP_WIDTH * 32, 50 + MAP_HEIGHT * 32);	
	m_bRun = false;

	//Create Cache DC
	CDC *pMainDC = ::AfxGetMainWnd()->GetDC();
	CBitmap CacheBitmap, MapBitmap;
	CacheDC.CreateCompatibleDC(pMainDC);	
	CacheBitmap.CreateCompatibleBitmap(pMainDC, GameClient.cx, GameClient.cy);
	CacheDC.SelectObject(&CacheBitmap);
	MapDC.CreateCompatibleDC(pMainDC);
	MapBitmap.CreateCompatibleBitmap(pMainDC, MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT);
	MapDC.SelectObject(&MapBitmap);
	::AfxGetMainWnd()->ReleaseDC(pMainDC);

	//Set Game Client
	::AfxGetMainWnd()->SetWindowPos(NULL, 70, 50, GameClient.cx, GameClient.cy, SWP_NOZORDER);

	Story.Init();
}

CGame::~CGame()
{

}

void CGame::OnDraw(CDC &dc)
{
	switch(GameState)
	{
		case GS_INIT:
			Story.OnDraw(CacheDC);			
			break;
		case GS_OVER:
			{
				CRect Rect(0, 0, MAX_WIDTH, MAX_HEIGHT);
				CBrush Brush(RGB(255, 255, 255));
				CacheDC.SelectObject(&Brush);
				CacheDC.Rectangle(&Rect);
				CacheDC.SetTextColor(RGB(0, 0, 0));
				CacheDC.TextOut(100, 100, "ʤ���˱��ҳ���, ", 16);
				CacheDC.TextOut(150, 130, "��������������! ", 16);
			}
			break;
		default:
			//������
			BackGround.OnDraw(CacheDC);					//����
			Info.DrawBorder(CacheDC, MainRect);			//�ұ߱߿�
			Info.OnDraw(CacheDC, InfoRect, Scene.GetRoleInfo(), Scene.GetSceneName());		//�����Ϣ
			Scene.OnDraw(MapDC);						//��Ϸ����
			CacheDC.BitBlt(MainRect.left, MainRect.top, MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT, &MapDC, 0, 0, SRCCOPY);

			//�Ի���ս������
			switch(GameState)
			{
				case GS_TALK:
					Talk.OnDraw(CacheDC);
					break;
				case GS_FIGHT:
					Fight.OnDraw(CacheDC);
					break;

			}
	}
	dc.BitBlt(0, 0, GameClient.cx, GameClient.cy, &CacheDC, 0, 0, SRCCOPY);
}

BOOL CGame::OnKeyDown(UINT nChar)
{
	//��Ϸ״̬��������, �൱��ϵͳ������Ϣ
	switch(nChar)
	{
		case 'Q':		//�˳�����
			::AfxGetMainWnd()->SendMessage(WM_CLOSE);
			break;
		case 'R':		//��Ϸ����, ���¿�ʼ, 
			return FALSE;
			break;
	}
	
	//��Ϸ��������
	switch(GameState)
	{
		case GS_INIT:
			if(Story.OnKeyDown(nChar) == FALSE)
			{
				GameState = GS_WALK;
				sndPlaySound(SOUND_BG_FILE, SND_ASYNC | SND_FILENAME | SND_NODEFAULT | SND_LOOP);
			}
			break;
		case GS_WALK:
			ptCurNpcPos = Scene.GetRoleNextPoint(nChar);			//ȡ��ɫ��һ������
			if(IDSCRIPT idScript = Scene.GetScriptID(ptCurNpcPos))	//ȡ��ӦNPC�Ľű���
			{
				Script.LoadScript(idScript);						//����ű�����
				RecurScript();										//��ʼ�ű�ѭ��
			}
			else
			{
				Scene.SetRolePos(ptCurNpcPos);						//��NPC, ǰ��
			}
			break;
		case GS_TALK:
			if(Talk.OnKeyDown(nChar) == FALSE)		//Talk ����FALSE, �����Ի�
			{
				GameState = GS_WALK;
				RecurScript();
			}
			break;
		case GS_FIGHT:
			if(Fight.OnKeyDown(nChar) == FALSE)					//Fight����FALSE, ս������
			{
				//Scene.SetRoleInfo(Fight.GetResult());			//��ȡս�����				
				GameState = GS_WALK;
				RecurScript();
			}			
			break;
		case GS_OVER:
			return FALSE;
	}
	::AfxGetMainWnd()->Invalidate(FALSE);
	return TRUE;
}

void CGame::OnTimer(UINT nIDEvent)
{
	Scene.OnTimer(nIDEvent);	//��Ӧֻд��GS_WALK, д�ڴ�, Ϊ��ʹ������NPCʼ�ձ��ֶ���
	switch(GameState)			//�ַ�Timer
	{
		case GS_INIT:
			if(Story.OnTimer(nIDEvent) == FALSE)
			{
				GameState = GS_WALK;
				sndPlaySound(SOUND_BG_FILE, SND_ASYNC | SND_FILENAME | SND_NODEFAULT | SND_LOOP);
			}
			break;
		case GS_WALK:			
			break;
		case GS_TALK:
			Talk.OnTimer(nIDEvent);
			break;
		case GS_FIGHT:
			if(Fight.OnTimer(nIDEvent) == FALSE)			//Fight����FALSE, ս������
			{
				Scene.HideNpc(ptCurNpcPos);
				sndPlaySound(SOUND_BG_FILE, SND_ASYNC | SND_FILENAME | SND_NODEFAULT | SND_LOOP);
				GameState = GS_WALK;
				RecurScript();
			}
			ROLEINFO RoleInfo = Fight.GetResult();
			Scene.SetRoleInfo(RoleInfo);
			if(RoleInfo.nHealth <= 0)
			{
				GameState = GS_OVER;
			}			
			break;
	}
	
	//���ڽű���ʱ
	/*
	if(nIDEvent == TIMER_DELAY)
	{
		::AfxGetMainWnd()->KillTimer(TIMER_DELAY);
		RecurScript();
	}
	*/

	::AfxGetMainWnd()->Invalidate(FALSE);
}

void CGame::RecurScript()
{
	m_bRun = TRUE;
	while(m_bRun)
	{
		ProcScript();
		Script.LoadNextScript();
	}
}

void CGame::ProcScript()
{
	IDFUN idFun = Script.GetScriptInfo().idFun;			//�ű�������
	DWORD Param1 = Script.GetScriptInfo().Param1;		//��Ҫ���ڴ���ID��
	DWORD Param2 = Script.GetScriptInfo().Param2;		//��Ҫ���ڴ���X����
	DWORD Param3 = Script.GetScriptInfo().Param3;		//��Ҫ���ڴ���Y����
	switch(idFun)
	{
		case SC_NULL:	
			m_bRun = false;
			break;
		case SC_SCENEFORWARD:
			Scene.Forward();			
			break;
		case SC_SCENEBACKWARD:
			Scene.Backward();
			break;
		case SC_FIGHT:					//ս��
			m_bRun = FALSE;				//��ʱ�˳��ű�, ս�����������
			GameState = GS_FIGHT;		//����ս��״̬
			ROLEINFO RoleInfo;
			NPCINFO	NpcInfo;
			IDTILE idTile[MAX_NPC_TILE];
			RoleInfo = Scene.GetRoleInfo();			//��ȡ��ɫ��Ϣ
			Scene.GetNpcTile(ptCurNpcPos, idTile, &NpcInfo);	//��ȡNPC��Ϣ
			Fight.Load(idTile, NpcInfo, RoleInfo);		//�ý�ɫ��Ϣ��NPC��Ϣ��ʹ��ս��,
			break;
		case SC_TALK:
			m_bRun = FALSE;				//��ʱ�˳��ű�, �Ի����������
			GameState = GS_TALK;		//����Ի�״̬
			Talk.Load(Param1);			//����Ի�
			break;
		case SC_NPC:
			{
				//_CrtDumpMemoryLeaks();	//����ڴ�й¶��
				ROLEINFO RoleInfo = Scene.GetRoleInfo();			
				NPCINFO NpcInfo = Scene.GetNpcInfo(ptCurNpcPos);			
				bool bNpcValid = true;							//RoleInfo, NpcInfo��Ӧ������Ƿ���Ч
				int i;
				for(i = 0; i < sizeof(RoleInfo) / sizeof(int); i++)
				{
					int *pRole = (int *)&RoleInfo + i;			//��RoleInfo��int�ֶ�
					int *pNpc = (int *)&NpcInfo + i;			//��NpcInfo��int�ֶ�
					if((*pRole) + (*pNpc) < 0 )					//����Ӧ�������, ��Ѫ���, �����, �����...
					{
						bNpcValid = false;
						break;
					}				
				}
				if(bNpcValid)				//��Ч��������зֶ�
				{
					for(i = 0; i < sizeof(RoleInfo) / sizeof(int); i++)
					{
						int *pRole = (int *)&RoleInfo + i;
						int *pNpc = (int *)&NpcInfo + i;
						*pRole += *pNpc;			
					}
					Scene.SetRoleInfo(RoleInfo);		//�����д���ɫ��Ϣ��
					Scene.HideNpc(ptCurNpcPos);			//Npc��ʧ
				}
			}
			break;
		case SC_SETNPCPOS:
			Scene.SetNpcPos(ptCurNpcPos, CPoint(Param2, Param3));		//������ӦNPC����
			break;

			//����ע�͵���Ϊ��������, �Ѳ���ʹ��, ֻ������
			/*
		case SC_DELAY:
			m_bRun = false;
			::AfxGetMainWnd()->SetTimer(TIMER_DELAY, Param1, NULL);
			break;
		case SC_LOADSCENE:
			Scene.Load(Param1);
			break;
		case SC_SETROLEPOS:
			Scene.SetRolePos(CPoint(Param2, Param3));
			break;
		
			/*
		case SC_HIDENPC:
			Scene.HideNpc(CPoint(Param2, Param3));
			break;
		case SC_HIDECURNPC:			
			Scene.HideNpc(ptCurNpcPos);
			break;
			*/
		default:
			//m_bRun = false;
			break;			
	}
	::AfxGetMainWnd()->Invalidate(FALSE);
}

