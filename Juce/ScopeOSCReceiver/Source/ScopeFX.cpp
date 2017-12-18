/**
 * Wrapper class that hosts the ScopeSync object and its GUI
 * on behalf of the Scope (or Scope SDK) applications, using 
 * the ScopeFX SDK. This requires it to be derived from the Effect
 * class.
 *
 *
 *  (C) Copyright 2014 bcmodular (http://www.bcmodular.co.uk/)
 *
 * This file is part of ScopeOSC.
 *
 * ScopeOSC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * ScopeOSC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ScopeOSC.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *  Will Ellis
 */

#include "ScopeFX.h"

using namespace ScopeFXParameterDefinitions;

ScopeFX::ScopeFX() : Effect(&effectDescription)
{
	for (int i = 0; i < numParameters; i++)
		parameters.add(new BCMParameter("/" + String(i)));
}

ScopeFX::~ScopeFX()
{
}

int ScopeFX::async(PadData** asyncIn,  PadData* /*syncIn*/,
                   PadData*  asyncOut, PadData* /*syncOut*/)
{
	(void)asyncIn;

	Array<int> currentValues;
	for (int i = 0; i < numParameters; i++)
		currentValues.add(i, parameters[i]->getScopeIntValue());

	asyncOut[OUTPAD_PARAMS].itg = (int)malloc(4 * numParameters);
	memcpy((int*)asyncOut[OUTPAD_PARAMS].itg, currentValues.getRawDataPointer(), numParameters * 4);
	
	return -1;
}

int ScopeFX::syncBlock(PadData** /*asyncIn*/, PadData* /*syncIn*/,
                       PadData* /*asyncOut*/, PadData* /*syncOut*/, 
                       int /*off*/,
                       int /*cnt*/)
{
	return -1;
}

Effect *newEffect()
{
	return new ScopeFX();
};

void deleteEffect (Effect *eff)
{
   delete eff;
}

EffectDescription *descEffect ()
{
    return &effectDescription;
}

extern "C"
::uint32 ioctlEffect (
					  ::uint32  /* dwService */, ::uint32  /* dwDDB */, ::uint32  /* hDevice */,
					  void * /* lpvInBuffer */, ::uint32 /* cbInBuffer */, 
					  void * /* lpvOutBuffer */, ::uint32 /* cbOutBuffer */,
					  ::uint32 * lpcbBytesReturned )
{
   *lpcbBytesReturned = 0;
   return ERROR_NOT_SUPPORTED;
}