/* Residual - A 3D game interpreter
 *
 * Residual is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
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
 */

#include "engines/myst3/directorysubentry.h"
#include "common/str.h"
#include "common/debug.h"
#include "common/file.h"
#include "common/memstream.h"

namespace Myst3 {

void DirectorySubEntry::readFromStream(Common::SeekableReadStream &inStream) {
	_offset = inStream.readUint32LE();
	_size = inStream.readUint32LE();
	_metadataSize = inStream.readUint16LE();
	_face = inStream.readByte();
	_type = inStream.readByte();

	if (_metadataSize == 0) return;

	if (_metadataSize == 2) {
		_spotItemData.u = inStream.readUint32LE();
		_spotItemData.v = inStream.readUint32LE();
	} else if (_metadataSize == 10) {
		_videoData.v1._coords[0] = inStream.readSint32LE() * 0.000001f;
		_videoData.v1._coords[1] = inStream.readSint32LE() * 0.000001f;
		_videoData.v1._coords[2] = inStream.readSint32LE() * 0.000001f;

		_videoData.v2._coords[0] = inStream.readSint32LE() * 0.000001f;
		_videoData.v2._coords[1] = inStream.readSint32LE() * 0.000001f;
		_videoData.v2._coords[2] = inStream.readSint32LE() * 0.000001f;

		_videoData.u = inStream.readSint32LE();
		_videoData.v = inStream.readSint32LE();
		_videoData.width = inStream.readSint32LE();
		_videoData.height = inStream.readSint32LE();
	} else {
		warning("Unknown metadata type");
		inStream.skip(_metadataSize * sizeof(uint32));
	}
}

void DirectorySubEntry::dump() {
	debug("offset : %x size: %d padding : %d face : %d type : %d", _offset, _size, _metadataSize, _face, _type);
}

void DirectorySubEntry::dumpToFile(Common::SeekableReadStream &inStream, uint16 index) {
	char fileName[255];
	
	switch (_type) {
		case 0:
		case 5:
			sprintf(fileName, "dump/%d-%d.jpg", index, _face);
			break;
		case 1:
			sprintf(fileName, "dump/%d-%d.mask", index, _face);
			break;
		case 8:
			sprintf(fileName, "dump/%d.bik", index);
			break;
		default:
			sprintf(fileName, "dump/%d-%d.%d", index, _face, _type);
			break;
	}
	
	
	debug("Extracted %s", fileName);
	
	Common::DumpFile outFile;
	outFile.open(fileName);
	
	inStream.seek(_offset);
	
	uint8 *buf = new uint8[_size];
	
	inStream.read(buf, _size);
	outFile.write(buf, _size);
	
	delete[] buf;
	
	outFile.close();
}

Common::MemoryReadStream *DirectorySubEntry::dumpToMemory(Common::SeekableReadStream &inStream) const {
	inStream.seek(_offset);
	return static_cast<Common::MemoryReadStream *>(inStream.readStream(_size));
}

} // end of namespace Myst3
