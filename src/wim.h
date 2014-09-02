#ifndef _WIM_H
#define _WIM_H

/*
 * Copyright (C) 2014 Michael Brown <mbrown@fensystems.co.uk>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/**
 * @file
 *
 * WIM format
 *
 * The file format is documented in the document "Windows Imaging File
 * Format (WIM)", available from
 * 
 *   http://www.microsoft.com/en-us/download/details.aspx?id=13096
 *
 * The wimlib source code is also a useful reference.
 *
 */

#include <stdint.h>

/** A WIM resource header */
struct wim_resource_header {
	/** Compressed length and flags */
	uint64_t zlen__flags;
	/** Offset */
	uint64_t offset;
	/** Uncompressed length */
	uint64_t len;
} __attribute__ (( packed ));

/** WIM resource header length mask */
#define WIM_RESHDR_ZLEN_MASK 0x00ffffffffffffffULL

/** WIM resource header flags */
enum wim_resource_header_flags {
	/** Resource contains metadata */
	WIM_RESHDR_METADATA = ( 0x02ULL << 56 ),
	/** Resource is compressed */
	WIM_RESHDR_COMPRESSED = ( 0x04ULL << 56 ),
	/** Resource is compressed using packed streams */
	WIM_RESHDR_PACKED_STREAMS = ( 0x10ULL << 56 ),
};

/** A WIM header */
struct wim_header {
	/** Signature */
	uint8_t signature[8];
	/** Header length */
	uint32_t header_len;
	/** Verson */
	uint32_t version;
	/** Flags */
	uint32_t flags;
	/** Chunk length */
	uint32_t chunk_len;
	/** GUID */
	uint8_t guid[16];
	/** Part number */
	uint16_t part;
	/** Total number of parts */
	uint16_t parts;
	/** Number of images */
	uint32_t images;
	/** Lookup table */
	struct wim_resource_header lookup;
	/** XML data */
	struct wim_resource_header xml;
	/** Boot metadata */
	struct wim_resource_header boot;
	/** Boot index */
	uint32_t boot_index;
	/** Integrity table */
	struct wim_resource_header integrity;
	/** Reserved */
	uint8_t reserved[60];
} __attribute__ (( packed ));;

/** A WIM lookup table entry */
struct wim_lookup_entry {
	/** Resource header */
	struct wim_resource_header resource;
	/** Part number */
	uint16_t part;
	/** Reference count */
	uint32_t refcnt;
	/** SHA-1 digest */
	uint8_t sha1[20];
} __attribute__ (( packed ));

#endif /* _WIM_H */