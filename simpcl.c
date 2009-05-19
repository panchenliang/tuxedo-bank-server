/*    Copyright (c) 1997 BEA Systems, Inc.

      All rights reserved

 

      THIS IS UNPUBLISHED PROPRIETARY

      SOURCE CODE OF BEA Systems, Inc.

      The copyright notice above does not

      evidence any actual or intended

      publication of such source code.

*/

 

/* #ident  "@(#) apps/simpapp/simpcl.c       $Revision: 1.3 $" */

 
#include <gtk/gtk.h>
#include <stdio.h>

#include <stdlib.h>

#include "atmi.h"           /* TUXEDO  Header File */

 

 
int say(char *content);
#if defined(__STDC__) || defined(__cplusplus)

main(int argc, char *argv[])

#else

main(argc, argv)

int argc;

char *argv[];

#endif
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *text;
	GtkWidget *vbox;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button=gtk_button_new_with_label("send");
	text=gtk_entry_new();
	vbox=gtk_vbox_new(TRUE,200);
	gtk_entry_set_text(text,"hello");
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),gtk_entry_get_text(GTK_ENTRY(text)));
	gtk_window_set_title(GTK_WINDOW(window),"HelloWIndow");
	gtk_window_set_default_size(GTK_WINDOW(window),500,100);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
//	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(say),NULL);
	
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_container_add(GTK_CONTAINER(vbox),text);
	gtk_container_add(GTK_CONTAINER(vbox),button);
	gtk_widget_show_all(window);
	gtk_main();
return 0;
}


 
int say(char *content){

       char *sendbuf, *rcvbuf;

       long sendlen, rcvlen;

       int ret;

//	char *content;
//	content=(gchar*)malloc(sizeof(gchar));
//	content=gtk_entry_get_text(GTK_ENTRY(text));
 

       /* Attach to System/T as a Client Process */

       if (tpinit((TPINIT *) NULL) == -1) {

              (void) fprintf(stderr, "Tpinit failed\n");

              exit(1);

       }

      

//       sendlen = strlen(argv[1]);

 	sendlen=strlen(content);

       /* Allocate STRING buffers for the request and the reply */

 

       if((sendbuf = (char *) tpalloc("STRING", NULL, sendlen+1)) == NULL) {

              (void) fprintf(stderr,"Error allocating send buffer\n");

              tpterm();

              exit(1);

       }

 

/*

       if((rcvbuf = (char *) tpalloc("STRING", NULL, sendlen+1)) == NULL) {

*/

       if((rcvbuf = (char *) tpalloc("STRING", NULL, 1)) == NULL) {

              (void) fprintf(stderr,"Error allocating receive buffer\n");

              tpfree(sendbuf);

              tpterm();

              exit(1);

       }

 

    //   (void) strcpy(sendbuf, argv[1]);

 	strcpy(sendbuf,content);

       /* Request the service TOUPPER, waiting for a reply */

       ret = tpcall("login", (char *)sendbuf, 0, (char **)&rcvbuf, &rcvlen, (long)0);

 

       if(ret == -1) {

              (void) fprintf(stderr, "Can't send request to service TOUPPER\n");

              (void) fprintf(stderr, "Tperrno = %d\n", tperrno);

              tpfree(sendbuf);

              tpfree(rcvbuf);

              tpterm();

              exit(1);

       }

 

       (void) fprintf(stdout, "Returned string is: %s\n", rcvbuf);

 

       /* Free Buffers & Detach from System/T */

       tpfree(sendbuf);

       tpfree(rcvbuf);

       tpterm();

       return(0);

}

