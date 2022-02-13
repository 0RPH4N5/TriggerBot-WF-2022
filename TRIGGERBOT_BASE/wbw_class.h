#pragma once
#include <Windows.h>
typedef unsigned int ClientID;
template<typename RDRCallbackSystem>
RDRCallbackSystem RDRCALLBACK(void* CallbackIndex, int CallbackValue) {
	return (*(RDRCallbackSystem**)CallbackIndex)[CallbackValue];
}
class RdrWeaponHost {
public:
	void RWH_START() {
		return RDRCALLBACK<void(__fastcall*)(void*)>(this, 11)(this);
	}
	void RWH_STOP() {
		return RDRCALLBACK<void(__fastcall*)(void*)>(this, 12)(this);
	}
};
class RdrItemHost {
public:
	RdrWeaponHost* RIH_GETWEAPON() {
		return (RdrWeaponHost*)((DWORD64)this + 0x28);
	}
};
class RdrClientHost {
public:
	ClientID RCH_CLIENT() {
		INT64 rc1 = *(INT64*)(INT64(this + 0x18));
		if (rc1 == 0x0) return 0;
		INT64 rc2 = *(INT64*)(INT64(rc1 + 0x68));
		if (rc2 == 0x0) return 0;
		INT64 rc3 = *(INT64*)(INT64(rc2 + 0x20));
		if (rc3 == 0x0) return 0;
		return *(ClientID*)(INT64(rc3 + 0x170));
	}
	INT RCH_GETCLIENTID() {
		return *(ClientID*)((DWORD64)this + 0x20);
	}
	INT RCH_GETHEALTH() {
		return RDRCALLBACK<INT(__fastcall*)(void*)>(this, 27)(this);
	}
	BOOL RCH_GETDEATH() {
		return RCH_GETHEALTH() <= 0;
	}
	INT RCH_GETTEAM() {
		return *(INT*)((DWORD64)this + 992);
	}
	RdrItemHost* RCH_GETITEM(bool weapon = false) {
		return RDRCALLBACK< RdrItemHost* (__fastcall*)(void*, bool)>(this, 57)(this, weapon);
	}

};
class RdrClientSystemHost {
public:
	RdrClientHost* RCSH_GETCLIENT(INT ClientID) {
		return RDRCALLBACK< RdrClientHost* (__fastcall*)(void*, INT)>(this, 15)(this, ClientID);
	}
};
class RdrFrameHost {
public:
	struct RdrRenderHost {
		struct RRH; struct RRSAVE; struct RRLOAD;
		virtual ~RdrRenderHost() {}
		virtual void OnPostUpdate(float render_float) = 0;
		virtual void OnSaveGame(RRSAVE* save) {}
		virtual void OnLoadGame(RRLOAD* load) {}
		virtual void OnLevelEnd(const char* rdr_char) {}
		virtual void OnActionEvent(const RRH& rrh_event) = 0;
		virtual void OnPreRender() = 0;
	};
	enum RdrRenderPriorityHost { RDR_RENDER_GAME = 1 };
public:

	void RFH_RENDER(RdrRenderHost* Rendering, const char* RenderingName,
		RdrRenderPriorityHost RenderingPriority) {
		return RDRCALLBACK<void(__fastcall*)(void*, RdrRenderHost*, const char*,
			RdrRenderPriorityHost)>(this, 108)(this, Rendering, RenderingName, RenderingPriority);
	}
	RdrClientHost* RFH_GETCLIENT() {
		RdrClientHost* nullptrclient = 0x0;
		BOOLEAN vClient = RDRCALLBACK<BOOLEAN(__fastcall*)(void*, RdrClientHost**)>(this, 142)(this, &nullptrclient);
		if (!vClient) nullptrclient = 0;
		return nullptrclient;
	}
	RdrClientSystemHost* RFH_GETCLIENTSYSTEM() {
		return RDRCALLBACK<RdrClientSystemHost* (__fastcall*)(void*)>(this, 25)(this);
	}
	RdrFrameHost* RFH_GAME() {
		return RDRCALLBACK< RdrFrameHost* (__fastcall*)(void*)>(this, 14)(this);
	}

};
class RdrEnviromentHost {
public:
	RdrFrameHost* REH_GAME() {
		return *(RdrFrameHost**)((__int64)this + 0xD0);
	}
	static RdrEnviromentHost* REH_STATIC() { return *reinterpret_cast<RdrEnviromentHost**>(0x141EF5480); }
};
class RdrCvarsHost {
public:
	void RCH_SCATTER(float Value) {
		*(float*)((DWORD64)this + 0x130) = Value;
	} 
};
class RdrRendering : public RdrFrameHost::RdrRenderHost{
public:
	RdrRendering(RdrFrameHost* RFH_RENDERING);
	~RdrRendering();
	void OnPreRender();
	void OnPostUpdate(float upd) {};
private:
	RdrFrameHost* global_frame;
	void OnSaveGame(RRSAVE* save){}
	void OnLoadGame(RRLOAD* load){}
	void OnLevelEnd(const char* rdr_char){}
	void OnActionEvent(const RRH& rrh_event){}
};