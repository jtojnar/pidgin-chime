/*
 * Pidgin/libpurple Chime client plugin
 *
 * Copyright © 2017 Amazon.com, Inc. or its affiliates.
 *
 * Author: David Woodhouse <dwmw2@infradead.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef __CHIME_CONTACT_H__
#define __CHIME_CONTACT_H__

#include <glib-object.h>
#include <json-glib/json-glib.h>

#include "chime-connection.h"

G_BEGIN_DECLS

#define CHIME_TYPE_CONTACT (chime_contact_get_type ())
G_DECLARE_FINAL_TYPE (ChimeContact, chime_contact, CHIME, CONTACT, GObject)

typedef enum {
	CHIME_AVAILABILITY_UNKNOWN = 0,
	CHIME_AVAILABILITY_OFFLINE,
	CHIME_AVAILABILITY_AVAILABLE,
	CHIME_AVAILABILITY_AWAY,
	CHIME_AVAILABILITY_BUSY,
	CHIME_AVAILABILITY_MOBILE,
	CHIME_AVAILABILITY_SIX,
	CHIME_AVAILABILITY_LAST
} ChimeAvailability;

ChimeContact *chime_connection_contact_by_email(ChimeConnection *cxn,
						const gchar *email);

/* Designed to match the NEW_CONTACT signal handler */
typedef void (*ChimeContactCB) (ChimeConnection *, ChimeContact *, gpointer);
void chime_connection_foreach_contact(ChimeConnection *cxn, ChimeContactCB cb,
				      gpointer cbdata);

void chime_connection_invite_contact_async(ChimeConnection *self,
					   const gchar *email,
					   GCancellable *cancellable,
					   GAsyncReadyCallback callback,
					   gpointer user_data);

gboolean chime_connection_invite_contact_finish(ChimeConnection *self,
						GAsyncResult *result,
						GError **error);

void chime_connection_remove_contact_async(ChimeConnection *self,
					   const gchar *email,
					   GCancellable *cancellable,
					   GAsyncReadyCallback callback,
					   gpointer user_data);

gboolean chime_connection_remove_contact_finish(ChimeConnection *self,
						GAsyncResult *result,
						GError **error);

G_END_DECLS

#endif /* __CHIME_CONTACT_H__ */