#include <atmi.h>
#include <userlog.h>
#include <stdio.h>

tpsvrinit(int argc,char **argv)
{
	userlog("Bank-Login-Server has started");
	return(0);
}



void login(TPSVCINFO *rqst)
{

	tpreturn(TPSUCCESS,0,rqst->data,0L,0);
}

