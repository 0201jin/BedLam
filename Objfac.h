class Obj;
template <typename T>
class Objfac
{
public:
	static Obj* CreateObj()
	{
		Obj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static Obj* CreateObj(float _fx, float _fy, float _x, float _y)
	{
		Obj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fx, _fy);
		pObj->SetSize(_x, _y);
		return pObj;
	}
public:
	Objfac(){}
	~Objfac(){}
};