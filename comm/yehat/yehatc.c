/* Copyright Paul Reiche, Fred Ford. 1992-2002 */

// 0 "WON_LAST_BATTLE" setContext
// 0 "YEHAT_CIVIL_WAR" setContext
// 0 "GLOBAL_FLAGS_AND_DATA_7" setContext
// 0 "YEHAT_HOME_VISITS" setContext
// 0 "YEHAT_VISITS" setContext
// "-" "player_said" setContext
// 0 "YEHAT_ROYALIST_INFO" setContext
// 0 "YEHAT_ROYALIST_TOLD_PKUNK" setContext
// 0 "PKUNK_VISITS" setContext
// 0 "PKUNK_HOME_VISITS" setContext
// 0 "NO_YEHAT_INFO" setContext
// 0 "NO_YEHAT_HELP_HOME" setContext
// 0 "NO_YEHAT_ALLY_HOME" setContext
// 0 "YEHAT_REBEL_INFO" setContext
// 0 "NO_YEHAT_HELP_SPACE" setContext
// 0 "NO_YEHAT_ALLY_SPACE" setContext
// 0 "SHOFIXTI_VISITS" setContext
// 0 "YEHAT_REBEL_TOLD_PKUNK" setContext
// 0 "HAVE_SHOFIXTI_ESCORT_SHIP" setContext
// 0 "YEHAT_REBEL_VISITS" setContext

// "Intro" goto

// nop #peace
// "PEACE" emit exit
//

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "../commall.h"
#include "resinst.h"
#include "strings.h"

#include "uqm/lua/luacomm.h"
#include "uqm/build.h"
#include "uqm/gameev.h"
#include "libs/mathlib.h"

static LOCDATA yehat_desc =
		{
				NULL,							/* init_encounter_func */
				NULL,							/* post_encounter_func */
				NULL,							/* uninit_encounter_func */
				YEHAT_PMAP_ANIM,	/* AlienFrame */
				YEHAT_FONT,				/* AlienFont */
				WHITE_COLOR_INIT, /* AlienTextFColor */
				BLACK_COLOR_INIT, /* AlienTextBColor */
				{0, 0},						/* AlienTextBaseline */
				0,
				/* (SIS_TEXT_WIDTH - 16) * 2 / 3, */ /* AlienTextWidth */
				ALIGN_CENTER,												 /* AlienTextAlign */
				VALIGN_MIDDLE,											 /* AlienTextValign */
				YEHAT_COLOR_MAP,										 /* AlienColorMap */
				YEHAT_MUSIC,												 /* AlienSong */
				NULL_RESOURCE,											 /* AlienAltSong */
				0,																	 /* AlienSongFlags */
				YEHAT_CONVERSATION_PHRASES,					 /* PlayerPhrases */
				15,																	 /* NumAnimations */
				{
						/* AlienAmbientArray (ambient animations) */
						{
								/* right hand-wing tapping keyboard; front guy */
								4,												/* StartIndex */
								3,												/* NumFrames */
								YOYO_ANIM | WAIT_TALKING, /* AnimFlags */
								ONE_SECOND / 10,
								ONE_SECOND / 10, /* FrameRate */
								ONE_SECOND / 4,
								ONE_SECOND / 2, /* RestartRate */
								(1 << 6) | (1 << 7),
						},
						{
								/* left hand-wing tapping keyboard; front guy */
								7,												/* StartIndex */
								3,												/* NumFrames */
								YOYO_ANIM | WAIT_TALKING, /* AnimFlags */
								ONE_SECOND / 10,
								ONE_SECOND / 10, /* FrameRate */
								ONE_SECOND / 4,
								ONE_SECOND / 2, /* RestartRate */
								(1 << 6) | (1 << 7),
						},
						{
								10,				 /* StartIndex */
								3,				 /* NumFrames */
								YOYO_ANIM, /* AnimFlags */
								ONE_SECOND / 20,
								0, /* FrameRate */
								ONE_SECOND,
								ONE_SECOND * 3, /* RestartRate */
								(1 << 4) | (1 << 14),
						},
						{
								13,				 /* StartIndex */
								3,				 /* NumFrames */
								YOYO_ANIM, /* AnimFlags */
								ONE_SECOND / 20,
								0, /* FrameRate */
								ONE_SECOND,
								ONE_SECOND * 3, /* RestartRate */
								(1 << 5),
						},
						{
								16,				 /* StartIndex */
								5,				 /* NumFrames */
								YOYO_ANIM, /* AnimFlags */
								ONE_SECOND / 15,
								ONE_SECOND / 15, /* FrameRate */
								ONE_SECOND * 6,
								ONE_SECOND * 3, /* RestartRate */
								(1 << 2) | (1 << 14),
						},
						{
								21,				 /* StartIndex */
								5,				 /* NumFrames */
								YOYO_ANIM, /* AnimFlags */
								ONE_SECOND / 15,
								ONE_SECOND / 15, /* FrameRate */
								ONE_SECOND * 6,
								ONE_SECOND * 3, /* RestartRate */
								(1 << 3),
						},
						{
								/* right arm-wing rising; front guy */
								26,												/* StartIndex */
								2,												/* NumFrames */
								YOYO_ANIM | WAIT_TALKING, /* AnimFlags */
								ONE_SECOND / 15,
								ONE_SECOND / 15, /* FrameRate */
								ONE_SECOND * 6,
								ONE_SECOND * 3, /* RestartRate */
								(1 << 0) | (1 << 1),
						},
						{
								/* left arm-wing rising; front guy */
								28,												/* StartIndex */
								2,												/* NumFrames */
								YOYO_ANIM | WAIT_TALKING, /* AnimFlags */
								ONE_SECOND / 15,
								ONE_SECOND / 15, /* FrameRate */
								ONE_SECOND * 6,
								ONE_SECOND * 3, /* RestartRate */
								(1 << 0) | (1 << 1),
						},
						{
								30,																/* StartIndex */
								3,																/* NumFrames */
								YOYO_ANIM,												/* AnimFlags */
								ONE_SECOND / 30, ONE_SECOND / 30, /* FrameRate */
								ONE_SECOND / 30, ONE_SECOND / 30, /* RestartRate */
								0,																/* BlockMask */
						},
						{
								33,																/* StartIndex */
								3,																/* NumFrames */
								YOYO_ANIM,												/* AnimFlags */
								ONE_SECOND / 30, ONE_SECOND / 30, /* FrameRate */
								ONE_SECOND / 30, ONE_SECOND / 30, /* RestartRate */
								0,																/* BlockMask */
						},
						{
								36,																/* StartIndex */
								3,																/* NumFrames */
								YOYO_ANIM,												/* AnimFlags */
								ONE_SECOND / 30, ONE_SECOND / 30, /* FrameRate */
								ONE_SECOND / 30, ONE_SECOND / 30, /* RestartRate */
								0,																/* BlockMask */
						},
						{
								39,																/* StartIndex */
								3,																/* NumFrames */
								YOYO_ANIM,												/* AnimFlags */
								ONE_SECOND / 30, ONE_SECOND / 30, /* FrameRate */
								ONE_SECOND / 30, ONE_SECOND / 30, /* RestartRate */
								0,																/* BlockMask */
						},
						{
								42,																/* StartIndex */
								3,																/* NumFrames */
								YOYO_ANIM,												/* AnimFlags */
								ONE_SECOND / 30, ONE_SECOND / 30, /* FrameRate */
								ONE_SECOND / 30, ONE_SECOND / 30, /* RestartRate */
								0,																/* BlockMask */
						},
						{
								45,																/* StartIndex */
								3,																/* NumFrames */
								YOYO_ANIM,												/* AnimFlags */
								ONE_SECOND / 30, ONE_SECOND / 30, /* FrameRate */
								ONE_SECOND / 30, ONE_SECOND / 30, /* RestartRate */
								0,																/* BlockMask */
						},
						{
								48,												/* StartIndex */
								4,												/* NumFrames */
								YOYO_ANIM | WAIT_TALKING, /* AnimFlags */
								ONE_SECOND / 30,
								0, /* FrameRate */
								ONE_SECOND,
								ONE_SECOND * 3, /* RestartRate */
								(1 << 2) | (1 << 4),
						},
				},
				{
						/* AlienTransitionDesc - empty */
						0,		/* StartIndex */
						0,		/* NumFrames */
						0,		/* AnimFlags */
						0, 0, /* FrameRate */
						0, 0, /* RestartRate */
						0,		/* BlockMask */
				},
				{
						/* AlienTalkDesc */
						1,									/* StartIndex */
						3,									/* NumFrames */
						0,									/* AnimFlags */
						ONE_SECOND / 15, 0, /* FrameRate */
						ONE_SECOND / 12, 0, /* RestartRate */
						0,									/* BlockMask */
				},
				NULL, /* AlienNumberSpeech - none */
				/* Filler for loaded resources */
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
};

static void
ExitConversation(RESPONSE_REF R)																 // nop #ExitConversation
{																																 //
	setSegue(Segue_hostile);																			 // "hostile" "segue" setContext
																																 //
	if (PLAYER_SAID(R, bye_homeworld))														 // "player_said" getContext "bye_homeworld" eq jgz
	{																															 // {
		NPCPhrase(GOODBYE_AND_DIE_HOMEWORLD);												 // "GOODBYE_AND_DIE_HOMEWORLD" emit
	}																															 // }
	else if (PLAYER_SAID(R, bye_royalist))												 // "player_said" getContext "bye_royalist" eq jgz
	{																															 // {
		NPCPhrase(GOODBYE_AND_DIE_ROYALIST);												 // "GOODBYE_AND_DIE_ROYALIST" emit
	}																															 // }
	else if (PLAYER_SAID(R, i_demand_you_ally_homeworld))					 // "player_said" getContext "i_demand_you_ally_homeworld" eq jgz
	{																															 // {
		NPCPhrase(ENEMY_MUST_DIE);																	 // "ENEMY_MUST_DIE" emit
																																 //
		SET_GAME_STATE(NO_YEHAT_ALLY_HOME, 1);											 // 1 "NO_YEHAT_ALLY_HOME" setContext
	}																															 // }
	else if (PLAYER_SAID(R, bye_space))														 // "player_said" getContext "bye_space" eq jgz
	{																															 // {
		if ((BYTE)TFB_Random() & 1)																	 // 2 randInt dup 1 eq jgz
		{																														 // {
			NPCPhrase(GOODBYE_AND_DIE_SPACE);													 // "GOODBYE_AND_DIE_SPACE" emit
		}																														 // }
		else																												 // jz
		{																														 // {
			NPCPhrase(GO_IN_PEACE);																		 // "GO_IN_PEACE" emit
																																 //
			setSegue(Segue_peace);																		 // "peace" "segue" setContext
		}																														 // }
	}																															 // }
	else if (PLAYER_SAID(R, not_here) || PLAYER_SAID(R, not_send)) // "player_said" getContext "not_here" eq "player_said" getContext "not_send" eq or jgz
	{																															 // {
		switch (GET_GAME_STATE(YEHAT_REBEL_VISITS))									 //
		{																														 // "YEHAT_REBEL_VISITS" getContext
		case 0:																											 // dup 0 eq jgz {
			NPCPhrase(JUST_A_TRICK_1);																 // "JUST_A_TRICK_1" emit "YEHAT_REBEL_VISITS" getContext 1 + "YEHAT_REBEL_VISITS" setContext
			break;																										 // }
		case 1:																											 // jgz {
			NPCPhrase(JUST_A_TRICK_2);																 // "JUST_A_TRICK_2" emit
			break;																										 // }
		}																														 //
		SET_GAME_STATE(YEHAT_REBEL_VISITS, 1);											 //
	}																															 // }
	else if (PLAYER_SAID(R, ok_send))															 // "player_said" getContext "ok_send" eq jgz
	{																															 // {
		NPCPhrase(WE_REVOLT);																				 // "WE_REVOLT" emit
																																 //
		setSegue(Segue_peace);																			 // "peace" "segue" setContext
		SET_GAME_STATE(YEHAT_CIVIL_WAR, 1);													 // 1 "YEHAT_CIVIL_WAR" setContext
		SET_GAME_STATE(YEHAT_VISITS, 0);														 //	0 "YEHAT_VISITS" setContext
		SET_GAME_STATE(YEHAT_HOME_VISITS, 0);												 // 0 "YEHAT_HOME_VISITS" setContext
		SET_GAME_STATE(YEHAT_REBEL_VISITS, 0);											 // 0 "YEHAT_REBEL_VISITS" setContext
		SET_GAME_STATE(YEHAT_REBEL_INFO, 0);												 // 0 "YEHAT_REBEL_INFO" setContext
		SET_GAME_STATE(YEHAT_REBEL_TOLD_PKUNK, 0);									 // 0 "YEHAT_REBEL_TOLD_PKUNK" setContext
		SET_GAME_STATE(NO_YEHAT_INFO, 0);														 // 0 "NO_YEHAT_INFO" setContext
																																 //
		AddEvent(RELATIVE_EVENT, 0, 0, 0, YEHAT_REBEL_EVENT);				 /* ???????? */
	}																															 // }
} // getResponse goto exit

static void
Royalists(RESPONSE_REF R)															// nop #Royalists
{																											//
	if (PLAYER_SAID(R, how_is_rebellion))								// "player_said" getContext "how_is_rebellion" eq jgz
	{																										// {
		BYTE NumVisits;																		//
																											//
		NumVisits = GET_GAME_STATE(YEHAT_ROYALIST_INFO);	// "YEHAT_ROYALIST_INFO" getContext
		switch (NumVisits++)															//
		{																									//
		case 0:																						// dup 0 eq jgz {
			NPCPhrase(ROYALIST_REBELLION_1);								// "ROYALIST_REBELLION_1" emit "YEHAT_ROYALIST_INFO" getContext 1 + "YEHAT_ROYALIST_INFO" setContext
			break;																					// }
		case 1:																						// 1 eq jgz {
			NPCPhrase(ROYALIST_REBELLION_2);								// "ROYALIST_REBELLION_2" emit
			--NumVisits;																		//
			break;																					// }
		}																									//
		SET_GAME_STATE(YEHAT_ROYALIST_INFO, NumVisits);		//
																											//
		DISABLE_PHRASE(how_is_rebellion);									// "how_is_rebellion" disableOption
	}																										// }
	else if (PLAYER_SAID(R, what_about_pkunk_royalist)) // "player_said" getContext "what_about_pkunk_royalist" eq jgz
	{																										// {
		if (GET_GAME_STATE(YEHAT_ABSORBED_PKUNK))					// "YEHAT_ABSORBED_PKUNK" getContext dup 1 eq jgz {
			NPCPhrase(PKUNK_ABSORBED_ROYALIST);							// "PKUNK_ABSORBED_ROYALIST" emit
		else																							// } 0 eq jgz {
			NPCPhrase(HATE_PKUNK_ROYALIST);									// "HATE_PKUNK_ROYALIST" emit }
																											//
		SET_GAME_STATE(YEHAT_ROYALIST_TOLD_PKUNK, 1);			// 1 "YEHAT_ROYALIST_TOLD_PKUNK" setContext
	}																										// }
	else if (PLAYER_SAID(R, sorry_about_revolution))		// "player_said" getContext "sorry_about_revolution" eq jgz
	{																										// {
		NPCPhrase(ALL_YOUR_FAULT);												// "ALL_YOUR_FAULT" emit
																											//
		SET_GAME_STATE(NO_YEHAT_INFO, 1);									// 1 "NO_YEHAT_INFO" setContext
	}																										// }
																											//
	if (PHRASE_ENABLED(how_is_rebellion))								// "how_is_rebellion" optionEnabled 1 eq jgz {
		Response(how_is_rebellion, Royalists);						// "how_is_rebellion" ppc 4 + { "how_is_rebellion" "player_said" setContext "Royalists" goto } response }
	if (!GET_GAME_STATE(YEHAT_ROYALIST_TOLD_PKUNK)			// "YEHAT_ROYALIST_TOLD_PKUNK" getContext not
			&& GET_GAME_STATE(PKUNK_VISITS)									// "PKUNK_VISITS" getContext and
			&& GET_GAME_STATE(PKUNK_HOME_VISITS))						// "PKUNK_HOME_VISITS" getContext and 1 eq jgz {
		Response(what_about_pkunk_royalist, Royalists);		// "what_about_pkunk_royalist" ppc 4 + { "what_about_pkunk_royalist" "player_said" setContext "Royalists" goto } response }
	if (!GET_GAME_STATE(NO_YEHAT_INFO))									// "NO_YEHAT_INFO" getContext not 1 eq jgz {
		Response(sorry_about_revolution, Royalists);			// "sorry_about_revolution" ppc 4 + { "sorry_about_revolution" "player_said" setContext "Royalists" goto } response }
	Response(bye_royalist, ExitConversation);						// "bye_royalist" ppc 4 + { "ExitConversation" goto } response
} // getResponse goto exit

static void
StartRevolt(RESPONSE_REF R)										 // nop #StartRevolt
{																							 //
	if (PLAYER_SAID(R, shofixti_alive_1))				 // "player_said" getContext "shofixti_alive_1" eq jgz
	{																						 // {
		NPCPhrase(SEND_HIM_OVER_1);								 // "SEND_HIM_OVER_1" emit
																							 //
		SET_GAME_STATE(YEHAT_REBEL_TOLD_PKUNK, 1); // 1 "YEHAT_REBEL_TOLD_PKUNK" setContext
	}																						 // }
	else if (PLAYER_SAID(R, shofixti_alive_2))	 //  "player_said" getContext "shofixti_alive_2" eq jgz
	{																						 // {
		NPCPhrase(SEND_HIM_OVER_2);								 // "SEND_HIM_OVER_2" emit
	}																						 // }
																							 //
	if (HaveEscortShip(SHOFIXTI_SHIP))					 // "HAVE_SHOFIXTI_ESCORT_SHIP" getContext 1 eq dup jgz
	{																						 // {
		Response(ok_send, ExitConversation);			 // "ok_send" ppc 4 + { "ok_send" "player_said" setContext "ExitConversation" goto } response
	}																						 // }
	else																				 //
	{																						 // jz {
		Response(not_here, ExitConversation);			 // "not_here" ppc 4 + { "not_here" "player_said" setContext "ExitConversation" goto } response
	}																						 // }
	Response(not_send, ExitConversation);				 // "not_send" ppc 4 + { "not_send" "player_said" setContext "ExitConversation" goto } response }
} // getResponse goto exit

static void
YehatHome(RESPONSE_REF R)																		 // nop #YehatHome
{																														 //
																														 //
	if (PLAYER_SAID(R, whats_up_homeworld))										 // "player_said" getContext "whats_up_homeworld" eq jgz
	{																													 // {
		BYTE NumVisits;																					 //
																														 //
		NumVisits = GET_GAME_STATE(YEHAT_ROYALIST_INFO);				 // "YEHAT_ROYALIST_INFO" getContext
		switch (NumVisits++)																		 //
		{																												 //
		case 0:																									 // dup 0 eq jgz {
			NPCPhrase(GENERAL_INFO_HOMEWORLD_1);									 // "GENERAL_INFO_HOMEWORLD_1" emit "YEHAT_ROYALIST_INFO" getContext 1 + "YEHAT_ROYALIST_INFO" setContext
			break;																								 // }
		case 1:																									 // 1 eq jgz {
			NPCPhrase(GENERAL_INFO_HOMEWORLD_2);									 // "GENERAL_INFO_HOMEWORLD_2" emit
			--NumVisits;																					 //
			break;																								 // }
		}																												 //
		SET_GAME_STATE(YEHAT_ROYALIST_INFO, NumVisits);					 //
																														 //
		DISABLE_PHRASE(whats_up_homeworld);											 // "whats_up_homeworld" disableOption
	}																													 // }
	else if (PLAYER_SAID(R, at_least_help_us_homeworld))			 // "player_said" getContext "at_least_help_us_homeworld" eq jgz
	{																													 // {
		NPCPhrase(NO_HELP_ENEMY);																 // "NO_HELP_ENEMY" emit
																														 //
		SET_GAME_STATE(NO_YEHAT_HELP_HOME, 1);									 // 1 "NO_YEHAT_HELP_HOME" setContext
	}																													 // }
	else if (PLAYER_SAID(R, give_info))												 // "player_said" getContext "give_info" eq jgz
	{																													 // {
		NPCPhrase(NO_INFO_FOR_ENEMY);														 // "NO_INFO_FOR_ENEMY" emit
																														 //
		SET_GAME_STATE(NO_YEHAT_INFO, 1);												 // 1 "NO_YEHAT_INFO" setContext
	}																													 // }
	else if (PLAYER_SAID(R, what_about_pkunk_royalist))				 // "player_said" getContext "what_about_pkunk_royalist" eq jgz
	{																													 // {
		if (GET_GAME_STATE(YEHAT_ABSORBED_PKUNK))								 // "YEHAT_ABSORBED_PKUNK" getContext 1 eq dup jgz
		{																												 // {
			NPCPhrase(PKUNK_ABSORBED_ROYALIST);										 // "PKUNK_ABSORBED_ROYALIST" emit
		}																												 // }
		else																										 // jz
		{																												 // {
			NPCPhrase(HATE_PKUNK_ROYALIST);												 // "HATE_PKUNK_ROYALIST" emit
		}																												 // }
																														 //
		SET_GAME_STATE(YEHAT_ROYALIST_TOLD_PKUNK, 1);						 // 1 "YEHAT_ROYALIST_TOLD_PKUNK" setContext
	}																													 // }
																														 //
	if (PHRASE_ENABLED(whats_up_homeworld))										 // "whats_up_homeworld" optionEnabled 1 eq jgz
	{																													 // {
		Response(whats_up_homeworld, YehatHome);								 // "whats_up_homeworld" ppc 4 + { "whats_up_homeworld" "player_said" setContext "YehatHome" goto } response
	}																													 // }
	if (!GET_GAME_STATE(YEHAT_ROYALIST_TOLD_PKUNK)						 // "YEHAT_ROYALIST_TOLD_PKUNK" getContext not
			&& GET_GAME_STATE(PKUNK_VISITS)												 // "PKUNK_VISITS" getContext and
			&& GET_GAME_STATE(PKUNK_HOME_VISITS))									 // "PKUNK_HOME_VISITS" getContext and 1 eq jgz
	{																													 // {
		Response(what_about_pkunk_royalist, YehatHome);					 // "what_about_pkunk_royalist" ppc 4 + { "what_about_pkunk_royalist" "player_said" setContext "YehatHome" goto } response
	}																													 // }
	if (!GET_GAME_STATE(NO_YEHAT_HELP_HOME))									 // "NO_YEHAT_HELP_HOME" getContext not 1 eq jgz
	{																													 // {
		Response(at_least_help_us_homeworld, YehatHome);				 // "at_least_help_us_homeworld" ppc 4 + { "at_least_help_us_homeworld" "player_said" setContext "YehatHome" goto } response
	}																													 // }
	if (!GET_GAME_STATE(NO_YEHAT_INFO))												 // "NO_YEHAT_INFO" getContext not 1 eq jgz
	{																													 // {
		Response(give_info, YehatHome);													 // "give_info" ppc 4 + { "give_info" "player_said" setContext "YehatHome" goto } response
	}																													 // }
	if (!GET_GAME_STATE(NO_YEHAT_ALLY_HOME))									 // "NO_YEHAT_ALLY_HOME" getContext not 1 eq jgz
	{																													 // {
		Response(i_demand_you_ally_homeworld, ExitConversation); // "i_demand_you_ally_homeworld" ppc 4 + { "i_demand_you_ally_homeworld" "player_said" setContext "ExitConversation" goto } response
	}																													 // }
	Response(bye_homeworld, ExitConversation);								 // "bye_homeworld" ppc 4 + { "bye_homeworld" "player_said" setContext "ExitConversation" goto } response }
} // getResponse goto exit

static void
YehatSpace(RESPONSE_REF R)								 // nop #YehatSpace
{																					 //
	BYTE i, LastStack;											 //
	RESPONSE_REF pStr[3];										 //
																					 //
	LastStack = 0;													 //
	pStr[0] = pStr[1] = pStr[2] = 0;				 //
	if (PLAYER_SAID(R, whats_up_space_1)		 // "player_said" getContext "whats_up_space_1" eq
			|| PLAYER_SAID(R, whats_up_space_2)	 // "player_said" getContext "whats_up_space_2" eq or
			|| PLAYER_SAID(R, whats_up_space_3)	 // "player_said" getContext "whats_up_space_3" eq or
			|| PLAYER_SAID(R, whats_up_space_4)) // "player_said" getContext "whats_up_space_4" eq or jgz
	{																				 // {
		BYTE NumVisits;

		NumVisits = GET_GAME_STATE(YEHAT_REBEL_INFO);			// "YEHAT_REBEL_INFO" getContext
		switch (NumVisits++)															//
		{																									//
		case 0:																						// dup 0 eq jgz {
			NPCPhrase(GENERAL_INFO_SPACE_1);								// "GENERAL_INFO_SPACE_1" emit "YEHAT_REBEL_INFO" getContext 1 + "YEHAT_REBEL_INFO" setContext
			break;																					// }
		case 1:																						// dup 1 eq jgz {
			NPCPhrase(GENERAL_INFO_SPACE_2);								// "GENERAL_INFO_SPACE_2" emit "YEHAT_REBEL_INFO" getContext 1 + "YEHAT_REBEL_INFO" setContext
			break;																					// }
		case 2:																						// dup 2 eq jgz {
			NPCPhrase(GENERAL_INFO_SPACE_3);								// "GENERAL_INFO_SPACE_3" emit "YEHAT_REBEL_INFO" getContext 1 + "YEHAT_REBEL_INFO" setContext
			break;																					// }
		case 3:																						// 3 eq jgz {
			NPCPhrase(GENERAL_INFO_SPACE_4);								// "GENERAL_INFO_SPACE_4" emit
			--NumVisits;																		//
			break;																					// }
		}																									//
		SET_GAME_STATE(YEHAT_REBEL_INFO, NumVisits);			//
																											//
		DISABLE_PHRASE(whats_up_space_1);									// "whats_up_space_1" disableOption "whats_up_space_2" disableOption "whats_up_space_3" disableOption "whats_up_space_4" disableOption
	}																										// }
	else if (PLAYER_SAID(R, i_demand_you_ally_space))		// "player_said" getContext "i_demand_you_ally_space" eq jgz
	{																										// {
		NPCPhrase(WE_CANNOT_1);														// "WE_CANNOT_1" emit
																											//
		LastStack = 2;																		//
		SET_GAME_STATE(NO_YEHAT_ALLY_SPACE, 1);						// 1 "NO_YEHAT_ALLY_SPACE" setContext
	}																										// }
	else if (PLAYER_SAID(R, obligation))								// "player_said" getContext "obligation" eq jgz
	{																										// {
		NPCPhrase(WE_CANNOT_2);														// "WE_CANNOT_2" emit
																											//
		setSegue(Segue_peace);														// "peace" "segue" setContext
		SET_GAME_STATE(NO_YEHAT_ALLY_SPACE, 2);						// 2 "NO_YEHAT_ALLY_SPACE" setContext
																											//
		return;																						/* ??? */
	}																										// }
	else if (PLAYER_SAID(R, at_least_help_us_space))		// "player_said" getContext "at_least_help_us_space" eq jgz
	{																										// {
		NPCPhrase(SORRY_CANNOT);													// "SORRY_CANNOT" emit
																											//
		LastStack = 1;																		//
		SET_GAME_STATE(NO_YEHAT_HELP_SPACE, 1);						// 1 "NO_YEHAT_HELP_SPACE" setContext
	}																										// }
	else if (PLAYER_SAID(R, dishonor))									// "player_said" getContext "dishonor" eq jgz
	{																										// {
		NPCPhrase(HERES_A_HINT);													// "HERES_A_HINT" emit
																											//
		SET_GAME_STATE(NO_YEHAT_HELP_SPACE, 2);						// 2 "NO_YEHAT_HELP_SPACE" setContext
	}																										// }
	else if (PLAYER_SAID(R, what_about_pkunk_royalist)) // "player_said" getContext "what_about_pkunk_royalist" eq jgz
	{																										// {
		if (GET_GAME_STATE(YEHAT_ABSORBED_PKUNK))					// "YEHAT_ABSORBED_PKUNK" getContext dup jgz
		{																									// {
			NPCPhrase(PKUNK_ABSORBED_ROYALIST);							// "iPKUNK_ABSORBED_ROYALIST" emit
		}																									// }
		else																							// jz
		{																									// {
			NPCPhrase(HATE_PKUNK_ROYALIST);									// "HATE_PKUNK_ROYALIST" emit
		}																									// }
		SET_GAME_STATE(YEHAT_ROYALIST_TOLD_PKUNK, 1);			// 1 "YEHAT_ROYALIST_TOLD_PKUNK" setContext
	}																										// }
																											//
	/* SET_FUNCPTR (&PtrDesc, YehatSpace); */						//
	if (PHRASE_ENABLED(whats_up_space_1))								// "whats_up_space_1" optionEnabled 1 eq jgz
	{																										// {
		switch (GET_GAME_STATE(YEHAT_REBEL_INFO))					// "YEHAT_REBEL_INFO" getContext
		{																									//
		case 0:																						// dup 0 eq jgz {
			pStr[0] = whats_up_space_1;											// "whats_up_space_1" ppc 4 + { "whats_up_space_1" "player_said" setContext "YehatSpace" goto } response
			break;																					// }
		case 1:																						// dup 1 eq jgz {
			pStr[0] = whats_up_space_2;											// "whats_up_space_2" ppc 4 + { "whats_up_space_2" "player_said" setContext "YehatSpace" goto } response
			break;																					// }
		case 2:																						// dup 2 eq jgz {
			pStr[0] = whats_up_space_3;											// "whats_up_space_3" ppc 4 + { "whats_up_space_3" "player_said" setContext "YehatSpace" goto } response
			break;																					// }
		case 3:																						// 3 eq jgz {
			pStr[0] = whats_up_space_4;											// "whats_up_space_4" ppc 4 + { "whats_up_space_4" "player_said" setContext "YehatSpace" goto } response
			break;																					// }
		}																									//
	}																										// }
	switch (GET_GAME_STATE(NO_YEHAT_HELP_SPACE))				// "NO_YEHAT_HELP_SPACE" getContext
	{																										//
	case 0:																							// dup 0 eq jgz {
		pStr[1] = at_least_help_us_space;									// "at_least_help_us_space" ppc 4 + { "at_least_help_us_space" "player_said" setContext "YehatSpace" goto } response
		break;																						// }
	case 1:																							// 1 eq jgz {
		pStr[1] = dishonor;																// "dishonor" ppc 4 + { "dishonor" "player_said" setContext "YehatSpace" goto } response
		break;																						// }
	}																										//
	switch (GET_GAME_STATE(NO_YEHAT_ALLY_SPACE))				// "NO_YEHAT_ALLY_SPACE" getContext
	{																										//
	case 0:																							// dup 0 eq jgz
	{																										// {
		pStr[2] = i_demand_you_ally_space;								// "i_demand_you_ally_space" ppc 4 + { "i_demand_you_ally_space" "player_said" setContext "YehatSpace" goto } response
		break;																						//
	}																										// }
	case 1:																							// 1 eq jgz {
		pStr[2] = obligation;															// "obligation" ppc 4 + { "obligation" "player_said" setContext "YehatSpace" goto } response
		break;																						// }
	}																										//
																											//
	if (pStr[LastStack])																//
		Response(pStr[LastStack], YehatSpace);						//
	for (i = 0; i < 3; ++i)															//
	{																										//
		if (i != LastStack && pStr[i])										//
			Response(pStr[i], YehatSpace);									//
																											//
	}																										//
																											//
	if (!GET_GAME_STATE(YEHAT_ROYALIST_TOLD_PKUNK)			// "YEHAT_ROYALIST_TOLD_PKUNK" getContext not
			&& GET_GAME_STATE(PKUNK_VISITS)									//  "PKUNK_VISITS" getContext and
			&& GET_GAME_STATE(PKUNK_HOME_VISITS))						// "PKUNK_HOME_VISITS" getContext and 1 eq jgz
	{																										// {
		Response(what_about_pkunk_royalist, YehatSpace);	// "what_about_pkunk_royalist" ppc 4 + { "what_about_pkunk_royalist" "player_said" setContext "YehatSpace" goto } response
	}																										// }
	if (GET_GAME_STATE(SHOFIXTI_VISITS))								// "SHOFIXTI_VISITS" getContext jgz
	{																										// {
		switch (GET_GAME_STATE(YEHAT_REBEL_TOLD_PKUNK))		// "YEHAT_REBEL_TOLD_PKUNK" getContext
		{																									//
		case 0:																						// dup 0 eq jgz {
			Response(shofixti_alive_1, StartRevolt);				// "shofixti_alive_1" ppc 4 + { "shofixti_alive_1" "player_said" setContext "StartRevolt" goto } response
			break;																					// }
		case 1:																						// 1 eq jgz {
			Response(shofixti_alive_2, StartRevolt);				// "shofixti_alive_2" ppc 4 + { "shofixti_alive_2" "player_said" setContext "StartRevolt" goto } response
			break;																					// }
		}																									//
	}																										// }
	Response(bye_space, ExitConversation);							// "bye_space" ppc 4 + { "bye_space" "player_said" setContext "ExitConversation" goto } response }
} // getResponse goto exit

static void
Intro(void)																									 // nop #Intro
{																														 //
	BYTE NumVisits;																						 //
																														 //
	if (LOBYTE(GLOBAL(CurrentActivity)) == WON_LAST_BATTLE)		 // "WON_LAST_BATTLE" getContext 1 eq jgz
	{																													 // {
		NPCPhrase(OUT_TAKES);																		 // "OUT_TAKES" emit
																														 //
		setSegue(Segue_peace);																	 //
		return;																									 // "peace" goto
	}																													 // }
																														 //
	if (GET_GAME_STATE(YEHAT_CIVIL_WAR))											 // "YEHAT_CIVIL_WAR" getContext dup 1 eq jgz
	{																													 // {
		if (GET_GAME_STATE(GLOBAL_FLAGS_AND_DATA) & (1 << 7))		 // "GLOBAL_FLAGS_AND_DATA_7" getContext dup 1 eq jgz
		{																												 // {
			NumVisits = GET_GAME_STATE(YEHAT_HOME_VISITS);				 // "YEHAT_HOME_VISITS" getContext
			switch (NumVisits++)																	 //
			{																											 //
			case 0:																								 // dup 0 eq jgz {
				NPCPhrase(ROYALIST_HOMEWORLD_HELLO_1);							 // "ROYALIST_HOMEWORLD_HELLO_1" emit "YEHAT_HOME_VISITS" getContext 1 + "YEHAT_HOME_VISITS" setContext
				break;																							 // }
			case 1:																								 // 1 eq jgz {
				NPCPhrase(ROYALIST_HOMEWORLD_HELLO_2);							 // "ROYALIST_HOMEWORLD_HELLO_2" emit
				--NumVisits;																				 //
				break;																							 // }
			}																											 //
			SET_GAME_STATE(YEHAT_HOME_VISITS, NumVisits);					 //
		}																												 // }
		else																										 // 0 eq jgz
		{																												 // {
			NumVisits = GET_GAME_STATE(YEHAT_VISITS);							 // "YEHAT_VISITS" getContext
			switch (NumVisits++)																	 //
			{																											 //
			case 0:																								 // dup 0 eq jgz {
				NPCPhrase(ROYALIST_SPACE_HELLO_1);									 // "ROYALIST_SPACE_HELLO_1" emit  "YEHAT_VISITS" getContext 1 + "YEHAT_VISITS" setContext
				break;																							 // }
			case 1:																								 // 1 eq jgz {
				NPCPhrase(ROYALIST_SPACE_HELLO_2);									 // "ROYALIST_SPACE_HELLO_2" emit
				--NumVisits;																				 //
				break;																							 // }
			}																											 //
			SET_GAME_STATE(YEHAT_VISITS, NumVisits);							 //
		}																												 // }
																														 //
		Royalists((RESPONSE_REF)0);															 // "Royalists" goto
	}																													 // }
	else if (GET_GAME_STATE(GLOBAL_FLAGS_AND_DATA) & (1 << 7)) // 0 eq "GLOBAL_FLAGS_AND_DATA_7" getContext and dup 1 eq jgz
	{																													 // {
		NumVisits = GET_GAME_STATE(YEHAT_HOME_VISITS);					 // "YEHAT_HOME_VISITS" getContext
		switch (NumVisits++)																		 //
		{																												 //
		case 0:																									 // dup 0 eq jgz {
			NPCPhrase(HOMEWORLD_HELLO_1);													 // "HOMEWORLD_HELLO_1" emit "YEHAT_HOME_VISITS" getContext 1 + "YEHAT_HOME_VISITS" setContext
			break;																								 // }
		case 1:																									 // 1 eq jgz {
			NPCPhrase(HOMEWORLD_HELLO_2);													 // "HOMEWORLD_HELLO_2" emit
			--NumVisits;																					 //
			break;																								 // }
		}																												 //
		SET_GAME_STATE(YEHAT_HOME_VISITS, NumVisits);						 //
																														 //
		YehatHome((RESPONSE_REF)0);															 // "YehatHome" goto
	}																													 // }
	else																											 // 0 eq jgz
	{																													 // {
		NumVisits = GET_GAME_STATE(YEHAT_VISITS);								 // "YEHAT_VISITS" getContext
		switch (NumVisits++)																		 //
		{																												 //
		case 0:																									 // dup 0 eq jgz {
			NPCPhrase(SPACE_HELLO_1);															 // "SPACE_HELLO_1" emit "YEHAT_VISITS" getContext 1 + "YEHAT_VISITS" setContext
			break;																								 // }
		case 1:																									 // dup 1 eq jgz {
			NPCPhrase(SPACE_HELLO_2);															 // "SPACE_HELLO_2" emit "YEHAT_VISITS" getContext 1 + "YEHAT_VISITS" setContext
			break;																								 // }
		case 2:																									 // dup 2 eq jgz {
			NPCPhrase(SPACE_HELLO_3);															 // "SPACE_HELLO_3" emit "YEHAT_VISITS" getContext 1 + "YEHAT_VISITS" setContext
			break;																								 // }
		case 3:																									 // 3 eq jgz {
			NPCPhrase(SPACE_HELLO_4);															 // "SPACE_HELLO_4" emit
			--NumVisits;																					 //
			break;																								 // }
		}																												 //
		SET_GAME_STATE(YEHAT_VISITS, NumVisits);								 //
																														 //
		YehatSpace((RESPONSE_REF)0);														 // "YehatSpace" goto
	}																													 // }
} // exit

static COUNT
uninit_yehat(void)
{
	luaUqm_comm_uninit();
	return (0);
}

static void
post_yehat_enc(void)
{
	/* nothing defined so far */
}

LOCDATA *
init_yehat_comm(void)
{
	LOCDATA *retval;

	yehat_desc.init_encounter_func = Intro;
	yehat_desc.post_encounter_func = post_yehat_enc;
	yehat_desc.uninit_encounter_func = uninit_yehat;

	luaUqm_comm_init(NULL, NULL_RESOURCE);
	/* Initialise Lua for string interpolation. This will be	generalised in the future. */

	yehat_desc.AlienTextBaseline.x = SIS_SCREEN_WIDTH * 2 / 3;
	yehat_desc.AlienTextBaseline.y = 60;
	yehat_desc.AlienTextWidth = (SIS_TEXT_WIDTH - 16) * 2 / 3;

	if (LOBYTE(GLOBAL(CurrentActivity)) != WON_LAST_BATTLE)
	{
		setSegue(Segue_hostile);
	}
	else
	{
		setSegue(Segue_peace);
	}
	retval = &yehat_desc;

	return (retval);
}
