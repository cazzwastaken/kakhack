#include "../hooks.h"

/*
* -------------------------------------------------------
* |			Name					|		Value		|
* -------------------------------------------------------

"CSGO_Notice_Alert_Match_Point"				"MATCH POINT"
"CSGO_Notice_Alert_Final_Round"				"FINAL ROUND"
"CSGO_Notice_Alert_Last_Round_Half"			"LAST ROUND OF FIRST HALF"
"CSGO_Notice_Alert_Warmup_Period"			"WARMUP {s:time_remaining}"
"CSGO_Notice_Alert_Warmup_Period_Ending"	"WARMUP ENDING {s:time_remaining}"
"CSGO_Notice_Alert_Waiting_For_Players"		"WAITING FOR PLAYERS {s:time_remaining}"
"CSGO_Notice_Alert_Match_Starting_In"		"<span class=\"MatchStartAlert\">MATCH STARTING IN {s:time_remaining}...</span>"
"CSGO_Notice_Alert_Match_Starting"			"<span class=\"MatchStartAlert\">MATCH STARTING</span>"
"CSGO_Notice_Alert_Match_Restarting_In"		"<span class=\"MatchStartAlert\">MATCH RESTARTING IN {s:time_remaining}...</span>"
"CSGO_Notice_Alert_Match_Restarting"		"<span class=\"MatchStartAlert\">MATCH RESTARTING</span>"
"CSGO_Notice_Alert_Replaying"				"<span class=\"ReplayAlert\">DELAYED REPLAY {s:time_remaining}</span>"
"CSGO_Notice_Alert_Match_Start"				"MATCH START"
"CSGO_Notice_Alert_Timeout"					"{s:team_name} Timeout {s:time_remaining}"
"CSGO_Notice_Alert_Technical_Timeout"		"{s:team_name} Technical Timeout {s:time_remaining}"
"CSGO_Notice_Alert_Timeout_Multi"			"{s:team_name} Timeout {s:time_remaining}   ( {d:timeouts_remaining} / {d:timeouts_max} )"
"CSGO_Notice_Alert_Freeze_Pause"			"MATCH PAUSED"
*/

/*
* X-Ref: "AlertVisible"
* If you want to call this function, store the thisptr (or sig it)
* and call the original function with desired text
* P.S: Also supports HTML
*/

/*
* X-Ref: "HideFlash"
* This will point you to the function that hides the alert,
* you should probably use that :think:
*/

void __fastcall h::ShowAlert(void* thisptr, void* edx, const char* text, int mode)
{
	switch (fnv::Hash(text))
	{
	case fnv::HashConst("#CSGO_Notice_Alert_Match_Point"):
		return ShowAlertOriginal(thisptr, "<font color=\"#ff0000\"> MATCH POINT </font>", mode);

	case fnv::HashConst("#CSGO_Notice_Alert_Final_Round"):
		return ShowAlertOriginal(thisptr, "<font color=\"#ff0000\"> FINAL ROUND BABY </font>", mode);

	case fnv::HashConst("#CSGO_Notice_Alert_Last_Round_Half"):
		return ShowAlertOriginal(thisptr, "<font color=\"#ff0000\"> LAST ROUND OF FIRST HALF </font>", mode);

	case fnv::HashConst("#CSGO_Notice_Alert_Warmup_Period"):
		return ShowAlertOriginal(thisptr, "<font color=\"#9370db\"> WARMUP BABY {s:time_remaining} </font>", mode);

	case fnv::HashConst("#CSGO_Notice_Alert_Warmup_Period_Ending"):
		return ShowAlertOriginal(thisptr, "<font color=\"#9370db\"> WARMUP ENDING {s:time_remaining} </font>", mode);

	case fnv::HashConst("#CSGO_Notice_Alert_Match_Start"):
		return ShowAlertOriginal(thisptr, "<font color=\"#ff0000\"> BEGIN </font>", mode);

	case fnv::HashConst("#CSGO_Notice_Alert_Timeout"):
		return ShowAlertOriginal(thisptr, "{s:team_name}s are toggling {s:time_remaining}", mode);
	}

	ShowAlertOriginal(thisptr, text, mode);
}
