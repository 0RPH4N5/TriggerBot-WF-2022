#pragma once
//Creator: 0RPH4N5
#include "wbw_class.h"
#define client_input ((SHORT(*)(int keyfound))0x1400A6290)
RdrRendering::RdrRendering(RdrFrameHost* RFH_GLOBAL) {
	this->global_frame = RFH_GLOBAL;
}
bool replace_team(RdrClientHost* mc_clientv1, RdrClientHost* mc_clientv2)
{
	return ((mc_clientv1->RCH_GETTEAM() != mc_clientv2->RCH_GETTEAM() || mc_clientv2->RCH_GETTEAM() == 0) && (mc_clientv2 != mc_clientv1));
}
RdrRendering::~RdrRendering(){}
void RdrRendering::OnPreRender() {
	if (RdrFrameHost* frame_host = *(RdrFrameHost**)0x14216ECA8) {
		if (RdrCvarsHost* cvars_host = *(RdrCvarsHost**)0x14216E020) {
			//cvars_host->RCH_SCATTER(999);
			if (client_input(0x02)) {
				if (RdrClientHost* client_host = frame_host->RFH_GETCLIENT()) {
					if (RdrItemHost* item_host = client_host->RCH_GETITEM()) {
						if (RdrWeaponHost* weapon_host = item_host->RIH_GETWEAPON()) {
							if (ClientID clientid = client_host->RCH_CLIENT()) {
								if (RdrClientHost* client_host_iterator = frame_host->RFH_GETCLIENTSYSTEM()->RCSH_GETCLIENT(clientid)) {
									if (!client_host_iterator->RCH_GETDEATH() && replace_team(client_host, client_host_iterator)) {
										weapon_host->RWH_START(),
											weapon_host->RWH_STOP();
									}
								}
							}
						}
					}
				}
			}
		}
		
	}
}