//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SOUND_H
#define AVL_SOUND_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"

namespace avl
{



	class PlaySoundFileBaseStateImpl
	{
	public:
		virtual ~PlaySoundFileBaseStateImpl() {}
	};

	struct PlaySoundFileState : public BaseState
	{
		PlaySoundFileState()
			: pImpl(NULL)
		{
		}

		~PlaySoundFileState()
		{
			delete pImpl;
		}

		PlaySoundFileBaseStateImpl* pImpl;

	private:
		PlaySoundFileState(const PlaySoundFileState&); //=delete
		PlaySoundFileState& operator=(const PlaySoundFileState&); //=delete
	};



	/// <summary>Plays specified audio file in WAV format.</summary>
	/// <param name="inFile">Sound file in WAV format.</param>
	/// <param name="inSynchronous">Plays sound in synchronous mode, waiting for the end of playback. Default value: False.</param>
	AVL_FUNCTION void PlaySoundFile
	(
		PlaySoundFileState&	ioState,
		const atl::File&	inFile,			
		bool				inSynchronous	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SOUND_H

