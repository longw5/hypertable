/**
 * Copyright (C) 2007 Doug Judd (Zvents, Inc.)
 * 
 * This file is part of Hypertable.
 * 
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or any later version.
 * 
 * Hypertable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Common/Error.h"

#include "AsyncComm/CommBuf.h"
#include "AsyncComm/Serialization.h"

#include "ResponseCallbackReaddir.h"

using namespace hypertable;
using namespace hypertable::DfsBroker;

int ResponseCallbackReaddir::response(std::vector<std::string> &listing) {
  hbuilder_.InitializeFromRequest(mEventPtr->header);
  uint32_t len = 8;
  for (size_t i=0; i<listing.size(); i++)
    len += Serialization::EncodedLengthString(listing[i]);
  CommBufPtr cbufPtr( new CommBuf(hbuilder_, len) );
  cbufPtr->AppendInt(Error::OK);
  cbufPtr->AppendInt(listing.size());
  for (size_t i=0; i<listing.size(); i++)
    cbufPtr->AppendString(listing[i]);
  return mComm->SendResponse(mEventPtr->addr, cbufPtr);
}
