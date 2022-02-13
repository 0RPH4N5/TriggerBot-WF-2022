#include "wbw_class.h"
#include "wbw_intialize.h"

BOOL __stdcall DllMain(void* RdrMod, __int64 RdrReason, void*) {
	if (RdrEnviromentHost* RDREnviromnet = RdrEnviromentHost::REH_STATIC()) {
		if (RdrFrameHost* RDRFrame = RDREnviromnet->REH_GAME()->RFH_GAME()) {
			if (RdrReason == 1) RDRFrame->RFH_RENDER(new RdrRendering(RDRFrame), 0, RdrFrameHost::RdrRenderPriorityHost::RDR_RENDER_GAME);
		}
	}
	return true;
}