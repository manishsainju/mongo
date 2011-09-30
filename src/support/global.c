/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2008-2011 WiredTiger, Inc.
 *	All rights reserved.
 */

#include "wt_internal.h"

/*
 * __wt_library_init --
 *	Some things to do, before we do anything else.
 */
int
__wt_library_init(void)
{
#ifdef HAVE_DIAGNOSTIC
	/* Load debug code the compiler might optimize out. */
	WT_RET(__wt_breakpoint());
#endif

	return (0);
}

#ifdef HAVE_DIAGNOSTIC
/*
 * __wt_breakpoint --
 *	A simple place to put a breakpoint, if you need one.
 */
int
__wt_breakpoint(void)
{
	return (0);
}

int __wt_debugger_attach;

/*
 * __wt_attach --
 *	A routine to wait for the debugging to attach.
 */
void
__wt_attach(WT_SESSION_IMPL *session)
{
#ifdef HAVE_ATTACH
	/*
	 * Force a load of the session dump function, for gdb -- session will
	 * never be NULL, so this code never runs, but gcc doesn't know that.
	 */
	if (session == NULL)
		__wt_session_dump_all(session);

	__wt_errx(session, "process ID %" PRIdMAX
	    ": waiting for debugger...", (intmax_t)getpid());
	while (__wt_debugger_attach == 0)
		__wt_sleep(10, 0);
#else
	WT_UNUSED(session);
#endif
}
#endif
