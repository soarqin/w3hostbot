#ifndef _GAMESLOT_H_
#define _GAMESLOT_H_

#include "common/Stream.h"

namespace HostBot
{
	//
	// GameSlot
	//

	class GameSlot
	{
	public:
		enum SlotStatus_t
		{
			SLOTSTATUS_OPEN	= 0,
			SLOTSTATUS_CLOSED = 1,
			SLOTSTATUS_OCCUPIED = 2
		};

		enum SlotRace_t
		{
			SLOTRACE_HUMAN = 1,
			SLOTRACE_ORC = 2,
			SLOTRACE_NIGHTELF = 4,
			SLOTRACE_UNDEAD = 8,
			SLOTRACE_RANDOM = 32,
			SLOTRACE_FIXED = 64
		};

		enum SlotComp_t
		{
			SLOTCOMP_EASY = 0,
			SLOTCOMP_NORMAL = 1,
			SLOTCOMP_HARD = 2
		};

		GameSlot( );
		GameSlot( std::vector<byte> &n );
		GameSlot( byte nPID, byte nDownloadStatus, byte nSlotStatus, byte nComputer, byte nTeam, byte nColor, byte nRace, byte nComputerType = 1, byte nHandicap = 100 );
		~GameSlot( );

		byte GetPID( )				{ return _PID; }
		byte GetDownloadStatus( )	{ return _DownloadStatus; }
		byte GetSlotStatus( )		{ return _SlotStatus; }
		byte GetComputer( )		{ return _Computer; }
		byte GetTeam( )			{ return _Team; }
		byte GetColor( )			{ return _Color; }
		byte GetRace( )			{ return _Race; }
		byte GetComputerType( )	{ return _ComputerType; }
		byte GetHandicap( )		{ return _Handicap; }

		void SetPID( byte nPID )							{ _PID = nPID; }
		void SetDownloadStatus( byte nDownloadStatus )		{ _DownloadStatus = nDownloadStatus; }
		void SetSlotStatus( byte nSlotStatus )				{ _SlotStatus = nSlotStatus; }
		void SetComputer( byte nComputer )					{ _Computer = nComputer; }
		void SetTeam( byte nTeam )							{ _Team = nTeam; }
		void SetColor( byte nColor )						{ _Color = nColor; }
		void SetRace( byte nRace )							{ _Race = nRace; }
		void SetComputerType( byte nComputerType )			{ _ComputerType = nComputerType; }
		void SetHandicap( byte nHandicap )					{ _Handicap = nHandicap; }

		std::vector<byte> GetArray( );
		void GetSlotData(Common::Stream& st);
	private:
		byte _PID;				// player id
		byte _DownloadStatus;		// download status (0% to 100%)
		byte _SlotStatus;			// slot status (0 = open, 1 = closed, 2 = occupied)
		byte _Computer;			// computer (0 = no, 1 = yes)
		byte _Team;				// team
		byte _Color;				// Color
		byte _Race;				// race (1 = human, 2 = orc, 4 = night elf, 8 = undead, 32 = random, 64 = fixed)
		byte _ComputerType;		// computer type (0 = easy, 1 = human or normal comp, 2 = hard comp)
		byte _Handicap;			// handicap
	};
}

#endif // _GAMESLOT_H_
