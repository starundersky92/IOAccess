#ifndef  __DEVICEACCESS_H__
#define  __DEVICEACCESS_H__

#include <afxtempl.h>

#define FT_READ				0x00
#define FT_WRITE			0x01

#define BIT_DATATYPE		0x0001
#define BYTE_DATATYPE		0x0002
#define INT_DATATYPE		0x0004
#define UINT_DATATYPE		0x0008
#define BCD_DATATYPE		0x0010
#define LONG_DATATYPE		0x0020
#define LONGBCD_DATATYPE	0x0040
#define FLOAT_DATATYPE		0x0080
#define STRING_DATATYPE		0x0100


//Device address information
typedef union
{
	LONG	nAddr;
	WORD	wAddr[2];
	BYTE	bAddr[4];
}DEVADDR, * LPDEVADDR;
typedef const DEVADDR * LPCDEVADDR;

//Device supported items.
typedef struct DevItem
{
	char   ItemName[21];	//�Ĵ�����
	UINT   MinIndex;		//�Ĵ�����Сϵ��
	UINT   MaxIndex;		//�Ĵ������ϵ��
	WORD   DataType;		//�Ĵ���֧�ֵĻ�����������
	BYTE   reserve[9];		//Match byte Align	
}DEVITEM;

//Available Device Item
typedef struct 
{
	UINT	ItemNo;			//Ӳ���Ĵ�����
	DEVITEM *pItems;
}DEVITEMAVL, * LPDEVITEMAVL;

typedef struct
{
	UINT	nAddr;
	WORD	wAddr;
	BYTE	bAddr[2];
}REGADDR, * LPREGADDR;
typedef const REGADDR * LPCREGADDR;

typedef union
{	
	BOOL  bitVal;
	BYTE  byteVal;
	short intVal;
	UINT  uintVal;
	WORD  bcdVal;
	long  longVal;
	float floatVal;
	DWORD longbcdVal;
	char* strVal;
}REGVALUE;

typedef struct 
{
	char*	pszDeviceName;		//�豸��Ϣ
	char*   pszItemName;		//�Ĵ�������
	WORD    DataType;			//�Ĵ�������
	WORD    WRType;				//�Ĵ�����д��ʽ
}DEVREGINFO;
typedef const DEVREGINFO * LPCREGINFO;

//Device register
typedef struct 
{
	DEVADDR		devAddr;		//�豸��ַ
	UINT        regType;     	//�Ĵ�������
	REGADDR		regAddr;		//�Ĵ�����ַ
   	WORD        RegDataType;    //�Ĵ����������� 
   	WORD        WRType;      	//��д��ʽ
}DEVREG, * LPDEVREG;
typedef const DEVREG* LPCDEVREG;

//COM port parmeters
struct COMPORTPARAM
{
	short nPort;
	long  lBaudRate;
	short nDataBits;
	short nStopBits;
	short nParity;
	short nTimeOut;
	short bRS485;
};

//Single Register
typedef struct
{	
	WORD		wTagId;					//����ID��
	DEVREG		devReg;					//�豸�Ĵ���

	REGVALUE    RegValue;				//��������ֵ
	FILETIME    ItemTime;				//�����ɼ�ʱ��
	UINT        ItemQuality;			//�����ɼ�����
}TAGREG, * LPTAGREG;
typedef CTypedPtrList<CPtrList, TAGREG*> CTagRegList;

//Data transmition frame.
typedef struct
{
	char*		pDeviceName;	//�豸��
	DEVADDR		DevAddr;		//�豸��ַ
    UINT		RegType;		//�Ĵ�������
	REGADDR		StartRegAddr;	//�Ĵ��������ʼƫ����
    REGADDR		EndRegAddr;		//�Ĵ�����Ž���ƫ����
 	WORD		WRType;			//��д��ʽ
    CTagRegList TagregList;     //�����������б�
	LPVOID		pDevice;
}DATAFRAME, * LPDATAFRAME;

// {027CD6C3-C18D-454b-9985-16841941A69F}
static const GUID IID_IDevAccess3 = 
{ 0x27cd6c3, 0xc18d, 0x454b, { 0x99, 0x85, 0x16, 0x84, 0x19, 0x41, 0xa6, 0x9f } };
class IDevAccess3 : public IUnknown
{
public:
	//Common interface of IUnkown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
    virtual ULONG STDMETHODCALLTYPE Release() = 0;
	virtual HRESULT STDMETHODCALLTYPE ReservedFunc1(INT32 p1, INT32 p2, INT32 p3, INT32 p4, INT32* pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE ReservedFunc2(INT32 p1, INT32 p2, INT32 p3, INT32 p4, INT32* pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetVersion(UINT32* pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE RegisterServer(VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE ValidateLicence(LPSTR szLibName, INT32 nLicType, void* pLicence, VARIANT_BOOL* pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetHelpString(LPSTR szLibName, INT32 nHelp, INT32* InfoDescrip, BSTR* pbstrHelp) = 0;
	virtual HRESULT STDMETHODCALLTYPE EnumItems(LPSTR szLibName, DEVITEMAVL* pDevRegAvl, VARIANT_BOOL* pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetDebugLevel(INT32 level) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetLastError(BSTR* pbstrError) = 0;
	virtual HRESULT STDMETHODCALLTYPE CompileDevAddr(LPSTR szLibName, LPSTR szAddr, DEVADDR* lpDevAddr, VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE CompileItem(DEVREGINFO * lpRegInfo, DEVREG* lpDevReg, VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetItemName(LPSTR szLibName, UINT regType, REGADDR* regAddr, BSTR* pbstrName) = 0;
	virtual HRESULT STDMETHODCALLTYPE InitialDevice(LPSTR szLibName, DEVADDR * lpDevAddr, LPVOID lpInitInfo, VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE InitComm(COMPORTPARAM* lpInitParam, VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE CloseComm(VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE OptimizeAccess(DATAFRAME* lpFrame, DEVREG* lpDevReg, VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE AccessDevice(DATAFRAME* lpFrame, VARIANT_BOOL * pRetVal) = 0;
	virtual HRESULT STDMETHODCALLTYPE Diagnose(LPSTR szLibName, DEVADDR * lpDevAddr, VARIANT_BOOL * pRetVal) = 0;
};

//////////////////////////
//������Ϣ�б�/////////////
#define  ADDR_OVERFLOW			0
#define  BAD_REGISTER           1
#define  REGISTER_OVERFLOW_LOW  2
#define  REGISTER_OVERFLOW_HIGH 3
#define  BAD_REGISTER_DATATYPE  4
#define	 OPENCOM_FAIL   		5
#define  INITIALDEVICE_FAIL		6
#define	 NO_DATA_RETURN 		7
#define  BAD_DATA_STRUCTURE		8
#define	 BAD_DATA_RWTYPE		9
#define  BAD_DEVICENAME         10
#define  COM_WORK_UNNOMAL       11
#define  DEVADDR_EMPTY			12
#define  DEVADDR_MUSTDIGIT		13
#define  BAD_ARGV				14
#define  NO_REGISTER_INDEX		15
#define  CRC_ERROR				16
#define  IPADDR_ERROR			17
#define  RESERVED2_ERROR		18
#define  RESERVED3_ERROR		19
#define  RESERVED4_ERROR		20
#define  LAST_ERROR				20

static char* ERROR_STR[] = 
{
	"��ַ����Խ��",
	"�Ĵ�������",
	"�Ĵ�����ΧԽ�½�",
	"�Ĵ�����ΧԽ�Ͻ�",
	"�Ĵ����������ʹ�",
	"�򿪴���ʧ��",
	"��ʼ���豸ʧ��",
	"�豸����Ӧ",
	"���ݷ��ظ�ʽ��",
	"�Ĵ�����д��ʽ��",
	"�豸����",
	"���ڹ���������",
	"�豸��ַΪ�գ�",
	"�豸��ַӦΪ���֣�",
	"���ò�������",
	"ȱ�ټĴ�����ַ",
	"����У�����",
	"IP��ַ����(192.168.1.12-DNET.DADR1.DADR2-L1024-P9-B192.168.1.11)",
	"δ֪����",
	"δ֪����",
	"δ֪����",
};

#endif	//__DEVICEACCESS_H__