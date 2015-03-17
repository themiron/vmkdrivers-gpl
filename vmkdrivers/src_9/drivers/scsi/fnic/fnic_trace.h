/*
 * Copyright 2012 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * [Insert appropriate license here when releasing outside of Cisco]
 * $Id: fnic_trace.h 95328 2012-02-09 01:42:58Z hiralpat $
 */

#ifndef __FNIC_TRACE_H__
#define __FNIC_TRACE_H__

#define FNIC_ENTRY_SIZE_BYTES 64


extern unsigned int fnic_trace_max_pages;
extern int fnic_tracing_enabled;
extern unsigned int trace_max_pages;

typedef struct fnic_trace_dbg {
	int wr_idx;
	int rd_idx;
	unsigned long long *page_offset;
} fnic_trace_dbg_t;

typedef struct fnic_dbgfs {
	int buffer_len;
	char *buffer;
} fnic_dbgfs_t;

struct fnic_trace_data {
	u64 timestamp;
	u64 fnaddr;
	u32 host_no;
	u32 tag;
	u64 data[5];
} __attribute__((__packed__));

typedef struct fnic_trace_data fnic_trace_data_t;

#define FNIC_TRACE_ENTRY_SIZE \
		  (FNIC_ENTRY_SIZE_BYTES - sizeof(fnic_trace_data_t))

#define FNIC_TRACE(_fn, _hn, _t, _a, _b, _c, _d, _e)           \
	if (unlikely(fnic_tracing_enabled)) {                   \
		fnic_trace_data_t *trace_buf = fnic_trace_get_buf(); \
		if (trace_buf) { \
			trace_buf->timestamp = jiffies; \
			trace_buf->fnaddr = _fn; \
			trace_buf->host_no = _hn; \
			trace_buf->tag = _t; \
			trace_buf->data[0] = _a; \
			trace_buf->data[1] = _b; \
			trace_buf->data[2] = _c; \
			trace_buf->data[3] = _d; \
			trace_buf->data[4] = _e; \
		} \
	}

fnic_trace_data_t *fnic_trace_get_buf(void);
int fnic_get_trace_data(fnic_dbgfs_t *);
int fnic_trace_buf_init(void);
void fnic_trace_free(void);

#endif