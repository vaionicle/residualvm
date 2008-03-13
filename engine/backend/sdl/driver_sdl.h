/* Residual - Virtual machine to run LucasArts' 3D adventure games
 * Copyright (C) 2003-2006 The ScummVM-Residual Team (www.scummvm.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * $URL$
 * $Id$
 *
 */

#ifndef BACKEND_DRIVER_SDL_H
#define BACKEND_DRIVER_SDL_H

#include "common/sys.h"
#include "common/vector3d.h"

#include "engine/color.h"
#include "engine/model.h"
#include "engine/colormap.h"
#include "engine/bitmap.h"
#include "engine/backend/driver.h"

#include <SDL.h>

// NOTE: This is not a complete driver, it needs to be subclassed
//       to provide rendering functionality.

class DriverSDL : public Driver {
public:
	DriverSDL() : _samplesPerSec(22050) { ; }
	virtual ~DriverSDL() { ; }

	char *getVideoDeviceName();

	const ControlDescriptor *listControls();
	int getNumControls();
	bool controlIsAxis(int num);
	float getControlAxis(int num);
	bool getControlState(int num);
	bool pollEvent(Event &event);
	uint32 getMillis();
	void delayMillis(uint msecs);
	void setTimerCallback();
	void clearTimerCallback();

	MutexRef createMutex();
	void lockMutex(MutexRef mutex);
	void unlockMutex(MutexRef mutex);
	void deleteMutex(MutexRef mutex);

	bool setSoundCallback(SoundProc proc, void *param);
	void clearSoundCallback();
	int getOutputSampleRate() const;

	void quit();

private:
	int _samplesPerSec;
};

#endif