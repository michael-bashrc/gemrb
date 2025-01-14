/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 */

#ifndef MUSIMPORTER_H
#define MUSIMPORTER_H

#include "MusicMgr.h"

#include "ResourceManager.h"
#include "Streams/FileStream.h"

#include <cstdio>

namespace GemRB {

/**MUS PlayList Importer
  *@author GemRB Development Team
  */

struct PLString {
	char PLFile[10]{};
	char PLLoop[10]{};
	char PLTag[10]{};
	char PLEnd[10]{};
	unsigned int soundID = 0;
};

class MUSImporter : public MusicMgr {
private:
	bool Initialized = false;
	bool Playing = false;
	char PLName[32]{};
	char PLNameNew[32]{};
	int PLpos = 0;
	int PLnext = -1;
	FileStream* str;
	std::vector< PLString> playlist;
	unsigned int lastSound = 0xffffffff;
	ResourceManager manager;
private:
	void PlayMusic(int pos);
	void PlayMusic(char* name);
public:
	MUSImporter();
	MUSImporter(const MUSImporter&) = delete;
	~MUSImporter() override;
	MUSImporter& operator=(const MUSImporter&) = delete;
	/** Loads a PlayList for playing */
	bool OpenPlaylist(const char* name) override;
	/** Initializes the PlayList Manager */
	bool Init() override;
	/** Switches the current PlayList while playing the current one */
	int SwitchPlayList(const char* name, bool Hard) override;
	/** Ends the Current PlayList Execution */
	void End() override;
	void HardEnd() override;
	/** Start the PlayList Music Execution */
	void Start() override;
	/** Plays the Next Entry */
	void PlayNext() override;
	/** Returns whether music is currently playing */
	bool IsPlaying() override { return Playing; }
	/** Returns whether given playlist is currently loaded */
	bool CurrentPlayList(const char* name) override;
};

}

#endif
