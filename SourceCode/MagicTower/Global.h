#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <mmsystem.h>		//��������

//ID
typedef BYTE				IDTILE;					//TILE ����ͼ��, ͼԪ, ��ʾͼ�ε���С��λ, ���ͼ������ͼ��ƴ�ɵ�
typedef unsigned int		IDSCENE;
typedef unsigned int		IDSCRIPT;
typedef unsigned int		IDFUN;
typedef unsigned int		IDTALK;

//Game Const
#ifdef _DEBUG
#define TILE_FILE_NAME			"..\\Tile.txt"
#define MAP_FILE_NAME			"..\\Map.txt"
#define NPC_FILE_NAME			"..\\Npc.txt"
#define STORY_FILE				"..\\�������.txt"
#define SOUND_INIT_FILE			"..\\Sound_830.wav"			//��Ϸ��ͷ������������
#define SOUND_BG_FILE			"..\\Sound_874.wav"			//��������
#define SOUND_FIGHT_FILE		"..\\Sound_13.wav"			//��������
#else
#define TILE_FILE_NAME			"Tile.txt"
#define MAP_FILE_NAME			"Map.txt"
#define NPC_FILE_NAME			"Npc.txt"
#define STORY_FILE				"�������.txt"
#define SOUND_INIT_FILE			"Sound_830.wav"
#define SOUND_BG_FILE			"Sound_874.wav"			
#define SOUND_FIGHT_FILE		"Sound_13.wav"

#endif

#define BORDER_COLOR		RGB(200, 100, 0)
#define STORY_BG_COLOR		RGB(0, 0, 0)
#define STORY_FT_COLOR		RGB(255, 255, 255)

#define MAX_WIDTH			640				//��Ϸ�Ի���Ŀ��
#define MAX_HEIGHT			480				//��Ϸ�Ի���ĸ߶�
#define MAX_SCENE			24				//ħ������, Ҳ�ǳ�������
#define MAP_WIDTH			11				//ÿ���ͼ��11��TILE
#define MAP_HEIGHT			11				//ÿ���ͼ��11��TILE
#define MAX_TILE			174				//����174��TILE
#define MAX_NPC				MAX_TILE		//��Ϸ��๲��174��NPC, Ps:ʵ�ʺ���100����
#define TILE_WIDTH			32				//ÿ��TILE��32����
#define TILE_HEIGHT			32				//ÿ��TILE��32����
#define MAX_ROLE_TILE		16				//���ǹ�16��TILE
#define MAX_NPC_TILE		2				//ÿ��NPC������2TILE
#define MAX_SCRIPT			100				//���100���ű�
#define MAX_COMMAND			20				//ÿ���ű������20������, ʵ�ʺ���2��, -_-!
#define MAX_TALK			16				//���16���Ի�
#define MAX_WORDS			64				//ÿ���Ի������64���ַ�
#define	MAX_NAME			16				//���������16���ַ�, �糡����
#define MAX_BUFFER			450				//������ڻ�������С

//TILE
#define TILE_BG				156
#define TILE_FLOOR			68
#define TILE_CELESTIAL		139			//����Tile��ID
#define TILE_ROLE			138			//����Tile��ID
#define TILE_ROLE_ENTRY		138			//���ǽ��볡��ʱ��Ĭ��ͼ��		
#define TILE_ROLE_EXIT		138			//�����˳��������Ĭ��ͼ��

//Timer

#define TIMER_INIT			1			//��Ϸ��������
#define TIMER_SCENE			2			//������ʱ
#define TIMER_ROLE			3			//���Ƕ�ʱ
#define TIMER_FIGHT			4			//ս����ʱ
//#define TIMER_TALK			5
//#define TIMER_DELAY			6


//Script ID
#define SI_NULL				0			//��
#define	SI_SCENE			1			//����
#define SI_ROLE				2			//����
#define SI_NPC				3			//NPC
#define SI_FLOOR			SI_NULL		//�ذ�
#define SI_WALL				4			//ǽ
#define SI_ENTRY			5			//���
#define SI_EXIT				6			//����
#define SI_MONSTER			7			//����	
#define SI_CELESTIAL		8			//����
#define SI_SHOP				9			//�̵�
#define SI_SECRET			10			//����


//Game Script Command
#define SC_NULL				0			//��, ����ֹͣ�ű�ѭ��
#define SC_SCENEFORWARD		7			//�л���ǰһ����
#define SC_SCENEBACKWARD	8			//�л�����һ����
#define SC_NPC				11			//NPC
#define SC_SETNPCPOS		2			//����
#define SC_FIGHT			12			//ս��
#define SC_TALK				-1			//�Ի�

/* //�Ѳ���, ����
#define SC_SETROLEPOS		1
#define SC_WAITTIMER		3
#define SC_LOADSCENE		4 
#define SC_HIDENPC			5
#define SC_HIDECURNPC		6
#define SC_SETROLE			9
#define SC_DELAY			10
*/
#endif