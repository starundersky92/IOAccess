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
	char   ItemName[21];	//寄存器名
	UINT   MinIndex;		//寄存器最小系数
	UINT   MaxIndex;		//寄存器最大系数
	WORD   DataType;		//寄存器支持的基本数据类型
	BYTE   reserve[9];		//Match byte Align	
}DEVITEM;

//Available Device Item
typedef struct 
{
	UINT	ItemNo;			//硬件寄存器数
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
	char*	pszDeviceName;		//设备信息
	char*   pszItemName;		//寄存器名称
	WORD    DataType;			//寄存器类型
	WORD    WRType;				//寄存器读写方式
}DEVREGINFO;
typedef const DEVREGINFO * LPCREGINFO;

//Device register
typedef struct 
{
	DEVADDR		devAddr;		//设备地址
	UINT        regType;     	//寄存器类型
	REGADDR		regAddr;		//寄存器地址
   	WORD        RegDataType;    //寄存器数据类型 
   	WORD        WRType;      	//读写方式
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
	WORD		wTagId;					//变量ID号
	DEVREG		devReg;					//设备寄存器

	REGVALUE    RegValue;				//变量数据值
	FILETIME    ItemTime;				//变量采集时间
	UINT        ItemQuality;			//变量采集质量
}TAGREG, * LPTAGREG;
typedef CTypedPtrList<CPtrList, TAGREG*> CTagRegList;

//Data transmition frame.
typedef struct
{
	char*		pDeviceName;	//设备名
	DEVADDR		DevAddr;		//设备地址
    UINT		RegType;		//寄存器类型
	REGADDR		StartRegAddr;	//寄存器序号起始偏移量
    REGADDR		EndRegAddr;		//寄存器序号结束偏移量
 	WORD		WRType;			//读写方式
    CTagRegList TagregList;     //变量的数据列表
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
//错误信息列表/////////////
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
	"地址定义越界",
	"寄存器名错",
	"寄存器范围越下界",
	"寄存器范围越上界",
	"寄存器数据类型错",
	"打开串口失败",
	"初始化设备失败",
	"设备无响应",
	"数据返回格式错",
	"寄存器读写方式错",
	"设备名错",
	"串口工作不正常",
	"设备地址为空！",
	"设备地址应为数字！",
	"调用参数错误！",
	"缺少寄存器地址",
	"数据校验错误",
	"IP地址错误(192.168.1.12-DNET.DADR1.DADR2-L1024-P9-B192.168.1.11)",
	"未知错误",
	"未知错误",
	"未知错误",
};

#endif	//__DEVICEACCESS_H__
